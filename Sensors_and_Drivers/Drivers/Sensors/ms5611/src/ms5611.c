/*
 * 		Driver for Differential Pressure sensor ms5611
 * 		I2C device attached in RedCape A1, used I2C bus - 1
 *
 *
 * 		Code by: Bart Garcia
 *
 *
 * 		Date : 10 - 09 - 2014
 *
 *
 *
 *
 */
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "types.h"
#include "i2c_drv.h"
#include "errorcodes.h"
#include "ms5611.h"



void ms5611_GetcalData(unsigned int C[6])
{
	int cont;
	unsigned char buf[10] = {0};
	if (i2c_init() != XDS_OK)
			printf("I2C initialisation failed\n");

	cont= 0;
	const uint8_t C_ADD[6] = {0xA2,0xA4,0xA6,0xA8,0xAA,0xAC,0xAC};//Calibration Data addresses

	for(cont=0; cont < 6;cont ++) {
		//send read sequence
		i2c_select_dev(MS5611_ADDR);
		i2c_transmit_msg(&C_ADD[cont], 1);
		i2c_select_dev(MS5611_ADDR);
		i2c_receive_msg(buf, (uint16_t) 2);
		C[cont]=(int)((buf[0])<<8)+ (int)buf[1];
		usleep(100);
		//printf("C [%d] = %i \n",cont, C[cont]);
		}

}


//void ms5611_GetValues(unsigned int C[6],double PRESS , double TEMP)
void ms5611_GetValues(unsigned int C[6] ,float val[2])
{

	double SENS,OFF,dT,TEMP,PRESS;
	unsigned long D1,D2;
	unsigned char buf[10] = {0};
	const uint8_t CONV_D1 = 0x48;
	const uint8_t CONV_D2 = 0x58;
	const uint8_t ADC_READ =0x00;


	//obtain Raw Pressure value
	i2c_select_dev(MS5611_ADDR);
	i2c_transmit_msg(&CONV_D1, 1);
	usleep(10000);
	i2c_select_dev(MS5611_ADDR);
	i2c_transmit_msg(&ADC_READ, 1);
	usleep(10000);
	i2c_select_dev(MS5611_ADDR);
	i2c_receive_msg(buf, (uint16_t) 3);
	D1=(int)((buf[0])<<16)+(int)((buf[1])<<8)+ (int)buf[2];
	usleep(100);
	//obtain Raw TEMP value
	i2c_select_dev(MS5611_ADDR);
	i2c_transmit_msg(&CONV_D2, 1);
	usleep(10000);
	i2c_select_dev(MS5611_ADDR);
	i2c_transmit_msg(&ADC_READ, 1);
	usleep(10000);
	i2c_select_dev(MS5611_ADDR);
	i2c_receive_msg(buf, (uint16_t) 3);
	D2=(int)((buf[0])<<16)+(int)((buf[1])<<8)+ (int)buf[2];
	usleep(100);
	// Convert to real values
	dT=D2-C[4]*pow(2,8);
	OFF=C[1]*pow(2,17)+dT*(C[3])/pow(2,6);
	SENS=C[0]*pow(2,16)+dT*(C[2])/pow(2,7);
	TEMP=(2000+(dT*C[5])/pow(2,23))/100;
	PRESS=((D1*SENS/pow(2,21)-OFF)/pow(2,16))/100;
	val[0] = (float)(TEMP);
	val[1] = (float)(PRESS);
	//printf("Press = %.2f mb\t Temp = %.2f C\n",PRESS,TEMP);



}

