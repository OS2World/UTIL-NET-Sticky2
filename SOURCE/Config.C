/******************************************************************************/
/*                                                                            */
/* Program: Sticky2.exe                                                       */
/*                                                                            */
/* Description: TCP Sticky Pad                                                */
/*                                                                            */
/* File Name : CONFIG.C                                                       */
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
#include "CONFIG.RCH"

/* ##START Form.34 Extra include files */
/* Code Section Extra include files - Form STICKY2\CONFIG */


#include "sticky2.h"
#include "data.h"
#include "O_NAMES.RCH"
/* ##END Extra include files */
/* declare pointer to main form info block */
extern PMAINFORMINFO pMainFormInfo;

MRESULT EXPENTRY CONFIGDlgProc(HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
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

         pFirstFieldInfo=(PFIELDINFO)WinSendDlgItemMsg(hwndDlg, OPTIONS_FOLDER,
                                                   CM_ALLOCDETAILFIELDINFO,
                                                   MPFROMLONG(2),
                                                   0);
         pFieldInfo=pFirstFieldInfo;

         pFieldInfo->cb=sizeof(FIELDINFO);
         pFieldInfo->flData=CFA_BITMAPORICON | CFA_HORZSEPARATOR | CFA_CENTER | CFA_VCENTER | CFA_FIREADONLY;
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

         fieldInsert.cb = sizeof(FIELDINFOINSERT);
         fieldInsert.pFieldInfoOrder = (PFIELDINFO)CMA_END;
         fieldInsert.cFieldInfoInsert = 2;
         fieldInsert.fInvalidateFieldInfo = TRUE;
         WinSendDlgItemMsg(hwndDlg, OPTIONS_FOLDER,
                           CM_INSERTDETAILFIELDINFO,
                           MPFROMP(pFirstFieldInfo),
                           MPFROMP(&fieldInsert));
         cnrInfo.cb = sizeof(CNRINFO);
         cnrInfo.pFieldInfoLast = pFirstFieldInfo->pNextFieldInfo;
         cnrInfo.xVertSplitbar=26;
         WinSendDlgItemMsg(hwndDlg, OPTIONS_FOLDER,
                           CM_SETCNRINFO,
                           MPFROMP(&cnrInfo),
                           MPFROMLONG( CMA_PFIELDINFOLAST | CMA_XVERTSPLITBAR));
      }
      {
      /* ##START Form.1  */
      /* Event Opened - Form STICKY2\CONFIG */
      CHAR aTextValue[255]="text";
      LONG anIntegerValue=0;
      ULONG anUnsignedValue=0;
      int	i=0;


      gConfigTerm = 0;
      /* Add a container record to end OPTIONS_FOLDER Container */
      {
         PCONFIG_OPTIONS_FOLDER_REC pRecord, pRecords; /* Pointer to cnr item. */
         
         /* IMPORTANT!!!! Manually replace MAIN with the form name */
         /* This pRecord typedef is contained in the .H for this form */
         RECORDINSERT RecordInsert;

         /* IMPORTANT!!! we allocate 32 extra bytes for the pszIcon string */
         /* We must allocate more than that if we have any extra PSZ members */
         /* as columns */
         pRecords=(PVOID)WinSendDlgItemMsg(hwndDlg, OPTIONS_FOLDER,
                        CM_ALLOCRECORD,
                        MPFROMLONG(sizeof(*pRecord)-sizeof(MINIRECORDCORE)+32), /* Bytes of additional data for Text*/
                        MPFROMLONG(gOptions));                  /* Number of records        */
                        
         pRecord = pRecords;               
         pRecord->Record.cb=sizeof(MINIRECORDCORE);
         pRecord->Record.flRecordAttr=0;
      //   pRecord->Record.hptrIcon=WinQuerySysPointer(HWND_DESKTOP,SPTR_FILE,FALSE);
         pRecord->Record.hptrIcon=WinLoadPointer(HWND_DESKTOP, 0L, ICON_SUNSMILE);
         pRecord->Record.pszIcon=(PBYTE)pRecord+sizeof(*pRecord);
         strcpy(pRecord->Record.pszIcon,"User");


         pRecord = (PCONFIG_OPTIONS_FOLDER_REC)pRecord->Record.preccNextRecord;
         pRecord->Record.cb=sizeof(MINIRECORDCORE);
         pRecord->Record.flRecordAttr=0;
         pRecord->Record.hptrIcon=WinLoadPointer(HWND_DESKTOP, 0L, ICON_DEBUG);
         pRecord->Record.pszIcon=(PBYTE)pRecord+sizeof(*pRecord);
         strcpy(pRecord->Record.pszIcon,"Debug");
         
         pRecord = (PCONFIG_OPTIONS_FOLDER_REC)pRecord->Record.preccNextRecord;
         pRecord->Record.cb=sizeof(MINIRECORDCORE);
         pRecord->Record.flRecordAttr=0;
         pRecord->Record.hptrIcon=WinLoadPointer(HWND_DESKTOP, 0L, ICON_TOOLS);
         pRecord->Record.pszIcon=(PBYTE)pRecord+sizeof(*pRecord);
         strcpy(pRecord->Record.pszIcon,"Setup");
         
         pRecord = (PCONFIG_OPTIONS_FOLDER_REC)pRecord->Record.preccNextRecord;
         pRecord->Record.cb=sizeof(MINIRECORDCORE);
         pRecord->Record.flRecordAttr=0;
         pRecord->Record.hptrIcon=WinLoadPointer(HWND_DESKTOP, 0L, ICON_ML1);
         pRecord->Record.pszIcon=(PBYTE)pRecord+sizeof(*pRecord);
         strcpy(pRecord->Record.pszIcon,"Names");
         
         pRecord = (PCONFIG_OPTIONS_FOLDER_REC)pRecord->Record.preccNextRecord;
         pRecord->Record.cb=sizeof(MINIRECORDCORE);
         pRecord->Record.flRecordAttr=0;
         pRecord->Record.hptrIcon=WinLoadPointer(HWND_DESKTOP, 0L, ICON_AUTOREPLY);
         pRecord->Record.pszIcon=(PBYTE)pRecord+sizeof(*pRecord);
         strcpy(pRecord->Record.pszIcon,"Auto\nReply");
           
         pRecord = (PCONFIG_OPTIONS_FOLDER_REC)pRecord->Record.preccNextRecord;
         pRecord->Record.cb=sizeof(MINIRECORDCORE);
         pRecord->Record.flRecordAttr=0;
         pRecord->Record.hptrIcon=WinLoadPointer(HWND_DESKTOP, 0L, ICON_WS1);
         pRecord->Record.pszIcon=(PBYTE)pRecord+sizeof(*pRecord);
         strcpy(pRecord->Record.pszIcon,"Threads");
         
         


      /* IMPORTANT!!! initiaize other members here if they exist */

         /* add the item to the container */
         RecordInsert.cb=sizeof(RECORDINSERT);
         RecordInsert.pRecordOrder=(PRECORDCORE)CMA_END;/* add to the end */
         RecordInsert.pRecordParent=(PRECORDCORE)0;     /* not a child record */
         RecordInsert.zOrder=CMA_TOP;
         RecordInsert.cRecordsInsert=gOptions;
         RecordInsert.fInvalidateRecord=TRUE;           /* repaint the record */
         WinSendDlgItemMsg(hwndDlg, OPTIONS_FOLDER,
                           CM_INSERTRECORD,
                           MPFROMP(pRecords),
                           MPFROMP(&RecordInsert));{
       }

      }

      /* Add page with no tab OPTIONS_NOTEBOOK Notebook */
      { 
      /* Important: assign hNewFrame with a newly created notebook form */
      HWND hNewFrame = OpenO_USER(hwndDlg, 0);      /* Window to go within page */
      ULONG ulPageId;        /* Page identifier */
      ulPageId=(ULONG)WinSendDlgItemMsg(hwndDlg, OPTIONS_NOTEBOOK,
                        BKM_INSERTPAGE ,
                        MPFROMLONG(0),
                        MPFROM2SHORT(BKA_STATUSTEXTON|BKA_AUTOPAGESIZE,
                           BKA_LAST));
      i = 0;
      MsgLog("Setting Notebook Pages");                     
      if (ulPageId) {
         /* Associate window within page */   WinSetOwner(hNewFrame, WinWindowFromID(hwndDlg, OPTIONS_NOTEBOOK));
         WinSetParent(hNewFrame, WinWindowFromID(hwndDlg, OPTIONS_NOTEBOOK),FALSE);
         WinSendDlgItemMsg(hwndDlg, OPTIONS_NOTEBOOK,
                        BKM_SETPAGEWINDOWHWND,
                        MPFROMLONG(ulPageId),    /* Page ID */
                        MPFROMHWND(hNewFrame));  /* Window within page */
         gPageId[i++] = ulPageId;
      }
      }

      /* Add page with no tab OPTIONS_NOTEBOOK Notebook */
      {
      /* Important: assign hNewFrame with a newly created notebook form */
      HWND hNewFrame = OpenO_DEBUG(hwndDlg, 0);      /* Window to go within page */
      ULONG ulPageId;        /* Page identifier */
      ulPageId=(ULONG)WinSendDlgItemMsg(hwndDlg, OPTIONS_NOTEBOOK,
                        BKM_INSERTPAGE ,
                        MPFROMLONG(0),
                        MPFROM2SHORT(BKA_STATUSTEXTON|BKA_AUTOPAGESIZE,
                           BKA_LAST));
      if (ulPageId) {
         /* Associate window within page */   WinSetOwner(hNewFrame, WinWindowFromID(hwndDlg, OPTIONS_NOTEBOOK));
         WinSetParent(hNewFrame, WinWindowFromID(hwndDlg, OPTIONS_NOTEBOOK),FALSE);
         WinSendDlgItemMsg(hwndDlg, OPTIONS_NOTEBOOK,
                        BKM_SETPAGEWINDOWHWND,
                        MPFROMLONG(ulPageId),    /* Page ID */
                        MPFROMHWND(hNewFrame));  /* Window within page */
         gPageId[i++] = ulPageId;                  
      }
      }

      /* Add page with no tab OPTIONS_NOTEBOOK Notebook */
      {
      /* Important: assign hNewFrame with a newly created notebook form */
      HWND hNewFrame = OpenO_CONFIG(hwndDlg, 0);      /* Window to go within page */
      ULONG ulPageId;        /* Page identifier */
      ulPageId=(ULONG)WinSendDlgItemMsg(hwndDlg, OPTIONS_NOTEBOOK,
                        BKM_INSERTPAGE ,
                        MPFROMLONG(0),
                        MPFROM2SHORT(BKA_STATUSTEXTON|BKA_AUTOPAGESIZE,
                           BKA_LAST));
      if (ulPageId) {
         /* Associate window within page */   WinSetOwner(hNewFrame, WinWindowFromID(hwndDlg, OPTIONS_NOTEBOOK));
         WinSetParent(hNewFrame, WinWindowFromID(hwndDlg, OPTIONS_NOTEBOOK),FALSE);
         WinSendDlgItemMsg(hwndDlg, OPTIONS_NOTEBOOK,
                        BKM_SETPAGEWINDOWHWND,
                        MPFROMLONG(ulPageId),    /* Page ID */
                        MPFROMHWND(hNewFrame));  /* Window within page */
         gPageId[i++] = ulPageId;                  
      }
      }

      /* Add page with no tab OPTIONS_NOTEBOOK Notebook */
      {
      /* Important: assign hNewFrame with a newly created notebook form */
      HWND hNewFrame = OpenO_NAMES(hwndDlg, 0);      /* Window to go within page */
      ULONG ulPageId;        /* Page identifier */
      ulPageId=(ULONG)WinSendDlgItemMsg(hwndDlg, OPTIONS_NOTEBOOK,
                        BKM_INSERTPAGE ,
                        MPFROMLONG(0),
                        MPFROM2SHORT(BKA_STATUSTEXTON|BKA_AUTOPAGESIZE,
                           BKA_LAST));
      if (ulPageId) {
         /* Associate window within page */   WinSetOwner(hNewFrame, WinWindowFromID(hwndDlg, OPTIONS_NOTEBOOK));
         WinSetParent(hNewFrame, WinWindowFromID(hwndDlg, OPTIONS_NOTEBOOK),FALSE);
         WinSendDlgItemMsg(hwndDlg, OPTIONS_NOTEBOOK,
                        BKM_SETPAGEWINDOWHWND,
                        MPFROMLONG(ulPageId),    /* Page ID */
                        MPFROMHWND(hNewFrame));  /* Window within page */
         gPageId[i++] = ulPageId;                  
      }
      }

      /* Add page with no tab OPTIONS_NOTEBOOK Notebook */
      {
      /* Important: assign hNewFrame with a newly created notebook form */
      HWND hNewFrame = OpenO_AUTO(hwndDlg, 0);      /* Window to go within page */
      ULONG ulPageId;        /* Page identifier */
      ulPageId=(ULONG)WinSendDlgItemMsg(hwndDlg, OPTIONS_NOTEBOOK,
                        BKM_INSERTPAGE ,
                        MPFROMLONG(0),
                        MPFROM2SHORT(BKA_STATUSTEXTON|BKA_AUTOPAGESIZE,
                           BKA_LAST));
      if (ulPageId) {
         /* Associate window within page */   WinSetOwner(hNewFrame, WinWindowFromID(hwndDlg, OPTIONS_NOTEBOOK));
         WinSetParent(hNewFrame, WinWindowFromID(hwndDlg, OPTIONS_NOTEBOOK),FALSE);
         WinSendDlgItemMsg(hwndDlg, OPTIONS_NOTEBOOK,
                        BKM_SETPAGEWINDOWHWND,
                        MPFROMLONG(ulPageId),    /* Page ID */
                        MPFROMHWND(hNewFrame));  /* Window within page */
         gPageId[i++] = ulPageId;                  
      }
      }

      /* Add page with no tab OPTIONS_NOTEBOOK Notebook */
      {
      /* Important: assign hNewFrame with a newly created notebook form */
      HWND hNewFrame = OpenO_THREADS(hwndDlg, 0);      /* Window to go within page */
      ULONG ulPageId;        /* Page identifier */
      ulPageId=(ULONG)WinSendDlgItemMsg(hwndDlg, OPTIONS_NOTEBOOK,
                        BKM_INSERTPAGE ,
                        MPFROMLONG(0),
                        MPFROM2SHORT(BKA_STATUSTEXTON|BKA_AUTOPAGESIZE,
                           BKA_LAST));
      if (ulPageId) {
         /* Associate window within page */   WinSetOwner(hNewFrame, WinWindowFromID(hwndDlg, OPTIONS_NOTEBOOK));
         WinSetParent(hNewFrame, WinWindowFromID(hwndDlg, OPTIONS_NOTEBOOK),FALSE);
         WinSendDlgItemMsg(hwndDlg, OPTIONS_NOTEBOOK,
                        BKM_SETPAGEWINDOWHWND,
                        MPFROMLONG(ulPageId),    /* Page ID */
                        MPFROMHWND(hNewFrame));  /* Window within page */
         gPageId[i++] = ulPageId;                  
      }
      }
      /* ##END  */
      }
      break;

   /* Form event Closed WM_CLOSE */
   case WM_CLOSE :
      {
      /* ##START Form.2  */
      /* Event Closed - Form STICKY2\CONFIG */
      CHAR aTextValue[255]="text";
      LONG anIntegerValue=0;
      ULONG anUnsignedValue=0;


      gConfigTerm = 1;

      /* Hide window OPTIONS_NOTEBOOK Notebook */
      WinShowWindow(WinWindowFromID(hwndDlg, OPTIONS_NOTEBOOK),FALSE);
      /* Get page id of first page OPTIONS_NOTEBOOK Notebook */
      {
      ULONG ulPageId=0;        /* Page identifier */
      ulPageId=(ULONG)WinSendDlgItemMsg(hwndDlg, OPTIONS_NOTEBOOK,
                        BKM_QUERYPAGEID ,
                        MPFROMLONG(0),
                        MPFROM2SHORT(BKA_FIRST,0));
        sprintf(aTextValue, "ulPageId = %d", ulPageId);
        MsgLog(aTextValue);
         
        while (ulPageId)  
        {
        anUnsignedValue=(ULONG)WinSendDlgItemMsg(hwndDlg, OPTIONS_NOTEBOOK,
                          BKM_QUERYPAGEWINDOWHWND,
                          MPFROMLONG(ulPageId),    /* Page id */
                          0);
                          
        WinSendMsg(anUnsignedValue, WM_CLOSE, 0, 0);
                          
        ulPageId=(ULONG)WinSendDlgItemMsg(hwndDlg, OPTIONS_NOTEBOOK,
                          BKM_QUERYPAGEID ,
                          MPFROMLONG(ulPageId),
                          MPFROM2SHORT(BKA_NEXT,0));
                          
        sprintf(aTextValue, "ulPageId = %d", ulPageId);
        MsgLog(aTextValue);

        } /* end while */
                        
      }


                        
      /* Delete item OPTIONS_FOLDER Container */
      {
         PCONFIG_OPTIONS_FOLDER_REC pRecord[100];
         USHORT	i=0;
         pRecord[i]=(PCONFIG_OPTIONS_FOLDER_REC)WinSendDlgItemMsg(hwndDlg, OPTIONS_FOLDER,
                           CM_QUERYRECORD,
                           MPFROMP(0), /* pointer to reference record */
                           MPFROM2SHORT(CMA_FIRST, CMA_ITEMORDER));
                         
         while (pRecord[i])
         {
         WinDestroyPointer(pRecord[i]->Record.hptrIcon);
         i++;
         pRecord[i] = (PCONFIG_OPTIONS_FOLDER_REC)WinSendDlgItemMsg(hwndDlg, OPTIONS_FOLDER,
                           CM_QUERYRECORD,
                           MPFROMP(pRecord[i-1]), /* pointer to reference record */
                           MPFROM2SHORT(CMA_NEXT, CMA_ITEMORDER));
         }
         
      sprintf(aTextValue, "Deleting (%d) records from options container", i);
      MsgLog(aTextValue);
         
         if(i)
           WinSendDlgItemMsg(hwndDlg, OPTIONS_FOLDER,
                             CM_REMOVERECORD,
                             MPFROMP(&pRecord), /* array of reference records */
                             MPFROM2SHORT(i,CMA_FREE | CMA_INVALIDATE)); /* delete 1 record */
      }

      gSendConfig = 0;
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
      /* Button DONE_CONFIG Clicked/Selected */
      case DONE_CONFIG:
         {
         /* ##START 1003.0  */
         /* Event Clicked/selected - Done DONE_CONFIG */
         CHAR aTextValue[255]="text";
         LONG anIntegerValue=0;
         ULONG anUnsignedValue=0;


         WinPostMsg(hwndDlg, WM_CLOSE, 0, 0);
         /* ##END  */
         }
         break;
      } /* end switch */
      break;

   case WM_CONTROL :
      switch (SHORT1FROMMP(mp1)) {
      /* Container OPTIONS_FOLDER Event Handlers */
      case OPTIONS_FOLDER:
         switch (SHORT2FROMMP(mp1)) {
         /* Click/Selected */
         case CN_EMPHASIS:
            {
            /* ##START 1000.0  */
            /* Event Click/Selected - Container OPTIONS_FOLDER */
            CHAR aTextValue[255]="text";
            LONG anIntegerValue=0;
            ULONG anUnsignedValue=0;
            /* pointer to a notify record emphasis structure */
            PNOTIFYRECORDEMPHASIS pNotifyRecordEmphasis = PVOIDFROMMP(mp2);

            /* Get first selected item OPTIONS_FOLDER Container */
            {
               PMINIRECORDCORE pRecord;
               ULONG ulPageId;
               CHAR locbuf[128];
               
               pRecord=(PMINIRECORDCORE)WinSendDlgItemMsg(hwndDlg, OPTIONS_FOLDER,
                                 CM_QUERYRECORDEMPHASIS,
                                 MPFROMP(CMA_FIRST), /* pointer to reference record */
                                 MPFROMLONG(CRA_SELECTED));
                                

             if (pRecord)
               {
               switch (pRecord->pszIcon[0])
                 {
                 case 'U':
                   ulPageId = gPageId[0];
                   break;
                 case 'D':
                   ulPageId = gPageId[1];
                   break;   
                 case 'S':
                   ulPageId = gPageId[2];
                   break;
                 case 'N':
                   ulPageId = gPageId[3];
                   break;
                 case 'A':
                   ulPageId = gPageId[4];
                   break;
                 case 'T':
                   ulPageId = gPageId[5];
                   break;
                 default :
                   ulPageId = gPageId[0];
                 } /* end switch */

                 WinSendDlgItemMsg(hwndDlg, OPTIONS_NOTEBOOK,
                              BKM_TURNTOPAGE,
                              MPFROMLONG(ulPageId),    /* Page ID */
                              MPFROMLONG(0));
                 
               }
               
            }
            /* ##END  */
            }
            break;
         } /* end switch */
         break;

      /* Notebook OPTIONS_NOTEBOOK Event Handlers */
      case OPTIONS_NOTEBOOK:
         switch (SHORT2FROMMP(mp1)) {
         /* Page selected */
         case BKN_PAGESELECTED:
            {
            /* ##START 1001.2  */
            /* Event Page selected - Notebook OPTIONS_NOTEBOOK */
            CHAR aTextValue[255]="text";
            LONG anIntegerValue=0;
            ULONG anUnsignedValue=0;
            /* pointer to a page select notify structure */
            PPAGESELECTNOTIFY pPageSelectNotify = PVOIDFROMMP(mp2);
            ULONG ulPageId = pPageSelectNotify->ulPageIdNew;

            if (!gConfigTerm)
            /* Select an item OPTIONS_FOLDER Container */
            {
               PMINIRECORDCORE pRecord;
               INT		i = 0;
               
               while (gPageId[i])
               {
               if (gPageId[i] == ulPageId)
                 break;
               i++;
               } /* end while */
               
               pRecord=(PMINIRECORDCORE)WinSendDlgItemMsg(hwndDlg, OPTIONS_FOLDER,
                                    CM_QUERYRECORD,
                                    MPFROMP(0), /* pointer to reference record */
                                    MPFROM2SHORT(CMA_FIRST, CMA_ITEMORDER));
                  
               if (i<gOptions)
               {
               for ( ;i ;i-- )
                 pRecord = pRecord->preccNextRecord;
               } /* end if */
               
               gSetSelect = 1;
               WinSendDlgItemMsg(hwndDlg, OPTIONS_FOLDER,
                                 CM_SETRECORDEMPHASIS,
                                 MPFROMP(pRecord), /* pointer to reference record */
                                 MPFROM2SHORT(TRUE, CRA_SELECTED));
            }
            /* ##END  */
            }
            break;
         } /* end switch */
         break;

      } /* end switch */
      break;

 /* ##START Form.38 User defined messages */
 /* Code Section User defined messages - Form STICKY2\CONFIG */


 case WM_MINMAXFRAME:
   {
   SWP *swp; 
   char locbuf[128];
   APIRET	rc;
   
   swp = PVOIDFROMMP( mp1 );
  /* hide list box when minimized so it doesn't overwrite icon */
   
   WinShowWindow(WinWindowFromID( hwndDlg, DONE_CONFIG),
           !(swp->fl & SWP_MINIMIZE));
   WinShowWindow(WinWindowFromID( hwndDlg, OPTIONS_FOLDER),
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
HWND OpenCONFIG(HWND hwndOwner, PVOID pInfo)
{
   HWND hwndFrame;
   if (WinQueryWindowUShort(hwndOwner, QWS_ID) == FID_CLIENT)
      hwndOwner = WinQueryWindow(hwndOwner, QW_PARENT);
   hwndFrame =(HWND) WinLoadDlg(HWND_DESKTOP,
           hwndOwner,   
           CONFIGDlgProc, 
           0, ID_CONFIGFORM, 
           pInfo); 
   WinShowWindow(hwndFrame, TRUE);
   return hwndFrame;
}
