/******************************************************************************/
/*                                                                            */
/* Program: STICKY/2                                                          */
/*                                                                            */
/* Description: Description                                                   */
/*                                                                            */
/* File Name : PMFUNCS.C                                                      */
/*                                                                            */
/* Author : ANDREW J. WYSOCKI                                                 */
/*                                                                            */
/* Copyright 1994 Copyright notice                                            */
/*                                                                            */
/******************************************************************************/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <io.h>
#include <fcntl.h>
#include <sys\stat.h>
#include "sticky2.h"
#include "pmfuncs.h"
#include "data.h"
#include "comms.h"
#include "Main.h"
#include "Main.RCH"


typedef struct _MRC {
   MINIRECORDCORE       Record;
   PSZ                  pszHost;
   PSZ                  pszPort;
   } NAMEENTRY, *PNAMEENTRY;
static HWND     sHwnd;
static ULONG    sID;

/*****************************************************************************/
/*                                                                           */
/*****************************************************************************/
void
SetHwndID(HWND _hwnd, ULONG _id)
{
   sHwnd = _hwnd;
   sID   = _id;
}


/*****************************************************************************/
/*                                                                           */
/*****************************************************************************/
PMINIRECORDCORE
AddName(char *_Name, char *_Host, char *_Port)
{
char    aTextValue[255];
PNAMEENTRY pRecord;
RECORDINSERT    RecordInsert;




  if (CheckYes(gLastNameFirst))
    CvtLastFirst(_Name, aTextValue);
  else
    strcpy(aTextValue, _Name);

  /* Add a container record to end of the Container */

   /* IMPORTANT!!! we allocate 32 extra bytes for the pszIcon string */
   /* We must allocate more than that if we have any extra PSZ members */
   /* as columns */
   /* Two extra columns */
   pRecord=(PVOID)WinSendDlgItemMsg(sHwnd, sID,
                  CM_ALLOCRECORD,
                  MPFROMLONG(sizeof(*pRecord)-sizeof(MINIRECORDCORE)+32), /* Bytes of additional data */
                  MPFROMLONG(1));                  /* Number of records        */
   pRecord->Record.cb=sizeof(MINIRECORDCORE);
   pRecord->Record.flRecordAttr=0;
   pRecord->Record.hptrIcon=0;
   pRecord->Record.pszIcon = (PVOID)GetSubMem(g1Meg, strlen(aTextValue)+1);
   if (pRecord->Record.pszIcon)
     strcpy(pRecord->Record.pszIcon, aTextValue);

   pRecord->pszHost = (PSZ)GetSubMem(g1Meg, strlen(_Host)+1);
   if (pRecord->pszHost)
     strcpy(pRecord->pszHost, _Host);

   pRecord->pszPort = (PSZ)GetSubMem(g1Meg, strlen(_Port)+1);
   if (pRecord->pszPort)
     strcpy(pRecord->pszPort, _Port);


/* IMPORTANT!!! initiaize other members here if they exist */
   /* add the item to the container */

   RecordInsert.cb=sizeof(RECORDINSERT);
   RecordInsert.pRecordOrder=(PRECORDCORE)CMA_END;/* add to the end */
   RecordInsert.pRecordParent=(PRECORDCORE)0;     /* not a child record */
   RecordInsert.zOrder=CMA_TOP;
   RecordInsert.cRecordsInsert=1;
   RecordInsert.fInvalidateRecord=TRUE;           /* repaint the record */
   WinSendDlgItemMsg(sHwnd, sID,
                     CM_INSERTRECORD,
                     MPFROMP(pRecord),
                     MPFROMP(&RecordInsert));



//   WinSendDlgItemMsg(hwndDlg, NAMES_CONTAINER,
//                     CM_SETRECORDEMPHASIS,
//                     MPFROMP(pRecord), /* pointer to reference record */
//                     MPFROM2SHORT(TRUE, CRA_SELECTED));

return((PMINIRECORDCORE)pRecord);
}


/*****************************************************************************/
/*****************************************************************************/
APIRET
SortNames()
{
     if (CheckYes(gSortNameList))
     {
     PMINIRECORDCORE pRecord;
     WinSendDlgItemMsg(sHwnd, sID,
                       CM_SORTRECORD,
                       MPFROMP(pfnCompare), 0);

     /* Get first item NAMES_CONTAINER Container */
     pRecord=(PMINIRECORDCORE)WinSendDlgItemMsg(sHwnd, sID,
                              CM_QUERYRECORD,
                              MPFROMP(0), /* pointer to reference record */
                              MPFROM2SHORT(CMA_FIRST, CMA_ITEMORDER));

     WinSendDlgItemMsg(sHwnd, sID,
                       CM_SETRECORDEMPHASIS,
                       MPFROMP(pRecord), /* pointer to reference record */
                       MPFROM2SHORT(TRUE, CRA_SELECTED));
     }

}

/*****************************************************************************/
/*****************************************************************************/
PMINIRECORDCORE
CheckHost(char *_Host)
{
PNAMEENTRY pRecord;
char locbuf[512];
  sprintf(locbuf, "Checking Host for duplicate [%-100.100s]", _Host);
  MsgLog(locbuf);


  /* Get first item NAMES_CONTAINER Container */
  pRecord=(PNAMEENTRY)WinSendDlgItemMsg(sHwnd, sID,
                                        CM_QUERYRECORD,
                                        MPFROMP(0), /* pointer to reference record */
                                        MPFROM2SHORT(CMA_FIRST, CMA_ITEMORDER));

  while (pRecord) {
     if (pRecord->pszHost[0] == _Host[0] && strcmp(pRecord->pszHost, _Host) == 0)
        return((PMINIRECORDCORE)pRecord);

     sprintf(locbuf, "pRecord [%100.100s] Next->%x", pRecord->pszHost, pRecord->Record.preccNextRecord);
     MsgLog(locbuf);

     pRecord=(PNAMEENTRY)WinSendDlgItemMsg(sHwnd, sID,
                       CM_QUERYRECORD,
                       MPFROMP(pRecord), /* pointer to reference record */
                       MPFROM2SHORT(CMA_NEXT, CMA_ITEMORDER));

//     pRecord = (PNAMEENTRY)pRecord->Record.preccNextRecord;

  } /* endwhile */
return(0);
}

/*****************************************************************************/
/*                                                                           */
/*****************************************************************************/
void
CvtFirstLast(char *_Name, char *_CvtName)
{
char    *first, *last;
char    *name;

  name = strdup(_Name);
  last  = name;
  first = strrchr(name, ',');
  if (first) {
     *first = 0;
     first += 2;
     sprintf(_CvtName, "%s %s", first, last);
  } else {
     strcpy(_CvtName, name);
  } /* endif */
  free(name);
}

/*****************************************************************************/
/*                                                                           */
/*****************************************************************************/
void
CvtLastFirst(char *_Name, char *_CvtName)
{
char    *first, *last;
char    *name;

  name = strdup(_Name);

  first = name;
  last = strrchr(name, ' ');
  if (last)
    {
    *last = 0;
    last++;
    sprintf(_CvtName, "%s, %s", last, first);
    }
  else
    {
    strcpy(_CvtName, first);
    } /* end if */

  free(name);
}


/*****************************************************************************/
/*                                                                           */
/*****************************************************************************/
CHAR *
TextChanged(HWND _hwnd, ULONG _id)
{
static char locbuf[512];

  if ((ULONG)WinSendDlgItemMsg(_hwnd, _id, EM_QUERYCHANGED , 0, 0))
     {
     WinQueryDlgItemText(_hwnd, _id, sizeof(locbuf), locbuf);
     return(locbuf);
     }

return(0);
}

