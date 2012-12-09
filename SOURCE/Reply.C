/******************************************************************************/
/*                                                                            */
/* Program: Sticky2.exe                                                       */
/*                                                                            */
/* Description: TCP Sticky Pad                                                */
/*                                                                            */
/* File Name : REPLY.C                                                        */
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
#include "REPLY.RCH"

/* ##START Form.34 Extra include files */
/* Code Section Extra include files - Form STICKY2\Reply */

#include "sticky2.h"
#include "data.h"
#include "pmsock.h"
/* ##END Extra include files */
/* declare pointer to main form info block */
extern PMAINFORMINFO pMainFormInfo;

MRESULT EXPENTRY REPLYDlgProc(HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  HWND hwndFrame = hwndDlg;
 /* ##START Form.37 Top of window procedure */
 /* ##END Top of window procedure */
   switch (msg) {
   /* Form event Opened WM_INITDLG */
   case WM_INITDLG :
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
      WinAssociateHelpInstance(pMainFormInfo->hwndHelpInstance, hwndFrame);

      {
      /* ##START Form.1  */
      /* Event Opened - Form STICKY2\REPLY */
      CHAR aTextValue[255]="text";
      LONG anIntegerValue=0;
      ULONG anUnsignedValue=0;


      /* Set text limit REPLY_TEXT Multi-Line Entry Field */
      WinSendDlgItemMsg(hwndDlg, REPLY_TEXT,
                        MLM_SETTEXTLIMIT,
                        MPFROMLONG(2048),  /* New text limit */
                        0);
      /* ##END  */
      }
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
      /* Button SEND_REPLY Clicked/Selected */
      case SEND_REPLY:
         {
         /* ##START 1003.0  */
         /* Event Clicked/selected - Send  1003 */
         CHAR aTextValue[255];
         CHAR SendText[4096];
         INT	rc;

         /* Get item text REPLY_TO Text */
         WinQueryDlgItemText(hwndDlg, REPLY_TO, sizeof(aTextValue), aTextValue);

         /* Get item text SEND_TEXT Multi-Line Entry Field */
         WinQueryDlgItemText(hwndDlg, REPLY_TEXT, sizeof(SendText), SendText);

         rc = SendTo(hwndFrame, gSocket, aTextValue, SendText);

         if (rc != 0)
         {
           /* Set item text ERROR_TEXT Text */
           WinSetDlgItemText(hwndDlg, REPLY_ERROR, "Error Sending to Thread");
         } /* end if */
         else
           {
           /* Set default button Cancel1004 Push Button */
           WinSendDlgItemMsg(hwndDlg, 1004,
                             BM_SETDEFAULT,
                             MPFROMLONG(TRUE), 0);
           if (CheckYes(gAfterReply))
             {
             WinPostMsg(hwndDlg, WM_CLOSE, 0, 0);
             } /* end if */

           }
         /* ##END  */
         }
         break;
      /* Button 1004 Clicked/Selected */
      case 1004:
         {
         /* ##START 1004.0  */
         /* Event Clicked/selected - Cancel  1004 */

         WinPostMsg(hwndDlg, WM_CLOSE, 0, 0);
         /* ##END  */
         }
         break;
      } /* end switch */
      break;

 /* ##START Form.38 User defined messages */
 /* Code Section User defined messages - Form STICKY2\Reply */
 {
 CHAR aTextValue[255]="text";
 LONG anIntegerValue=0;
 ULONG anUnsignedValue=0;

 case WM_USER_IP:
   {
   CHAR aTextValue[255]="text";
   CHAR locbuf[255];
   
   ReverseLookup((char *)&mp1, aTextValue);
   /* Set item text REPLY_TO Text */
   WinSetDlgItemText(hwndDlg, REPLY_TO, aTextValue);

   }	
   break;
 case WM_USER_REPLYMT:
   {
   PMSGTEXT	mt;
   
   mt = PVOIDFROMMP(mp1);
   /* Set item text REPLY_TEXT Multi-Line Entry Field */
   WinSetDlgItemText(hwndDlg, REPLY_TEXT, mt->msgtext);
   
   /* Add item to end REPLY_TEXT Multi-Line Entry Field */
   anIntegerValue=(LONG)WinSendDlgItemMsg(hwndDlg, REPLY_TEXT,
                     MLM_QUERYTEXTLENGTH,
                     0, 0);
                     
   /* The helper function MLEInsertText (in MAIN.C) sets MLE text*/
   anUnsignedValue = MLEInsertText(hwndDlg, REPLY_TEXT,
                     anIntegerValue,      /* Insert at end        */
                     "\r------- Reply ------\r");        /* Text value           */

                     
   
   FreeSubMem(gSubMemBase, mt, mt->len);




   }	
   break;
   
 case WM_USER_STATUS:
   {
   APIRET	rc;
   CHAR		locbuf[255];
   rc = SetTextError(LONGFROMMP(mp1), LONGFROMMP(mp2), locbuf);  
   
   /* Set item text REPLY_ERROR Text */
   WinSetDlgItemText(hwndDlg, REPLY_ERROR, locbuf);
   
   }
   break;
   
   case WM_MINMAXFRAME:
   {
   SWP *swp;
     
   /* hide list box when minimized so it doesn't overwrite icon */
   swp = PVOIDFROMMP( mp1 );
   WinShowWindow(WinWindowFromID( hwndDlg, SEND_REPLY),
           !(swp->fl & SWP_MINIMIZE));

   }
   break;
   
 }
 /* ##END User defined messages */
   default :
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
     return WinDefDlgProc(hwndDlg,msg,mp1,mp2);
   } /* end switch for main msg dispatch */
   return (MRESULT)FALSE;
} /* end dialog procedure */
HWND OpenREPLY(HWND hwndOwner, PVOID pInfo)
{
   HWND hwndFrame;
   if (WinQueryWindowUShort(hwndOwner, QWS_ID) == FID_CLIENT)
      hwndOwner = WinQueryWindow(hwndOwner, QW_PARENT);
   hwndFrame =(HWND) WinLoadDlg(HWND_DESKTOP,
           hwndOwner,   
           REPLYDlgProc, 
           0, ID_REPLYFORM, 
           pInfo); 
   WinShowWindow(hwndFrame, TRUE);
   return hwndFrame;
}
