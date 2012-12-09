/******************************************************************************/
/*                                                                            */
/* Program: Sticky2.exe                                                       */
/*                                                                            */
/* Description: TCP Sticky Pad                                                */
/*                                                                            */
/* File Name : POPUP.C                                                        */
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
#include "POPUP.RCH"

/* ##START Form.34 Extra include files */
/* ##END Extra include files */
/* declare pointer to main form info block */
extern PMAINFORMINFO pMainFormInfo;

MRESULT EXPENTRY POPUPDlgProc(HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
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
      } /* end switch */
      break;

  /* Initialize sub menus, if any */
  case WM_INITMENU:
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
HWND OpenPOPUP(HWND hwndOwner, PVOID pInfo)
{
   HWND hwndFrame;
   if (WinQueryWindowUShort(hwndOwner, QWS_ID) == FID_CLIENT)
      hwndOwner = WinQueryWindow(hwndOwner, QW_PARENT);
   hwndFrame =(HWND) WinLoadDlg(HWND_DESKTOP,
           hwndOwner,   
           POPUPDlgProc, 
           0, ID_POPUPFORM, 
           pInfo); 
   WinShowWindow(hwndFrame, TRUE);
   return hwndFrame;
}
