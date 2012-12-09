/******************************************************************************/
/*                                                                            */
/* Program: Sticky2.exe                                                       */
/*                                                                            */
/* Description: TCP Sticky Pad                                                */
/*                                                                            */
/* File Name : O_CONFIG.H                                                     */
/*                                                                            */
/* Author : ANDY WYSOCKI                                                      */
/*                                                                            */
/* Copyright 1996 Copyright notice                                            */
/*                                                                            */
/* Generated using VisPro/C serial number VPC5012127                          */
/*                                                                            */
/******************************************************************************/

#ifndef O_CONFIGWINDOW_H
#define O_CONFIGWINDOW_H

 /* ##START Form.39 Form header definitions */
 /* ##END Form header definitions */
HWND OpenO_CONFIG(HWND hwndOwner, PVOID pInfo);

typedef struct _O_CONFIGFORMINFO {
   PSWP pControlSize;   /* Used to handle control sizing */
   /* ##START Form.33 Window structure members */
   /* ##END Window structure members */
} O_CONFIGFORMINFO;
typedef O_CONFIGFORMINFO * PO_CONFIGFORMINFO;
#define ID_FORMTIMER 100   /* Used for timer events */
#endif