/*
 * 		Driver for Integrated IMU MPU6000
 * 		I2C device attached in RedCape A1
 *
 *
 * 		Code by: Bart Garcia
 *
 *
 * 		Date : 6 - 05 - 2014
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
#include "mpu6000.h"
BOOL				DebugFlag;

void mpu6000_Init()
{

	if (i2c_init() != XDS_OK)
		printf("I2C initialisation failed\n");


}

void mpu6000_GetValues(float values[6])
{
	float a_x_val,a_y_val,a_z_val;
	float g_x_val,g_y_val,g_z_val;
	unsigned char buf[10] = {0};
	const uint8_t value = 0x00;

	//configure Register 2 for Taking one measurement
	i2c_write_register(MPU6000_ADDR, MPU6000_PWR_MGMT_1, &value, (uint16_t) 1);
	usleep(10000);
	//Obtain Xvalue- ACC
	i2c_read_register(MPU6000_ADDR, MPU6000_REG_ACCEL_X_H, buf, (uint16_t) 1);
	a_x_val = (float)((buf[0]& 0b00001111)<<8);
	i2c_read_register(MPU6000_ADDR, MPU6000_REG_ACCEL_X_L, buf, (uint16_t) 1);
	a_x_val=a_x_val+ (float)buf[0];
	//Obtain Yvalue- ACC
	i2c_read_register(MPU6000_ADDR, MPU6000_REG_ACCEL_Y_H, buf, (uint16_t) 1);
	a_y_val = (float)((buf[0]& 0b00001111)<<8);
	i2c_read_register(MPU6000_ADDR, MPU6000_REG_ACCEL_Y_L, buf, (uint16_t) 1);
	a_y_val =a_y_val +(float)buf[0];
	//Obtain Zvalue- ACC
	i2c_read_register(MPU6000_ADDR, MPU6000_REG_ACCEL_Z_H, buf, (uint16_t) 1);
	a_z_val = (float)((buf[0]& 0b00001111)<<8);
	i2c_read_register(MPU6000_ADDR, MPU6000_REG_ACCEL_Z_L, buf, (uint16_t) 1);
	a_z_val = a_z_val +(float)buf[0];
	//Obtain Xvalue- GYRO
	i2c_read_register(MPU6000_ADDR, MPU6000_REG_GYRO_X_H, buf, (uint16_t) 1);
	g_x_val = (float)((buf[0]& 0b00001111)<<8);
	i2c_read_register(MPU6000_ADDR, MPU6000_REG_GYRO_X_L, buf, (uint16_t) 1);
	g_x_val=g_x_val+ (float)buf[0];
	//Obtain Yvalue- GYRO
	i2c_read_register(MPU6000_ADDR, MPU6000_REG_GYRO_Y_H, buf, (uint16_t) 1);
	g_y_val = (float)((buf[0]& 0b00001111)<<8);
	i2c_read_register(MPU6000_ADDR, MPU6000_REG_GYRO_Y_L, buf, (uint16_t) 1);
	g_y_val =g_y_val +(float)buf[0];
	//Obtain Zvalue- GYRO
	i2c_read_register(MPU6000_ADDR, MPU6000_REG_GYRO_Z_H, buf, (uint16_t) 1);
	g_z_val = (float)((buf[0]& 0b00001111)<<8);
	i2c_read_register(MPU6000_ADDR, MPU6000_REG_GYRO_Z_L, buf, (uint16_t) 1);
	g_z_val = g_z_val +(float)buf[0];

	values[0]=a_x_val;
	values[1]=a_y_val;
	values[2]=a_z_val;
	values[3]=g_x_val;
	values[4]=g_y_val;
	values[5]=g_z_val;




}
