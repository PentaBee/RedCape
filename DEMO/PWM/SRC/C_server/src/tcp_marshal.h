/*
/////////////////////////////////////////////////////////////////////////////
//
//  Detector Interface Software.
//
/////////////////////////////////////////////////////////////////////////////
//                                                           
//	File : TCP_MARSHAL.H
//
//	Description : Contains code to convert structures to/from network order
//
//  Author : Kevin Moon
//
//  Date Created : 28/9/98
//
/////////////////////////////////////////////////////////////////////////////
*/

#ifndef IBIS4A_MARSHAL_H
#define IBIS4A_MARSHAL_H

//#include "../drivers/imgsens/imgsensor.h"
//#include "../drivers/fs_drv.h" //TODO: get rid of this?

#define	IBIS4A_SYS_INFO			0xaa20	// get general system info
#define IBIS4A_TCP_GETCFG		0xaa21	// get configuration
#define IBIS4A_TCP_SETCFG		0xaa22	// set configuration
#define IBIS4A_TCP_GETEXPTIME	0xaa23	// get integration (exposure) time
#define IBIS4A_TCP_SETEXPTIME	0xaa24	// set integration (exposure) time
#define IBIS4A_TCP_COLOURBITMAP		0xaa25	// get colour bitmap image
#define IBIS4A_TCP_AVERAGE		0xaa26	// get average pixel value
//DAC commands (control a AD56x7R/AD56x7 DAC which resides on the I2C-bus)
#define FF_DAC_SET_VOLTAGE	0xaa40 //set voltage value using a binary code
/* Accelerometer polling command (control a LIS3LV02DL MEMS inertial sensor
 * which resides on the I2C-bus) */
#define EVS_PTC					0xaa41	// acquire photon transfer curve (PTC) data
#define EVS_TEMPERATURE			0xaa42	/* get temperature readings
										(from TI TMP42x sensor) */
#define EVS_SHUTTER_MOVE		0xaa43	/* move image sensor shutter */
#define EVS_SHUTTER_STATUS		0xaa44	/* read status of the imager shutter */
#define EVS_PELTIER_READ		0xaa45	/* read current Peltier parameters */
#define EVS_PELTIER_WRITE		0xaa46	/* set Peltier parameters */
#define EVS_ADC_READ			0xaa47	/* read ADC channels */
#define EVS_ADC_SCALE_SET		0xaa48	/* set ADC scale */
#define FF_ACC_GET_ACCELERATION 0xaa50 //get acceleration data
#define FF_I2C_READ				0xcc00 //read i2c device register
#define FF_I2C_WRITE			0xcc01 //write to the i2c deivce register

/////////////////////////////////////////////////////////////////////////////
// TYPE DEFINITIONS
/////////////////////////////////////////////////////////////////////////////

#undef WINDOWS
#if defined(_WIN32) || defined(_WIN16) || defined(_M_X64)
#define WINDOWS
#endif

#ifdef WINDOWS
#pragma pack(push,2)
//#pragma pack(push,4)
#endif

// RPC call header

typedef struct
#ifndef WINDOWS
__attribute__((packed))
#endif
{
	uint16_t	Type;								// packet type
} TCP_CALL_T;

// RPC reply header

typedef struct
#ifndef WINDOWS
__attribute__((packed))
#endif
{
	uint16_t			Type;						// packet type
	uint32_t			Error;						// function error return code
} TCP_REPLY_T;

//DAC command structure
typedef struct
#ifndef WINDOWS
__attribute__((packed))
#endif
{
	uint16_t			Channels;					// set bit to 1 to select a corresponding channel
												// number of channels defined by DAC_NUMBER_OF_CHANNELS in dac_drv.h
												// if all bits set to 0, than all channels will be updated
	uint16_t			VoltageCode;				// binary code, corresponding to the voltage divider value
												// (see AD56x7R/AD56x7 manual) (the latter is not implemented)
} DAC_VOLTAGE_CODE_T;

/* I2C device structure to send/receive the data over the network */
typedef struct
#ifndef WINDOWS
__attribute__((packed))
#endif
{
	uint8_t			DevAddr;				// device address on I2C bus
	uint8_t			Register;				// address of the register to read/write
	uint32_t		MsgSize;				// message size
} I2C_DEV_T;

#ifdef WINDOWS
#pragma pack(pop)
#endif

#ifdef __cplusplus
extern "C" {
#endif

int IsBigEndian();
int IsLittleEndian();
void TcpMarshalCallHeader (TCP_CALL_T *CallHeader);
void TcpMarshalReplyHeader (TCP_REPLY_T *ReplyHeader);


void TcpMarshalI2cDev(I2C_DEV_T *dev);

#ifdef __cplusplus
}
#endif

#endif
