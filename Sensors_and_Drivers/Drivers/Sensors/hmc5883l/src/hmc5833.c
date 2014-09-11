/*
 * 		Driver for the 3D Magnetometer 5833l
 * 		I2C device attached in RedCape A2, used I2C bus - 1
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
#include "types.h"
#include "i2c_drv.h"
#include "errorcodes.h"
#include "hmc5833.h"



void HMC5833_Init()
{
	const uint8_t regist3 = 0x01;
	if (i2c_init() != XDS_OK)
		printf("I2C initialisation failed\n");
	i2c_write_register(HMC5883L_ADDR, HMC5883L_CONF_REG, &regist3, (uint16_t) 1);
	usleep(10000);

}

float HMC5833_xvalue()
{
	unsigned char buf[10] = {0};
	float temp;


	i2c_read_register(HMC5883L_ADDR, HMC5883L_REG_X_H, buf, (uint16_t) 1);
	temp = (float)((buf[0]& 0b00001111)<<8);
	i2c_read_register(HMC5883L_ADDR, HMC5883L_REG_X_L, buf, (uint16_t) 1);
	temp=temp+ (float)buf[0];
	return(temp);
}

float HMC5833_yvalue()
{
	unsigned char buf[10] = {0};
	float temp;


	i2c_read_register(HMC5883L_ADDR, HMC5883L_REG_Y_H, buf, (uint16_t) 1);
	temp = (float)((buf[0]& 0b00001111)<<8);
	i2c_read_register(HMC5883L_ADDR, HMC5883L_REG_Y_L, buf, (uint16_t) 1);
	temp=temp+ (float)buf[0];
	return(temp);
}

float HMC5833_zvalue()
{
	unsigned char buf[10] = {0};
	float temp;


	i2c_read_register(HMC5883L_ADDR, HMC5883L_REG_Z_H, buf, (uint16_t) 1);
	temp = (float)((buf[0]& 0b00001111)<<8);
	i2c_read_register(HMC5883L_ADDR, HMC5883L_REG_Z_L, buf, (uint16_t) 1);
	temp=temp+ (float)buf[0];
	return(temp);
}


