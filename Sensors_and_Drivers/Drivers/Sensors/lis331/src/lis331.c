/*
 * 		Driver for the accelerometer lis331
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
#include "lis331.h"

void lis331_Init()
{
	const uint8_t normalmode = 0x27;//Value for register 1 to enter normal mode and start giving values at a 50Hz frequency
	if (i2c_init() != XDS_OK)
		printf("I2C initialisation failed\n");
	//configure Register 2 for Taking one measurement
	i2c_write_register(LIS331_ADDR, LIS331_CONF_REG1, &normalmode, (uint16_t) 1);
	usleep(10000);
}

float lis331_xval()
{
	unsigned char buf[10] = {0};
	float temp;
	i2c_read_register(LIS331_ADDR, LIS331_REG_X_H, buf, (uint16_t) 1);
	temp = (float)((buf[0]& 0b00001111)<<8);
	i2c_read_register(LIS331_ADDR, LIS331_REG_X_L, buf, (uint16_t) 1);
	temp=temp+ (float)buf[0];
	return(temp);	

}

float lis331_yval()
{
	unsigned char buf[10] = {0};
	float temp;
	i2c_read_register(LIS331_ADDR, LIS331_REG_Y_H, buf, (uint16_t) 1);
	temp = (float)((buf[0]& 0b00001111)<<8);
	i2c_read_register(LIS331_ADDR, LIS331_REG_Y_L, buf, (uint16_t) 1);
	temp=temp+ (float)buf[0];
	return(temp);	

}
float lis331_zval()
{
	unsigned char buf[10] = {0};
	float temp;
	i2c_read_register(LIS331_ADDR, LIS331_REG_Z_H, buf, (uint16_t) 1);
	temp = (float)((buf[0]& 0b00001111)<<8);
	i2c_read_register(LIS331_ADDR, LIS331_REG_Z_L, buf, (uint16_t) 1);
	temp=temp+ (float)buf[0];
	return(temp);	

}

