/******************************************************************************/
/*                                                                            */
/* Program: Thread.h                                                          */
/*                                                                            */
/* Description: Description                                                   */
/*                                                                            */
/* File Name : Main.C                                                         */
/*                                                                            */
/* Author : ANDREW J. WYSOCKI                                                 */
/*                                                                            */
/* Copyright 1994 Copyright notice                                            */
/*                                                                            */
/* Generated using VisPro/C serial number VPC5012127                          */
/*                                                                            */
/******************************************************************************/

#define INCL_WIN
#define INCL_NLS
#define INCL_DOS
#define INCL_GPI
#include <os2.h>
#include "Main.h"
#include "Main.RCH"
#include "Send.h"
#include "Send.RCH"
#include "pmsock.h"
#include "parse.h"


#ifndef PMFUNCS_H
#define PMFUNCS_H

void            SetHwndID(HWND _hwnd, ULONG _id);
PMINIRECORDCORE     AddName(char *_Name, char *_Host, char *_Port);
PMINIRECORDCORE     CheckHost(char *_Host);

void            CvtFirstLast(char *_Name, char *_CvtName);
void            CvtLastFirst(char *_Name, char *_CvtName);

CHAR *          TextChanged(HWND _hwnd, ULONG _id);
APIRET          CheckChanged(HWND _hwnd, ULONG _id, int *_Check);

#endif
