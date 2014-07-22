/*
/////////////////////////////////////////////////////////////////////////////
//
//  Detector Interface Software.
//
/////////////////////////////////////////////////////////////////////////////
//
//	File : TCPNET.H
//
//	Description : Low level tcp functions
//
//  Author : Kevin Moon
//
//  Date Created : 14/4/2004
//
/////////////////////////////////////////////////////////////////////////////
*/


#ifndef TCPNET_H

// function return codes

#define		TCP_OK		0				// no error
#define		TCP_ERR		(-1)			// error


#ifdef __cplusplus
extern "C"{
#endif

int		TcpGetSysError (void);

int		TcpClientOpen (char *strHost, char *strPort);
void	TcpClientClose (void);

int		TcpServerOpen (char *strPort);
int		TcpServerConnect (void);
void	TcpServerClose (void);
void	TcpServerQuit (void);

int 	TcpWrite (char *pBuffer, int iSize, int iTimeOut);
int		TcpRead (char *pBuffer, int iSize, int iTimeOut);

int		TcpTimeOut();
void	TcpSetTimeOut(int iTimeOut);

#ifdef __cplusplus
}
#endif


#endif
