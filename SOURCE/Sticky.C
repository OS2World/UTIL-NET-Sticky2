/******************************************************************************/
/*                                                                            */
/* Program: Sticky2.exe                                                       */
/*                                                                            */
/* Description: TCP Sticky Pad                                                */
/*                                                                            */
/* File Name : STICKY.C                                                       */
/*                                                                            */
/* Author : ANDY WYSOCKI                                                      */
/*                                                                            */
/* Copyright 1996 Copyright notice                                            */
/*                                                                            */
/* Generated using VisPro/C serial number VPC5012127                          */
/*                                                                            */
/******************************************************************************/

/* ##START Form.41 Top of source file */
/* ##END Top of source file */
#define INCL_WIN
#define INCL_NLS
#define INCL_DOS
#define INCL_GPI
#include <os2.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "ABOUT.h"
#include "AUTORPLY.h"
#include "CONFIG.h"
#include "Main.h"
#include "O_AUTO.h"
#include "O_CONFIG.h"
#include "O_DEBUG.h"
#include "O_NAMES.h"
#include "O_THREADS.h"
#include "O_USER.h"
#include "POPUP.h"
#include "REPLY.h"
#include "Send.h"
#include "STICKY.h"
#include "STICKY2.RCH"
#include "STICKY.RCH"

/* ##START Form.34 Extra include files */
/* Code Section Extra include files - Form STICKY2\Sticky */

#include "sticky2.h"
#include "data.h"
#include "pmsock.h"
#include "time.h"
/* ##END Extra include files */
/* declare pointer to main form info block */
extern PMAINFORMINFO pMainFormInfo;

MRESULT EXPENTRY STICKYDlgProc(HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  HWND hwndFrame = hwndDlg;
 /* ##START Form.37 Top of window procedure */
 /* ##END Top of window procedure */
   switch (msg) {
   /* Form event Opened WM_INITDLG */
   case WM_INITDLG :
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
      WinAssociateHelpInstance(pMainFormInfo->hwndHelpInstance, hwndFrame);

      /* ##START Form.1  */
      /* ##END  */
      break;

   /* Form event Closed WM_CLOSE */
   case WM_CLOSE :
      /* ##START Form.2  */
      /* ##END  */
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
      break;

   /* Form event Destroyed WM_DESTROY */
   case WM_DESTROY :
      /* ##START Form.3  */
      /* ##END  */
     /* Remove help instance */
     WinAssociateHelpInstance((HWND) 0, hwndFrame);
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
      break;

   case WM_COMMAND :
      switch (SHORT1FROMMP(mp1)) {
      /* Button NOTE_CLEAR Clicked/Selected */
      case NOTE_CLEAR:
         {
         /* ##START 1004.0  */
         /* Event Clicked/selected - Clear NOTE_CLEAR */
         CHAR aTextValue[255]="text";
         LONG anIntegerValue=0;
         ULONG anUnsignedValue=0;


         WinPostMsg(hwndDlg, WM_CLOSE, 0, 0);
         /* ##END  */
         }
         break;
      /* Button NOTE_REPLY Clicked/Selected */
      case NOTE_REPLY:
         {
         /* ##START 1005.0  */
         /* Event Clicked/selected - Reply NOTE_REPLY */
         CHAR aTextValue[255]="text";
         LONG anIntegerValue=0;
         ULONG anUnsignedValue=0;
         ULONG ipa;
         HOSTENT *phe;

         /* Open the form D:\Projects\Sticky2\Reply */
         {

            HWND hNewFrame;
            hNewFrame = OpenREPLY(HWND_DESKTOP, 0);
            /* Get item text NOTE_FROM Text */
            WinQueryDlgItemText(hwndDlg, NOTE_FROM, sizeof(aTextValue), aTextValue);
           
            if ((ipa = inet_addr(aTextValue)) == INADDR_NONE)
              {
              if (phe = gethostbyname(aTextValue))
                ipa = *((ULONG *)phe->h_addr);
              } /* endif */
           
            
           WinPostMsg(hNewFrame, WM_USER_IP, MPFROMLONG(ipa), 0);
         }
         /* ##END  */
         }
         break;
      /* Button NOTE_REPLYWITH Clicked/Selected */
      case NOTE_REPLYWITH:
         {
         /* ##START 1006.0  */
         /* Event Clicked/selected - Reply with NOTE_REPLYWITH */
         CHAR aTextValue[255]="text";
         LONG anIntegerValue=0;
         ULONG anUnsignedValue=0;
         PMSGTEXT mt;
         ULONG	ipa;
         HOSTENT	*phe;

         /* Open the form D:\Projects\Sticky2\Reply */
         {

            HWND hNewFrame;
            hNewFrame = OpenREPLY(HWND_DESKTOP, 0);
            /* Get item text NOTE_FROM Text */
            WinQueryDlgItemText(hwndDlg, NOTE_FROM, sizeof(aTextValue), aTextValue);
           
            if ((ipa = inet_addr(aTextValue)) == INADDR_NONE)
              {
              if (phe = gethostbyname(aTextValue))
                ipa = *((ULONG *)phe->h_addr);
              } /* endif */
              
              
           /* Get text length NOTE_NOTE Multi-Line Entry Field */
           anIntegerValue=(LONG)WinSendDlgItemMsg(hwndDlg, NOTE_NOTE,
                             MLM_QUERYTEXTLENGTH ,
                             0, 0);

          
              
           mt = (PMSGTEXT)GetSubMem(gSubMemBase, anIntegerValue + sizeof(MSGTEXT) - sizeof(mt->msgtext) + 1);
           mt->len = (SHORT)anIntegerValue + sizeof(MSGTEXT) - sizeof(mt->msgtext) + 1;
           mt->type = MT_TEXT;
           mt->ftype = 0;
           mt->hwnd = hNewFrame;
           /* Get item text NOTE_HOST Group Box */
           WinQueryDlgItemText(hwndDlg, NOTE_NOTE, anIntegerValue, mt->msgtext);
           /* Get item text NOTE_NOTE Multi-Line Entry Field */
           {
           PBYTE pText;
           /* The helper function MLEGetItemText (in MAIN.C) gets MLE text */
           anUnsignedValue = MLEGetItemText(hwndDlg, NOTE_NOTE,
                             0,       /* Starting from the beginning        */
                             -1,      /* Until the end of the text          */
                             &pText); /* Ptr for text buffer area           */
         /* The MLE text is returned in a buffer pointed to by pText      */
         /* Note: after use, pText should be deallocated by using         */

           strcpy(mt->msgtext, pText);
           free(pText);                                                  

         }


         //  sprintf(aTextValue, "Rply/W Buf=%d, QTL=%d, len=%d, str=%s", mt->len, anIntegerValue, strlen(mt->msgtext), mt->msgtext);
         //  MsgLog(aTextValue);
           
            
           WinPostMsg(hNewFrame, WM_USER_IP, MPFROMLONG(ipa), 0);
           WinPostMsg(hNewFrame, WM_USER_REPLYMT, MPFROMP(mt), 0);
           
           
         }
         /* ##END  */
         }
         break;
      } /* end switch */
      break;

 /* ##START Form.38 User defined messages */
 /* Code Section User defined messages - Form STICKY2\Sticky */


 case WM_USER_STICKY_MSG:
   {
   /* Open the form D:\Projects\Sticky2\Sticky */
   CHAR aTextValue[512];
   CHAR SL[4096];
   CHAR CRLF[3] = "\r\n";
   LONG anIntegerValue=0;
   LONG	curloc, alen;
   APIRET 	rc;
   PRECVMSG 	rm;
   time_t	lt;
   
   struct hostent *hostent = 0;
   struct ipaddr {
     char	b1,b2,b3,b4;
   } *ipa;
  
   rm = (PRECVMSG)(PVOIDFROMMP(mp1));
   
   curloc = 0;
   memset(aTextValue, 0, sizeof(aTextValue));
   
   memcpy(aTextValue, rm->msg, ASCLEN);
   alen = atoi(aTextValue);
   curloc += ASCLEN;
   
   memset(aTextValue, 0, sizeof(aTextValue));
   memcpy(aTextValue, &rm->msg[curloc], alen);
   /* Set item text NOTE_FROM Text */
   WinSetDlgItemText(hwndDlg, NOTE_HOST, aTextValue);
   
   strcpy(SL, "<<<--- Received Sticky !\r\n");
   strcat(SL, aTextValue);
   strcat(SL, CRLF);
   curloc += alen + ASCLEN;
   
   ipa = (struct ipaddr *)&rm->addr;
   
   if (CheckYes(gReverseLookup))
     hostent = gethostbyaddr((char *)ipa, 4, PF_INET);
     
   if (hostent)
   {
     sprintf(aTextValue, "%s", hostent->h_name);
   } else {
     sprintf(aTextValue, "%d.%d.%d.%d", ipa->b1, ipa->b2, ipa->b3, ipa->b4);  
   } /* end if */
   
   

   /* Set item text NOTE_HOST Group Box */
   WinSetDlgItemText(hwndDlg, NOTE_FROM, aTextValue);
   
   strcat(SL, aTextValue);
   strcat(SL, CRLF);
   
     
   time(&lt);
   sprintf(aTextValue, "Note # %d @ %s", rm->stickynum, ctime(&lt));
   WinSetWindowText(hwndFrame, aTextValue);
   strcat(SL, aTextValue);
   strcat(SL, CRLF);

   /* Set item text NOTE_NOTE Multi-Line Entry Field */
   WinSetDlgItemText(hwndDlg, NOTE_NOTE, &rm->msg[curloc]);
   strcat(SL, &rm->msg[curloc]);
   strcat(SL, CRLF);
   StickyLog(SL);
   
   rc = FreeSubMem(gSubMemBase, rm->ptr, rm->len);
   sprintf(aTextValue, "RC from DosSubFreeMem = %d", rc);
   MsgLog(aTextValue);
   
   }
 break;

 case WM_MINMAXFRAME:
   {
   SWP *swp;
     
   /* hide list box when minimized so it doesn't overwrite icon */
   swp = PVOIDFROMMP( mp1 );
   WinShowWindow(WinWindowFromID( hwndDlg, NOTE_CLEAR),
           !(swp->fl & SWP_MINIMIZE));

   }
   break;
 /* ##END User defined messages */
   default :
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
     return WinDefDlgProc(hwndDlg,msg,mp1,mp2);
   } /* end switch for main msg dispatch */
   return (MRESULT)FALSE;
} /* end dialog procedure */
HWND OpenSTICKY(HWND hwndOwner, PVOID pInfo)
{
   HWND hwndFrame;
   if (WinQueryWindowUShort(hwndOwner, QWS_ID) == FID_CLIENT)
      hwndOwner = WinQueryWindow(hwndOwner, QW_PARENT);
   hwndFrame =(HWND) WinLoadDlg(HWND_DESKTOP,
           hwndOwner,   
           STICKYDlgProc, 
           0, ID_STICKYFORM, 
           pInfo); 
   WinShowWindow(hwndFrame, TRUE);
   return hwndFrame;
}
