/******************************************************************************/
/*                                                                            */
/* Program: Sticky2.exe                                                       */
/*                                                                            */
/* Description: TCP Sticky Pad                                                */
/*                                                                            */
/* File Name : AUTORPLY.C                                                     */
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
#include "AUTORPLY.RCH"

/* ##START Form.34 Extra include files */
/* Code Section Extra include files - Form STICKY2\Sticky */

#include "sticky2.h"
#include "data.h"
#include "time.h"
/* ##END Extra include files */
/* declare pointer to main form info block */
extern PMAINFORMINFO pMainFormInfo;

MRESULT EXPENTRY AUTORPLYDlgProc(HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
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
      /* Event Opened - Form STICKY2\AUTORPLY */
      ULONG anUnsignedValue=0;


        anUnsignedValue = atol(gClearAuto);
        if (anUnsignedValue)
          WinStartTimer(0,hwndDlg,ID_FORMTIMER, anUnsignedValue * 1000);
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

   /* Form event Timer expired WM_TIMER */
   case WM_TIMER :
      {
      /* ##START Form.13  */
      /* Event Timer expired - Form STICKY2\AUTORPLY */

      WinPostMsg(hwndDlg, WM_CLOSE, 0, 0);
      /* ##END  */
      }
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
      } /* end switch */
      break;

 /* ##START Form.38 User defined messages */
 /* Code Section User defined messages - Form STICKY2\Sticky */


 case WM_USER_STICKY_MSG:
   {
   /* Open the form D:\Projects\Sticky2\Sticky */
   CHAR aTextValue[2048+512];
   CHAR SL[2048+512] = "< >--- AutoReply";
   CHAR CRLF[] = "\r\n";
   CHAR key[128], value[128];
   LONG anIntegerValue=0;
   LONG	curloc, alen;
   CHAR	*c_ptr, *cs_ptr, *e_ptr;
   APIRET 	rc;
   PRECVMSG rm;
   time_t	lt;
   struct ipaddr {
     char	b1,b2,b3,b4;
   } *ipa;
   HOSTENT *hostent = 0;
   static ULONG	arnumber=0;

   rm = (PRECVMSG)(PVOIDFROMMP(mp1));


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
   arnumber++;
   sprintf(aTextValue, "AutoReply # %d @ %s", arnumber, ctime(&lt));
   WinSetWindowText(hwndFrame, aTextValue);
   strcat(SL, aTextValue);
   strcat(SL, CRLF);

   MsgLog(aTextValue);
   
   c_ptr = strchr(rm->msg, 0xE1);
   if (c_ptr)
     {
     *c_ptr = 0;
     c_ptr++;
     
     while (*c_ptr < ' ')
       c_ptr++;
       
     while (c_ptr && *c_ptr)
       {
       cs_ptr = strchr(c_ptr, 0x0A);
       if (cs_ptr)
         {
         *cs_ptr = 0;
         cs_ptr++;
         }
       c_ptr++;
       e_ptr = strchr(c_ptr, ']');
       if (e_ptr)
         *e_ptr = 0;
       else
         break;
       strcpy(key, c_ptr);
       c_ptr = e_ptr + 2;
       
       e_ptr = strchr(c_ptr, ']');
       if (e_ptr)
         *e_ptr = 0;
       else
         break;
       strcpy(value, c_ptr);
       
       strcat(SL, key);
       strcat(SL, " = ");
       strcat(SL, value);
       strcat(SL, CRLF);

       switch (key[0])
       {
       case 'R':
          /* Set item text NOTE_FROM Text */
          WinSetDlgItemText(hwndDlg, AUTO_HOST, value);
          break;
       case 'A':
          /* Set item text NOTE_FROM Text */
          WinSetDlgItemText(hwndDlg, AUTO_TIME , value);
          break;
       case 'S':
          /* Set item text NOTE_FROM Text */
          WinSetDlgItemText(hwndDlg, AUTO_VERSION, value);    
          break;
       } /* end switch */
       c_ptr = cs_ptr;
       } /* end while */

     } /* end if */

   WinSetDlgItemText(hwndDlg, NOTE_NOTE, rm->msg);
   strcat(SL, rm->msg);
   strcat(SL, CRLF);
   StickyLog(SL);

   
   rc = FreeSubMem(gSubMemBase, rm->ptr, rm->len);
   sprintf(aTextValue, "RC from FreeSubMem = %d", rc);
   
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
HWND OpenAUTORPLY(HWND hwndOwner, PVOID pInfo)
{
   HWND hwndFrame;
   if (WinQueryWindowUShort(hwndOwner, QWS_ID) == FID_CLIENT)
      hwndOwner = WinQueryWindow(hwndOwner, QW_PARENT);
   hwndFrame =(HWND) WinLoadDlg(HWND_DESKTOP,
           hwndOwner,   
           AUTORPLYDlgProc, 
           0, ID_AUTORPLYFORM, 
           pInfo); 
   WinShowWindow(hwndFrame, TRUE);
   return hwndFrame;
}
