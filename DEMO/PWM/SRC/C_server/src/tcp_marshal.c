/*
/////////////////////////////////////////////////////////////////////////////
//
//  Detector Interface Software.
//
/////////////////////////////////////////////////////////////////////////////
//                                                           
//	File : TCP_MARSHAL.C
//
//	Description : Contains code to convert structures to/from network order
//
//  Author : Kevin Moon
//
//  Date Created : 28/9/98
//
/////////////////////////////////////////////////////////////////////////////
*/

#include "byteswap.h"
#include "tcp_marshal.h"
#include "types.h"
//---------------------------------------------------------------------------
// IsBigEndian
//
// Parameters :		none
//
// Returns :		1, if the current system is big endian, 0 otherwise
//
// Description :	Run-time endianness test. This function does not distinguish
//					between little and middle endianness.
//---------------------------------------------------------------------------
int IsBigEndian()
{
	union
	{
		int		lval;
		char 	cvals[sizeof(int)];
	} test;
	test.lval = 1;
	return (test.cvals[sizeof(int) - 1]);
}

//---------------------------------------------------------------------------
// IsLittleEndian
//
// Parameters :		none
//
// Returns :		1, if the current system is little endian, 0 otherwise
//
// Description :	Run-time endianness test. This function does not distinguish
//					between big and middle endianness.
//---------------------------------------------------------------------------
int IsLittleEndian()
{
	union
	{
		int		lval;
		char 	cvals[sizeof(int)];
	} test;
	test.lval = 1;
	return (test.cvals[0]);
}

//---------------------------------------------------------------------------
// TcpMarshalCallHeader
//
// Parameters :		CallHeader			- Pointer to header
//
// Returns :		nothing
//
// Description :	Convert call header to/from network byte order
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
// TcpMarshalReplyHeader
//
// Parameters :		CallHeader			- Pointer to header
//
// Returns :		nothing
//
// Description :	Convert call header to/from network byte order
//---------------------------------------------------------------------------




//---------------------------------------------------------------------------
// TcpMarshalConfig
//
// Parameters :		Config				- Pointer to configuration
//
// Returns :		nothing
//
// Description :	Convert configuration to/from network byte order
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
// TcpMarshalImage
//
// Parameters :		Image				- Pointer to image descriptor
//
// Returns :		nothing
//
// Description :	Convert image descriptor to/from network byte order
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
// TcpMarshalImagePixels
//
// Parameters :		Pixels			- Pointer to image buffer
//					Size			- Size of buffer (WORDS)
//
// Returns :		nothing
//
// Description :	Convert image buffer to/from network byte order
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
// TcpMarshalImagePixels32
//
// Parameters :		Pixels			- Pointer to image buffer
//					Size			- Size of buffer (DWORDS)
//
// Returns :		nothing
//
// Description :	Convert 32-bit image buffer to/from network byte order
//---------------------------------------------------------------------------

/*
void TcpMarshalImagePixels32 (uint32_t *Pixels, uint32_t Size)
{
#ifdef M_LITTLE_ENDIAN
	SwapDWordArray(Pixels,Size);
#endif
}
*/

//---------------------------------------------------------------------------
// TcpMarshalFloatArray
//
// Parameters :		vals			- Pointer to the buffer of floating values
//					Size			- number of values in the buffer
//
// Returns :		nothing
//
// Description :	Convert a buffer of single-precision floating point values
//					to/from network byte order
//---------------------------------------------------------------------------
void TcpMarshalFloatArray(float *vals, uint32_t Size)
{
#ifdef M_LITTLE_ENDIAN
	SwapFloatArray(vals, Size);
#endif
}
//---------------------------------------------------------------------------
// TcpMarshalQuadCog
//
// Parameters :		CallHeader			- Pointer to header
//
// Returns :		nothing
//
// Description :	Convert call header to/from network byte order
//---------------------------------------------------------------------------




//TcpMarshalDoubleWord - swaps a single double word.
/*
void TcpMarshalDoubleWord(uint32_t *swapdword)
{
#ifdef M_LITTLE_ENDIAN
	SwapDWord (swapdword);
#endif
}


void TcpMarshalI2cDev(I2C_DEV_T *dev)
{
#ifdef M_LITTLE_ENDIAN
	SwapDWord (&(dev->MsgSize));
#endif
}

*/
