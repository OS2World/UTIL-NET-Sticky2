/******************************************************************************/
/*                                                                            */
/* Program: Sticky2.exe                                                       */
/*                                                                            */
/* Description: TCP Sticky Pad                                                */
/*                                                                            */
/* File Name : O_CONFIG.C                                                     */
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
#include "O_CONFIG.RCH"

/* ##START Form.34 Extra include files */
/* Code Section Extra include files - Form STICKY2\O_CONFIG */

#include "sticky2.h"
#include "data.h"

INT c_cas=0, c_car=0, c_pop=0, c_aus=0, c_beep=0, c_mini=0, c_clr=0;
/* ##END Extra include files */
/* declare pointer to main form info block */
extern PMAINFORMINFO pMainFormInfo;

MRESULT EXPENTRY O_CONFIGDlgProc(HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  PO_CONFIGFORMINFO pO_CONFIGFormInfo=(PO_CONFIGFORMINFO) WinQueryWindowULong(hwndDlg, QWL_USER);
  HWND hwndFrame = hwndDlg;
 /* ##START Form.37 Top of window procedure */
 /* ##END Top of window procedure */
   switch (msg) {
   /* Form event Opened WM_INITDLG */
   case WM_INITDLG :
     if (mp2==0)
        mp2 = (MPARAM) malloc(sizeof(O_CONFIGFORMINFO));
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
     pO_CONFIGFormInfo=(PO_CONFIGFORMINFO) WinQueryWindowULong(hwndDlg, QWL_USER);
      WinAssociateHelpInstance(pMainFormInfo->hwndHelpInstance, hwndFrame);

      {
      /* ##START Form.1  */
      /* Event Opened - Form STICKY2\O_CONFIG */
      CHAR aTextValue[255]="text";
      LONG anIntegerValue=0;
      ULONG anUnsignedValue=0;

      c_cas = c_car = c_pop = c_aus = c_beep = c_mini = c_clr = 0;

      WinCheckButton(hwndDlg, SEND_CONFIG, CheckYes(gAfterSend));
      WinCheckButton(hwndDlg, REPLY_CONFIG, CheckYes(gAfterReply));
      WinCheckButton(hwndDlg, BACKGROUND_CONFIG, CheckYes(gPUS));
      WinCheckButton(hwndDlg, SURE_CONFIG, CheckYes(gSure));
      WinCheckButton(hwndDlg, MINI_CONFIG, CheckYes(gStickyIcon));

      WinCheckButton(hwndDlg, BEEP_CONFIG, CheckYes(gBeep));

      if (CheckNo(gBeep))
      {

      WinEnableControl(hwndDlg, 1006, FALSE);
      WinEnableControl(hwndDlg, 1007, FALSE);
      WinEnableControl(hwndDlg, FREQUENCY_CONFIG, FALSE);
      WinEnableControl(hwndDlg, DURATION_CONFIG, FALSE);

      } /* end if */


      /* Set range (numeric style) FREQUENCY_CONFIG Spin Button */
      WinSendDlgItemMsg(hwndDlg, FREQUENCY_CONFIG,
                        SPBM_SETLIMITS,
                        MPFROMLONG(5000),                  /* Upper limit */
                        MPFROMLONG(10));                   /* Lower limit */ 
      WinSendDlgItemMsg(hwndDlg, DURATION_CONFIG,
                        SPBM_SETLIMITS,
                        MPFROMLONG(1000),                  /* Upper limit */
                        MPFROMLONG(10));                   /* Lower limit */ 

      WinSendDlgItemMsg(hwndDlg, FREQUENCY_CONFIG,
                        SPBM_SETCURRENTVALUE,
                        MPFROMLONG(atol(gFreq)), /* Value within range */
                        0);

      WinSendDlgItemMsg(hwndDlg, DURATION_CONFIG,
                        SPBM_SETCURRENTVALUE,
                        MPFROMLONG(atol(gDur)), /* Value within range */
                        0);


      /* Set range without update CLEAR_CONFIG Spin Button */
      WinSendDlgItemMsg(hwndDlg, CLEAR_CONFIG,
                        SPBM_OVERRIDESETLIMITS,
                        MPFROMLONG(120),         /* Upper limit */
                        MPFROMLONG(0));          /* Lower limit */

      /* Set item value (numeric style) CLEAR_CONFIG Spin Button */
      WinSendDlgItemMsg(hwndDlg, CLEAR_CONFIG,
                        SPBM_SETCURRENTVALUE,
                        MPFROMLONG(atol(gClearAuto)), /* Value within range */
                        0);
      /* ##END  */
      }
      break;

   /* Form event Closed WM_CLOSE */
   case WM_CLOSE :
      {
      /* ##START Form.2  */
      /* Event Closed - Form STICKY2\O_CONFIG */
      CHAR aTextValue[255]="text";
      LONG anIntegerValue=0;
      ULONG anUnsignedValue=0;


      MsgLog("Closing O_CONFIG");

      if (c_mini)
      {
      SWP swp;
      anUnsignedValue=(ULONG)WinQueryButtonCheckstate(hwndDlg,MINI_CONFIG);
        
        strcpy(gStickyIcon, anUnsignedValue ? gYes : gNo);  
        PutString(S_StickyIcon, gStickyIcon); 
        WinQueryWindowPos(gHwndFrame, &swp);
        if (swp.fl & SWP_RESTORE)
           {
           MsgLog("O_CONFIG - RESTORE");
           WinPostMsg(gHwndFrame, WM_USER_RESTORE, 0, 0);
           }
       

      } /* end if */

      if (c_cas)
      {
      anUnsignedValue=(ULONG)WinQueryButtonCheckstate(hwndDlg,SEND_CONFIG);

        strcpy(gAfterSend, anUnsignedValue ? gYes : gNo);  
        PutString(S_CloseAfterSend, gAfterSend); 
      } /* end if */
      if (c_car)
      {
      anUnsignedValue=(ULONG)WinQueryButtonCheckstate(hwndDlg,REPLY_CONFIG);
        strcpy(gAfterReply, anUnsignedValue ? gYes: gNo );  
        PutString(S_CloseAfterReply, gAfterReply); 

      } /* end if */
      if (c_pop)
      {
      anUnsignedValue=(ULONG)WinQueryButtonCheckstate(hwndDlg,BACKGROUND_CONFIG);
        strcpy(gPUS, anUnsignedValue ? gYes: gNo );  
        PutString(S_PopUpSticky, gPUS); 

          
      } /* end if */
      if (c_aus)
      {
      anUnsignedValue=(ULONG)WinQueryButtonCheckstate(hwndDlg,SURE_CONFIG);
        
         strcpy(gSure, anUnsignedValue ? gYes : gNo );
         PutString(S_AreYouSure, gSure ); 

        
      } /* end if */
      if (c_beep)
      {
      anUnsignedValue=(ULONG)WinQueryButtonCheckstate(hwndDlg,BEEP_CONFIG);
        
        PutString(S_Beep, anUnsignedValue ? gYes: gNo ); 
        strcpy(gBeep, anUnsignedValue ? gYes : gNo);
        
      } /* end if */
      /* Get item value (numeric style) FREQUENCY_CONFIG Spin Button */
      WinSendDlgItemMsg(hwndDlg, FREQUENCY_CONFIG,
                        SPBM_QUERYVALUE,
                        MPFROMP(&anUnsignedValue),   /* Buffer for value */
                        MPFROM2SHORT(0,SPBQ_ALWAYSUPDATE));
      if (atol(gFreq) != anUnsignedValue)
      {
        sprintf(gFreq, "%d", anUnsignedValue);
        PutString(S_Frequency, gFreq);
      } /* end if */
                        

      /* Get item value (numeric style) DURATION_CONFIG Spin Button */
      WinSendDlgItemMsg(hwndDlg, DURATION_CONFIG,
                        SPBM_QUERYVALUE,
                        MPFROMP(&anUnsignedValue),   /* Buffer for value */
                        MPFROM2SHORT(0,SPBQ_ALWAYSUPDATE));
      if (atol(gDur) != anUnsignedValue)
      {
        sprintf(gDur, "%d", anUnsignedValue);
        PutString(S_Duration, gDur);
      } /* end if */

      /* Get item value (numeric style) DURATION_CONFIG Spin Button */
      WinSendDlgItemMsg(hwndDlg, CLEAR_CONFIG,
                        SPBM_QUERYVALUE,
                        MPFROMP(&anUnsignedValue),   /* Buffer for value */
                        MPFROM2SHORT(0,SPBQ_ALWAYSUPDATE));
      if (atol(gClearAuto) != anUnsignedValue)
      {
        sprintf(gClearAuto, "%d", anUnsignedValue);
        PutString(S_ClearAuto, gClearAuto);
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
      /* Check Box SEND_CONFIG Event Handlers */
      case SEND_CONFIG:
         switch (SHORT2FROMMP(mp1)) {
         /* Clicked/Selected */
         case BN_CLICKED:
            {
            /* ##START 1000.0  */
            /* Event Clicked/Selected - Close window after Send SEND_CONFIG */

            c_cas = 1;
            /* ##END  */
            }
            break;
         } /* end switch */
         break;

      /* Check Box REPLY_CONFIG Event Handlers */
      case REPLY_CONFIG:
         switch (SHORT2FROMMP(mp1)) {
         /* Clicked/Selected */
         case BN_CLICKED:
            {
            /* ##START 1001.0  */
            /* Event Clicked/Selected - Close Window after Reply REPLY_CONFIG */

            c_car = 1;
            /* ##END  */
            }
            break;
         } /* end switch */
         break;

      /* Check Box BACKGROUND_CONFIG Event Handlers */
      case BACKGROUND_CONFIG:
         switch (SHORT2FROMMP(mp1)) {
         /* Clicked/Selected */
         case BN_CLICKED:
            {
            /* ##START 1002.0  */
            /* Event Clicked/Selected - Popup Sticky on Receive BACKGROUND_CONFIG */
            c_pop = 1;
            /* ##END  */
            }
            break;
         } /* end switch */
         break;

      /* Check Box BEEP_CONFIG Event Handlers */
      case BEEP_CONFIG:
         switch (SHORT2FROMMP(mp1)) {
         /* Clicked/Selected */
         case BN_CLICKED:
            {
            /* ##START 1003.0  */
            /* Event Clicked/Selected - Beep BEEP_CONFIG */
            ULONG	anUnsignedValue;

            c_beep = 1;
            /* Is button selected? BEEP_CONFIG Check Box */
            anUnsignedValue=(ULONG)WinQueryButtonCheckstate(hwndDlg,BEEP_CONFIG);

            WinEnableControl(hwndDlg, 1006, anUnsignedValue);
            WinEnableControl(hwndDlg, 1007, anUnsignedValue);
            WinEnableControl(hwndDlg, FREQUENCY_CONFIG, anUnsignedValue);
            WinEnableControl(hwndDlg, DURATION_CONFIG, anUnsignedValue);
            /* ##END  */
            }
            break;
         } /* end switch */
         break;

      /* Check Box SURE_CONFIG Event Handlers */
      case SURE_CONFIG:
         switch (SHORT2FROMMP(mp1)) {
         /* Clicked/Selected */
         case BN_CLICKED:
            {
            /* ##START 1009.0  */
            /* Event Clicked/Selected - Are You Sure Prompts SURE_CONFIG */
            c_aus = 1;
            /* ##END  */
            }
            break;
         } /* end switch */
         break;

      /* Check Box MINI_CONFIG Event Handlers */
      case MINI_CONFIG:
         switch (SHORT2FROMMP(mp1)) {
         /* Clicked/Selected */
         case BN_CLICKED:
            {
            /* ##START 1010.0  */
            /* Event Clicked/Selected - Mini ICON when shrunk MINI_CONFIG */
            CHAR aTextValue[255]="text";
            LONG anIntegerValue=0;
            ULONG anUnsignedValue=0;

            c_mini = 1;
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
HWND OpenO_CONFIG(HWND hwndOwner, PVOID pInfo)
{
   HWND hwndFrame;
   if (WinQueryWindowUShort(hwndOwner, QWS_ID) == FID_CLIENT)
      hwndOwner = WinQueryWindow(hwndOwner, QW_PARENT);
   hwndFrame =(HWND) WinLoadDlg(hwndOwner,
           hwndOwner,   
           O_CONFIGDlgProc, 
           0, ID_O_CONFIGFORM, 
           pInfo); 
   return hwndFrame;
}
