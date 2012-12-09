/******************************************************************************/
/*                                                                            */
/* Program: Sticky2.exe                                                       */
/*                                                                            */
/* Description: TCP Sticky Pad                                                */
/*                                                                            */
/* File Name : Send.C                                                         */
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
#include "Send.RCH"

/* ##START Form.34 Extra include files */
/* Code Section Extra include files - Form THREAD\Main */
#include "sticky2.h"
#include "data.h"
#include "time.h"
/* ##END Extra include files */
/* declare pointer to main form info block */
extern PMAINFORMINFO pMainFormInfo;

MRESULT EXPENTRY SENDDlgProc(HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
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
         PFIELDINFO pFieldInfo;
         PFIELDINFO pFirstFieldInfo;
         FIELDINFOINSERT fieldInsert;
         CNRINFO cnrInfo;

         pFirstFieldInfo=(PFIELDINFO)WinSendDlgItemMsg(hwndDlg, IP_CONTAINER,
                                                   CM_ALLOCDETAILFIELDINFO,
                                                   MPFROMLONG(4),
                                                   0);
         pFieldInfo=pFirstFieldInfo;

         pFieldInfo->cb=sizeof(FIELDINFO);
         pFieldInfo->flData=CFA_BITMAPORICON | CFA_HORZSEPARATOR | CFA_LEFT | CFA_VCENTER | CFA_INVISIBLE | CFA_FIREADONLY;
         pFieldInfo->flTitle=CFA_FITITLEREADONLY | CFA_VCENTER | CFA_CENTER;
         pFieldInfo->pTitleData="Icon";
         pFieldInfo->offStruct=FIELDOFFSET(MINIRECORDCORE,hptrIcon);
         pFieldInfo->cxWidth=0;
         pFieldInfo=pFieldInfo->pNextFieldInfo;

         pFieldInfo->cb=sizeof(FIELDINFO);
         pFieldInfo->flData=CFA_STRING | CFA_HORZSEPARATOR | CFA_LEFT | CFA_VCENTER | CFA_FIREADONLY;
         pFieldInfo->flTitle=CFA_FITITLEREADONLY | CFA_VCENTER | CFA_CENTER;
         pFieldInfo->pTitleData="Name";
         pFieldInfo->offStruct=FIELDOFFSET(MINIRECORDCORE,pszIcon);
         pFieldInfo->cxWidth=0;
         pFieldInfo=pFieldInfo->pNextFieldInfo;

         pFieldInfo->cb=sizeof(FIELDINFO);
         pFieldInfo->flData=CFA_STRING | CFA_HORZSEPARATOR | CFA_LEFT | CFA_VCENTER | CFA_FIREADONLY;
         pFieldInfo->flTitle=CFA_FITITLEREADONLY | CFA_VCENTER | CFA_CENTER;
         pFieldInfo->pTitleData="Host";
         pFieldInfo->offStruct=sizeof(MINIRECORDCORE)+0;
         pFieldInfo->cxWidth=150;
         pFieldInfo=pFieldInfo->pNextFieldInfo;

         pFieldInfo->cb=sizeof(FIELDINFO);
         pFieldInfo->flData=CFA_STRING | CFA_HORZSEPARATOR | CFA_LEFT | CFA_VCENTER | CFA_FIREADONLY;
         pFieldInfo->flTitle=CFA_FITITLEREADONLY | CFA_VCENTER | CFA_CENTER;
         pFieldInfo->pTitleData="Port";
         pFieldInfo->offStruct=sizeof(MINIRECORDCORE)+4;
         pFieldInfo->cxWidth=50;
         pFieldInfo=pFieldInfo->pNextFieldInfo;

         fieldInsert.cb = sizeof(FIELDINFOINSERT);
         fieldInsert.pFieldInfoOrder = (PFIELDINFO)CMA_END;
         fieldInsert.cFieldInfoInsert = 4;
         fieldInsert.fInvalidateFieldInfo = TRUE;
         WinSendDlgItemMsg(hwndDlg, IP_CONTAINER,
                           CM_INSERTDETAILFIELDINFO,
                           MPFROMP(pFirstFieldInfo),
                           MPFROMP(&fieldInsert));
         cnrInfo.cb = sizeof(CNRINFO);
         cnrInfo.pFieldInfoLast = pFirstFieldInfo->pNextFieldInfo;
         cnrInfo.xVertSplitbar=88;
         WinSendDlgItemMsg(hwndDlg, IP_CONTAINER,
                           CM_SETCNRINFO,
                           MPFROMP(&cnrInfo),
                           MPFROMLONG( CMA_PFIELDINFOLAST | CMA_XVERTSPLITBAR));
      }
      {
      /* ##START Form.1  */
      /* Event Opened - Form STICKY2\Send */
      CHAR name[512];
      CHAR host[512];
      CHAR port[8]="6711";
      CHAR locbuf[128];
      CHAR *last, *first;
      LONG anIntegerValue=0;
      ULONG anUnsignedValue=0;
      USHORT LastNameFirst = 1;
      APIRET rc;
      ULONG	index;
      PMINIRECORDCORE pRecord;

        rc = AllocInitSubMem(&g1Meg, ONE_MEG_NAMES);
        if (rc)
          {
          sprintf(locbuf, "Error allocating memory RC=%d", rc);
          MsgLog(locbuf);
          } /* end if */


      SetHwndID(hwndDlg, IP_CONTAINER);
        
      rc = 0;
      index = 1;
      while (rc == 0 && index < MAXNAMES)
      {
        sprintf(locbuf, "Name%04d", index);
        rc = GetStringN(locbuf, "", name, sizeof(name));

        if (rc)
          break;

        sprintf(locbuf, "Host%04d", index);
        GetStringN(locbuf, "", host, sizeof(host));
        
        if (CheckNo(gP6711))
        {
        sprintf(locbuf, "Port%04d", index);
        GetStringN(locbuf, "6711", port, sizeof(port));
        } 
        
        AddName(name, host, port);	

        index++;

      } /* end while */

        SortNames();
        
        pRecord=(PMINIRECORDCORE)WinSendDlgItemMsg(hwndDlg, IP_CONTAINER,
                                  CM_QUERYRECORD,
                                  MPFROMP(0), /* pointer to reference record */
                                  MPFROM2SHORT(CMA_FIRST, CMA_ITEMORDER));
                                    
         WinSendDlgItemMsg(hwndDlg, IP_CONTAINER,
                           CM_SETRECORDEMPHASIS,
                           MPFROMP(pRecord), /* pointer to reference record */
                           MPFROM2SHORT(TRUE, CRA_SELECTED));


      /* View as details IP_CONTAINER Container */
      {
         CNRINFO cnrinfo;
         SWP 	swp;
         char	locbuf[32];
         
         HWND	hwnd = WinWindowFromID(hwndDlg, IP_CONTAINER);

         WinQueryWindowPos(hwnd, &swp);

         if (atol(gSplitPercent) == -1)
         {
           cnrinfo.xVertSplitbar = (swp.cx * 50) / 100;   
         } else {
           cnrinfo.xVertSplitbar = atol(gSplitPercent);
         } /* end if */
      	
      	
         cnrinfo.cb=sizeof(CNRINFO);
         cnrinfo.flWindowAttr=CV_DETAIL | CA_DETAILSVIEWTITLES | CA_MIXEDTARGETEMPH;
         WinSendDlgItemMsg(hwndDlg, IP_CONTAINER,
                           CM_SETCNRINFO,
                           MPFROMP(&cnrinfo),
                           MPFROMLONG(CMA_FLWINDOWATTR | CMA_XVERTSPLITBAR));
      }

           
         WinSendDlgItemMsg(hwndDlg, IP_CONTAINER,
                           CM_SETRECORDEMPHASIS,
                           MPFROMP(0), /* pointer to reference record */
                           MPFROM2SHORT(FALSE, CRA_SELECTED));

      /* Set text limit SEND_TEXT Multi-Line Entry Field */
      WinSendDlgItemMsg(hwndDlg, SEND_TEXT,
                        MLM_SETTEXTLIMIT,
                        MPFROMLONG(2048),  /* New text limit */
                        0);
      /* ##END  */
      }
      break;

   /* Form event Closed WM_CLOSE */
   case WM_CLOSE :
      {
      /* ##START Form.2  */
      /* Event Closed - Form STICKY2\Send */
      LONG anIntegerValue=0;
      ULONG anUnsignedValue=0;
      APIRET	rc;



        WinSendDlgItemMsg(hwndDlg, IP_CONTAINER,
                               CM_REMOVERECORD,
                               MPFROMP(0), /* all Records */
                               MPFROM2SHORT(0,CMA_FREE | CMA_INVALIDATE)); /* delete all records */


        {
         CNRINFO cnrinfo;
         SWP 	swp;
         
         WinQueryWindowPos(WinWindowFromID(hwndDlg, IP_CONTAINER), &swp);

         cnrinfo.cb=sizeof(CNRINFO);
         cnrinfo.flWindowAttr=CV_DETAIL | CA_DETAILSVIEWTITLES | CA_MIXEDTARGETEMPH;
         WinSendDlgItemMsg(hwndDlg, IP_CONTAINER,
                           CM_QUERYCNRINFO,
                           MPFROMP(&cnrinfo),
                           MPFROMLONG(CMA_FLWINDOWATTR | CMA_XVERTSPLITBAR));

        sprintf(gSplitPercent, "%d", cnrinfo.xVertSplitbar);
        PutString(S_SplitPercentSend, gSplitPercent);
        }



      rc = FreeAllSubMem(g1Meg);
      g1Meg = 0;
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
      /* Button 1000 Clicked/Selected */
      case 1000:
         {
         /* ##START 1000.0  */
         /* Event Clicked/selected - Send  1000 */
         CHAR aTextValue[3*1024]="text";
         LONG anIntegerValue=0;
         ULONG anUnsignedValue=0;
         CHAR SendText[4096+32];
         INT	rc=0;
         PSEND_IP_CONTAINER_REC pRecord;
         time_t	lt;

         /* Get first selected item IP_CONTAINER Container */
         {
           
            pRecord=(PSEND_IP_CONTAINER_REC)WinSendDlgItemMsg(hwndDlg, IP_CONTAINER,
                              CM_QUERYRECORDEMPHASIS,
                              MPFROMP(CMA_FIRST), /* pointer to reference record */
                              MPFROMLONG(CRA_SELECTED));
         }

         /* Get item text SEND_TEXT Multi-Line Entry Field */
         WinQueryDlgItemText(hwndDlg, SEND_TEXT, sizeof(SendText), SendText);

         while (pRecord)
           {
           rc = SendTo(hwndFrame, gSocket, pRecord->pszHost, SendText);
           time(&lt);
             
           sprintf(aTextValue, ">>>--- Sent Sticky\r\n%s\r\n%s\r\n%s\r\n%s\r\n",
           	  ctime(&lt), pRecord->Record.pszIcon, pRecord->pszHost, SendText);
           StickyLog(aTextValue);
           
           
            pRecord=(PSEND_IP_CONTAINER_REC)WinSendDlgItemMsg(hwndDlg, IP_CONTAINER,
                              CM_QUERYRECORDEMPHASIS,
                              MPFROMP(pRecord), /* pointer to reference record */
                              MPFROMLONG(CRA_SELECTED));

           }

         if (rc != 0)
         {
         /* Set item text ERROR_TEXT Text */
         WinSetDlgItemText(hwndDlg, ERROR_TEXT, "Error Sending to Thread");
         } /* end if */

         if (CheckYes(gAfterSend))
           {
           WinPostMsg(hwndDlg, WM_CLOSE, 0, 0);
           } /* end if */
         /* ##END  */
         }
         break;
      /* Button SEND_CANCEL Clicked/Selected */
      case SEND_CANCEL:
         {
         /* ##START 1004.0  */
         /* Event Clicked/selected - Cancel SEND_CANCEL */
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
 /* Code Section User defined messages - Form STICKY2\Main */


 case WM_USER_STATUS:
   {
   APIRET	rc;
   char locbuf[255];
   
   rc = SetTextError(LONGFROMMP(mp1), LONGFROMMP(mp2), locbuf);

   /* Set item text ERROR_TEXT Text */
   WinSetDlgItemText(hwndDlg, ERROR_TEXT, locbuf);
   }
   break; 


 case WM_MINMAXFRAME:
   {
   SWP *swp;
     
   /* hide list box when minimized so it doesn't overwrite icon */
   swp = PVOIDFROMMP( mp1 );
   WinShowWindow(WinWindowFromID( hwndDlg, ERROR_TEXT),
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
HWND OpenSEND(HWND hwndOwner, PVOID pInfo)
{
   HWND hwndFrame;
   if (WinQueryWindowUShort(hwndOwner, QWS_ID) == FID_CLIENT)
      hwndOwner = WinQueryWindow(hwndOwner, QW_PARENT);
   hwndFrame =(HWND) WinLoadDlg(HWND_DESKTOP,
           hwndOwner,   
           SENDDlgProc, 
           0, ID_SENDFORM, 
           pInfo); 
   WinShowWindow(hwndFrame, TRUE);
   return hwndFrame;
}
