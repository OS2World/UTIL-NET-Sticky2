/******************************************************************************/
/*                                                                            */
/* Program: Sticky2.exe                                                       */
/*                                                                            */
/* Description: TCP Sticky Pad                                                */
/*                                                                            */
/* File Name : O_NAMES.H                                                      */
/*                                                                            */
/* Author : ANDY WYSOCKI                                                      */
/*                                                                            */
/* Copyright 1996 Copyright notice                                            */
/*                                                                            */
/* Generated using VisPro/C serial number VPC5012127                          */
/*                                                                            */
/******************************************************************************/

#ifndef O_NAMESWINDOW_H
#define O_NAMESWINDOW_H

 /* ##START Form.39 Form header definitions */
 /* ##END Form header definitions */
HWND OpenO_NAMES(HWND hwndOwner, PVOID pInfo);

typedef struct _O_NAMESFORMINFO {
   PSWP pControlSize;   /* Used to handle control sizing */
   /* ##START Form.33 Window structure members */
   /* ##END Window structure members */
} O_NAMESFORMINFO;
typedef O_NAMESFORMINFO * PO_NAMESFORMINFO;
typedef struct _O_NAMES_NAMES_CONTAINER_REC {
   MINIRECORDCORE Record;
   PSZ pszHost;
   PSZ pszPort;
} O_NAMES_NAMES_CONTAINER_REC;
typedef O_NAMES_NAMES_CONTAINER_REC * PO_NAMES_NAMES_CONTAINER_REC;
#define ID_FORMTIMER 100   /* Used for timer events */
#endif