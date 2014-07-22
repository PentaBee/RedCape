/*
/////////////////////////////////////////////////////////////////////////////
//
//  Detector Interface Software.
//
/////////////////////////////////////////////////////////////////////////////
//
//	File : pwm_MARSHAL.C
//
//	Description : Contains code to convert structures to/from network order
//
//  Author : Pete Scott
//
//  Date Created : Feb 2008
//
/////////////////////////////////////////////////////////////////////////////
*/

#ifdef WIN32
#include <windows.h>
#include "xdstypes.h"
#else
#include "types.h"
#endif

#include "byteswap.h"
#include "pwm.h"
#include "pwm_marshal.h"

//---------------------------------------------------------------------------
// TcpMarshalCallHeader
//
// Parameters :		CallHeader			- Pointer to header
//
// Returns :		nothing
//
// Description :	Convert call header to/from network byte order
//---------------------------------------------------------------------------

void TcpMarshalCallHeader(TCP_CALL_T *Header)
{
#ifdef M_LITTLE_ENDIAN
	SwapWord (&(Header->Type));
#endif
}

//---------------------------------------------------------------------------
// TcpMarshalReplyHeader
//
// Parameters :		CallHeader			- Pointer to header
//
// Returns :		nothing
//
// Description :	Convert call header to/from network byte order
//---------------------------------------------------------------------------

void TcpMarshalReplyHeader(TCP_REPLY_T *Header)
{
#ifdef M_LITTLE_ENDIAN
	SwapWord (&(Header->Type));
	SwapDWord (&(Header->Error));
#endif
}

//---------------------------------------------------------------------------
// TcpMarshalConfig
//
// Parameters :		Config				- Pointer to configuration
//
// Returns :		nothing
//
// Description :	Convert configuration to/from network byte order
//---------------------------------------------------------------------------

void TcpMarshalConfig (PWM_CONFIG_T *Config)
{
#ifdef M_LITTLE_ENDIAN
	SwapDWord(&(Config->pwm_duty));
	SwapDWord(&(Config->pwm_roll));
	SwapDWord(&(Config->pwm_pitch));
#endif
}


void TcpMarshalConfigVolt (Vout_CONFIG_T *Configure)
{
#ifdef M_LITTLE_ENDIAN
	SwapDWord(&(Configure->voltage1));
	SwapDWord(&(Configure->voltage2));
#endif
}




