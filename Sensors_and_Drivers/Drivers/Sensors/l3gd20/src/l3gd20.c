
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "types.h"
#include "i2c_drv.h"
#include "errorcodes.h"
#include "l3gd20.h"


void l3gd20_Init()
{
	const uint8_t normalmode = 0x0F;//Value for register 1 to enter normal mode and start giving values at a 95Hz frequency	
	if (i2c_init() != XDS_OK)
		printf("I2C initialisation failed\n");
	
	//configure Register 2 for Taking one measurement
	i2c_write_register(L3GD20_ADDR, L3GD20_CTRL_REG1, &normalmode, (uint16_t) 1);
	usleep(100);
	//return XDS_OK;
}

float l3gd20_xval()
{
	float temp;
	unsigned char buf[10] = {0};
  	i2c_read_register(L3GD20_ADDR, L3GD20_REG_X_H, buf, (uint16_t) 1);
	temp = (float)((buf[0]& 0b00001111)<<8);
	i2c_read_register(L3GD20_ADDR, L3GD20_REG_X_L, buf, (uint16_t) 1);
	temp=temp+ (float)buf[0];
	return(temp);
}
float l3gd20_yval()
{
	float temp;
	unsigned char buf[10] = {0};
  	i2c_read_register(L3GD20_ADDR, L3GD20_REG_Y_H, buf, (uint16_t) 1);
	temp = (float)((buf[0]& 0b00001111)<<8);
	i2c_read_register(L3GD20_ADDR, L3GD20_REG_Y_L, buf, (uint16_t) 1);
	temp=temp+ (float)buf[0];
	return(temp);
}
float l3gd20_zval()
{
	float temp;
	unsigned char buf[10] = {0};
  	i2c_read_register(L3GD20_ADDR, L3GD20_REG_Z_H, buf, (uint16_t) 1);
	temp = (float)((buf[0]& 0b00001111)<<8);
	i2c_read_register(L3GD20_ADDR, L3GD20_REG_Z_L, buf, (uint16_t) 1);
	temp=temp+ (float)buf[0];
	return(temp);
}



