/*
//
//	File : pwm_drv.C
//
//  Author :  Octavio Rico
//
//  Date Created : Sep 2013
//
*/
#include <stdio.h>
#include <malloc.h>
#include <float.h>
#include <math.h>
#include <time.h>
#include "types.h"
#include "pwm.h"
#include "pwm_drv.h"

#include "fpga_drv.h"
#include "fpga_regs.h"
#include "omap_defs.h"

#include "errorcodes.h"

#include "i2c_drv.h"
#include "dac_drv.h"


extern	BOOL	DebugFlag;

DWORD pwm_Init (void)
{
	WORD	wReg;

	if(DebugFlag)
		printf ("\nReset FPGA\n");

	fpga_write_short(FPGA_RESET, 0);

	if(DebugFlag)
		printf ("Read FPGA ID register\n");

	fpga_write_short(FPGA_ADDR, 0x0010);
	wReg = fpga_read_short(0x0016);

	if (wReg != FPGA_ID_CODE) {
		printf ("\nFPGA ID code error %x - wrong FPGA code??\n",wReg);
		return XDS_E_FPGA_ID;
	}

	else if (DebugFlag)
	{
		printf ("FPGA self diagnostics OK\n");
		printf ("FPGA ID code = %04x\n\n",wReg);
	}

	return XDS_OK;
}

DWORD	pwm_config (PWM_CONFIG_T *Config)
{
	WORD wReg;
	if(DebugFlag)
	{
		printf("Configuration in process\n\n");
		printf("\t\t\t\tvalue in\nparameter name\t\t\tdecimal\n");
		printf("Pulse Width Modulation:\t\t%lu\n",Config->pwm_duty); // 600000 = 50 %
		printf("Pulse Width Modulation roll:\t\t%lu\n",Config->pwm_roll); // 600000 = 50 %
		printf("Pulse Width Modulation pitch:\t\t%lu\n",Config->pwm_pitch); // 600000 = 50 %
		//For this example we send two words of 16 Bits
		//because the maximum value sent to the FPGA is 18 Bits long
	}
	//set pwm_drv page chip select
	fpga_write_short (FPGA_ADDR,0x0020);

	//PWM width Lower 16 bits
	wReg = (uint16_t) Config->pwm_duty & 0xFFFF;
	fpga_write_short (0x0024,wReg); //lower 16 bits of PWM counter
	//PWM width upper 16 bits
	wReg = (uint16_t)(Config->pwm_duty>>16) & 0xFFFF;
	fpga_write_short (0x0026,wReg); //upper 16 bits of PWM counter

	//PWM width Lower 16 bits Roll
	wReg = (uint16_t) Config->pwm_roll & 0xFFFF;
	fpga_write_short (0x0028,wReg); //lower 16 bits of PWM counter
	//PWM width upper 16 bits Roll
	wReg = (uint16_t)(Config->pwm_roll>>16) & 0xFFFF;
	fpga_write_short (0x002A,wReg); //upper 16 bits of PWM counter

	//PWM width Lower 16 bits Pitch
	wReg = (uint16_t) Config->pwm_pitch & 0xFFFF;
	fpga_write_short (0x002C,wReg); //lower 16 bits of PWM counter
	//PWM width upper 16 bits Pitch
	wReg = (uint16_t)(Config->pwm_pitch>>16) & 0xFFFF;
	fpga_write_short (0x002E,wReg); //upper 16 bits of PWM counter

//	//Other way of assign data (only if the max value can be represented by using 12 bits).
//
//	wReg = (uint16_t) Config->pwm_roll & 0x0FFF; //12 bits
//	wReg |= 0x1000;
//	fpga_write_short (0x0024,wReg);
//	wReg = (uint16_t)(Config->pwm_roll>>16) & 0x0FFF;
//	wReg |= 0x2000;
//	fpga_write_short (0x0024,wReg); //12 + identifier


	return XDS_OK;
}


uint32_t set_dac(uint16_t addr, uint16_t dacA, uint16_t dacB)
{
	uint32_t dwRes;
	if(DebugFlag)
	printf("\n-Acquiring DAC voltage to be Set-\n");

	//dwRes = i2c_select_dev(DAC_ADDR);
	dwRes = i2c_select_dev(addr);
	if(XDS_OK != dwRes)
		return dwRes;
	uint8_t data[3] = {0x1F,(uint8_t)(dacA>>8), (uint8_t)(dacA & 0x00FF)}; //0x19
	uint16_t lendata = (uint16_t)(sizeof(data) / sizeof(data[0]));

	/* the command and voltage code in one package */
	if(XDS_OK != (dwRes = i2c_transmit_msg(data, 3)))
		return dwRes;

	if(DebugFlag)
		printf("\nDAC voltage1 Set!!\nExternal DACIn: %i \n", dacA);

	//dwRes = i2c_select_dev(DAC_ADDR);
	dwRes = i2c_select_dev(addr);
	if(XDS_OK != dwRes)
		return dwRes;
	uint8_t data2[3] = {0x1F,(uint8_t)(dacB>>8), (uint8_t)(dacB & 0x00FF)}; //0x19

	/* the command and voltage code in one package */
	if(XDS_OK != (dwRes = i2c_transmit_msg(data2, 3)))
		return dwRes;

	if(DebugFlag)
		printf("\nDAC voltage2 Set!!\nExternal DACIn: %i \n", dacB);

	return XDS_OK;
}
