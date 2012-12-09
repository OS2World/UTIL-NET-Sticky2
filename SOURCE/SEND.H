/******************************************************************************/
/*                                                                            */
/* Program: Sticky2.exe                                                       */
/*                                                                            */
/* Description: TCP Sticky Pad                                                */
/*                                                                            */
/* File Name : Send.H                                                         */
/*                                                                            */
/* Author : ANDY WYSOCKI                                                      */
/*                                                                            */
/* Copyright 1996 Copyright notice                                            */
/*                                                                            */
/* Generated using VisPro/C serial number VPC5012127                          */
/*                                                                            */
/******************************************************************************/

#ifndef SENDWINDOW_H
#define SENDWINDOW_H

 /* ##START Form.39 Form header definitions */
 /* ##END Form header definitions */
HWND OpenSEND(HWND hwndOwner, PVOID pInfo);

typedef struct _SEND_IP_CONTAINER_REC {
   MINIRECORDCORE Record;
   PSZ pszHost;
   PSZ pszPort;
} SEND_IP_CONTAINER_REC;
typedef SEND_IP_CONTAINER_REC * PSEND_IP_CONTAINER_REC;
#define ID_FORMTIMER 100   /* Used for timer events */
#endif