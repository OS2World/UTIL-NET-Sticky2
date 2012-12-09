/******************************************************************************/
/*                                                                            */
/* Program: Sticky2.exe                                                       */
/*                                                                            */
/* Description: TCP Sticky Pad                                                */
/*                                                                            */
/* File Name : O_USER.H                                                       */
/*                                                                            */
/* Author : ANDY WYSOCKI                                                      */
/*                                                                            */
/* Copyright 1996 Copyright notice                                            */
/*                                                                            */
/* Generated using VisPro/C serial number VPC5012127                          */
/*                                                                            */
/******************************************************************************/

#ifndef O_USERWINDOW_H
#define O_USERWINDOW_H

 /* ##START Form.39 Form header definitions */
 /* ##END Form header definitions */
HWND OpenO_USER(HWND hwndOwner, PVOID pInfo);

typedef struct _O_USERFORMINFO {
   PSWP pControlSize;   /* Used to handle control sizing */
   /* ##START Form.33 Window structure members */
   /* ##END Window structure members */
} O_USERFORMINFO;
typedef O_USERFORMINFO * PO_USERFORMINFO;
#define ID_FORMTIMER 100   /* Used for timer events */
#endif