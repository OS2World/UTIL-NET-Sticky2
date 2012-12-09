/******************************************************************************/
/*                                                                            */
/* Program: Sticky2.exe                                                       */
/*                                                                            */
/* Description: TCP Sticky Pad                                                */
/*                                                                            */
/* File Name : O_USER.C                                                       */
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
#include "O_USER.RCH"

/* ##START Form.34 Extra include files */
/* Code Section Extra include files - Form STICKY2\O_USER */


#include "sticky2.h"
#include "data.h"
/* ##END Extra include files */
/* declare pointer to main form info block */
extern PMAINFORMINFO pMainFormInfo;

MRESULT EXPENTRY O_USERDlgProc(HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  PO_USERFORMINFO pO_USERFormInfo=(PO_USERFORMINFO) WinQueryWindowULong(hwndDlg, QWL_USER);
  HWND hwndFrame = hwndDlg;
 /* ##START Form.37 Top of window procedure */
 /* ##END Top of window procedure */
   switch (msg) {
   /* Form event Opened WM_INITDLG */
   case WM_INITDLG :
     if (mp2==0)
        mp2 = (MPARAM) malloc(sizeof(O_USERFORMINFO));
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
     pO_USERFormInfo=(PO_USERFORMINFO) WinQueryWindowULong(hwndDlg, QWL_USER);
      WinAssociateHelpInstance(pMainFormInfo->hwndHelpInstance, hwndFrame);

      {
      /* ##START Form.1  */
      /* Event Opened - Form STICKY2\O_USER */
      CHAR aTextValue[255]="text";
      LONG anIntegerValue=0;
      ULONG anUnsignedValue=0;


      /* Set item text O_USER_NAME Entry Field */
      WinSetDlgItemText(hwndDlg, O_USER_NAME, gMyName);

      anUnsignedValue = (ULONG)gethostname(aTextValue, sizeof(aTextValue));
      /* Set item text O_USER_IP Text */
      WinSetDlgItemText(hwndDlg, O_USER_IP, aTextValue);
      /* ##END  */
      }
      break;

   /* Form event Closed WM_CLOSE */
   case WM_CLOSE :
      {
      /* ##START Form.2  */
      /* Event Closed - Form STICKY2\O_USER */
      CHAR aTextValue[255]="text";
      LONG anIntegerValue=0;
      ULONG anUnsignedValue=0;
      CHAR *c_ptr;

      MsgLog("Closing O_USER");

        c_ptr = (CHAR *)TextChanged(hwndDlg, (ULONG)O_USER_NAME);
        if (c_ptr)
          {
          PutString(S_MyName, c_ptr);
          strcpy(gMyName, c_ptr);
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

 /* ##START Form.38 User defined messages */
 /* ##END User defined messages */
   default :
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
     return WinDefDlgProc(hwndDlg,msg,mp1,mp2);
   } /* end switch for main msg dispatch */
   return (MRESULT)FALSE;
} /* end dialog procedure */
HWND OpenO_USER(HWND hwndOwner, PVOID pInfo)
{
   HWND hwndFrame;
   if (WinQueryWindowUShort(hwndOwner, QWS_ID) == FID_CLIENT)
      hwndOwner = WinQueryWindow(hwndOwner, QW_PARENT);
   hwndFrame =(HWND) WinLoadDlg(hwndOwner,
           hwndOwner,   
           O_USERDlgProc, 
           0, ID_O_USERFORM, 
           pInfo); 
   return hwndFrame;
}
