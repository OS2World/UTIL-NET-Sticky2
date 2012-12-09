/******************************************************************************/
/*                                                                            */
/* Program: Sticky2.exe                                                       */
/*                                                                            */
/* Description: TCP Sticky Pad                                                */
/*                                                                            */
/* File Name : O_AUTO.C                                                       */
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
#include "O_AUTO.RCH"

/* ##START Form.34 Extra include files */
/* Code Section Extra include files - Form STICKY2\O_CONFIG */

#include "sticky2.h"
#include "data.h"

int c_e, c_v, c_t, c_n;
/* ##END Extra include files */
/* declare pointer to main form info block */
extern PMAINFORMINFO pMainFormInfo;

MRESULT EXPENTRY O_AUTODlgProc(HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  PO_AUTOFORMINFO pO_AUTOFormInfo=(PO_AUTOFORMINFO) WinQueryWindowULong(hwndDlg, QWL_USER);
  HWND hwndFrame = hwndDlg;
 /* ##START Form.37 Top of window procedure */
 /* ##END Top of window procedure */
   switch (msg) {
   /* Form event Opened WM_INITDLG */
   case WM_INITDLG :
     if (mp2==0)
        mp2 = (MPARAM) malloc(sizeof(O_AUTOFORMINFO));
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
     pO_AUTOFormInfo=(PO_AUTOFORMINFO) WinQueryWindowULong(hwndDlg, QWL_USER);
      WinAssociateHelpInstance(pMainFormInfo->hwndHelpInstance, hwndFrame);

      {
      /* ##START Form.1  */
      /* Event Opened - Form STICKY2\O_CONFIG */
      CHAR aTextValue[255]="text";
      LONG anIntegerValue=0;
      ULONG anUnsignedValue=0;

      c_e = c_v = c_t = c_n = 0;

      WinCheckButton(hwndDlg, ENABLE_AUTO, CheckYes(gAutoReply));
      WinCheckButton(hwndDlg, VERSION_AUTO, CheckYes(gAutoVer));
      WinCheckButton(hwndDlg, TIME_AUTO, CheckYes(gAutoTime));
      WinCheckButton(hwndDlg, NAME_AUTO, CheckYes(gAutoName));
      /* Set text limit TEXT_AUTO Multi-Line Entry Field */
      WinSendDlgItemMsg(hwndDlg, TEXT_AUTO,
                        MLM_SETTEXTLIMIT,
                        MPFROMLONG(255),  /* New text limit */
                        0);


      /* Set item text TEXT_AUTO Multi-Line Entry Field */
      WinSetDlgItemText(hwndDlg, TEXT_AUTO, gAutoText);



      if (CheckNo(gAutoReply))
      {

      WinEnableControl(hwndDlg, 1004, FALSE);
      WinEnableControl(hwndDlg, VERSION_AUTO, FALSE);
      WinEnableControl(hwndDlg, TIME_AUTO, FALSE);
      WinEnableControl(hwndDlg, NAME_AUTO, FALSE);
      WinEnableControl(hwndDlg, TEXT_AUTO, FALSE);

      } /* end if */
      /* ##END  */
      }
      break;

   /* Form event Closed WM_CLOSE */
   case WM_CLOSE :
      {
      /* ##START Form.2  */
      /* Event Closed - Form STICKY2\O_CONFIG */
      CHAR aTextValue[512];
      LONG anIntegerValue=0;
      ULONG anUnsignedValue=0;
      CHAR *c_ptr, *e_ptr;


      MsgLog("Closing O_AUTO");


      if (c_e)
      {
      anUnsignedValue=(ULONG)WinQueryButtonCheckstate(hwndDlg, ENABLE_AUTO);
        strcpy(gAutoReply, anUnsignedValue ? gYes : gNo);  
        PutString(S_AutoReply, gAutoReply); 

      } /* end if */
      if (c_v)
      {
        anUnsignedValue=(ULONG)WinQueryButtonCheckstate(hwndDlg, VERSION_AUTO);
        strcpy(gAutoVer, anUnsignedValue ? gYes : gNo);  
        PutString(S_AutoVer, gAutoVer); 

      } /* end if */
      if (c_t)
      {
        anUnsignedValue=(ULONG)WinQueryButtonCheckstate(hwndDlg, TIME_AUTO);
        strcpy(gAutoTime, anUnsignedValue ? gYes : gNo);  
        PutString(S_AutoTime, gAutoTime); 

      } /* end if */
      if (c_n)
      {
        anUnsignedValue=(ULONG)WinQueryButtonCheckstate(hwndDlg, NAME_AUTO);
        strcpy(gAutoName, anUnsignedValue ? gYes : gNo);  
        PutString(S_AutoName, gAutoName); 

      } /* end if */


        /* Has text value changed? TEXT_AUTO Multi-Line Entry Field */
        if((ULONG)WinSendDlgItemMsg(hwndDlg, TEXT_AUTO,
                          MLM_QUERYCHANGED ,
                          0, 0))
          {              
          WinQueryDlgItemText(hwndDlg, TEXT_AUTO, sizeof(aTextValue), aTextValue);
          strcpy(gAutoText, aTextValue);
          
          e_ptr = strchr(aTextValue, '\r');
          while (e_ptr)
            {
            *e_ptr = '~';
            e_ptr = strchr(e_ptr, '\r');
            } /* end while */
          e_ptr = strchr(aTextValue, '\n');
          while (e_ptr)
            {
            *e_ptr = '^';
            e_ptr = strchr(e_ptr, '\n');
            } /* end while */
            
          PutString(S_AutoText, aTextValue);
          }
      /* ##END  */
      }
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
      } /* end switch */
      break;

   case WM_CONTROL :
      switch (SHORT1FROMMP(mp1)) {
      /* Check Box ENABLE_AUTO Event Handlers */
      case ENABLE_AUTO:
         switch (SHORT2FROMMP(mp1)) {
         /* Clicked/Selected */
         case BN_CLICKED:
            {
            /* ##START 1000.0  */
            /* Event Clicked/Selected - Enable Auto Reply ENABLE_AUTO */
            CHAR aTextValue[255]="text";
            LONG anIntegerValue=0;
            ULONG anUnsignedValue=0;


            c_e = 1;
            /* Is button selected? BEEP_CONFIG Check Box */
            anUnsignedValue=(ULONG)WinQueryButtonCheckstate(hwndDlg,ENABLE_AUTO);

            WinEnableControl(hwndDlg, 1004, anUnsignedValue);
            WinEnableControl(hwndDlg, VERSION_AUTO, anUnsignedValue);
            WinEnableControl(hwndDlg, TIME_AUTO, anUnsignedValue);
            WinEnableControl(hwndDlg, NAME_AUTO, anUnsignedValue);
            WinEnableControl(hwndDlg, TEXT_AUTO, anUnsignedValue);
            /* ##END  */
            }
            break;
         } /* end switch */
         break;

      /* Check Box VERSION_AUTO Event Handlers */
      case VERSION_AUTO:
         switch (SHORT2FROMMP(mp1)) {
         /* Clicked/Selected */
         case BN_CLICKED:
            {
            /* ##START 1001.0  */
            /* Event Clicked/Selected - Include Version number VERSION_AUTO */
            c_v = 1;
            /* ##END  */
            }
            break;
         } /* end switch */
         break;

      /* Check Box TIME_AUTO Event Handlers */
      case TIME_AUTO:
         switch (SHORT2FROMMP(mp1)) {
         /* Clicked/Selected */
         case BN_CLICKED:
            {
            /* ##START 1002.0  */
            /* Event Clicked/Selected - Include Local Time Received TIME_AUTO */

            c_t = 1;
            /* ##END  */
            }
            break;
         } /* end switch */
         break;

      /* Check Box NAME_AUTO Event Handlers */
      case NAME_AUTO:
         switch (SHORT2FROMMP(mp1)) {
         /* Clicked/Selected */
         case BN_CLICKED:
            {
            /* ##START 1003.0  */
            /* Event Clicked/Selected - Include Your Name NAME_AUTO */
            c_n = 1;
            /* ##END  */
            }
            break;
         } /* end switch */
         break;

      } /* end switch */
      break;

 /* ##START Form.38 User defined messages */
 /* ##END User defined messages */
   default :
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
     return WinDefDlgProc(hwndDlg,msg,mp1,mp2);
   } /* end switch for main msg dispatch */
   return (MRESULT)FALSE;
} /* end dialog procedure */
HWND OpenO_AUTO(HWND hwndOwner, PVOID pInfo)
{
   HWND hwndFrame;
   if (WinQueryWindowUShort(hwndOwner, QWS_ID) == FID_CLIENT)
      hwndOwner = WinQueryWindow(hwndOwner, QW_PARENT);
   hwndFrame =(HWND) WinLoadDlg(hwndOwner,
           hwndOwner,   
           O_AUTODlgProc, 
           0, ID_O_AUTOFORM, 
           pInfo); 
   return hwndFrame;
}
