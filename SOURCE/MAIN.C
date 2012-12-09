/******************************************************************************/
/*                                                                            */
/* Program: Sticky2.exe                                                       */
/*                                                                            */
/* Description: TCP Sticky Pad                                                */
/*                                                                            */
/* File Name : Main.C                                                         */
/*                                                                            */
/* Author : ANDREW J. WYSOCKI                                                 */
/*                                                                            */
/* Copyright 1996 Copyright AB Software                                       */
/*                                                                            */
/* Generated using VisPro/C serial number VPC5020318                          */
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
/* ##START Form.43 Pre include files */
/* ##END Pre include files */
#include "MAIN.H"
#include "Sticky2.RCH"
#include "Main.RCH"

/* ##START Form.34 Extra include files */
/* Code Section Extra include files - Form THREAD\Main */

#include "POPUP.H"
#include "POPUP.RCH"
#include "STICKY.H"
#include "STICKY.RCH"
#include "AUTORPLY.H"
#include "AUTORPLY.RCH"
#include "sticky2.h"
#include "data.h"
#include "log.h"
#include "comms.h"
/* ##END Extra include files */
/* declare main forms info block */
PMAINFORMINFO pMainFormInfo;

int main(int argc, char *argv[], char *envp[])                                                  
{                                                                           
  HAB   hab;                                                                
  QMSG  qmsg;                                                               
  HMQ  hmq;                                                               
  HWND  hwndMainFrame;                                                               
  /* Help initialization structure     */                                   
  HELPINIT hmiHelpData;                                                     
                                                                            
  /* ##START Form.40 Top of application procedure */
  /* Code Section Top of application procedure - Form STICKY2\Main */

  {
  char *c_ptr;
  char *l_buf;
  char locbuf[128];

     l_buf = strdup(argv[0]);
     c_ptr = strrchr(l_buf, '\\');
     gDataPath = l_buf;

    if (c_ptr)
      {
      c_ptr++;
      *c_ptr = 0;
      sprintf(gINIFile, "%sSticky2.INI", gDataPath);
      } /* end if */


    if (argc > 1 && isdigit(argv[1][0]))
    {
      strcpy(locbuf, argv[1]);
      strcpy(gSocketString, argv[1]);
    } else {
      GetString(S_Socket, "6711", locbuf, sizeof(locbuf));
    } /* end if */

    
    if (strcmp(locbuf, "6711") != 0)
      {
      strcat(gAppName, "_");
      strcat(gAppName, locbuf);
      } /* end if */


  }
  /* ##END Top of application procedure */
                                                                            
  hab = WinInitialize( 0 );                                                 
  if(!hab) {                                                                
    exit(1);                                                                
  }                                                                         
                                                                            
  hmq = WinCreateMsgQueue( hab, 0 );                                        
  if(!hmq) {                                                                
    WinTerminate(hab);                                                      
    exit(1);                                                                
  }                                                                         
  pMainFormInfo = malloc(sizeof(MAINFORMINFO));
  memset((PVOID) pMainFormInfo, 0, sizeof(MAINFORMINFO));

  /**********************************************************************/  
  /* IPF Initialization Structure                                       */  
  /**********************************************************************/  
  /* size of initialization structure                                   */  
  /**********************************************************************/  
  hmiHelpData.cb = sizeof(HELPINIT);                                        
  /**********************************************************************/  
  /* store HM return code from init.                                    */  
  /**********************************************************************/  
  hmiHelpData.ulReturnCode = (ULONG)NULL;                                   
  /**********************************************************************/  
  /* no tutorial program                                                */  
  /**********************************************************************/  
  hmiHelpData.pszTutorialName = NULL;                                       
  /**********************************************************************/  
  /* indicates help table is defined in the RC file.                    */  
  /**********************************************************************/  
  hmiHelpData.phtHelpTable = (PVOID)(0xffff0000 | 1);                       
  /**********************************************************************/  
  /* action bar is not tailored                                         */  
  /**********************************************************************/  
  hmiHelpData.hmodAccelActionBarModule = 0;                                 
  hmiHelpData.idAccelTable = 0;                                             
  hmiHelpData.idActionBar = 0;                                              
  /**********************************************************************/  
  /* help window title                                                  */  
  /**********************************************************************/  
  hmiHelpData.pszHelpWindowTitle = "Sticky/2";
  /**********************************************************************/  
  /* help table in not in a DLL                                         */  
  /**********************************************************************/  
  hmiHelpData.hmodHelpTableModule = 0;                    
  /**********************************************************************/  
  /* help panels ID is not displayed                                    */  
  /**********************************************************************/  
  hmiHelpData.fShowPanelId = 0;                                             
  hmiHelpData.pszHelpLibraryName = "sticky2.hlp";
  /**********************************************************************/  
  /* Create Instance of IPF pass Anchor Block handle and address of IPF */  
  /* initialization structure, and check that creation was successful.  */  
  /**********************************************************************/  
  pMainFormInfo->hwndHelpInstance = WinCreateHelpInstance(0, &hmiHelpData);                
                                                                            
  if (!pMainFormInfo->hwndHelpInstance || hmiHelpData.ulReturnCode) {                      
    WinAlarm(HWND_DESKTOP,WA_ERROR);                                        
    if (pMainFormInfo->hwndHelpInstance) {                                                 
       WinDestroyHelpInstance(pMainFormInfo->hwndHelpInstance);                            
       pMainFormInfo->hwndHelpInstance=0;                                                  
    }                                                                       
  }                                                                         
  /* ##START Form.35 Application initialization */
  /* ##END Application initialization */

  hwndMainFrame = OpenMain(HWND_DESKTOP, pMainFormInfo);
  if (!hwndMainFrame) {
     WinDestroyMsgQueue( hmq );
     WinTerminate( hab );
     exit(1);
  }

  /* Get and dispatch messages from the application message queue  */
  /* until WinGetMsg returns FALSE, indicating a WM_QUIT message.  */
  while( WinGetMsg( hab, &qmsg, (HWND)NULL, 0, 0 ) )                        
    WinDispatchMsg( hab, &qmsg );                                           
                                                                            
  /* ##START Form.36 Application termination */
  /* ##END Application termination */
  if (pMainFormInfo->hwndHelpInstance) {                                                   
    /* Destroy Help Instance */                                             
    WinDestroyHelpInstance(pMainFormInfo->hwndHelpInstance);                               
  }                                                                         
  WinDestroyWindow(hwndMainFrame);
  WinDestroyMsgQueue( hmq );            /* and                          */  
  WinTerminate( hab );                  /* terminate the application    */  
  return(0);                                                                
}                                                                          
MRESULT EXPENTRY MainDlgProc(HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  PMAINFORMINFO pMainFormInfo=(PMAINFORMINFO) WinQueryWindowULong(hwndDlg, QWL_USER);
  HWND hwndFrame = hwndDlg;
 /* ##START Form.37 Top of window procedure */
 /* Code Section Top of window procedure - Form STICKY2\Main */
 // char locbuf[128];

 // {

 // sprintf(locbuf, "MAIN Msg=%d 0x%x", msg, msg);
 // MsgLog(locbuf);
 // }

 switch (msg)
 {
 //   case WM_ADJUSTFRAMEPOS:
 //      {
 //      SWP *swp;
 //      swp = PVOIDFROMMP(mp1);
 //      sprintf(locbuf, "ADJUSTFRAMEPOS %x y=%d, x=%d", swp->fl, swp->y, swp->x);
 //      MsgLog(locbuf);
 //      }
 //      break;
       
 //   case WM_ADJUSTWINDOWPOS:
 //      {
 //      SWP *swp;
 //      swp = PVOIDFROMMP(mp1);
 //      sprintf(locbuf, "ADJUSTWINDOWPOS %x y=%d, x=%d", swp->fl, swp->y, swp->x);
 //      MsgLog(locbuf);
 //      }
 //      break;
       
 //   case WM_WINDOWPOSCHANGED:
 //      {
 //      SWP *swp;
 //      swp = PVOIDFROMMP(mp1);
 //      sprintf(locbuf, "ADJUSTWINDOWPOS %x y=%d, x=%d", swp->fl, swp->y, swp->x);
 //      MsgLog(locbuf);
 //      }
 //      break;
       
       
    case WM_COMMAND :
       switch (SHORT1FROMMP(mp1)) {
       /* Button SEND_MAIN Clicked/Selected */
       case PUM_SEND:
          WinPostMsg(hwndDlg, msg, MPFROM2SHORT(SEND_MAIN, 0), 0);
          break;
       case PUM_EXIT:
          WinPostMsg(hwndDlg, msg, MPFROM2SHORT(EXIT_MAIN, 0), 0);
          break;
       case PUM_CONFIG:
          WinPostMsg(hwndDlg, msg, MPFROM2SHORT(CONFIG_MAIN, 0), 0);
          break;
       case PUM_CLEAR:
          WinPostMsg(hwndDlg, msg, MPFROM2SHORT(CLEAR_MAIN, 0), 0);
          break;
       case PUM_ABOUT:
          WinPostMsg(hwndDlg, msg, MPFROM2SHORT(ABOUT_MAIN, 0), 0);
          break;
       case PUM_MAXIMIZE:
       WinSetParent(WinWindowFromID(HWND_OBJECT, FID_MINMAX), 
                    hwndFrame, FALSE);
       WinSetParent(WinWindowFromID(HWND_OBJECT, FID_SYSMENU), 
                    hwndFrame, FALSE);    
       WinPostMsg(hwndFrame, WM_UPDATEFRAME, MPFROMLONG(FCF_MINMAX | FCF_SYSMENU), 0);
       WinSetWindowText(WinWindowFromID(hwndFrame, FID_TITLEBAR), "Sticky/2");      
       WinInvalidateRect(hwndFrame, NULL, TRUE);
       
          WinSetWindowPos(hwndDlg, NULLHANDLE, 0, 0, 0, 0, SWP_MAXIMIZE);      
          break;
          
       } /* end switch */
       break;
 } /* end switch */
 /* ##END Top of window procedure */
   switch (msg) {
   /* Form event Opened WM_INITDLG */
   case WM_INITDLG :
     if (mp2==0)
        mp2 = (MPARAM) malloc(sizeof(MAINFORMINFO));
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
     pMainFormInfo=(PMAINFORMINFO) WinQueryWindowULong(hwndDlg, QWL_USER);
      WinAssociateHelpInstance(pMainFormInfo->hwndHelpInstance, hwndFrame);

      {
      /* ##START Form.1  */
      /* Event Opened - Form THREAD\Main */
      CHAR aTextValue[255]="text";
      LONG anIntegerValue=0;
      ULONG anUnsignedValue=0;
      int	index;
      static	char Init=0;
      char Yes[] = "Yes";
      char No[] = "No";
      CHAR *e_ptr;
      SWP tswp;


      gHwndFrame = hwndFrame;


      /* Get item text VERSION_MAIN Text */
      WinQueryDlgItemText(hwndDlg, VERSION_MAIN, sizeof(gVersion), gVersion);

      GetString(S_DebugLog, No, gDebugLog, sizeof(gDebugLog));
      GetString(S_LogSticky, Yes, gLogSticky, sizeof(gLogSticky));
      GetString(S_SendStatus, Yes, gSendStatus, sizeof(gSendStatus));
      GetString(S_SendLines, "200", gSendLines, sizeof(gSendLines));


      GetString(S_CloseAfterSend, No, gAfterSend, sizeof(gAfterSend));
      GetString(S_CloseAfterReply, No, gAfterReply, sizeof(gAfterReply));
      GetString(S_PopUpSticky, Yes, gPUS, sizeof(gPUS));
      GetString(S_Frequency, "2000", gFreq, sizeof(gFreq));
      GetString(S_Duration, "500", gDur, sizeof(gDur));
      GetString(S_Beep, Yes, gBeep, sizeof(gBeep));

      GetString(S_SortNameList, Yes, gSortNameList, sizeof(gSortNameList));
      GetString(S_LastNameFirst, Yes, gLastNameFirst, sizeof(gLastNameFirst));
      //GetString(S_MaxStatus, "100", gMaxStatus, sizeof(gMaxStatus));
      GetString(S_SplitPercentSend, "-1", gSplitPercent, sizeof(gSplitPercent));
      GetString(S_SplitPercentConfig, "-1", gSplitPercentC, sizeof(gSplitPercentC));
      GetString(S_Default6711, Yes, gP6711, sizeof(gP6711));
      GetString(S_AreYouSure, Yes, gSure, sizeof(gSure));
      GetString(S_AutoReply, No, gAutoReply, sizeof(gAutoReply));
      GetString(S_AutoVer, Yes, gAutoVer, sizeof(gAutoVer));
      GetString(S_AutoTime, Yes, gAutoTime, sizeof(gAutoTime));
      GetString(S_AutoName, Yes, gAutoName, sizeof(gAutoName));
      GetString(S_AutoText, "", gAutoText, sizeof(gAutoText));
      GetString(S_StickyIcon, "No", gStickyIcon, sizeof(gStickyIcon));
      GetString(S_ReverseLookup, "Yes", gReverseLookup, sizeof(gReverseLookup));
      GetString(S_ClearAuto, "0", gClearAuto, sizeof(gClearAuto));
      GetString(S_Threads, "1", gThreads, sizeof(gThreads));

          e_ptr = strchr(gAutoText, '~');
          while (e_ptr)
            {
            *e_ptr = '\r';
            e_ptr = strchr(e_ptr, '~');
            } /* end while */
          e_ptr = strchr(gAutoText, '^');
          while (e_ptr)
            {
            *e_ptr = '\n';
            e_ptr = strchr(e_ptr, '^');
            } /* end while */




      GetString(S_Socket, gSocketString, aTextValue, sizeof(aTextValue));
      gSocket = atoi(aTextValue);
      GetString(S_MyName, "", gMyName, sizeof(gMyName));

      if (!Init)
        {
        RecvInit(gSocket, hwndFrame);
        
        for (index=0 ;index < atol(gThreads) ; index++)
          {
          SockInit(index, hwndFrame);
          } /* end for */

        Init=1;
        } /* end if */


      /* Hide window STICKY_ICO Icon */
      WinShowWindow(WinWindowFromID(hwndDlg, STICKY_ICO),FALSE);

      /* Set graphic handle STICKY_ICO Icon */
      /* Important: assign hptr to the icon handle to be used */
      {
        HPOINTER hptr;
        hptr=WinLoadPointer(HWND_DESKTOP, 0L, ICON_BIGSTICKY);

        WinSendDlgItemMsg(hwndDlg, STICKY_ICO,
                        SM_SETHANDLE,
                        MPFROMLONG(hptr),   /* Icon handle */
                        0);
        WinInvalidateRect(WinWindowFromID(hwndDlg, STICKY_ICO),0,TRUE);

      }


      WinQueryWindowPos(hwndDlg, &gSWP);

      MsgLog("Restoring Window Position");
      if(WinRestoreWindowPos("Sticky/2", "WINDOW_POS", hwndDlg) == FALSE)
        {
        SWP swp1, swp2; 
        
        MsgLog("Restore Window Pos not found - Defaults");
          
        WinQueryWindowPos(WinWindowFromID(hwndDlg, SEND_MAIN), &swp1);
        WinQueryWindowPos(WinWindowFromID(hwndDlg, FID_TITLEBAR), &swp2);
                  /* hide list box when minimized so it doesn't overwrite icon */
        WinSetWindowPos(hwndDlg, NULLHANDLE, 0, 0, gSWP.cx, swp1.cy + swp2.cy + 10, SWP_SIZE);
        }
        
        WinQueryWindowPos(hwndDlg, &tswp);

        sprintf(aTextValue, "After Restore -> tswp.fl = %x", tswp.fl);
        MsgLog(aTextValue);

        
        if (tswp.y < 0 || tswp.x < 0)
          {
          WinSetWindowPos(hwndDlg, HWND_TOP, abs(tswp.y), abs(tswp.x), 0, 0, SWP_MOVE);  
          } /* end if */

        if (CheckYes(gStickyIcon) && tswp.fl & SWP_RESTORE)
          {
          MsgLog("Sticky/2 ICON Mode");
          WinSetParent(WinWindowFromID(hwndDlg, FID_MINMAX), HWND_OBJECT, FALSE);
          WinSetParent(WinWindowFromID(hwndDlg, FID_SYSMENU), HWND_OBJECT, FALSE);    
          WinSendMsg(hwndDlg, WM_UPDATEFRAME, MPFROMLONG(FCF_MINMAX | FCF_SYSMENU), 0);
          WinShowWindow(WinWindowFromID( hwndDlg, SEND_MAIN), 0);
          WinShowWindow(WinWindowFromID( hwndDlg, STICKY_ICO), 1);
          WinSetWindowText(WinWindowFromID(hwndFrame, FID_TITLEBAR), 0);
          }
        


      if (strlen(gMyName) == 0)
      {
        anUnsignedValue=(ULONG)WinMessageBox(HWND_DESKTOP, hwndFrame, "Your name is not set.  Config screen will be displayed, please set your name.", "Name not Set", 256, MB_OK | MB_INFORMATION | MB_MOVEABLE);
        WinPostMsg(hwndFrame, WM_COMMAND, MPFROM2SHORT(CONFIG_MAIN, 0), 0);
      } /* end if */
      /* ##END  */
      }
      break;

   /* Form event Closed WM_CLOSE */
   case WM_CLOSE :
      {
      /* ##START Form.2  */
      /* Event Closed - Form STICKY2\Main */
      CHAR aTextValue[255]="text";
      LONG anIntegerValue=0;
      ULONG anUnsignedValue=0;
      SWP swp;

      WinStoreWindowPos("Sticky/2", "WINDOW_POS", hwndFrame);

      WinQueryWindowPos(hwndFrame, &swp);
      MsgLog("Saving Window Location/Position");

      //sprintf(aTextValue, "FL=%x, cy=%x, cx=%x, y=%d, x=%d", swp.fl, swp.cy, swp.cx, swp.y, swp.x);
      //MsgLog(aTextValue);
      /* ##END  */
      }
     WinPostMsg(hwndDlg, WM_QUIT, 0, 0);
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
      /* Button SEND_MAIN Clicked/Selected */
      case SEND_MAIN:
         {
         /* ##START 1000.0  */
         /* Event Clicked/selected - Send  1000 */
         CHAR aTextValue[255]="text";
         LONG anIntegerValue=0;
         ULONG anUnsignedValue=0;

         /* Open the modal form E:\Projects\Sticky2\Send */
         {
            USHORT usReturn;
            HWND hNewFrame;
            hNewFrame = OpenSEND(hwndDlg, 0);
            usReturn = (USHORT) WinProcessDlg(hNewFrame);
         }
         /* ##END  */
         }
         break;
      /* Button CONFIG_MAIN Clicked/Selected */
      case CONFIG_MAIN:
         {
         /* ##START 1001.0  */
         /* Event Clicked/selected - Config CONFIG_MAIN */
         CHAR aTextValue[255]="text";
         LONG anIntegerValue=0;
         ULONG anUnsignedValue=0;



         /* Open the modal form E:\Projects\Sticky2\CONFIG */
         {
            USHORT usReturn;
            HWND hNewFrame;
            hNewFrame = OpenCONFIG(hwndDlg, 0);
            gSendConfig = hNewFrame;
            usReturn = (USHORT) WinProcessDlg(hNewFrame);
         }
         /* ##END  */
         }
         break;
      /* Button CLEAR_MAIN Clicked/Selected */
      case CLEAR_MAIN:
         {
         /* ##START 1002.0  */
         /* Event Clicked/selected - Exit  1002 */
         CHAR aTextValue[255]="text";
         LONG anIntegerValue=0;
         ULONG anUnsignedValue=0;
         HWND	hwndNext;

         hwndNext = WinWindowFromID(HWND_DESKTOP, ID_STICKYFORM);
         sprintf(aTextValue, "hwnd=%d", hwndNext);
         MsgLog(aTextValue);
         while (hwndNext!=NULLHANDLE)
         {
         WinSendMsg(hwndNext, WM_CLOSE, 0, 0);
         hwndNext = WinWindowFromID(HWND_DESKTOP, ID_STICKYFORM);
         sprintf(aTextValue, "hwnd=%d", hwndNext);
         MsgLog(aTextValue);

         } /* end while */

         hwndNext = WinWindowFromID(HWND_DESKTOP, ID_AUTORPLYFORM);
         sprintf(aTextValue, "hwnd=%d", hwndNext);
         MsgLog(aTextValue);

         while (hwndNext!=NULLHANDLE)
         {
         WinSendMsg(hwndNext, WM_CLOSE, 0, 0);
         hwndNext = WinWindowFromID(HWND_DESKTOP, ID_AUTORPLYFORM);
         sprintf(aTextValue, "hwnd=%d", hwndNext);
         MsgLog(aTextValue);

         } /* end while */
         /* ##END  */
         }
         break;
      /* Button EXIT_MAIN Clicked/Selected */
      case EXIT_MAIN:
         {
         /* ##START 1003.0  */
         /* Event Clicked/selected - Exit EXIT_MAIN */
         CHAR aTextValue[255]="text";
         LONG anIntegerValue=0;
         ULONG anUnsignedValue=0;


         WinPostMsg(hwndDlg, WM_CLOSE, 0, 0);
         /* ##END  */
         }
         break;
      /* Button ABOUT_MAIN Clicked/Selected */
      case ABOUT_MAIN:
         {
         /* ##START 1008.0  */
         /* Event Clicked/selected - About ABOUT_MAIN */
         CHAR aTextValue[255]="text";
         LONG anIntegerValue=0;
         ULONG anUnsignedValue=0;


         /* Open the modal form D:\Projects\Sticky2\ABOUT */
         {
            USHORT usReturn;
            HWND hNewFrame;
            hNewFrame = OpenABOUT(hwndDlg, 0);
            usReturn = (USHORT) WinProcessDlg(hNewFrame);
         }
         /* ##END  */
         }
         break;
      } /* end switch */
      break;

 /* ##START Form.38 User defined messages */
 /* Code Section User defined messages - Form STICKY2\Main */

 /* Code Section User defined messages - Form THREAD\Main */
 {
 char	locbuf[128];

 extern MRESULT EXPENTRY STICKYDlgProc(HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2);
 #include "sticky.rch"

 case WM_BUTTON1DBLCLK:
   {
   WinPostMsg(hwndDlg, WM_COMMAND, MPFROM2SHORT(SEND_MAIN, 0), 0);
   }
   break;
   
 case WM_BUTTON2DOWN:
   {
   static HWND hwndPopUpMenu= 0;
   
   if (!hwndPopUpMenu)
     hwndPopUpMenu = WinLoadMenu(HWND_OBJECT, 0, ID_POPUPFORM);
   WinPopupMenu(hwndFrame, hwndFrame, hwndPopUpMenu,
   	       SHORT1FROMMP(mp1), SHORT2FROMMP(mp1), 0,
   	       PU_HCONSTRAIN | PU_VCONSTRAIN | PU_KEYBOARD | PU_MOUSEBUTTON1);
 //  MsgLog("Called WinPopupMenu");  
   }	       
   break;


 case WM_USER_RESTORE:
   {
   SWP swp1, swp2; 
   
   MsgLog("User RESTORE Message");

   if (CheckYes(gStickyIcon))
     {
     MsgLog("Restore from MiniIcon");
     WinQueryWindowPos(WinWindowFromID(hwndDlg, STICKY_ICO), &swp1);
     WinQueryWindowPos(WinWindowFromID(hwndDlg, FID_TITLEBAR), &swp2);
       
     WinSetParent(WinWindowFromID(hwndDlg, FID_MINMAX), HWND_OBJECT, FALSE);
     WinSetParent(WinWindowFromID(hwndDlg, FID_SYSMENU), HWND_OBJECT, FALSE);    
     WinSendMsg(hwndDlg, WM_UPDATEFRAME, MPFROMLONG(FCF_MINMAX | FCF_SYSMENU), 0);
     WinInvalidateRect(hwndFrame, NULL, TRUE);      
       
     WinShowWindow(WinWindowFromID( hwndDlg, SEND_MAIN), 0);
     WinShowWindow(WinWindowFromID( hwndDlg, STICKY_ICO), 1);
                
     WinSetWindowText(WinWindowFromID(hwndFrame, FID_TITLEBAR), 0);      
     WinSetWindowPos(hwndFrame, NULLHANDLE, 0,0, swp1.cx, swp1.cy+swp2.cy+5, SWP_SIZE);
     } 
   else 
     {
     WinShowWindow(WinWindowFromID( hwndDlg, SEND_MAIN), 1);
     WinShowWindow(WinWindowFromID( hwndDlg, STICKY_ICO), 0);
     
     WinSetParent(WinWindowFromID(HWND_OBJECT, FID_MINMAX), hwndFrame, FALSE);
     WinSetParent(WinWindowFromID(HWND_OBJECT, FID_SYSMENU), hwndFrame, FALSE);    
     WinSendMsg(hwndDlg, WM_UPDATEFRAME, MPFROMLONG(FCF_MINMAX | FCF_SYSMENU), 0);
     WinInvalidateRect(hwndFrame, NULL, TRUE);      
     
     WinQueryWindowPos(WinWindowFromID(hwndDlg, CLEAR_MAIN), &swp1);
     WinQueryWindowPos(WinWindowFromID(hwndDlg, FID_TITLEBAR), &swp2);
     WinSetWindowText(WinWindowFromID(hwndFrame, FID_TITLEBAR), "Sticky/2"); 
     sprintf(locbuf, "swp1.cy=%d, swp2.cy=%d", swp1.cy, swp2.cy);
     MsgLog(locbuf);   
     WinSetWindowPos(hwndFrame, NULLHANDLE, 0,0, gSWP.cx, swp1.cy+swp2.cy + 10, SWP_SIZE);    
     } /* end if */
         
   }
   break;

 case WM_USER_STICKY_MSG:
   {
  
   /* Open the form E:\Projects\Sticky2\STICKY */
   {
      HWND hNewFrame;
      hNewFrame = OpenSTICKY(HWND_DESKTOP, 0);

      if (CheckNo(gPUS))
      {
         WinSetWindowPos(hNewFrame, HWND_BOTTOM, 0, 0, 0, 0, SWP_DEACTIVATE);  
      } /* end if */

      
      WinPostMsg(hNewFrame,
                 WM_USER_STICKY_MSG,
                 mp1,
                 mp2);

      if (CheckYes(gBeep))
        DosBeep(atoi(gFreq), atoi(gDur));
                 
               
    }

   }
   break;
   

 case WM_USER_AUTOREPLY:
   {
  
   /* Open the form E:\Projects\Sticky2\STICKY */
   {
      HWND hNewFrame;
      hNewFrame = OpenAUTORPLY(HWND_DESKTOP, 0);

      
      WinPostMsg(hNewFrame,
                 WM_USER_STICKY_MSG,
                 mp1,
                 mp2);

      if (CheckYes(gBeep))
        DosBeep(atoi(gFreq), atoi(gDur));
                 
               
    }
   }
   break;
   
   
   
   
 case WM_USER_STATUS:
   {
   APIRET	rc;
   CHAR		locbuf[255];
   if (CheckYes(gSendStatus))
   {
    
   rc = SetTextError(LONGFROMMP(mp1), LONGFROMMP(mp2), locbuf);

   if (strlen(locbuf))
     anIntegerValue=(LONG)WinSendDlgItemMsg(hwndDlg, STATUS_MAIN,
                       LM_INSERTITEM,
                       MPFROMSHORT(LIT_END),
                       MPFROMP(locbuf));  /* Text for new item */
   

   anIntegerValue=(LONG)WinSendDlgItemMsg(hwndDlg, STATUS_MAIN,
                     LM_QUERYITEMCOUNT, 0, 0);
   
   if (anIntegerValue > atol(gSendLines))
   {
   anIntegerValue=(LONG)WinSendDlgItemMsg(hwndDlg, STATUS_MAIN,
                     LM_DELETEITEM, 0, 0);
   
   } /* end if */


   WinSendDlgItemMsg(hwndDlg, STATUS_MAIN,
                     LM_SETTOPINDEX,
                     MPFROMLONG(anIntegerValue-5), /* Index of item */
                     0);



   } /* end if */
  
   }
   break; 

 }


 case WM_MINMAXFRAME:
   {
   SWP *swp;
   SWP oswp;
   CHAR locbuf[128];
   
   swp = PVOIDFROMMP( mp1 );
   
   /* hide list box when minimized so it doesn't overwrite icon */  
   WinShowWindow(WinWindowFromID( hwndDlg, SEND_MAIN),
           !(swp->fl & SWP_MINIMIZE));
   WinShowWindow(WinWindowFromID( hwndDlg, STICKY_ICO),
           !(swp->fl & SWP_MINIMIZE));


   sprintf(locbuf, "WM_MINMAXFRAME: mp1(swp) fl=%x, y=%d, x=%d", swp->fl, swp->y, swp->x);
   MsgLog(locbuf);

   WinQueryWindowPos(hwndDlg, &oswp);

   sprintf(locbuf, "oswp.fl=%x y=%d, x=%d", oswp.fl, oswp.y, oswp.x);
   MsgLog(locbuf);
   
   if (swp->fl & SWP_MAXIMIZE)
     {
     swp->cx = gSWP.cx;
     swp->cy = gSWP.cy;
     swp->x = gSWP.x;
     swp->y = gSWP.y;
     swp->fl |= SWP_SHOW;
     swp->fl &= ~SWP_HIDE;    
     
     WinShowWindow(WinWindowFromID( hwndDlg, SEND_MAIN), 1);
     WinShowWindow(WinWindowFromID( hwndDlg, STICKY_ICO), 0);
     
     MsgLog("--->>> Maximize");
     } 
   else if (swp->fl & SWP_RESTORE)
     {
     SWP swp1, swp2; 
         
     if (CheckYes(gStickyIcon))
       {
       MsgLog("Restore from MiniIcon");
       WinQueryWindowPos(WinWindowFromID(hwndDlg, STICKY_ICO), &swp1);
       WinQueryWindowPos(WinWindowFromID(hwndDlg, FID_TITLEBAR), &swp2);
       
       WinSetParent(WinWindowFromID(hwndDlg, FID_MINMAX), HWND_OBJECT, TRUE);
       WinSetParent(WinWindowFromID(hwndDlg, FID_SYSMENU), HWND_OBJECT, FALSE);    
       WinSendMsg(hwndDlg, WM_UPDATEFRAME, MPFROMLONG(FCF_MINMAX | FCF_SYSMENU), 0);
       WinInvalidateRect(hwndFrame, NULL, TRUE);      
       
       swp->cy = swp1.cy + swp2.cy + 5;
       swp->cx = swp1.cx;
       swp->x = gSWP.x;
       swp->y = gSWP.y;
       swp->fl |= SWP_SHOW;
       
       WinShowWindow(WinWindowFromID( hwndDlg, SEND_MAIN), 0);
       WinShowWindow(WinWindowFromID( hwndDlg, STICKY_ICO), 1);
                
       WinSetWindowText(WinWindowFromID(hwndFrame, FID_TITLEBAR), 0);      
       
     } else {
       WinQueryWindowPos(WinWindowFromID(hwndDlg, CONFIG_MAIN), &swp1);
       WinQueryWindowPos(WinWindowFromID(hwndDlg, ABOUT_MAIN), &swp2);
       swp->cy = swp1.cy + swp2.cy + 10;
       swp->cx = gSWP.cx;
       swp->x = gSWP.x;
       swp->y = gSWP.y;
       swp->fl |= SWP_SHOW;
       WinSetWindowText(WinWindowFromID(hwndFrame, FID_TITLEBAR), "Sticky/2");
       WinShowWindow(WinWindowFromID( hwndDlg, SEND_MAIN), 1);
       WinShowWindow(WinWindowFromID( hwndDlg, STICKY_ICO), 0);
       
     } /* end if */
         
     MsgLog("--->>> Restore");
     }
   else if (swp->fl & SWP_MINIMIZE)
     {
     MsgLog("--->>> Minimize");
     gSWP.y = oswp.y;
     gSWP.x = oswp.x;
     WinShowWindow(WinWindowFromID( hwndDlg, SEND_MAIN), 0);
     WinShowWindow(WinWindowFromID( hwndDlg, STICKY_ICO), 0);
     
     }
   }
   break;
   
 case WM_MOVE:
   {
   SWP oswp;
   CHAR locbuf[128];
   
    
   WinQueryWindowPos(hwndDlg, &oswp);
   if (!(oswp.fl & SWP_MINIMIZE))
     {
     gSWP.y = oswp.y;
     gSWP.x = oswp.x;
     } /* end if */

   }
   break;
 /* ##END User defined messages */
   default :
     HandleMessage(hwndFrame, hwndDlg, msg, mp1, mp2);
     return WinDefDlgProc(hwndDlg,msg,mp1,mp2);
   } /* end switch for main msg dispatch */
   return (MRESULT)FALSE;
} /* end dialog procedure */
HWND OpenMain(HWND hwndOwner, PVOID pInfo)
{
   HWND hwndFrame;
   if (WinQueryWindowUShort(hwndOwner, QWS_ID) == FID_CLIENT)
      hwndOwner = WinQueryWindow(hwndOwner, QW_PARENT);
   hwndFrame =(HWND) WinLoadDlg(HWND_DESKTOP,
           hwndOwner,   
           MainDlgProc, 
           0, ID_MAINFORM, 
           pInfo); 
   WinShowWindow(hwndFrame, TRUE);
   return hwndFrame;
}
MRESULT HandleMessage(HWND hwndFrame, HWND hwndDlg, ULONG msg, MPARAM mp1, MPARAM mp2)
{
  HENUM  henum;
  HWND   hwndCtl;
  HWND   hwndHScroll;
  HWND   hwndVScroll;
  LONG   lOffset;
  POINTL pointl;
  PSWP   pCtlSize;
  PSWP   pswp;
  PULONG *pWindowInfo;
  RECTL  rectl;
  SWP    swp;
  ULONG  ulCnt;
  switch (msg) {
  /* Default initialization of window */
  case WM_INITDLG:
     WinSetWindowULong(hwndDlg, QWL_USER, (ULONG) mp2);
     pWindowInfo = (PULONG *) mp2;
     if (pWindowInfo)
        *pWindowInfo=0; /* clear out size data pointer */
     if (hwndFrame == hwndDlg) {
        ULONG  ulPicture;
        HACCEL hAccel;
        WinLoadMenu(hwndFrame, 0, WinQueryWindowUShort(hwndFrame, QWS_ID));
        hAccel = WinLoadAccelTable(0,0,WinQueryWindowUShort(hwndFrame, QWS_ID));
        if (hAccel)
           WinSetAccelTable(0, hAccel, hwndFrame);
        WinQueryWindowRect(hwndDlg, &rectl);
        if (WinWindowFromID(hwndFrame, FID_MENU))
           rectl.yTop += WinQuerySysValue(HWND_DESKTOP, SV_CYMENU);
        WinQueryTaskSizePos(0, 0, &swp);
        if (swp.y+rectl.yTop>WinQuerySysValue(HWND_DESKTOP,SV_CYSCREEN)) {
           swp.y=WinQuerySysValue(HWND_DESKTOP,SV_CYSCREEN)-rectl.yTop;
        } /* endif */
        if (swp.x+rectl.xRight>WinQuerySysValue(HWND_DESKTOP,SV_CXSCREEN)) {
           swp.x=WinQuerySysValue(HWND_DESKTOP,SV_CXSCREEN)-rectl.xRight;
        } /* endif */
        WinSetWindowPos(hwndFrame,0,
           swp.x, swp.y, rectl.xRight, rectl.yTop, SWP_SIZE|SWP_MOVE);
        ulPicture=(ULONG) WinLoadPointer(HWND_DESKTOP, 0,
              WinQueryWindowUShort(hwndFrame, QWS_ID));
        if (!ulPicture)
           ulPicture=(ULONG)WinQuerySysPointer(HWND_DESKTOP,SPTR_APPICON,FALSE);
        WinSendMsg(hwndFrame, WM_SETICON, (MPARAM) ulPicture, (MPARAM) 0);
     } else {
        WinSetWindowUShort(hwndDlg, QWS_ID, FID_CLIENT);

        /* Calculate window positioning and size */
        WinQueryWindowRect(hwndDlg, &rectl);
        WinSendMsg(hwndFrame, WM_QUERYBORDERSIZE, (MPARAM)&pointl, 0);
        rectl.xLeft += pointl.x;
        rectl.xRight += pointl.x;
        rectl.yBottom += pointl.y;
        rectl.yTop += pointl.y;

        if (WinWindowFromID(hwndFrame,FID_HORZSCROLL)) {
           rectl.yBottom+=WinQuerySysValue(HWND_DESKTOP,SV_CYHSCROLL);
           rectl.yTop+=WinQuerySysValue(HWND_DESKTOP,SV_CYHSCROLL);
        }
        WinCalcFrameRect(hwndFrame, &rectl, FALSE);

        WinQueryTaskSizePos(0, 0, &swp);
        if (swp.y+rectl.yTop>WinQuerySysValue(HWND_DESKTOP,SV_CYSCREEN)) {
           swp.y=WinQuerySysValue(HWND_DESKTOP,SV_CYSCREEN)-rectl.yTop;
        } /* endif */
        if (swp.x+rectl.xRight>WinQuerySysValue(HWND_DESKTOP,SV_CXSCREEN)) {
           swp.x=WinQuerySysValue(HWND_DESKTOP,SV_CXSCREEN)-rectl.xRight;
        } /* endif */

        WinSetWindowPos(hwndFrame,0,
           swp.x, swp.y, rectl.xRight, rectl.yTop, SWP_SIZE|SWP_MOVE);

        /* Initialize information to handle sizing and scrolling windows */
        pWindowInfo = (PULONG *) mp2;
        if (pWindowInfo)
           *pWindowInfo = 0;

        /* Count number of controls */
        ulCnt=0;
        henum = WinBeginEnumWindows(hwndDlg);
        hwndCtl=WinGetNextWindow(henum);
        while (hwndCtl) {
           ulCnt++;
           hwndCtl=WinGetNextWindow(henum);
        } /* endwhile */
        WinEndEnumWindows(henum);

        pCtlSize = malloc(sizeof(SWP)*(ulCnt+2));

        /* Store client window information first */
        if (pCtlSize) {
           WinQueryWindowPos(hwndDlg, &(pCtlSize[0]));

           /* Query size information on all controls */
           ulCnt=1;
           henum = WinBeginEnumWindows(hwndDlg);
           hwndCtl=WinGetNextWindow(henum);
           while (hwndCtl) {
              if (WinQueryWindowPos(hwndCtl, &(pCtlSize[ulCnt]))) {
                 if (!pCtlSize[ulCnt].cx || !pCtlSize[ulCnt].cy)
                    pCtlSize[ulCnt].hwnd = 0;
                 else
                    ulCnt++;
              }
              hwndCtl=WinGetNextWindow(henum);
           } /* endwhile */
           WinEndEnumWindows(henum);
           pCtlSize[ulCnt].hwnd = 0;
        }
       /* Store number of controls */       pCtlSize[1].ulReserved1 = ulCnt;
        pWindowInfo = (PULONG *) mp2;
        *pWindowInfo = (PULONG) pCtlSize;

        /* If scrollable, initialize scroll bars */
        if (WinWindowFromID(hwndFrame,FID_HORZSCROLL)) {
           HandleMessage(hwndFrame, hwndDlg, WM_SIZE, 0, 0);
        }
     }
     break;
  /* Default WM_SIZE for sizeable or scrollable windows */
  case WM_SIZE:
     if (hwndFrame==hwndDlg)
        return 0;
     pWindowInfo = (PULONG *) WinQueryWindowULong(hwndDlg, QWL_USER);
     if (!pWindowInfo)
        return 0;
     pCtlSize = (PSWP) *pWindowInfo;
     if (!pCtlSize)
        return 0;
     if (!WinQueryWindowPos(hwndDlg,&swp))
        return 0;
     if (!swp.cx || !swp.cy)
        return 0;

     /* Handle sizing of scrollable window */
     hwndHScroll=WinWindowFromID(hwndFrame,FID_HORZSCROLL);
     hwndVScroll=WinWindowFromID(hwndFrame,FID_VERTSCROLL);

     if (hwndHScroll && hwndVScroll) {
        /* Get viewable size of client area */
        WinQueryWindowRect(hwndFrame, &rectl);
        WinCalcFrameRect(hwndFrame, &rectl, TRUE);

        if (pCtlSize[0].cx<=rectl.xRight) {
           pCtlSize[0].x = 0;
           WinEnableWindow(hwndHScroll,FALSE);
           WinSendMsg(hwndHScroll,SBM_SETSCROLLBAR,MPFROMSHORT(0),
                      MPFROM2SHORT(0,0));
           WinSendMsg(hwndHScroll,SBM_SETTHUMBSIZE,
                      MPFROM2SHORT(0,0),0);
        } else {
           pCtlSize[0].x = pCtlSize[0].cx-rectl.xRight+rectl.xLeft;
           pCtlSize[0].ulReserved1= 0;
           WinEnableWindow(hwndHScroll,TRUE);
           WinSendMsg(hwndHScroll,SBM_SETSCROLLBAR,
                      MPFROMSHORT(pCtlSize[0].ulReserved1),
                      MPFROM2SHORT(0,pCtlSize[0].x));
           WinSendMsg(hwndHScroll,SBM_SETTHUMBSIZE,
                      MPFROM2SHORT(rectl.xRight,pCtlSize[0].cx),0);
        } /* endif */
        if (pCtlSize[0].cy<=rectl.yTop) {
           pCtlSize[0].y = 0;
           WinEnableWindow(hwndVScroll,FALSE);
           WinSendMsg(hwndVScroll,SBM_SETSCROLLBAR,MPFROMSHORT(0),
                      MPFROM2SHORT(0,0));
           WinSendMsg(hwndVScroll,SBM_SETTHUMBSIZE,
                      MPFROM2SHORT(0,0),0);
        } else {
           pCtlSize[0].y = pCtlSize[0].cy-rectl.yTop+rectl.yBottom;
           pCtlSize[0].ulReserved2= pCtlSize[0].y;
           WinEnableWindow(hwndVScroll,TRUE);
           WinSendMsg(hwndVScroll,SBM_SETSCROLLBAR,
                      MPFROMSHORT(pCtlSize[0].ulReserved2),
                      MPFROM2SHORT(0,pCtlSize[0].y));
           WinSendMsg(hwndVScroll,SBM_SETTHUMBSIZE,
                      MPFROM2SHORT(rectl.yTop, pCtlSize[0].cy),0);
        } /* endif */
        ulCnt = 1;
        hwndCtl=pCtlSize[ulCnt].hwnd;
        while (hwndCtl) {
           WinSetWindowPos(hwndCtl, 0, pCtlSize[ulCnt].x,
              pCtlSize[ulCnt].y-pCtlSize[0].y+pCtlSize[0].ulReserved2,
              0, 0, SWP_MOVE);
           ulCnt++;
           hwndCtl=pCtlSize[ulCnt].hwnd;
        }

     }
     /* Handle sizing of a regular sizeable window */
     else {
        SWP   swpCtl;
        SWP   swpTest;
        ulCnt = 1;
        hwndCtl=pCtlSize[ulCnt].hwnd;
        while (hwndCtl) {
           swpCtl.x = (pCtlSize[ulCnt].x * swp.cx)/pCtlSize[0].cx;
           swpCtl.y = (pCtlSize[ulCnt].y * swp.cy)/pCtlSize[0].cy;
           swpCtl.cx = (pCtlSize[ulCnt].cx * swp.cx)/pCtlSize[0].cx;
           swpCtl.cy = (pCtlSize[ulCnt].cy * swp.cy)/pCtlSize[0].cy;
           WinSetWindowPos(hwndCtl, 0, swpCtl.x, swpCtl.y, swpCtl.cx, swpCtl.cy, SWP_MOVE | SWP_SIZE);

           /* If needed, adjust the control position */
           WinQueryWindowPos(hwndCtl,&swpTest);
           if (swpTest.x != swpCtl.x || swpTest.y != swpCtl.y) {
              swpCtl.x += (swpCtl.x - swpTest.x);
              swpCtl.y += (swpCtl.y - swpTest.y);
              swpCtl.cx += (swpCtl.cx - swpTest.cx);
              swpCtl.cy += (swpCtl.cy - swpTest.cy);
              WinSetWindowPos(hwndCtl, 0, swpCtl.x, swpCtl.y, swpCtl.cx, swpCtl.cy, SWP_MOVE | SWP_SIZE);
           }
           ulCnt++;
           hwndCtl=pCtlSize[ulCnt].hwnd;
        }
     }
     break;
  /* If position changed, force a WM_SIZE message  */
  case WM_WINDOWPOSCHANGED:
     if (hwndFrame!=hwndDlg) {
        pWindowInfo = (PULONG *) WinQueryWindowULong(hwndDlg, QWL_USER );
        if (!pWindowInfo)
           return 0;
        pCtlSize = (PSWP) *pWindowInfo;
        if (pCtlSize) {
           pswp = (PSWP) mp1;
           if ((pswp[0].cx != pswp[1].cx) || (pswp[0].cy != pswp[1].cy))
              WinSendMsg(hwndDlg, WM_SIZE, MPFROM2SHORT(pswp[1].cx, pswp[1].cy),
                   MPFROM2SHORT(pswp[0].cx, pswp[0].cy));
        }
     }
     break;
  /* Default handling for WM_CLOSE */
  case WM_CLOSE:
     WinDismissDlg(hwndFrame, DID_CANCEL);
     WinDestroyWindow(hwndFrame);
     break;
  case WM_HSCROLL:
     if (hwndFrame==hwndDlg)
        return 0;
     pWindowInfo = (PULONG *) WinQueryWindowULong(hwndDlg, QWL_USER);
     if (!pWindowInfo)
        return 0;
     pCtlSize = (PSWP) *pWindowInfo;
     if (!pCtlSize)
        return 0;
     hwndHScroll=WinWindowFromID(hwndFrame,FID_HORZSCROLL);
     lOffset = pCtlSize[0].ulReserved1;
     switch (SHORT2FROMMP(mp2)) {
     case SB_LINELEFT:
        lOffset--;
        break;
     case SB_LINERIGHT:
        lOffset++;
        break;
     case SB_PAGELEFT:
        WinQueryWindowRect(hwndFrame, &rectl);
        WinCalcFrameRect(hwndFrame, &rectl, TRUE);
        lOffset-=rectl.xRight;
        break;
     case SB_PAGERIGHT:
        WinQueryWindowRect(hwndFrame, &rectl);
        WinCalcFrameRect(hwndFrame, &rectl, TRUE);
        lOffset+=rectl.xRight;
        break;
     case SB_SLIDERTRACK:
     case SB_SLIDERPOSITION:
        lOffset = SHORT1FROMMP(mp2);
        break;
     } /* endswitch */

     if (lOffset < 0)
        lOffset = 0;
     if (lOffset > pCtlSize[0].x)
        lOffset = pCtlSize[0].x;
     if (lOffset > pCtlSize[0].ulReserved1) {
        ulCnt = 1;
        hwndCtl=pCtlSize[ulCnt].hwnd;
        while (hwndCtl) {
           WinSetWindowPos(hwndCtl, 0, pCtlSize[ulCnt].x-lOffset,
              pCtlSize[ulCnt].y-pCtlSize[0].y+pCtlSize[0].ulReserved2,
              0, 0, SWP_MOVE );
           ulCnt++;
           hwndCtl=pCtlSize[ulCnt].hwnd;
        }
        pCtlSize[0].ulReserved1 = lOffset;
        WinSendMsg(hwndHScroll,SBM_SETPOS, MPFROMSHORT(lOffset),0);
     } /* endif */
     else
     if (lOffset < pCtlSize[0].ulReserved1) {
        ulCnt = pCtlSize[1].ulReserved1;
        while (ulCnt >0) {
           hwndCtl=pCtlSize[ulCnt].hwnd;
           WinSetWindowPos(hwndCtl, 0, pCtlSize[ulCnt].x-lOffset,
              pCtlSize[ulCnt].y-pCtlSize[0].y+pCtlSize[0].ulReserved2,
              0, 0, SWP_MOVE);
           ulCnt--;
        }
        pCtlSize[0].ulReserved1 = lOffset;
        WinSendMsg(hwndHScroll,SBM_SETPOS, MPFROMSHORT(lOffset),0);
     } /* endif */
     break;
  case WM_VSCROLL:
     if (hwndFrame==hwndDlg)
        return 0;
     pWindowInfo = (PULONG *) WinQueryWindowULong(hwndDlg, QWL_USER);
     if (!pWindowInfo)
        return 0;
     pCtlSize = (PSWP) *pWindowInfo;
     if (!pCtlSize)
        return 0;
     hwndVScroll=WinWindowFromID(hwndFrame,FID_VERTSCROLL);
     lOffset = pCtlSize[0].ulReserved2;
     switch (SHORT2FROMMP(mp2)) {
     case SB_LINEUP:
        lOffset--;
        break;
     case SB_LINEDOWN:
        lOffset++;
        break;
     case SB_PAGEUP:
        WinQueryWindowRect(hwndFrame, &rectl);
        WinCalcFrameRect(hwndFrame, &rectl, TRUE);
        lOffset-=rectl.yTop;
        break;
     case SB_PAGEDOWN:
        WinQueryWindowRect(hwndFrame, &rectl);
        WinCalcFrameRect(hwndFrame, &rectl, TRUE);
        lOffset+=rectl.yTop;
        break;
     case SB_SLIDERTRACK:
     case SB_SLIDERPOSITION:
        lOffset = SHORT1FROMMP(mp2);  /* verified should be positive */
        break;
     } /* endswitch */

     if (lOffset < 0)
        lOffset = 0;
     if (lOffset > pCtlSize[0].y)
        lOffset = pCtlSize[0].y;
     if (lOffset < pCtlSize[0].ulReserved2) {
        ulCnt = 1;
        hwndCtl=pCtlSize[ulCnt].hwnd;
        while (hwndCtl) {
           WinSetWindowPos(hwndCtl, 0,
              pCtlSize[ulCnt].x-pCtlSize[0].ulReserved1,
              pCtlSize[ulCnt].y-pCtlSize[0].y+lOffset, 0, 0, SWP_MOVE);
           ulCnt++;
           hwndCtl=pCtlSize[ulCnt].hwnd;
        }
        pCtlSize[0].ulReserved2 = lOffset;
        WinSendMsg(hwndVScroll,SBM_SETPOS, MPFROMSHORT(lOffset),0);
     } /* endif */
    else
    if (lOffset > pCtlSize[0].ulReserved2) {
       ulCnt = pCtlSize[1].ulReserved1;
       while (ulCnt > 0) {
          hwndCtl=pCtlSize[ulCnt].hwnd;
          WinSetWindowPos(hwndCtl, 0,
             pCtlSize[ulCnt].x-pCtlSize[0].ulReserved1,
             pCtlSize[ulCnt].y-pCtlSize[0].y+lOffset, 0, 0, SWP_MOVE);
          ulCnt--;
       }
       pCtlSize[0].ulReserved2 = lOffset;
       WinSendMsg(hwndVScroll,SBM_SETPOS, MPFROMSHORT(lOffset),0);
    } /* endif */
     break;
  /* When window is destroyed, deallocate window memory */
  case WM_DESTROY:
     pWindowInfo = (PULONG *) WinQueryWindowULong(hwndDlg, QWL_USER);
     if (pWindowInfo) {
        pCtlSize = (PSWP) *pWindowInfo;
        if (pCtlSize)
           free(pCtlSize);
        free(pWindowInfo);
        WinSetWindowULong(hwndDlg, QWL_USER, 0L);
     }
     break;
  }
  return (MRESULT) FALSE;
}

/***************************************************************/
/* MLEGetItemText                                              */
/*                                                             */
/* Description:                                                */
/*                                                             */
/* This helper function is used easily retrieve all or part    */
/* of the text within an MLE.  There is no limit on the amount */
/* of text to be retrieved.                                    */
/*                                                             */
/* Parameters:                                                 */
/*                                                             */
/*    hwndDlg      - handle to window containing the MLE       */
/*    ulID         - MLE identifier                            */
/*    lIptPosition - Starting IPT position to get value        */
/*                   Use 0 to start at the beginning           */
/*                   Use -1 to start at the cursor position    */
/*    lBoundary    - Number of characters to get               */
/*                   Used -1 to get characters until the end   */
/*    ppText       - Pointer to receive a pointer to text area */
/***************************************************************/
ULONG MLEGetItemText(HWND hwndDlg, ULONG ulID, LONG lIptPosition,
      LONG lBoundary, PBYTE *ppText)
{
  ULONG ulTextSize;
  PBYTE pText=0;
  HWND  hwndControl = WinWindowFromID(hwndDlg, ulID);

  /* Get text length */
  ulTextSize = (LONG)WinSendMsg(hwndControl,MLM_QUERYFORMATTEXTLENGTH,MPFROMLONG(lIptPosition),MPFROMLONG(lBoundary));
  if (ulTextSize>0) {
     PBYTE pMLEBuff=0;
     ULONG ulBuffSize;
     pText = malloc(ulTextSize);

     /* Allocate MLE transfer buffer. MLE limited to 64K tiled memory */
     ulBuffSize = 65535;
     if (pText && !DosAllocMem((PPVOID) &pMLEBuff, (ULONG) ulBuffSize,
                PAG_COMMIT | PAG_READ | PAG_WRITE | OBJ_TILE)) {
        ULONG ulBytesCopied=0;
        ULONG ulBytesToCopy;
        ULONG ulTransfer;

        /* Set import/export MLE buffer */
        WinSendMsg(hwndControl, MLM_SETIMPORTEXPORT,
           MPFROMP(pMLEBuff), MPFROMLONG( ulBuffSize));

        do {
           if (ulBuffSize < ulTextSize-ulBytesCopied)
              ulBytesToCopy=ulBuffSize;
           else
              ulBytesToCopy=ulTextSize-ulBytesCopied;

           /* Get text at given IPT */
           ulTransfer = (ULONG) WinSendMsg(hwndControl,
                    MLM_EXPORT,
                    MPFROMLONG(&lIptPosition), MPFROMLONG(&ulBytesToCopy));

           if (!ulTransfer)
              ulBytesCopied=ulTextSize;
           else {
              memcpy((PVOID)&(pText[ulBytesCopied]),
                     (PVOID)pMLEBuff, ulTransfer);
              ulBytesCopied+=ulTransfer;
           }
        } while (ulBytesCopied < ulTextSize);

        /* Free MLE transfer buffer */
        DosFreeMem((PBYTE)pMLEBuff);
     }
  }
  pText[ulTextSize]=0;
  *ppText = pText;
  return ulTextSize;
}

/***************************************************************/
/* MLEInsertText                                               */
/*                                                             */
/* Description:                                                */
/*                                                             */
/* This helper function is used easily insert text within the  */
/* MLE.  There is no limit on the amount of text to be inserted*/
/*                                                             */
/* Parameters:                                                 */
/*                                                             */
/*    hwndDlg      - handle to window containing the MLE       */
/*    ulID         - MLE identifier                            */
/*    lIptPosition - IPT to insert text                        */
/*                   Use 0 to start at the beginning           */
/*                   Use -1 to start at the cursor position    */
/*    pText        - Pointer to text area                      */
/***************************************************************/
ULONG MLEInsertText(HWND hwndDlg, ULONG ulID, LONG iptPosition, PBYTE pText)
{
  PBYTE pMLEBuff=0;
  ULONG ulBuffSize;
  ULONG ulBytesCopied=0;
  HWND  hwndControl = WinWindowFromID(hwndDlg, ulID);

  /* Allocate MLE transfer buffer. MLE limited to 64K tiled memory */
  ulBuffSize = 65535;
  if (!DosAllocMem((PPVOID) &pMLEBuff, (ULONG) ulBuffSize,
             PAG_COMMIT | PAG_READ | PAG_WRITE | OBJ_TILE)) {
     ULONG ulBytesToCopy;
     ULONG ulTextSize = strlen((char *)pText);

     /* Set import/export MLE buffer */
     WinSendMsg(hwndControl, MLM_SETIMPORTEXPORT,
           MPFROMP(pMLEBuff), MPFROMLONG( ulBuffSize));
     do {
        if (ulBuffSize < ulTextSize-ulBytesCopied)
           ulBytesToCopy=ulBuffSize;
        else
           ulBytesToCopy=ulTextSize-ulBytesCopied;
        memcpy((PVOID) pMLEBuff, &(pText[ulBytesCopied]),
                     ulBytesToCopy);

        /* Insert text at given IPT */
        WinSendMsg(hwndControl, MLM_IMPORT,
                 (MPARAM) &iptPosition, (MPARAM) ulBytesToCopy);
        ulBytesCopied+=ulBytesToCopy;
     } while (ulBytesCopied < ulTextSize);

     /* Free MLE transfer buffer */
     DosFreeMem((PBYTE)pMLEBuff);
  }
  return ulBytesCopied;
}
