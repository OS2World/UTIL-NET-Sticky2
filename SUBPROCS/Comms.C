/******************************************************************************/
/*                                                                            */
/* Program: STICKY2                                                           */
/*                                                                            */
/* Description: Description                                                   */
/*                                                                            */
/* File Name : COMMS.C                                                        */
/*                                                                            */
/* Author : ANDREW J. WYSOCKI                                                 */
/*                                                                            */
/* Copyright 1994 Copyright notice                                            */
/*                                                                            */
/******************************************************************************/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <sys\stat.h>
#include <share.h>
#include <io.h>
//#include "Main.h"
//#include "Main.RCH"
#include "sticky2.h"
#include "threads.h"
#include "threadr.h"
#include "mem.h"
#include "data.h"
#include "comms.h"

/* -------------------------------------------- */
/* EXTERNALS                                    */
/* -------------------------------------------- */


/* -------------------------------------------- */
/* DATA defines                                 */
/* -------------------------------------------- */

/*---------------------------------------------------------------------------*/
/* COMMSINIT - Set up the Thread and Save TID                                */
/*---------------------------------------------------------------------------*/
USHORT
SockInit(ULONG _SocketPort, HWND _Hwnd)
{
char locbuf[128];
APIRET  rc=0;
int     ix;

  sprintf(locbuf, "SOCKINIT: Port[%ld]", _SocketPort);
  MsgLog(locbuf);


  ix = _SocketPort;

                                         /* Already have a Thread for CommPort*/
  if (gPorts[ix].stid || gPorts[ix].que)
     {
     sprintf(locbuf, "Already have a Thread running! stid=%ld, que=%ld, pid=%ld",
             gPorts[ix].stid, gPorts[ix].que, gPorts[ix].pid);
     MsgLog(locbuf);
     return(-1);
     }


  gPorts[ix].hwnd = _Hwnd;               /* Save the screen handle            */

  if (!gSubMemBase)
     rc = AllocInitSubMem((PVOID *)&gSubMemBase, QUE_MEM);


  if (!rc)
    rc = DosCreateThread((PTID) &gPorts[ix].stid,
                         (PFNTHREAD)SendThread,
                         (ULONG)ix,
                         (ULONG)0,
                         (ULONG)15360L);

  sprintf(locbuf, "SOCKINIT: stid[%ld] RC=%ld", (ULONG) gPorts[ix].stid, rc);
  MsgLog(locbuf);






return((USHORT)rc);
}


/*---------------------------------------------------------------------------*/
/* RecvINIT - Set up the Thread and Save TID                                 */
/*---------------------------------------------------------------------------*/
USHORT
RecvInit(ULONG _SocketPort, HWND _Hwnd)
{
char locbuf[128];
APIRET  rc=0;
int     ix;

  sprintf(locbuf, "RECVINIT: Port[%ld]", _SocketPort);
  MsgLog(locbuf);


  DosCreateMutexSem(0, &gThreadTbl, 0, FALSE);
  gTblBot       = &gPorts[0];
  gPorts[MAXPORTS].socket = _SocketPort;
  gPorts[MAXPORTS].hwnd   = _Hwnd;               /* Save the screen handle            */
  rc = DosCreateThread((PTID) &gPorts[MAXPORTS].rtid,
                          (PFNTHREAD)RecvThread,
                          (ULONG)MAXPORTS,
                          (ULONG)0,
                          (ULONG)15360L);
  sprintf(locbuf, "RECVINIT: rtid[%ld] RC=%ld", (ULONG) gPorts[MAXPORTS].stid, rc);
  MsgLog(locbuf);


return((USHORT)rc);
}



/*---------------------------------------------------------------------------*/
/* SOCKSENDMSG - Send a message to a user                                    */
/*---------------------------------------------------------------------------*/
USHORT
SockSendMsg(ULONG _SocketPort, HWND _Hwnd, ULONG _Len, CHAR * _Data)
{
union MsgQue *MQ;
USHORT rc;
ULONG   pri=7;
char    locbuf[128];
char    *c_ptr;
int     ix = -1;
int     index=0;
int     secondtry = 0;

  while (ix < 0) 
  {

    ix = GetThread();

 
    if (ix == -2) 
       {
       DosSleep(100);
       secondtry++;
       }
                           /* No port to send on      */
    if (secondtry > 20) 
       return(-1);

  } /* endwhile */


  if (!gPorts[ix].que)
     OpenQue(ix);

  if (!gPorts[ix].que)
     return(-1);

  _Len += 12;                   /* Add the Header to the length              */
  MQ = GetSubMem(gSubMemBase, _Len);
  sprintf(locbuf,
          "COMMS:Sending Msg:Port=%d, Len=%ld, Data=%ld, MQ=%d, Thread=%d",
          _SocketPort, _Len, _Data, MQ, ix);
  MsgLog(locbuf);
  MsgLog(_Data);


  if (MQ != 0) {
    c_ptr = (char *)_Data;
    strcpy(MQ->MT.msgtext, c_ptr);
    MQ->MT.type = MT_TEXT;
    MQ->MT.len  = _Len;
    MQ->MT.ftype = 0;
    MQ->MT.hwnd = _Hwnd;          /* Set up handle for all requests               */
    gPorts[ix].sready = 0;
    rc = DosWriteQueue(gPorts[ix].que,
                       CP_SEND_MSG,
                       _Len,
                       (void *)MQ,
                        pri);
    sprintf(locbuf, "DosWriteQueue RC=%d", rc);
    MsgLog(locbuf);
    DosSleep(100);
  } /* endif */
return(rc);
}


/****************************************************************************************/
/* OpenQue - Opens up a QUE                                                             */
/****************************************************************************************/
HQUEUE
OpenQue(ULONG ix)
{
char locbuf[256];
APIRET  rc;

  sprintf(locbuf, gStickyQueue, ix);
  MsgLog(locbuf);
  rc = DosOpenQueue(&gPorts[ix].pid,
               &gPorts[ix].que,
               locbuf);

  sprintf(locbuf, "Open Queue RC=%ld, Queue Handle=%ld", rc, gPorts[ix].que);
  MsgLog(locbuf);

return(rc);
}




/****************************************************************************************/
/* SENDTO                                                                               */
/****************************************************************************************/

APIRET
SendTo(HWND _hwnd, ULONG _Port, CHAR *_IP, CHAR *_Msg)
{
/* Event Clicked/selected - Send  1000 */
CHAR Locbuf[255];
CHAR SendText[4096];
CHAR delim[2];
INT  rc;
CHAR    *c_ptr;
CHAR    *host;

delim[0] = 255;
delim[1] = 0;

  host = strdup(_IP);
  c_ptr = strtok(host, ";");
  while (c_ptr) {
    sprintf(SendText, "%d", _Port);
    strcat(SendText, delim);
    strcat(SendText, c_ptr);
    strcat(SendText, delim);
    strcat(SendText, gMyName);
    strcat(SendText, delim);
    strcat(SendText, _Msg);
   
    rc = SockSendMsg(gSocket, _hwnd, strlen(SendText), SendText);

    c_ptr = strtok(NULL, ";");
  } /* endwhile */

free(host);

return(rc);
}

/****************************************************************************************/
/*                                                                                      */
/****************************************************************************************/
APIRET
SetTextError(ULONG _mp1, ULONG _mp2, CHAR *_Buf)
{
  memset(_Buf, 0, sizeof(_Buf));
  switch (_mp1)
  {
  case ST_MSG_SENT:
     sprintf(_Buf, "Message Sent! # characters = %d", _mp2);
     break;
  case ST_TCP_LISTENERR:
     strcpy(_Buf, "Error setting Listen count!");
     break;
  case ST_TCPSOCKET:
     strcpy(_Buf, "Error getting a TCP socket!");
     break;
  case ST_TCPSTART:
     strcpy(_Buf, "Error starting TCP subsystem");
     break;
  case ST_THREADINITS:
     sprintf(_Buf, "SEND Thread READY! [%d]", _mp2);
     break;
  case ST_THREADINITR:
     sprintf(_Buf, "RECEIVE Thread READY! [%d]", _mp2);
     break;
  case ST_THREADSTARTS:
     sprintf(_Buf, "Starting SEND Thread! [%d]", _mp2);
     break;
  case ST_THREADSTARTR:
     sprintf(_Buf, "Starting RECEIVE Thread! [%d]", _mp2);
     break;
  case ST_MSG_NOTSENT:
     strcpy(_Buf, "Message was not SENT");
     break;
  case ST_TCP_NOHOST:
     sprintf(_Buf, "HOST was not found [%s]", CvtIP(_mp2));
     break;
  case ST_MSG_SENDING:
     sprintf(_Buf, "Message queued to thread %d ...", _mp2);
     break;
  case ST_TCP_NOSOCKET:
     strcpy(_Buf, "No Sockets available");
     break;
  case ST_TCP_NOCONNECT:
     sprintf(_Buf, "Can not connect to HOST [%s]", CvtIP(_mp2));
     break;
  case ST_TCP_CONNECTED:
     sprintf(_Buf, "Connected, sending message to [%s]", CvtIP(_mp2));
     break;
  case ST_TCP_SENDERR:
     strcpy(_Buf, "Error sending message");
     break;
  case ST_TCP_BINDERR:
     strcpy(_Buf, "Error Binding to Socket! - Can't continue...");
     break;
  case ST_THREAD_READY:
     _Buf[0] = 0;
     break;
  default :
     ;
     sprintf(_Buf, "USER STATUS MP1=%ld, MP2=%ld", _mp1, _mp2);
     MsgLog(_Buf);
  }
return(_mp1);
}


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
PFN
pfnCompare(PSEND_IP_CONTAINER_REC _p1, PSEND_IP_CONTAINER_REC _p2, PVOID _pStorage)
{
return((PFN)strcmp(_p1->Record.pszIcon, _p2->Record.pszIcon));
}



/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
APIRET
ReverseLookup(char * _IP, char * _Host)
{
HOSTENT *hostent=0;

  if (CheckYes(gReverseLookup))
    hostent = gethostbyaddr(_IP, 4, PF_INET);

  if (hostent)
  {
    sprintf(_Host, "%s", hostent->h_name);
  } else {
    sprintf(_Host, "%d.%d.%d.%d", _IP[0], _IP[1], _IP[2], _IP[3]);
  } /* end if */

return(0);
}


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
CHAR *
CvtIP(ULONG _addr)
{

char    *ipa;
static  char    buffer[16];

  ipa = (char *)&_addr;


sprintf(buffer, "%d.%d.%d.%d", ipa[0], ipa[1], ipa[2], ipa[3]);
return(buffer);
}




/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
ULONG
GetThread()
{
int   rc;

   rc = DosRequestMutexSem(gThreadTbl, 100);

   if (rc) 
      return(-1);

   if (gTblTop == NULL)
      {
      DosReleaseMutexSem(gThreadTbl);
      return(-2);
      }

   rc = gTblTop->index;

   gTblTop = gTblTop->next;
   DosReleaseMutexSem(gThreadTbl);

   return(rc);
}


void
ReleaseThread(ULONG  _ThreadIndex)
{

   DosRequestMutexSem(gThreadTbl, SEM_INDEFINITE_WAIT);

   gTblBot->next = &gPorts[_ThreadIndex];
   gTblBot       = &gPorts[_ThreadIndex];
   gTblBot->next = NULL;

   if (gTblTop == NULL)
      gTblTop = gTblBot;

   DosReleaseMutexSem(gThreadTbl);



}






