/******************************************************************************/
/*                                                                            */
/* Program: Sticky2.exe                                                       */
/*                                                                            */
/* Description: TCP Sticky Pad                                                */
/*                                                                            */
/* File Name : O_DEBUG.C                                                      */
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
#include "O_DEBUG.RCH"

/* ##START Form.34 Extra include files */
/* Code Section Extra include files - Form STICKY2\O_DEBUG */

#include "sticky2.h"
#include "data.h"

int	c_dl, c_ls, c_ss;
/* ##END Extra include files */
/* declare pointer to main form info block */
extern PMAINFORMINFO pMainFormInfo;

MRESULT EXPENTRY O_DEBUGDlgProc(HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  PO_DEBUGFORMINFO pO_DEBUGFormInfo=(PO_DEBUGFORMINFO) WinQueryWindowULong(hwndDlg, QWL_USER);
  HWND hwndFrame = hwndDlg;
 /* ##START Form.37 Top of window procedure */
 /* ##END Top of window procedure */
   switch (msg) {
   /* Form event Opened WM_INITDLG */
   case WM_INITDLG :
     if (mp2==0)
        mp2 = (MPARAM) malloc(sizeof(O_DEBUGFORMINFO));
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
     pO_DEBUGFormInfo=(PO_DEBUGFORMINFO) WinQueryWindowULong(hwndDlg, QWL_USER);
      WinAssociateHelpInstance(pMainFormInfo->hwndHelpInstance, hwndFrame);

      {
      /* ##START Form.1  */
      /* Event Opened - Form STICKY2\O_DEBUG */

      c_dl = c_ls = c_ss = 0;

      WinCheckButton(hwndDlg, LOG_DEBUG, CheckYes(gDebugLog));
      WinCheckButton(hwndDlg, DEBUG_DEBUG, CheckYes(gLogSticky));
      WinCheckButton(hwndDlg, STATUS_DEBUG, CheckYes(gSendStatus));

      /* Set range (numeric style) STATUS_SPIN Spin Button */
      WinSendDlgItemMsg(hwndDlg, STATUS_SPIN,
                        SPBM_SETLIMITS,
                        MPFROMLONG(1000),                 /* Upper limit */
                        MPFROMLONG(1));                   /* Lower limit */ 

      /* Set item value (numeric style) STATUS_SPIN Spin Button */
      WinSendDlgItemMsg(hwndDlg, STATUS_SPIN,
                        SPBM_SETCURRENTVALUE,
                        MPFROMLONG(atol(gSendLines)), /* Value within range */
                        0);

      if (CheckNo(gSendStatus))
      {
      /* Disable window Lines1004 Text */
      WinEnableControl(hwndDlg, 1004, FALSE);
      /* Disable window STATUS_SPIN Spin Button */
      WinEnableControl(hwndDlg, STATUS_SPIN, FALSE);
      } /* end if */
      /* ##END  */
      }
      break;

   /* Form event Closed WM_CLOSE */
   case WM_CLOSE :
      {
      /* ##START Form.2  */
      /* Event Closed - Form STICKY2\O_DEBUG */
      CHAR aTextValue[255]="text";
      LONG anIntegerValue=0;
      ULONG anUnsignedValue=0;

      MsgLog("Closing O_DEBUG");

      if (c_dl)
      {
      anUnsignedValue=(ULONG)WinQueryButtonCheckstate(hwndDlg,DEBUG_DEBUG);
        
        PutString(S_DebugLog, anUnsignedValue ? gYes : gNo); 
        strcpy(gDebugLog, anUnsignedValue ? gYes : gNo);  
      } /* end if */

      if (c_ls)
      {
      anUnsignedValue=(ULONG)WinQueryButtonCheckstate(hwndDlg,LOG_DEBUG);
        
        PutString(S_LogSticky, anUnsignedValue ? gYes : gNo); 
        strcpy(gLogSticky, anUnsignedValue ? gYes : gNo);  
      } /* end if */

      if (c_ss)
      {
      anUnsignedValue=(ULONG)WinQueryButtonCheckstate(hwndDlg,STATUS_DEBUG);
        
        PutString(S_SendStatus, anUnsignedValue ? gYes : gNo); 
        strcpy(gSendStatus, anUnsignedValue ? gYes : gNo);  
      } /* end if */
      /* Get item value (numeric style) FREQUENCY_CONFIG Spin Button */
      WinSendDlgItemMsg(hwndDlg, STATUS_SPIN,
                        SPBM_QUERYVALUE,
                        MPFROMP(&anUnsignedValue),   /* Buffer for value */
                        MPFROM2SHORT(0,SPBQ_ALWAYSUPDATE));
      if (atol(gSendLines) != anUnsignedValue)
      {
        sprintf(gSendLines, "%d", anUnsignedValue);
        PutString(S_SendLines, gSendLines);
      } /* end if */
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
      /* Check Box LOG_DEBUG Event Handlers */
      case LOG_DEBUG:
         switch (SHORT2FROMMP(mp1)) {
         /* Clicked/Selected */
         case BN_CLICKED:
            {
            /* ##START 1000.0  */
            /* Event Clicked/Selected - Log Sent & Received Sticky's to  LOG_DEBUG */

            c_ls = 1;
            /* ##END  */
            }
            break;
         } /* end switch */
         break;

      /* Check Box DEBUG_DEBUG Event Handlers */
      case DEBUG_DEBUG:
         switch (SHORT2FROMMP(mp1)) {
         /* Clicked/Selected */
         case BN_CLICKED:
            {
            /* ##START 1001.0  */
            /* Event Clicked/Selected - Debug Log DEBUG_DEBUG */
            c_dl = 1;
            /* ##END  */
            }
            break;
         } /* end switch */
         break;

      /* Check Box STATUS_DEBUG Event Handlers */
      case STATUS_DEBUG:
         switch (SHORT2FROMMP(mp1)) {
         /* Clicked/Selected */
         case BN_CLICKED:
            {
            /* ##START 1002.0  */
            /* Event Clicked/Selected - Send Status STATUS_DEBUG */
            ULONG anUnsignedValue;
            c_ss = 1;
            /* Is button selected? STATUS_DEBUG Check Box */
            anUnsignedValue=(ULONG)WinQueryButtonCheckstate(hwndDlg,STATUS_DEBUG);

            /* Enable window Lines1004 Text */
            WinEnableControl(hwndDlg, 1004, anUnsignedValue);

            /* Enable window STATUS_SPIN Spin Button */
            WinEnableControl(hwndDlg, STATUS_SPIN, anUnsignedValue);
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
HWND OpenO_DEBUG(HWND hwndOwner, PVOID pInfo)
{
   HWND hwndFrame;
   if (WinQueryWindowUShort(hwndOwner, QWS_ID) == FID_CLIENT)
      hwndOwner = WinQueryWindow(hwndOwner, QW_PARENT);
   hwndFrame =(HWND) WinLoadDlg(hwndOwner,
           hwndOwner,   
           O_DEBUGDlgProc, 
           0, ID_O_DEBUGFORM, 
           pInfo); 
   return hwndFrame;
}
