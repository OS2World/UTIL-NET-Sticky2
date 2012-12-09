/* PMSOCK.C--PM Sockets interface to IBM TCP/IP
 *
 * This file corresponds to version 1.0 of the PM Sockets specification,
 * which is based on version 1.1 of the Windows Sockets
 * specification.  
 *
 * This file includes parts which are Copyright (c) 1982-1986 Regents
 * of the University of California.  All rights reserved.  The
 * Berkeley Software License Agreement specifies the terms and
 * conditions for redistribution.
 *
 * Change log:
 *
 * Fri Sept 2 1994 Don Loflin
 *      Changing to be less direct
 * Sun Aug 21 1994 Don Loflin
 *	Redid to use IBM TCP routines directly
 * Fri Aug 11 1994 Don Loflin (loflin@mail.utexas.edu)
 * 	Created PMSOCK.C from PMSOCK.H
 * Mon Aug 8 1994  Don Loflin (loflin@mail.utexas.edu)
 *	Created PMSOCK.H from WINSOCK.H
 */

#include "pmsock.h"

/* IBM routines used here, from tcpip/include/sys/socket.h */
extern int _System soclose( int );
extern int _System sock_errno( void );
extern int _System ioctl(int, int, char *, int);


int closesocket (SOCKET s)
{
   return (soclose(s)); 
}

int ioctlsocket (SOCKET s, long cmd, u_long *argp)
{
   /* WinSock ioctlsocket only allows param to be u_long, so just pass that */
   /*size to IBM ioctl */
  /* return(ioctl(s, cmd, (char *) argp, sizeof(u_long)) );*/
}


/* Microsoft Windows Extension function prototypes */

int WSAStartup(WORD wVersionRequired, LPWSADATA lpWSAData)
{
   return(sock_init());
}


int WSACleanup(void)
{
/* null - IBM TCP doesn't require anything */
}

void WSASetLastError(int iError)
{
/* not allowed */
}

int WSAGetLastError(void)
{
   return (sock_errno()); 
}

/*
 * Aync calls optional
 */
#undef PMSAAsync
#ifdef PMSAAsync 

BOOL PASCAL FAR WSAIsBlocking(void);

int PASCAL FAR WSAUnhookBlockingHook(void);

FARPROC PASCAL FAR WSASetBlockingHook(FARPROC lpBlockFunc);

int PASCAL FAR WSACancelBlockingCall(void);

HANDLE PASCAL FAR WSAAsyncGetServByName(HWND hWnd, u_int wMsg,
                                        const char FAR * name, 
                                        const char FAR * proto,
                                        char FAR * buf, int buflen);

HANDLE PASCAL FAR WSAAsyncGetServByPort(HWND hWnd, u_int wMsg, int port,
                                        const char FAR * proto, char FAR * buf,
                                        int buflen);

HANDLE PASCAL FAR WSAAsyncGetProtoByName(HWND hWnd, u_int wMsg,
                                         const char FAR * name, char FAR * buf,
                                         int buflen);

HANDLE PASCAL FAR WSAAsyncGetProtoByNumber(HWND hWnd, u_int wMsg,
                                           int number, char FAR * buf,
                                           int buflen);

HANDLE PASCAL FAR WSAAsyncGetHostByName(HWND hWnd, u_int wMsg,
                                        const char FAR * name, char FAR * buf,
                                        int buflen);

HANDLE PASCAL FAR WSAAsyncGetHostByAddr(HWND hWnd, u_int wMsg,
                                        const char FAR * addr, int len, int type,
                                        char FAR * buf, int buflen);

int PASCAL FAR WSACancelAsyncRequest(HANDLE hAsyncTaskHandle);

int PASCAL FAR WSAAsyncSelect(SOCKET s, HWND hWnd, u_int wMsg,
                               long lEvent);

#endif /* PMSAAsync */


