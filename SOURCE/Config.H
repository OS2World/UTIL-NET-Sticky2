/******************************************************************************/
/*                                                                            */
/* Program: Sticky2.exe                                                       */
/*                                                                            */
/* Description: TCP Sticky Pad                                                */
/*                                                                            */
/* File Name : CONFIG.H                                                       */
/*                                                                            */
/* Author : ANDY WYSOCKI                                                      */
/*                                                                            */
/* Copyright 1996 Copyright notice                                            */
/*                                                                            */
/* Generated using VisPro/C serial number VPC5012127                          */
/*                                                                            */
/******************************************************************************/

#ifndef CONFIGWINDOW_H
#define CONFIGWINDOW_H

 /* ##START Form.39 Form header definitions */
 /* ##END Form header definitions */
HWND OpenCONFIG(HWND hwndOwner, PVOID pInfo);

typedef struct _CONFIG_OPTIONS_FOLDER_REC {
   MINIRECORDCORE Record;
} CONFIG_OPTIONS_FOLDER_REC;
typedef CONFIG_OPTIONS_FOLDER_REC * PCONFIG_OPTIONS_FOLDER_REC;
#define ID_FORMTIMER 100   /* Used for timer events */
#endif