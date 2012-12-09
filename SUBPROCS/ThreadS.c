/******************************************************************************/
/*                                                                            */
/* Program: STICKY/2                                                          */
/*                                                                            */
/* Description: Description                                                   */
/*                                                                            */
/* File Name : THREADS.C                                                      */
/*                                                                            */
/* Author : ANDREW J. WYSOCKI                                                 */
/*                                                                            */
/* Copyright 1994 Copyright notice                                            */
/*                                                                            */
/******************************************************************************/

#define INCL_WIN
#define INCL_NLS
#define INCL_DOS
#define INCL_DOSPROCESS
#define INCL_DOSFILEMGR
#define INCL_DOSDEVIOCTL
#define INCL_GPI
#include <os2.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <sys\stat.h>
//#include "Main.h"
//#include "Main.RCH"
#include "sticky2.h"
#include "data.h"
#include "threads.h"
#include "comms.h"

//#include "threadr.h"
#include "pmsock.h"
#include "mem.h"
#include "log.h"

static WSADATA sWSAData;
#define WSVERSION       0x101


VOID _System SendThread(ULONG _IX)
{
SHORT   loop=1;
APIRET  rc;
char    locbuf[128];
struct  ThreadGlobal TG;



  TG.hwndMainFrame = gPorts[_IX].hwnd;
  TG.hwnd          = gPorts[_IX].hwnd;
  TG.Socket        = _IX;

  gPorts[_IX].sready = 0;
  gPorts[_IX].index  = _IX;

  TG.Throttle   = 100;
  TG.TInc       = 100;
  TG.TMax       = 500;
  TG.TCount     = 0;
  TG.AutoReply  = 1;

  TG.DCWW = DCWW_NOWAIT;

  TG.IX = _IX;


  sprintf(locbuf, "Starting Sending Thread! ix=%d", _IX);
  MsgLog(locbuf);
  UserStatus(&TG, MPFROMLONG(ST_THREADSTARTS), MPFROMLONG(_IX));

  sprintf(locbuf, gStickyQueue, _IX);

  rc = DosCreateQueue(&TG.RQueue,
                      QUE_PRIORITY,
                      locbuf);

  sprintf(locbuf, "SendTHREAD:Created Queue for READ [%ld] QUEUE RC=%d", _IX, rc);
  MsgLog(locbuf);


  DosCreateEventSem(0, &TG.hQueEv, DC_SEM_SHARED, 0);
  DosCreateEventSem(0, &TG.hWrtEv, DC_SEM_SHARED, 0);

  if ((rc = WSAStartup(WSVERSION, &sWSAData)))
    {
    sprintf(locbuf, "WSAStartup RC=%d", rc);
    MsgLog(locbuf);
    UserStatus(&TG, MPFROMLONG(ST_TCPSTART), MPFROMLONG(rc));
    DosExit(EXIT_THREAD, 0);
    }


  UserStatus(&TG, MPFROMLONG(ST_THREADINITS), MPFROMLONG(_IX));

  gPorts[_IX].sready = 1;


  while (loop)
     {
     TG.ElementCode = 0;

     gPorts[_IX].sready = 1;

     ReleaseThread(_IX);

     UserStatus(&TG, MPFROMLONG(ST_THREAD_READY), MPFROMLONG(_IX));

     ProcessQue(&TG);


  }

}

/*--------------------------------------------------------------------------------------*/
/* PROCESSQUE - This function will process the QUE messages pass in from ANYWHERE       */
/*--------------------------------------------------------------------------------------*/
APIRET
ProcessQue(struct ThreadGlobal *_TG)
{
union   MsgQue  *MQ;
APIRET  rc;
char    locbuf[4096];
char    pbuf[512];
PVOID   DataPtr;
ULONG   DataLen;
HWND    CloseHwnd;
CHAR    *port, *host, *name, *msg;
PVOID   pv;
PRECVMSG rm;
int     msglen, nchars;
CHAR    *c_ptr;
ULONG   ipa;
SERVENT *pse;
HOSTENT *phe;
SOCKADDR_IN  server;

     DosReadQueue(_TG->RQueue,
                  &_TG->Request,
                  &_TG->DataLen,
                  &_TG->DataPtr,
                  0,
                  DCWW_WAIT,
                  &_TG->Priority,
                  _TG->hQueEv);

     gPorts[_TG->IX].sready = 0;

     MQ = (union MsgQue *)_TG->DataPtr;

     sprintf(locbuf, "ProcessQUE:Req=%ld, Set=%d, hwnd=%ld, Len=%ld, Data=%ld", MQ->MP.type, MQ->MP.set, MQ->MP.hwnd, MQ->MP.len, MQ->MP.data);
     MsgLog(locbuf);

     _TG->hwnd = MQ->MP.hwnd;

    switch (_TG->Request.ulData) {
      case CP_SEND_MSG:
         MsgLog("CP_SEND_MSG from queue...");
         UserStatus(_TG, MPFROMLONG(ST_MSG_SENDING),
                    MPFROMLONG(_TG->Socket));
         MsgLog(MQ->MT.msgtext);
         c_ptr = MQ->MT.msgtext;
         port  = c_ptr;
         c_ptr = strchr(c_ptr, 255);
         *c_ptr = 0;
         c_ptr++;
         while (*c_ptr == ' ')
            c_ptr++;
         host  = c_ptr;
         c_ptr = strchr(c_ptr, 255);
         *c_ptr = 0;
         c_ptr++;
         name  = c_ptr;
         c_ptr = strchr(c_ptr, 255);
         *c_ptr = 0;
         c_ptr++;
         msg   = c_ptr;

         MsgLog(port);

         c_ptr = strchr(host, ' ');
         if (c_ptr)
            *c_ptr = 0;
         MsgLog(host);

         MsgLog(name);
         MsgLog(msg);
         if ((ipa = inet_addr(host)) == INADDR_NONE)
           {
           if (phe = gethostbyname(host))
              ipa = *((ULONG *)phe->h_addr);
           else
              {
              UserStatus(_TG, MPFROMLONG(ST_TCP_NOHOST),
                         MPFROMLONG(_TG->IX));
              break;
              }
           } /* endif */

          if ((_TG->ss = socket(AF_INET, SOCK_STREAM, 0)) >= 0) 
          {
           sprintf( locbuf, "Obtained socket 0x%X", _TG->ss);
           MsgLog( locbuf );
           memset(&server, 0, sizeof(server));

           server.sin_family = AF_INET;
           server.sin_port = bswap((SHORT)atoi(port));
           server.sin_addr.s_addr = ipa;
           sprintf( locbuf, "Port 0x%04X IP Address 0x%04X", port, ipa);
           MsgLog( locbuf );
           if (!connect(_TG->ss, (SOCKADDR *)&server, sizeof(server)))
           {
             sprintf(locbuf, "CONNECTED:%04d%s%04d%s", strlen(name), name, strlen(msg), msg);
             MsgLog(locbuf);
             msglen = strlen(locbuf);
             UserStatus(_TG, MPFROMLONG(ST_TCP_CONNECTED),
                        MPFROMLONG(ipa));
             if (send(_TG->ss, locbuf, msglen, 0) == msglen) 
             {
                memset(locbuf, 0, sizeof(locbuf));
                nchars = recv(_TG->ss, (char FAR *)&locbuf, sizeof(locbuf), 0);
                sprintf(pbuf, "nchars=%d, [%-.256s]", nchars, locbuf);
                MsgLog(pbuf);
                if (nchars >= 2 && locbuf[0] == 'O' && locbuf[1] == 'K') 
                {
                  UserStatus(_TG, MPFROMLONG(ST_MSG_SENT),
                             MPFROMLONG(msglen));

                  if (nchars > 4) {

                    pv = GetSubMem(gSubMemBase, nchars - 4 + EXTRA_RM);

                    if (pv != 0) 
                    {
                       rm = (PRECVMSG)pv;
                       rm->ptr   = (PVOID)pv;
                       rm->len   = nchars - 4 + EXTRA_RM;
                       rm->addr = ipa;
                       rm->stickynum = _TG->AutoReply++;
                       memcpy(rm->msg, &locbuf[4], nchars - 4);
                       rm->msg[nchars - 4] = 0;
 
                       rc = FALSE;
                       while(rc == FALSE)
                         rc = WinPostMsg(_TG->hwndMainFrame,
                                         WM_USER_AUTOREPLY,
                                         MPFROMP(rm),
                                         MPFROMLONG(rm->len));

                      }
                  } /* endif */


                } 
                else 
                {
                  UserStatus(_TG, MPFROMLONG(ST_MSG_NOTSENT),
                             MPFROMLONG(ipa));
                } /* endif */

             } 
             else 
             {
               UserStatus(_TG, MPFROMLONG(ST_TCP_SENDERR),
                          MPFROMLONG(ipa));
             } /* endif */

           } 
           else 
           {
             UserStatus(_TG, MPFROMLONG(ST_TCP_NOCONNECT),
                        MPFROMLONG(ipa));
           } /* endif */
           closesocket(_TG->ss);
        } 
        else 
        {
          UserStatus(_TG, MPFROMLONG(ST_TCP_NOSOCKET),
                     MPFROMLONG(_TG->IX));
        } /* endif */
        
        break;

     case CP_CLOSE:
        CloseHwnd = MQ->MP.hwnd;
        rc = DosCloseQueue(gPorts[_TG->IX].que);
        sprintf(locbuf, "DosCloseQue [que] RC=%d", rc);
        MsgLog(locbuf);
        rc = DosCloseQueue(_TG->RQueue);
        sprintf(locbuf, "DosCloseQue [RQueue] RC=%d", rc);
        MsgLog(locbuf);

        gPorts[_TG->IX].stid = 0;
        gPorts[_TG->IX].que = 0;
        MsgLog("Exiting thread!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
        UserStatus(_TG, MPFROMLONG(ST_THREADTERM),
                   MPFROMLONG(_TG->IX));
        DosExit(EXIT_THREAD, 0);
        break;

     default:
       break;
     } /* endswitch */
    FreeSubMem(gSubMemBase, _TG->DataPtr, _TG->DataLen);
   _TG->DataPtr = 0;
   _TG->DataLen = 0;
}



/*-----------------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------------*/
APIRET
CheckQue(struct ThreadGlobal *_TG)
{
ULONG   ljunk=0;
APIRET  rc;
char    locbuf[128];

  DosResetEventSem(_TG->hQueEv, &ljunk);

  _TG->ElementCode = 0;
  rc = DosPeekQueue(_TG->RQueue,
                    &_TG->Request,
                    &_TG->DataLen,
                    &_TG->DataPtr,
                    &_TG->ElementCode,
                    _TG->DCWW,
                    &_TG->Priority,
                    _TG->hQueEv);


return(rc);
}



/*--------------------------------------------------------------------------------------*/
/* USERSTATUS - Send User status back to the calling PM program                         */
/*--------------------------------------------------------------------------------------*/
APIRET UserStatus(struct ThreadGlobal *_TG, MPARAM _mp1, MPARAM _mp2)
{
  char locbuf[128];
  int rc = FALSE;
  int loop = 0;
 

  while (rc == FALSE) 
  {
    rc = WinPostMsg(_TG->hwnd,
                    WM_USER_STATUS,
                   _mp1,
                   _mp2);
  } /* endwhile */

  if (_TG->hwnd != _TG->hwndMainFrame)
     {
     rc = FALSE;
     while (rc == FALSE) {
       rc = WinPostMsg(_TG->hwndMainFrame,
                       WM_USER_STATUS,
                       _mp1,
                       _mp2);
       } /* endwhile */
     } /* endwhile */

  sprintf(locbuf, "UserStatus: %d [%d]", _mp1, _mp2);
  MsgLog(locbuf);

}

