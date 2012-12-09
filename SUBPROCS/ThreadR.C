/******************************************************************************/
/*                                                                            */
/* Program: ThreadR.c                                                         */
/*                                                                            */
/* Description: Receive msg's from Port 6711                                  */
/*                                                                            */
/* File Name : Main.C                                                         */
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
#include "Main.h"
#include "Main.RCH"
#include "sticky2.h"
#include "data.h"
#include "pmsock.h"
#include "mem.h"
#include "log.h"

static WSADATA sWSAData;
#define WSVERSION       0x101


VOID _System RecvThread(ULONG _IX)
{
SHORT   loop=1;
APIRET  rc;
char    locbuf[3*1024];
char    pbuf[3*1024];
char    locbuf2[256];
char    E1[4];
struct  ThreadGlobalR TG;
int     addrlen;
int     rlen;
int     autostuff=0;
PVOID   pv;
PRECVMSG rm;
DATETIME pdt;

  E1[0] = 0xE1;
  E1[1] = '\n';
  E1[2] = 0;
  E1[3] = 0;

  TG.hwndMainFrame = gPorts[_IX].hwnd;
  TG.hwnd          = gPorts[_IX].hwnd;
  TG.Socket        = gPorts[_IX].socket;
 
  TG.StickyNum = 1;
  TG.IX = _IX;

  sprintf(locbuf, "Starting Recv Thread! Socket [%ld] ix = %d", TG.Socket, _IX);
  MsgLog(locbuf);
  UserStatus((TGS)&TG, MPFROMLONG(ST_THREADSTARTR), MPFROMLONG(TG.Socket));

  DosSleep(2000);

  if ((rc = WSAStartup(WSVERSION, &sWSAData)))
    {
    sprintf(locbuf, "WSAStartup RC=%d", rc);
    MsgLog(locbuf);
    UserStatus((TGS)&TG, MPFROMLONG(ST_TCPSTART), MPFROMLONG(rc));
    DosExit(EXIT_THREAD, 0);
    }

  if ((TG.ls = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
    sprintf(locbuf, "Socket RC=%d", rc);
    MsgLog(locbuf);
    UserStatus((TGS)&TG, MPFROMLONG(ST_TCPSOCKET), MPFROMLONG(rc));
    DosExit(EXIT_THREAD, 0);
    }

  sprintf(locbuf, "Receive Socket handle = %d", TG.rs);
  MsgLog(locbuf);

  TG.lsa.sin_family      = AF_INET;
  TG.lsa.sin_addr.s_addr = 0; /*gethostid();*/
  TG.lsa.sin_port        = htons(TG.Socket);
  sprintf(locbuf, "Binding handle <%d> Socket %d [%x] to addr [%x]", TG.rs, TG.Socket, TG.lsa.sin_port, gethostid());
  MsgLog(locbuf);

  rc = bind(TG.ls, (LPSOCKADDR)&TG.lsa, sizeof(TG.lsa));
  if (rc != 0)
    {
    sprintf(locbuf, "Bind RC=%d LastError=%d", rc, WSAGetLastError());
    MsgLog(locbuf);
    UserStatus((TGS)&TG, MPFROMLONG(ST_TCP_BINDERR), MPFROMLONG(rc));
    soclose(TG.ls);
    DosExit(EXIT_THREAD, 0);
    }

  rc = listen(TG.ls, 5);
  if (rc != 0)
    {
    sprintf(locbuf, "Listen RC=%d LastError=%d", rc, WSAGetLastError());
    MsgLog(locbuf);
    UserStatus((TGS)&TG, MPFROMLONG(ST_TCP_LISTENERR), MPFROMLONG(rc));
    soclose(TG.ls);
    DosExit(EXIT_THREAD, 0);
    }

  UserStatus((TGS)&TG, MPFROMLONG(ST_THREADINITR), MPFROMLONG(TG.Socket));

  while (loop)
     {
     addrlen = sizeof(TG.rsa);
     TG.rs = accept(TG.ls, (struct sockaddr *)&TG.rsa, &addrlen);
     if (TG.rs >= 0)
       {
       sprintf(locbuf, "Address = %x", TG.rsa.sin_addr.s_addr);
       MsgLog(locbuf);

        memset(locbuf, 0, sizeof(locbuf));
        rlen = recv(TG.rs, locbuf, sizeof(locbuf), 0);
        sprintf(pbuf, "Receive Len=%d", rlen);
        MsgLog(pbuf);
        DumpLog( locbuf, rlen );

        memset(locbuf, 0, sizeof(locbuf));
        rlen = recv(TG.rs, locbuf, sizeof(locbuf), 0);
        sprintf(pbuf, "Receive Len=%d", rlen);
        MsgLog(pbuf);
        DumpLog( locbuf, rlen );


        autostuff = 0;

        if (rlen >= 0) {
//           MsgLog(locbuf);
           if (CheckYes(gAutoReply)) {

              strcpy(pbuf, "OK\r\n");

              if (strlen(gAutoText))
                 strcat(pbuf, gAutoText);
              
              if (CheckYes(gAutoName)) {
                 if (autostuff == 0) {
                    strcat(pbuf, E1);
                    autostuff = 1;
                 } /* endif */
                 sprintf(locbuf2, "[Received by : ][%s]\n", gMyName);
                 strcat(pbuf, locbuf2);
              } /* endif */

              if (CheckYes(gAutoVer)) {
                 if (autostuff == 0) {
                    strcat(pbuf, E1);
                    autostuff = 1;
                 } /* endif */
                 sprintf(locbuf2, "[Sticky Version : ][%s]\n", gVersion);
                 strcat(pbuf, locbuf2);
              } /* endif */

              if (CheckYes(gAutoTime)) {
                 if (autostuff == 0) {
                    strcat(pbuf, E1);
                    autostuff = 1;
                 } /* endif */
                 DosGetDateTime(&pdt);
                 sprintf(locbuf2, "[At Local Time : ][%02d:%02d:%02d]", pdt.hours, pdt.minutes, pdt.seconds);
                 strcat(pbuf, locbuf2);
              } /* endif */
           } else {
              strcpy(pbuf, "OK\r\n");
           } /* endif */
           send(TG.rs, pbuf, strlen(pbuf), 0);

           pv = GetSubMem(gSubMemBase, rlen + EXTRA_RM);

           if (pv != 0) {
              rm = (PRECVMSG)pv;
              rm->ptr   = (PVOID)pv;
              rm->len   = rlen + EXTRA_RM;
              rm->addr = TG.rsa.sin_addr.s_addr;
              rm->stickynum = TG.StickyNum++;
              memcpy(rm->msg, locbuf, rlen);
              rm->msg[rlen] = 0;

              rc = FALSE;
              while(rc == FALSE)
                rc = WinPostMsg(TG.hwnd,
                        WM_USER_STICKY_MSG,
                        MPFROMP(rm),
                        MPFROMLONG(rlen + EXTRA_RM));

            }
        } /* endif */

       soclose(TG.rs);
       }
     else
       {
       } /* endif */
     }

}

