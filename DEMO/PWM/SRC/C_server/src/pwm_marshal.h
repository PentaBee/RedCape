/*
/////////////////////////////////////////////////////////////////////////////
//
//  Detector Interface Software.
//
/////////////////////////////////////////////////////////////////////////////
//
//
//	Description : Contains code to convert structures to/from network order
//
//  Author : Kevin Moon
//
//  Date Created : 28/9/98
//
/////////////////////////////////////////////////////////////////////////////
*/

#define	TCP_TIMEOUT				4		// receive time out

#ifdef WIN32
#pragma pack(push,2)
//#pragma pack(push,4)
#endif

// RPC call header

typedef struct
#ifndef WIN32
__attribute__((packed))
#endif
{
	WORD	Type;								// packet type
} TCP_CALL_T;

// RPC reply header

typedef struct
#ifndef WIN32
__attribute__((packed))
#endif
{
	WORD			Type;						// packet type
	DWORD			Error;						// function error return code
} TCP_REPLY_T;



#ifdef WIN32
#pragma pack(pop)
#endif


void TcpMarshalCallHeader (TCP_CALL_T *CallHeader);
void TcpMarshalReplyHeader (TCP_REPLY_T *ReplyHeader);
void TcpMarshalConfig (PWM_CONFIG_T *Config);
void TcpMarshalImagePixels (WORD *Pixels, DWORD Size);

