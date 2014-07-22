#ifndef _ERROR_CODES_H_
#define _ERROR_CODES_H_

/////////////////////////////////////////////////////////////////////////////
// Error codes
/////////////////////////////////////////////////////////////////////////////

#define		XDS_OK				0			// No error
#define		XDS_E_INI_FILE		1			// Error readng ini file
#define		XDS_E_NET_CONNECT	2			// could not connect to server
#define		XDS_E_NET_FAIL		3			// network data transfer failed
#define		XDS_E_FPGA_ID		4			// fpga type incorrect
#define		XDS_E_PARAM			5			// config parameter error
#define		XDS_E_INT_TIME		6			// impossible to set requested integration time value
#define		XDS_E_INVALID_ARG	7			// invalid input arguments
#define		XDS_E_INIT			8			// initialization error
#define		XDS_E_NOT_FOUND		9			// requested resource not found
#define		XDS_E_IMAGESIZE		10			// requested and replied image sizes mismatch
#define		XDS_E_INUSE			11			// requested resources already in use
#define		XDS_E_TERMINATED	12			// routine execution has been terminated externally or due to an error
#define		XDS_E_THREAD		13			// wxThread call failed
#define		XDS_E_CONDITION		14			// wxCondition call failed
#define		XDS_E_WXTHREAD		XDS_E_THREAD
#define		XDS_E_WXCONDITION	XDS_E_CONDITION
#define		XDS_E_OUT_OF_MEMORY	15			// not enough memory
#define		XDS_E_TIMEOUT		16			// operation was terminated because of timeout
#define		XDS_E_ACTION		17			// action execution failed
#define		XDS_E_EXT_STATE		18			// external system erroroneous state (could be a device or subsystem to which the programme is trying to talk to)
#define		XDS_E_I2C			19			// I2C communication failed
#define		XDS_E_I2C_INIT		20			// I2C initialization failed
#define		XDS_E_MEM_INIT		21			// memory initialization failed
#define		XDS_E_FPGA_INIT		22			// fpga configuration failed
#define		XDS_E_FILEOPEN		23			// failed to open a file
#define		XDS_E_FILE_IO		24			// failed to read/write a file
#define		XDS_E_FILE			25			// file operation failed (create, delete, get info, etc)
#define		XDS_E_CHECKSUM		26			// checksum test failed
#define		XDS_E_VERSION		27			// resource of unsupported version has been encountered
#define		XDS_E_SPAWN			28			// process spawning or thread start failed
#define		XDS_E_NOPROC		29			// requested process is not running
#define		XDS_E_ARCHITECT		30			// invalid file/program/code/system architecture
#define		XDS_E_PERMISSION	31			// failed to apply new access permission
#define		XDS_E_ACCESS		32			// access to a requested resource has been denied
#define		XDS_E_IMAGERID		33			// image sensor signature (FPGA) does not correspond to the loaded image driver
#define		XDS_E_NET_REPLY		34			// invalid type of the network reply (echo)
#define		XDS_E_SYSTEM		35			// error occurred during a system call

#endif
