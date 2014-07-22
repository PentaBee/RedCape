/*
/////////////////////////////////////////////////////////////////////////////
//
//  Detector Interface Software.
//
/////////////////////////////////////////////////////////////////////////////
//
//	File : TCPNET.C
//
//	Description : Low level tcp functions
//
//  Author : Kevin Moon
//
//  Date Created : 14/4/2004
//
/////////////////////////////////////////////////////////////////////////////
*/


#ifdef WIN32

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
//#include <winsock2.h>

#else

#define _GNU_SOURCE 	//needed to reference h_addr member of hostent structure
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>

#ifndef __uClinux__
#include <sys/select.h>
#endif

#endif


#include "tcpnet.h"


#ifdef _WINSOCKAPI_

#define ERRNO				(WSAGetLastError ())
#define H_ERRNO				(WSAGetLastError ())
#define BZERO(b,n)			memset ((b), 0, (n))
#define CLOSE(s)			closesocket (s);

#else

typedef int					SOCKET;
#define INVALID_SOCKET		(-1)
#define SOCKET_ERROR		(-1)
#define ERRNO				errno
#define H_ERRNO				h_errno
#define BZERO(b,n)			bzero ((b), (n))
#define CLOSE(s)			close (s);

#endif

#define XDS_MAX_SOCKET		8

static SOCKET				Socket = INVALID_SOCKET;
static SOCKET				ServerSocket = INVALID_SOCKET;
static struct sockaddr_in	SockAddr;
static struct timeval		SelectTime;
static        fd_set		SelectMask;
static int					TcpError;
static int					UserTimeOut = 4; // send/receive time out (seconds)

#ifdef _WINSOCKAPI_

int inet_aton (const char *cp, struct in_addr *inp)
{
	if ((inp->S_un.S_addr = inet_addr(cp)) == INADDR_NONE)
		return 0;
	else
		return -1;
}

#endif



//---------------------------------------------------------------------------
// TcpGetError
//
// Parameters :		none
//
// Returns :		int				- system error code
//
// Description :	get last system error
//---------------------------------------------------------------------------

int TcpGetSysError (void)
{
	return TcpError;
}


//---------------------------------------------------------------------------
// TcpSetAddress
//
// Parameters :		strPort			- port/service name
//					strHost			- host - server name
//
// Returns :		int				- tcp error code
//
// Description :	fill in a sockaddr_in structure
//---------------------------------------------------------------------------

int TcpSetAddress (char *strHost, char *strPort,
					struct sockaddr_in *SockAddr, char *strProtocol)
{
	struct servent	*sp;
	struct hostent	*hp;
	char			*endptr;
	short			port;

	BZERO (SockAddr, sizeof(*SockAddr));
	SockAddr->sin_family = AF_INET;
	if (strHost != NULL) {
		if (!inet_aton (strHost, &(SockAddr->sin_addr))) {
			hp = gethostbyname (strHost);
			if (!hp) {
				TcpError = H_ERRNO;
				return TCP_ERR;
			}
			SockAddr->sin_addr = *(struct in_addr *)hp->h_addr;
		}
	} else {
		SockAddr->sin_addr.s_addr = htonl (INADDR_ANY);
	}
	port = (short)(strtol (strPort, &endptr, 0));
	if ( *endptr == '\0' ) {
		SockAddr->sin_port = htons ((uint16_t)port);
	} else {
		sp = getservbyname (strPort, strProtocol);
		if (!sp) {
			TcpError = H_ERRNO;
			return TCP_ERR;
		}
		SockAddr->sin_port = (in_port_t)sp->s_port;
	}
	return TCP_OK;
}


//---------------------------------------------------------------------------
// TcpClientOpen
//
// Parameters :		strHost			- host - server name
//					strPort			- port/service name
//
// Returns :		int				- tcp error code
//
// Description :	Open tcp socket connection to a server
//---------------------------------------------------------------------------


int TcpClientOpen (char *strHost, char *strPort)
{
	int		iStatus;

#ifdef _WINSOCKAPI_
	WSADATA			wsaData;

	if (TcpError = WSAStartup (MAKEWORD (2,2), &wsaData))
		return TCP_ERR;

	if (LOBYTE(wsaData.wVersion) != 2
	 || HIBYTE(wsaData.wVersion) != 2) {
		TcpError = WSAVERNOTSUPPORTED;
		return TCP_ERR;
	}
#endif

	if (iStatus = TcpSetAddress (strHost, strPort, &SockAddr, "tcp"))
		return iStatus;

	if ((Socket = socket(AF_INET,SOCK_STREAM,0)) == INVALID_SOCKET) {
		TcpError = ERRNO;
		return TCP_ERR;
	}

	if (connect( Socket, (struct sockaddr *)&SockAddr, sizeof(SockAddr)) == SOCKET_ERROR) {
		TcpError = ERRNO;
		return TCP_ERR;
	}

	return TCP_OK;
}


//---------------------------------------------------------------------------
// TcpClientClose
//
// Parameters :		none
//
// Returns :		nothing
//
// Description :	close tcp socket connection to a server
//---------------------------------------------------------------------------


void TcpClientClose (void)
{
	if (Socket != INVALID_SOCKET) {
		shutdown (Socket, 2);
		CLOSE (Socket);
	}

#ifdef _WINSOCKAPI_
	WSACleanup();
#endif
}


//---------------------------------------------------------------------------
// TcpServerOpen
//
// Parameters :		strHost			- host - server name
//
// Returns :		int				- tcp error code
//
// Description :	Open tcp socket connection to a server
//---------------------------------------------------------------------------


int TcpServerOpen (char *strPort)
{
	int		on = 1;
	int		iStatus;

#ifdef _WINSOCKAPI_
	WSADATA			wsaData;

	if (TcpError = WSAStartup (MAKEWORD (2,2), &wsaData))
		return TCP_ERR;

	if (LOBYTE(wsaData.wVersion) != 2
	 || HIBYTE(wsaData.wVersion) != 2) {
		TcpError = WSAVERNOTSUPPORTED;
		return TCP_ERR;
	}
#endif

	if (iStatus = TcpSetAddress (NULL, strPort, &SockAddr, "tcp"))
		return iStatus;

	if ((ServerSocket = socket(AF_INET,SOCK_STREAM,0)) == INVALID_SOCKET) {
		TcpError = ERRNO;
		return TCP_ERR;
	}

	if (setsockopt (ServerSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof (on)) == SOCKET_ERROR) {
		TcpError = ERRNO;
		return TCP_ERR;
	}

	if (bind (ServerSocket, (struct sockaddr *)&SockAddr, sizeof(SockAddr)) == SOCKET_ERROR) {
		TcpError = ERRNO;
		return TCP_ERR;
	}

	if (listen (ServerSocket, 1) == SOCKET_ERROR) {
		TcpError = ERRNO;
		return TCP_ERR;
	}

	return TCP_OK;
}


//---------------------------------------------------------------------------
// TcpServerConnect
//
// Parameters :		none
//
// Returns :		int				- tcp error code
//
// Description :	connect to client
//---------------------------------------------------------------------------


int TcpServerConnect (void)
{
	if ((Socket = accept (ServerSocket,0,0)) == INVALID_SOCKET) {
		TcpError = ERRNO;
		return TCP_ERR;
	}

	return TCP_OK;
}


//---------------------------------------------------------------------------
// TcpServerClose
//
// Parameters :		none
//
// Returns :		nothing
//
// Description :	close tcp server socket
//---------------------------------------------------------------------------


void TcpServerClose (void)
{
	if (Socket != INVALID_SOCKET) {
		shutdown (Socket, 2);
		CLOSE (Socket);
	}
	Socket = INVALID_SOCKET;
}


//---------------------------------------------------------------------------
// TcpServerQuit
//
// Parameters :		none
//
// Returns :		nothing
//
// Description :	terminate server
//---------------------------------------------------------------------------


void TcpServerQuit (void)
{
	if (Socket != INVALID_SOCKET) {
		shutdown (Socket, 2);
		CLOSE (Socket);
	}
	if (ServerSocket != INVALID_SOCKET) {
		shutdown (ServerSocket, 2);
		CLOSE (ServerSocket);
	}

#ifdef _WINSOCKAPI_
	WSACleanup();
#endif
}


//---------------------------------------------------------------------------
// TcpWrite
//
// Parameters :		pBuffer			- pointer to buffer
//					iSize			- size of buffer
//					iTimeOut		- timeout in seconds
//
// Returns :		int				- tcp error code
//
// Description :	write packet until error or data sent
//---------------------------------------------------------------------------


int TcpWrite (char *pBuffer, int iSize, int iTimeOut)
{
	struct timeval tv;
	int		iStatus;

	if (iTimeOut > 0) {
		tv.tv_sec = iTimeOut;
		tv.tv_usec = 0;
		if (setsockopt(Socket, SOL_SOCKET, SO_SNDTIMEO, (char *) &tv,
				sizeof(tv)) == SOCKET_ERROR) {
			TcpError = ERRNO;
			return TCP_ERR;
		}
	}

	do {
		/* use MSG_NOSIGNAL flag to suppress sending SIGPIPE when writing to the socket
		 * that is closed on the other end by a client - this can happen after one client
		 * disconnects and there has been a connection request from another client
		 * while the first was connected, since connection requests are queued as
		 * defined by listen() call in TcpServerOpen(), it can happen that we will try
		 * to write into the brocken socket corresponding to the second client
		 * Warning: MSG_NOSIGNAL flash is not portable outside Linux kernel 2.2+ */
		if ((iStatus = send (Socket, pBuffer, (size_t)iSize, MSG_NOSIGNAL)) == SOCKET_ERROR) {
			TcpError = ERRNO;
			return TCP_ERR;
		}

		iSize -= iStatus;
		pBuffer += iStatus;

	} while (iSize > 0);

	return TCP_OK;
}


//---------------------------------------------------------------------------
// TcpRead
//
// Parameters :		pBuffer			- pointer to buffer
//					iSize			- size of buffer
//					iTimeOut		- timeout in seconds
//
// Returns :		int				- tcp error code
//
// Description :	read packet until error or data received
//					if Timeout = 0 read blocks until data ready
//					if Timeout != 0 read waits for up TimeOut seconds for data
//---------------------------------------------------------------------------


int TcpRead (char *pBuffer, int iSize, int iTimeOut)
{
	int		iStatus;

	do {
		if (iTimeOut != 0) {							// recv with timeout
			FD_ZERO (&SelectMask);						// Set desc mask
			FD_SET ((unsigned int)Socket, &SelectMask);
			SelectTime.tv_usec = 0;						// set timeout
			SelectTime.tv_sec = iTimeOut;
			iStatus = select ((int)Socket+1, &SelectMask, NULL, NULL, &SelectTime);
			if (iStatus == SOCKET_ERROR) {				// select failed
				TcpError = ERRNO;
				return TCP_ERR;
			}
			if (iStatus == 0) {							// timed out
#ifdef _WINSOCKAPI_
				TcpError = WSAETIMEDOUT;
#else
				TcpError = ETIMEDOUT;
#endif
				return TCP_ERR;
			}
		}

		if ((iStatus = recv (Socket, pBuffer, (size_t)iSize, 0)) == SOCKET_ERROR) {
			TcpError = ERRNO;
			return TCP_ERR;
		}
		if (iStatus == 0)
			return TCP_ERR;

		iSize -= iStatus;
		pBuffer += iStatus;
	} while (iSize > 0);

	return TCP_OK;
}

int		TcpTimeOut()
{
	return UserTimeOut;
}

void	TcpSetTimeOut(int iTimeOut)
{
	UserTimeOut = iTimeOut;
}

/*

Compute checksum for a block of data


DWORD TcpCheckSum(BYTE far *Packet,int PacketSize)
{
  DWORD    CheckSum;
  int      i;

  CheckSum = 0;
  for (i=0;i<PacketSize;i++)
    CheckSum += *Packet++;
  return CheckSum;
}


*/




