/******************************************************************************/
/*                                                                            */
/* Program: Thread.h                                                          */
/*                                                                            */
/* Description: Description                                                   */
/*                                                                            */
/* File Name : Main.C                                                         */
/*                                                                            */
/* Author : ANDREW J. WYSOCKI                                                 */
/*                                                                            */
/* Copyright 1994 Copyright notice                                            */
/*                                                                            */
/* Generated using VisPro/C serial number VPC5012127                          */
/*                                                                            */
/******************************************************************************/

#define INCL_WIN
#define INCL_NLS
#define INCL_DOS
#define INCL_GPI
#include <os2.h>
#include "Main.h"
#include "Main.RCH"
#include "Send.h"
#include "Send.RCH"
#include "pmsock.h"
#include "parse.h"
#include "pmfuncs.h"


#ifndef THREAD_H
#define THREAD_H

#define YESNOSIZE       8
#define VALUE_INT       10

#define QUE_MEM         20480L

#define MAXNAMES        1500

#define WM_USER_STATUS          WM_USER+1
#define WM_USER_STICKY_MSG      WM_USER+2
#define WM_USER_IP              WM_USER+3
#define WM_USER_AUTOREPLY       WM_USER+4
#define WM_USER_RESTORE         WM_USER+5

#define CP_SEND_MSG             1000L
#define CP_CLOSE                1001L

#define ST_MSG_SENT             1L
#define ST_MSG_NOTSENT          2L
#define ST_THREADINITS          3L
#define ST_THREADTERM           4L
#define ST_TCPSTART             5L
#define ST_TCPSOCKET            6L
#define ST_TCP_NOHOST           7L
#define ST_TCP_NOSOCKET         8L
#define ST_TCP_NOCONNECT        9L
#define ST_TCP_CONNECTED        10L
#define ST_TCP_SENDERR          11L
#define ST_MSG_SENDING          12L
#define ST_TCP_BINDERR          13L
#define ST_TCP_LISTENERR        14L
#define ST_THREADSTARTS         15L
#define ST_THREADSTARTR         16L
#define ST_THREADINITR          17L

#define  S_Socket               0
#define  S_MyName               1
#define  S_DebugLog             2
#define  S_LogSticky            3
#define  S_SendStatus           4
#define  S_SendLines            5
#define  S_CloseAfterSend       6
#define  S_CloseAfterReply      7
#define  S_PopUpSticky          8
#define  S_Beep                 9
#define  S_Frequency            10
#define  S_Duration             11
#define  S_SortNameList         12
#define  S_LastNameFirst        13
#define  S_SplitPercentSend     14
#define  S_SplitPercentConfig   15
#define  S_StickyIcon           16
#define  S_Default6711          17
#define  S_AreYouSure           18
#define  S_AutoReply            19
#define  S_AutoVer              20
#define  S_AutoTime             21
#define  S_AutoName             22
#define  S_AutoText             23




struct  StatusStr {
   ULONG        len;
   UCHAR        data[251];
   };

struct RecvMsg {
   PVOID        mbase;
   PVOID        ptr;
   ULONG        len;
   ULONG        addr;
   ULONG        stickynum;
   char         msg[8];                        /* Message                              */
   };


typedef struct RecvMsg * RECVMSG;

#define EXTRA_RM        32                      /* Extra bytes for mbase, len, addr & null */
#define ASCLEN          4                       /* 4 Characters for Length              */

struct  MsgParm {
  ULONG         type;
  USHORT        set;
  USHORT        len;
  HWND          hwnd;
  ULONG         data;
  };

struct  MsgText {
   ULONG        type;
   USHORT       ftype;
#define MT_TEXT         1
   USHORT       len;
   HWND         hwnd;
   char         msgtext[1024];
};


union MsgQue {
   struct       MsgParm MP;
   struct       MsgText MT;
   };

struct pidque {
   TID          stid;
   TID          rtid;
   PID          pid;
   HWND         hwnd;
   HQUEUE       que;
   PBYTE        mbase;
   ULONG        socket;
};
#define  MAXPORTS       11

struct  ThreadGlobal {
   HWND         hwndMainFrame;
   HWND         hwnd;
   PVOID        mbase;                  /* Base pointer of Main Storage area    */

   HQUEUE       RQueue;

   HFILE        hCP;                    /* Com Port handle      */
   HEV          hQueEv;                 /* QUE Event sem        */
   HEV          hWrtEv;                 /* Write Event Sem      */

   REQUESTDATA  Request;                /* Que resuest data     */

   PVOID        DataPtr;                /* Que Data             */
   PVOID        RBuf;                   /* Low Level Com Read Buffer    */
   PVOID        Buf;                    /* Extra Com Buffer     */

   ULONG        RBufLen;
   LONG         RBufCount;
   ULONG        BufLen;

   ULONG        DataLen;                /* Length of Que data   */

   ULONG        Socket;                 /* Active Socket Port   */
   ULONG        IX;                     /* Active Socket Index  */
   SOCKET       ss;                     /* Send Socket                       */
   SOCKADDR_IN  si;                     /* Socket Name                       */


   ULONG        ElementCode;            /* Element Code         */

   ULONG        Throttle;
   ULONG        TInc;
   ULONG        TMax;
   ULONG        TCount;
   ULONG        DCWW;

   ULONG        AutoReply;

   BYTE         Priority;               /* Priority of message  */
#define MAX_PRIORITY    15

};


typedef struct ThreadGlobal * TGS;



struct  ThreadGlobalR {
   HWND         hwndMainFrame;
   HWND         hwnd;

   PVOID        mbase;                  /* Base pointer of Main Storage area    */

   ULONG        Socket;                 /* Active Socket Port Number 6711    */
   ULONG        IX;                     /* Active Socket Index               */
   SOCKET       ls;                     /* Listen  Socket                    */
   SOCKET       rs;                     /* Receive Socket                    */
   SOCKADDR_IN  lsa;                    /* My Socket Name                    */
   SOCKADDR_IN  rsa;
   ULONG        StickyNum;
};

struct InfoParms {
   USHORT       Version;                /* Version # of Parameters                      */
   USHORT       ParmsLen;               /* Total length of parameters                   */
   USHORT       CommPort;               /* Comm port # 1-10                             */
   USHORT       VoiceComp;              /* Voice Compression 2, 3, 4                    */
   USHORT       Debug;                  /* Debug on or off                              */
   SHORT        Rings;                  /* Answer on Ring -1 = Toll saver               */
};

/* File entries                                                              */
struct  StickyEntry {
  char  *name;
  char  *addr;
  short port;
  };

typedef struct StickyEntry STICKYENTRY;
#define STICKY_BUFFER           1024*60


extern  char    gYes[];
extern  char    gNo[];
extern STICKYENTRY      gSE[5000];
extern int              gSECount;


extern HWND gHwndFrame;

extern char gMyName[255];
extern char gVersion[32];
extern char *gDataPath;
extern char gINIFile[255];
extern char gAppName[255];
extern char gSocketString[12];
extern ULONG gSocket;

extern char gBeep[YESNOSIZE];
extern char gFreq[YESNOSIZE];
extern char gDur[YESNOSIZE];
extern char gPUS[YESNOSIZE];
extern char gLogSticky[YESNOSIZE];
extern char gDebugLog[YESNOSIZE];
extern char gSortNameList[YESNOSIZE];
extern char gLastNameFirst[YESNOSIZE];
extern char gMaxStatus[VALUE_INT];
extern char gSplitPercent[VALUE_INT];
extern char gSplitPercentC[VALUE_INT];
extern char gSendStatus[YESNOSIZE];
extern char gSendLines[VALUE_INT];
extern char gAfterSend[YESNOSIZE];
extern char gAfterReply[YESNOSIZE];
extern char gP6711[YESNOSIZE];
extern char gSure[YESNOSIZE];
extern char gAutoReply[YESNOSIZE];
extern char gAutoVer[YESNOSIZE];
extern char gAutoTime[YESNOSIZE];
extern char gAutoName[YESNOSIZE];
extern char gAutoText[255];
extern char gStickyIcon[YESNOSIZE];


/*  Global Defines/Externals */
extern struct InfoParms gIP, gCIP;
extern struct pidque sPorts[MAXPORTS];

VOID  _System   SendThread(ULONG _Parm);
VOID  _System   RecvThread(ULONG _Parm);

USHORT          SockInit(ULONG _SockPort, HWND _Hwnd);
USHORT          SockSendMsg(ULONG _SockPort, HWND _Hwnd, ULONG _Len, CHAR *_Text);
APIRET          SendTo(HWND _hwnd, ULONG _PORT, CHAR * _IP, CHAR *_MSG);
APIRET          SetTextError(ULONG _mp1, ULONG _mp2, CHAR *_Buf);

HQUEUE          OpenQue(ULONG _IX);
APIRET          CheckQue(struct ThreadGlobal *_TG);
VOID            MsgLog(char *_Str);
APIRET          ProcessQue(struct ThreadGlobal *_TG);
APIRET          ReadQue(struct ThreadGlobal *_TG, int _Type, int _TimeOut);
APIRET          UserStatus(struct ThreadGlobal *_TG, MPARAM _mp1, MPARAM _mp2);


APIRET          GetString(int _KeyName, char *_Default, char *_String, int _StringLen);
APIRET          GetStringN(char *_KeyName, char *_Default, char *_String, int _StringLen);
APIRET          PutString(int _KeyName, char *_String);
APIRET          PutStringN(char *_KeyName, char *_String);

APIRET          AllocInitSubMem(void);
APIRET          FreeAllSubMem(void);
PVOID           GetSubMem(ULONG _Len);
APIRET          FreeSubMem(VOID *_Ptr, ULONG _Len);

APIRET          CheckYes(char *_Check);
APIRET          CheckNo(char *_Check);
PFN  _System    pfnCompare(PSEND_IP_CONTAINER_REC _p1, PSEND_IP_CONTAINER_REC _p2, PVOID _pStorage);

#endif
