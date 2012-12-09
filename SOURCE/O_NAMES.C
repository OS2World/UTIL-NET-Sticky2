/******************************************************************************/
/*                                                                            */
/* Program: Sticky2.exe                                                       */
/*                                                                            */
/* Description: TCP Sticky Pad                                                */
/*                                                                            */
/* File Name : O_NAMES.C                                                      */
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
#include "O_NAMES.RCH"

/* ##START Form.34 Extra include files */
/* Code Section Extra include files - Form STICKY2\O_NAMES */


#include "sticky2.h"
#include "data.h"
#include "pmfuncs.h"

static SHORT sNamesChange = 0;
static PO_NAMES_NAMES_CONTAINER_REC spRecord;

ULONG c_s, c_lnf, c_p, c_rev;
/* ##END Extra include files */
/* declare pointer to main form info block */
extern PMAINFORMINFO pMainFormInfo;

MRESULT EXPENTRY O_NAMESDlgProc(HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  PO_NAMESFORMINFO pO_NAMESFormInfo=(PO_NAMESFORMINFO) WinQueryWindowULong(hwndDlg, QWL_USER);
  HWND hwndFrame = hwndDlg;
 /* ##START Form.37 Top of window procedure */
 /* ##END Top of window procedure */
   switch (msg) {
   /* Form event Opened WM_INITDLG */
   case WM_INITDLG :
     if (mp2==0)
        mp2 = (MPARAM) malloc(sizeof(O_NAMESFORMINFO));
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
     pO_NAMESFormInfo=(PO_NAMESFORMINFO) WinQueryWindowULong(hwndDlg, QWL_USER);
      WinAssociateHelpInstance(pMainFormInfo->hwndHelpInstance, hwndFrame);

      {
         PFIELDINFO pFieldInfo;
         PFIELDINFO pFirstFieldInfo;
         FIELDINFOINSERT fieldInsert;
         CNRINFO cnrInfo;

         pFirstFieldInfo=(PFIELDINFO)WinSendDlgItemMsg(hwndDlg, NAMES_CONTAINER,
                                                   CM_ALLOCDETAILFIELDINFO,
                                                   MPFROMLONG(4),
                                                   0);
         pFieldInfo=pFirstFieldInfo;

         pFieldInfo->cb=sizeof(FIELDINFO);
         pFieldInfo->flData=CFA_BITMAPORICON | CFA_HORZSEPARATOR | CFA_CENTER | CFA_VCENTER | CFA_INVISIBLE | CFA_FIREADONLY;
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
         pFieldInfo->cxWidth=100;
         pFieldInfo=pFieldInfo->pNextFieldInfo;

         pFieldInfo->cb=sizeof(FIELDINFO);
         pFieldInfo->flData=CFA_STRING | CFA_HORZSEPARATOR | CFA_LEFT | CFA_VCENTER | CFA_FIREADONLY;
         pFieldInfo->flTitle=CFA_FITITLEREADONLY | CFA_VCENTER | CFA_CENTER;
         pFieldInfo->pTitleData="Port";
         pFieldInfo->offStruct=sizeof(MINIRECORDCORE)+4;
         pFieldInfo->cxWidth=60;
         pFieldInfo=pFieldInfo->pNextFieldInfo;

         fieldInsert.cb = sizeof(FIELDINFOINSERT);
         fieldInsert.pFieldInfoOrder = (PFIELDINFO)CMA_END;
         fieldInsert.cFieldInfoInsert = 4;
         fieldInsert.fInvalidateFieldInfo = TRUE;
         WinSendDlgItemMsg(hwndDlg, NAMES_CONTAINER,
                           CM_INSERTDETAILFIELDINFO,
                           MPFROMP(pFirstFieldInfo),
                           MPFROMP(&fieldInsert));
         cnrInfo.cb = sizeof(CNRINFO);
         cnrInfo.pFieldInfoLast = pFirstFieldInfo->pNextFieldInfo;
         cnrInfo.xVertSplitbar=79;
         WinSendDlgItemMsg(hwndDlg, NAMES_CONTAINER,
                           CM_SETCNRINFO,
                           MPFROMP(&cnrInfo),
                           MPFROMLONG( CMA_PFIELDINFOLAST | CMA_XVERTSPLITBAR));
      }
      {
      /* ##START Form.1  */
      /* Event Opened - Form STICKY2\O_NAMES */
      CHAR aTextValue[1024];
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

      sNamesChange = 0;
      spRecord = 0;
      c_s = c_lnf = c_p = 0;

        rc = AllocInitSubMem(&g1Meg, ONE_MEG_NAMES);
        if (rc)
          {
          sprintf(locbuf, "Error allocating memory RC=%d", rc);
          MsgLog(locbuf);
          } /* end if */


      SetHwndID(hwndDlg, NAMES_CONTAINER);
       
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


      /* View as details IP_CONTAINER Container */
      {
         CNRINFO cnrinfo;
         SWP 	swp;
         char	locbuf[32];
         
         WinQueryWindowPos(WinWindowFromID(hwndDlg, IP_CONTAINER), &swp);

         if (atol(gSplitPercentC) == -1)
         {
         cnrinfo.xVertSplitbar = (swp.cx * 40) / 100;
         } else {
         cnrinfo.xVertSplitbar = atol(gSplitPercentC);
         } /* end if */

      	
         cnrinfo.cb=sizeof(CNRINFO);
         cnrinfo.flWindowAttr=CV_DETAIL | CA_DETAILSVIEWTITLES | CA_MIXEDTARGETEMPH;
         WinSendDlgItemMsg(hwndDlg, NAMES_CONTAINER,
                           CM_SETCNRINFO,
                           MPFROMP(&cnrinfo),
                           MPFROMLONG(CMA_FLWINDOWATTR | CMA_XVERTSPLITBAR));
      }



      WinCheckButton(hwndDlg, SORT_NAMES, CheckYes(gSortNameList));
      WinCheckButton(hwndDlg, LAST_NAMES, CheckYes(gLastNameFirst));
      WinCheckButton(hwndDlg, P6711_NAMES, CheckYes(gP6711));
      WinCheckButton(hwndDlg, REVERSELOOKUP_NAMES, CheckYes(gReverseLookup));

      if (CheckYes(gP6711))
        {
        WinEnableControl(hwndDlg, PORT_NAMES, FALSE);
        WinEnableControl(hwndDlg, 1003, FALSE);
        }
      /* ##END  */
      }
      break;

   /* Form event Closed WM_CLOSE */
   case WM_CLOSE :
      {
      /* ##START Form.2  */
      /* Event Closed - Form STICKY2\O_NAMES */
      CHAR aTextValue[512];
      LONG anIntegerValue=0;
      ULONG anUnsignedValue=0;
      ULONG saveLNF;

        MsgLog("Closing O_NAMES");
        
        saveLNF = CheckYes(gLastNameFirst);
        
      if (c_s)
      {
      anUnsignedValue=(ULONG)WinQueryButtonCheckstate(hwndDlg,SORT_NAMES);
        strcpy(gSortNameList, anUnsignedValue ? gYes : gNo);    
        PutString(S_SortNameList, gSortNameList); 
      } /* end if */

      if (c_lnf)
      {
      anUnsignedValue=(ULONG)WinQueryButtonCheckstate(hwndDlg,LAST_NAMES);
        strcpy(gLastNameFirst, anUnsignedValue ? gYes : gNo);    
        PutString(S_LastNameFirst, gLastNameFirst); 
      } /* end if */

      if (c_rev)
      {
        anUnsignedValue=(ULONG)WinQueryButtonCheckstate(hwndDlg,REVERSELOOKUP_NAMES);
        strcpy(gReverseLookup, anUnsignedValue ? gYes : gNo);    
        PutString(S_ReverseLookup, gReverseLookup); 
      } /* end if */

      if (c_p)
      {
        anUnsignedValue=(ULONG)WinQueryButtonCheckstate(hwndDlg,P6711_NAMES);
        strcpy(gP6711, anUnsignedValue ? gYes : gNo);    
        PutString(S_Default6711, gP6711); 
      } /* end if */
        

       
        if (sNamesChange)
        {
         PO_NAMES_NAMES_CONTAINER_REC pRecord;
         ULONG	index = 1;
         CHAR		locbuf[64];
         
         PutStringN("", "");  /* Delete all Names */
         
         pRecord=(PO_NAMES_NAMES_CONTAINER_REC)WinSendDlgItemMsg(hwndDlg, NAMES_CONTAINER,
                           CM_QUERYRECORD,
                           MPFROMP(0), /* pointer to reference record */
                           MPFROM2SHORT(CMA_FIRST, CMA_ITEMORDER));
         while (pRecord)
         {
         sprintf(locbuf, "Name%04d", index);
         
         if(saveLNF)
           CvtFirstLast(pRecord->Record.pszIcon, aTextValue);
         PutStringN(locbuf, saveLNF ? aTextValue : pRecord->Record.pszIcon);
         sprintf(locbuf, "Host%04d", index);
         PutStringN(locbuf, pRecord->pszHost);
         if (CheckNo(gP6711))
           {
           sprintf(locbuf, "Port%04d", index);
           PutStringN(locbuf, pRecord->pszPort);
           } /* end if */

         /* Get next item NAMES_CONTAINER Container */
         pRecord=(PO_NAMES_NAMES_CONTAINER_REC)WinSendDlgItemMsg(hwndDlg, NAMES_CONTAINER,
                           CM_QUERYRECORD,
                           MPFROMP(pRecord), /* pointer to reference record */
                           MPFROM2SHORT(CMA_NEXT, CMA_ITEMORDER));
         index++;
         } /* end while */

        sprintf(locbuf, "%d", index-1);
        PutStringN("NameCount", locbuf);
                          
        } /* end if */
        
        {
         CNRINFO cnrinfo;
         SWP 	swp;
         
         WinQueryWindowPos(WinWindowFromID(hwndDlg, NAMES_CONTAINER), &swp);

         cnrinfo.cb=sizeof(CNRINFO);
         cnrinfo.flWindowAttr=CV_DETAIL | CA_DETAILSVIEWTITLES | CA_MIXEDTARGETEMPH;
         WinSendDlgItemMsg(hwndDlg, NAMES_CONTAINER,
                           CM_QUERYCNRINFO,
                           MPFROMP(&cnrinfo),
                           MPFROMLONG(CMA_FLWINDOWATTR | CMA_XVERTSPLITBAR));

        sprintf(gSplitPercentC, "%d", cnrinfo.xVertSplitbar);
        PutString(S_SplitPercentConfig, gSplitPercentC);
        }
        
        WinSendDlgItemMsg(hwndDlg, NAMES_CONTAINER,
                               CM_REMOVERECORD,
                               MPFROMP(0), /* all Records */
                               MPFROM2SHORT(0,CMA_FREE | CMA_INVALIDATE)); /* delete all records */

        FreeAllSubMem(g1Meg);
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
      /* Button DELETE_NAMES Clicked/Selected */
      case DELETE_NAMES:
         {
         /* ##START 1008.0  */
         /* Event Clicked/selected - Delete DELETE_NAMES */
         CHAR aTextValue[255]="text";
         LONG anIntegerValue=0;
         ULONG anUnsignedValue=0;

         PO_NAMES_NAMES_CONTAINER_REC pRecord;

           pRecord=(PO_NAMES_NAMES_CONTAINER_REC)WinSendDlgItemMsg(hwndDlg, NAMES_CONTAINER,
                             CM_QUERYRECORDEMPHASIS,
                             MPFROMP(CMA_FIRST), /* pointer to reference record */
                             MPFROMLONG(CRA_SELECTED));
                             
           anUnsignedValue = 0;                    
           if (CheckYes(gSure))
             {
             anUnsignedValue=(ULONG)WinMessageBox(HWND_DESKTOP, 
                                                  hwndFrame, 
                                                  "Delete Selected Names?", 
                                                  "Delete Names", 
                                                  256, 
                                                  MB_YESNO | MB_INFORMATION | MB_MOVEABLE);
             } /* end if */
                                 
           if (anUnsignedValue == MBID_YES)
             {
             sNamesChange = 1;
             while (pRecord)
             {
               PMINIRECORDCORE pRecs[2];
               MsgLog("Deleting Record");
               FreeSubMem(pRecord->Record.pszIcon, strlen(pRecord->Record.pszIcon)+1);
               FreeSubMem(pRecord->pszHost, strlen(pRecord->pszHost)+1);
               FreeSubMem(pRecord->pszPort, strlen(pRecord->pszPort)+1);
               pRecs[0] = (PMINIRECORDCORE)pRecord;
               
               pRecord=(PO_NAMES_NAMES_CONTAINER_REC)WinSendDlgItemMsg(hwndDlg, NAMES_CONTAINER,
                                 CM_QUERYRECORDEMPHASIS,
                                 MPFROMP(pRecord), /* pointer to reference record */
                                 MPFROMLONG(CRA_SELECTED));

               WinSendDlgItemMsg(hwndDlg, NAMES_CONTAINER,
                                 CM_REMOVERECORD,
                                 MPFROMP(&pRecs), /* array of reference records */
                                 MPFROM2SHORT(1,CMA_FREE | CMA_INVALIDATE)); /* delete 1 record */
               
               }                  
             } /* end if */
         /* ##END  */
         }
         break;
      /* Button MODIFY_NAMES Clicked/Selected */
      case MODIFY_NAMES:
         {
         /* ##START 1009.0  */
         /* Event Clicked/selected - Modify MODIFY_NAMES */
         CHAR aTextValue[512];
         LONG anIntegerValue=0;
         ULONG anUnsignedValue=0;
         CHAR name[512], host[512], port[8];
         int  namelen, hostlen, portlen;
         int  nl, hl, pl;
         PMINIRECORDCORE pRecord;

         if (!spRecord)
         {
           anUnsignedValue=(ULONG)WinMessageBox(HWND_DESKTOP, hwndFrame, "You must 'Double Click' a name before you can modify it.", "No record was selected", 256, MB_OK | MB_INFORMATION | MB_MOVEABLE);
         } else {
           /* Get item text NAME_NAMES Entry Field */
           WinQueryDlgItemText(hwndDlg, NAME_NAMES, sizeof(name), name);
           WinQueryDlgItemText(hwndDlg, HOST_NAMES, sizeof(host), host);
           WinQueryDlgItemText(hwndDlg, PORT_NAMES, sizeof(port), port);    
           
           pRecord = CheckHost(host);
           if (pRecord && pRecord != (PMINIRECORDCORE)spRecord)
           {
           anUnsignedValue=(ULONG)WinMessageBox(HWND_DESKTOP, hwndFrame, "Host name is already in the list, change the host.", "Duplicate Host", 256, MB_OK | MB_INFORMATION | MB_MOVEABLE);  
           } else {
           if (CheckYes(gLastNameFirst))
             CvtLastFirst(name, aTextValue);
           else
             strcpy(aTextValue, name);
             
           anUnsignedValue = inet_addr(host);
           if (anUnsignedValue != INADDR_NONE)
             ReverseLookup((char *)&anUnsignedValue, host);
             
           namelen = strlen(aTextValue)+1;
           hostlen = strlen(host)+1;
           portlen = strlen(port)+1;
           nl = strlen(spRecord->Record.pszIcon)+1;
           hl = strlen(spRecord->pszHost)+1;
           pl = strlen(spRecord->pszPort)+1;

           if (namelen != nl)
             {
             FreeSubMem(g1Meg, spRecord->Record.pszIcon, nl);
             spRecord->Record.pszIcon = (CHAR *)GetSubMem(g1Meg, namelen);
             } /* end if */
           if (hostlen != hl)
             {
             FreeSubMem(g1Meg, spRecord->pszHost, hl);
             spRecord->pszHost = (CHAR *)GetSubMem(g1Meg, hostlen);
             } /* end if */
           if (portlen != pl)
             {
             FreeSubMem(g1Meg, spRecord->pszPort, pl);
             spRecord->pszPort = (CHAR *)GetSubMem(g1Meg, portlen);
             } /* end if */
             
           strcpy(spRecord->Record.pszIcon, aTextValue);
           strcpy(spRecord->pszHost, host);  
           strcpy(spRecord->pszPort, port);
           
           WinSendDlgItemMsg(hwndDlg, NAMES_CONTAINER,
                             CM_INVALIDATERECORD,
                             MPFROMP(&spRecord),
                             MPFROM2SHORT(1,CMA_REPOSITION));

           
           /* Set item text NAME_NAMES Entry Field */
           WinSetDlgItemText(hwndDlg, NAME_NAMES, 0);
           WinSetDlgItemText(hwndDlg, HOST_NAMES, 0);
           WinSetDlgItemText(hwndDlg, PORT_NAMES, 0);
           
           spRecord = 0;
           sNamesChange = 1;  
           } /* end if */



         } /* end if */
         /* ##END  */
         }
         break;
      /* Button ADD_NAMES Clicked/Selected */
      case ADD_NAMES:
         {
         /* ##START 1004.0  */
         /* Event Clicked/selected - Add ADD_NAMES */
         CHAR aTextValue[255]="text";
         LONG anIntegerValue=0;
         ULONG anUnsignedValue=0;
         CHAR name[512], host[512], port[8];
         PMINIRECORDCORE pRecord;

         /* Get item text NAME_NAMES Entry Field */
         WinQueryDlgItemText(hwndDlg, NAME_NAMES, sizeof(name), name);
         WinQueryDlgItemText(hwndDlg, HOST_NAMES, sizeof(host), host);

         /* Is button selected? P6711_NAMES Check Box */
         if (WinQueryButtonCheckstate(hwndDlg,P6711_NAMES))
           strcpy(port, "6711");
         else
           WinQueryDlgItemText(hwndDlg, PORT_NAMES, sizeof(port), port);

         pRecord = CheckHost(host);
         if (pRecord)
         {
           anUnsignedValue=(ULONG)WinMessageBox(HWND_DESKTOP, hwndFrame, "This host is already in the list.  Modify the name to change Name or Port", "Host already in list", 256, MB_OK | MB_INFORMATION | MB_MOVEABLE);
         } else {

           sNamesChange = 1;
           
           anUnsignedValue = inet_addr(host);
           if (anUnsignedValue != INADDR_NONE)
             ReverseLookup((char *)&anUnsignedValue, host);
           
           pRecord = AddName(name, host, port);

           
           SortNames();

           WinSendDlgItemMsg(hwndDlg, NAMES_CONTAINER,
                             CM_SETRECORDEMPHASIS,
                             MPFROMP(pRecord), /* pointer to reference record */
                             MPFROM2SHORT(TRUE, CRA_SELECTED));

         /* Clear text NAME_NAMES Entry Field */
         WinSetDlgItemText(hwndDlg, NAME_NAMES, "");
         /* Clear text HOST_NAMES Entry Field */
         WinSetDlgItemText(hwndDlg, HOST_NAMES, "");
         /* Clear text PORT_NAMES Entry Field */
         WinSetDlgItemText(hwndDlg, PORT_NAMES, "");




         } /* end if */
         /* ##END  */
         }
         break;
      } /* end switch */
      break;

   case WM_CONTROL :
      switch (SHORT1FROMMP(mp1)) {
      /* Container NAMES_CONTAINER Event Handlers */
      case NAMES_CONTAINER:
         switch (SHORT2FROMMP(mp1)) {
         /* Mouse button 1 double click */
         case CN_ENTER:
            {
            /* ##START 1005.3  */
            /* Event Mouse button 1 double click - Container NAMES_CONTAINER */
            CHAR aTextValue[512]="text";
            LONG anIntegerValue=0;
            ULONG anUnsignedValue=0;
            /* pointer to a notify record enter structure */
            PNOTIFYRECORDENTER pNotifyRecordEnter= PVOIDFROMMP(mp2);

            PO_NAMES_NAMES_CONTAINER_REC pRecord;

            pRecord = (PO_NAMES_NAMES_CONTAINER_REC)pNotifyRecordEnter->pRecord;

            spRecord = pRecord;

            /* Set item text NAME_NAMES Entry Field */
            if (CheckYes(gLastNameFirst))
            {
              CvtFirstLast(pRecord->Record.pszIcon, aTextValue);
            } else {
              strcpy(aTextValue, pRecord->Record.pszIcon);
            } /* end if */

            WinSetDlgItemText(hwndDlg, NAME_NAMES, aTextValue);
            WinSetDlgItemText(hwndDlg, HOST_NAMES, pRecord->pszHost);
            WinSetDlgItemText(hwndDlg, PORT_NAMES, pRecord->pszPort);
            /* ##END  */
            }
            break;
         } /* end switch */
         break;

      /* Check Box SORT_NAMES Event Handlers */
      case SORT_NAMES:
         switch (SHORT2FROMMP(mp1)) {
         /* Clicked/Selected */
         case BN_CLICKED:
            {
            /* ##START 1006.0  */
            /* Event Clicked/Selected - Sort SORT_NAMES */
            c_s = 1;
            /* ##END  */
            }
            break;
         } /* end switch */
         break;

      /* Check Box LAST_NAMES Event Handlers */
      case LAST_NAMES:
         switch (SHORT2FROMMP(mp1)) {
         /* Clicked/Selected */
         case BN_CLICKED:
            {
            /* ##START 1007.0  */
            /* Event Clicked/Selected - Last name first LAST_NAMES */
            c_lnf = 1;
            /* ##END  */
            }
            break;
         } /* end switch */
         break;

      /* Check Box P6711_NAMES Event Handlers */
      case P6711_NAMES:
         switch (SHORT2FROMMP(mp1)) {
         /* Clicked/Selected */
         case BN_CLICKED:
            {
            /* ##START 1010.0  */
            /* Event Clicked/Selected - Port 6711  1010 */
            CHAR aTextValue[255]="text";
            LONG anIntegerValue=0;
            ULONG anUnsignedValue=0;

            /* Disable window PORT_NAMES Entry Field */
            anIntegerValue = WinQueryButtonCheckstate(hwndDlg, P6711_NAMES);
            if (anIntegerValue)
            {
            anIntegerValue = 0;
            } else {
            anIntegerValue = 1;
            } /* end if */

            WinEnableControl(hwndDlg, PORT_NAMES, anIntegerValue);

            WinEnableControl(hwndDlg, 1003, anIntegerValue);

            c_p = 1;
            /* ##END  */
            }
            break;
         } /* end switch */
         break;

      /* Check Box REVERSELOOKUP_NAMES Event Handlers */
      case REVERSELOOKUP_NAMES:
         switch (SHORT2FROMMP(mp1)) {
         /* Clicked/Selected */
         case BN_CLICKED:
            {
            /* ##START 1013.0  */
            /* Event Clicked/Selected - Convert IP to host name REVERSELOOKUP_NAMES */
            CHAR aTextValue[255]="text";
            LONG anIntegerValue=0;
            ULONG anUnsignedValue=0;


            c_rev = 1;

            /* Is button selected? REVERSELOOKUP_NAMES Check Box */
            anUnsignedValue=(ULONG)WinQueryButtonCheckstate(hwndDlg,REVERSELOOKUP_NAMES);
            strcpy(gReverseLookup, anUnsignedValue ? "Yes" : "No");
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
HWND OpenO_NAMES(HWND hwndOwner, PVOID pInfo)
{
   HWND hwndFrame;
   if (WinQueryWindowUShort(hwndOwner, QWS_ID) == FID_CLIENT)
      hwndOwner = WinQueryWindow(hwndOwner, QW_PARENT);
   hwndFrame =(HWND) WinLoadDlg(hwndOwner,
           hwndOwner,   
           O_NAMESDlgProc, 
           0, ID_O_NAMESFORM, 
           pInfo); 
   return hwndFrame;
}
