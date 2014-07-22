/*
/////////////////////////////////////////////////////////////////////////////
//
//  Detector Interface Software.
//
/////////////////////////////////////////////////////////////////////////////
//
//	File : BYTESWAP.H
//
//	Description : Definitions and constants for rpc data marshalling
//
//  Author : Kevin Moon
//
//  Date Created : 12/4/2004
//
/////////////////////////////////////////////////////////////////////////////
*/

#ifndef BYTESWAP_H
#define BYTESWAP_H
#include "types.h"


typedef union {
	float			fVal;
	struct {
		BYTE		b1;
 		BYTE		b2;
		BYTE		b3;
		BYTE		b4;
	} b;
} U_FLOAT_BYTES;


typedef union {
	DWORD			dwVal;
	struct {
		BYTE		b1;
 		BYTE		b2;
		BYTE		b3;
		BYTE		b4;
	} b;
} U_DWORD_BYTES;


typedef union {
	WORD			wVal;
	struct {
		BYTE		b1;
 		BYTE		b2;
	} b;
} U_WORD_BYTES;


static void SwapFloat (float *fVal)
{
	BYTE			bTemp;
	U_FLOAT_BYTES	Temp;

	Temp.fVal = *fVal;

	bTemp = Temp.b.b1;
	Temp.b.b1 = Temp.b.b4;
	Temp.b.b4 = bTemp;
	bTemp = Temp.b.b2;
	Temp.b.b2 = Temp.b.b3;
	Temp.b.b3 = bTemp;

	*fVal = Temp.fVal;
}



static void SwapDWord (DWORD *dwVal)
{
	BYTE			bTemp;
	U_DWORD_BYTES	Temp;

	Temp.dwVal = *dwVal;

	bTemp = Temp.b.b1;
	Temp.b.b1 = Temp.b.b4;
	Temp.b.b4 = bTemp;
	bTemp = Temp.b.b2;
	Temp.b.b2 = Temp.b.b3;
	Temp.b.b3 = bTemp;

	*dwVal = Temp.dwVal;
}



static void SwapWord (WORD *wVal)
{
	BYTE			bTemp;
	U_WORD_BYTES	Temp;

	Temp.wVal = *wVal;

	bTemp = Temp.b.b1;
	Temp.b.b1 = Temp.b.b2;
	Temp.b.b2 = bTemp;

	*wVal = Temp.wVal;
}


static void SwapFloatArray (float *fVal, DWORD Size)
{
	BYTE			bTemp;
	U_FLOAT_BYTES	Temp;

	while (Size-- > 0) {
		Temp.fVal = *fVal;

		bTemp = Temp.b.b1;
		Temp.b.b1 = Temp.b.b4;
		Temp.b.b4 = bTemp;
		bTemp = Temp.b.b2;
		Temp.b.b2 = Temp.b.b3;
		Temp.b.b3 = bTemp;

		*fVal++ = Temp.fVal;
	}
}



static void SwapDWordArray (DWORD *dwVal, DWORD Size)
{
	BYTE			bTemp;
	U_DWORD_BYTES	Temp;

	while (Size-- > 0) {
		Temp.dwVal = *dwVal;

		bTemp = Temp.b.b1;
		Temp.b.b1 = Temp.b.b4;
		Temp.b.b4 = bTemp;
		bTemp = Temp.b.b2;
		Temp.b.b2 = Temp.b.b3;
		Temp.b.b3 = bTemp;

		*dwVal++ = Temp.dwVal;
	}
}



static void SwapWordArray (WORD *wVal, DWORD Size)
{
	BYTE			bTemp;
	U_WORD_BYTES	Temp;

	while (Size-- > 0) {
		Temp.wVal = *wVal;

		bTemp = Temp.b.b1;
		Temp.b.b1 = Temp.b.b2;
		Temp.b.b2 = bTemp;

		*wVal++ = Temp.wVal;
	}
}

#endif
