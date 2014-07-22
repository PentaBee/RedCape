//*******************************************************************************
//
//	File:		pwm_server.c
//	Author:		Octavio Rico
//	Date:		24/09/2013
//
//	server code
//*******************************************************************************
#ifdef WIN32
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#else
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "types.h"
#endif

#include "pwm.h"
#include "tcpnet.h"
#include "pwm_marshal.h"
#include "pwm_drv.h"
#include "fpga_drv.h"
#include "fpga_regs.h"
#include "omap_defs.h"

#include "i2c_drv.h"
#include "dac_drv.h"

#include "errorcodes.h"

/*test*/

#define		FPGA_ID_CODE			0x2347	// device id
TCP_CALL_T			test;

/***************************/


BOOL				DebugFlag;
char				strPort[] = "2222";
TCP_CALL_T			CallHeader;
TCP_REPLY_T			ReplyHeader;
PWM_CONFIG_T		TcpConfig;
PWM_CONFIG_T		SysConfig = {600000, 600000, 600000}; //50% Duty cycle
Vout_CONFIG_T		TcpConfigVout;
Vout_CONFIG_T		SysConfigVout = {1000, 1000};

uint32_t err;

int main(int argc, char* argv[])
{
	BOOL	ExitFlag;
	DWORD	Error;
	int		ArgPos;
	WORD	wReg;
	uint32_t dwRes;


	/* initialise FPGA driver */
			printf ("\nInitialise fpga\n");

			err = InitFpga();

			printf ("\nInitialised fpga\n");

	// check flags
	DebugFlag = FALSE;
	for (ArgPos=1; ArgPos<argc; ArgPos++) {
		if (strcmp (argv[ArgPos],"-debug") == 0)
			DebugFlag = TRUE;
	}

	// initialise hardware and set default configuration

	if (DebugFlag)
		printf ("\nInitialise hardware\n");

	//Initialising I2C
	if (i2c_init() != XDS_OK)
		printf("I2C initialisation failed\n");

	//Start up FPGA code
	if (pwm_Init () != XDS_OK)
		goto ErrorExit;

	//set the default configuration in SysConfig
	pwm_config (&SysConfig);

	if (DebugFlag)
	printf ("Server open\n");

	if (TcpServerOpen (strPort) != TCP_OK){
		goto ErrorExit;
	}

	dwRes = set_dac(0x0C, 0xB000,0xB000);
	dwRes = set_dac(0x0F, 0xA000,0xA000);

	while (1)
	{
		if (DebugFlag)
			printf ("Server connect wait\n");

		if (TcpServerConnect () != TCP_OK)
			break;

		if (DebugFlag)
			printf ("Server connected\n");

		ExitFlag = FALSE;

		while (ExitFlag == FALSE)
		{
			// get call header
			if (TcpRead ((char *)&CallHeader, sizeof (CallHeader), 0) != TCP_OK)
			{
				ExitFlag = TRUE;
				break;
				continue;
			}
			TcpMarshalCallHeader (&CallHeader);
			// decode call header

			switch (CallHeader.Type)
			{
			case 0xab22:	//set configuration
				if(DebugFlag)
					printf("\n\n'Set PWM'\n");

				// get call parameters and marshal
				if (TcpRead ((char *)&TcpConfig, sizeof (TcpConfig), TcpTimeOut()) != TCP_OK)
				{
					ExitFlag = TRUE;
					break;
				}
				TcpMarshalConfig (&TcpConfig);
				if (DebugFlag)
					printf("Reading Configuration from User\n");

				// do function call
				Error = pwm_config(&TcpConfig);
				if (Error == XDS_OK)
					SysConfig = TcpConfig;

				// marshal reply header and send
				ReplyHeader.Error = Error;
				ReplyHeader.Type = CallHeader.Type;
				TcpMarshalReplyHeader (&ReplyHeader);
				if (TcpWrite ((char *)&ReplyHeader, sizeof (ReplyHeader), TcpTimeOut()) != TCP_OK) {
					ExitFlag = TRUE;
					break;
				}
			break;

			case 0xAB23:	//set configuration DACs
				if(DebugFlag)
					printf("\n\n'Set Analogue Output'\n");

				// get call parameters and marshal
				if (TcpRead ((char *)&TcpConfigVout, sizeof (TcpConfigVout), TcpTimeOut()) != TCP_OK)
				{
					printf("\nDAC voltage1 Set!!\nExternal DACIn: %i  %i \n", TcpConfigVout.voltage1, TcpConfigVout.voltage2);
					printf("\n\n'Exit!!'\n");
					ExitFlag = TRUE;
					break;
				}
				printf("\n\n'Marshal'\n");
				TcpMarshalConfigVolt (&TcpConfigVout);
				printf("\nDAC voltage1 Set!!\nExternal DACIn: %i  %i \n", TcpConfigVout.voltage1, TcpConfigVout.voltage2);
				if (DebugFlag)
					printf("Reading Configuration from User\n");

				//Set analogue output
				set_dac(0x0C, TcpConfigVout.voltage1,TcpConfigVout.voltage1);

				set_dac(0x0F, TcpConfigVout.voltage2,TcpConfigVout.voltage2);

			break;

			default:
				if(DebugFlag)
					printf("invalid call header\n");
			break;

			}
		}
	}
	if (DebugFlag)
		printf ("Server close\n");
	TcpServerClose ();

	i2c_finalize();

	if (DebugFlag)
		printf ("Server quit\n");
	TcpServerQuit ();

	return 0;

	ErrorExit:
	printf ("Termination Error\n");

	return 0;
}

