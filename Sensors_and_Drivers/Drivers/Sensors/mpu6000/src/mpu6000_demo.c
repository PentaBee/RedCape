/*
 * 		Test for Integrated IMU MPU6000
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



int main(int argc, char *argv[])
{
	float values[6];
	mpu6000_Init();
	while(1)
	{
	mpu6000_GetValues(values);
	printf("The value of the linear acceleration vector is :\n %.0f X, %.0f Y, %.0f Z \n The value of the angular acceleration vector is : \n %.0f X, %.0f Y, %.0f Z \n ",values[0],values[1],values[2],values[3],values[4],values[5]);
	}

	i2c_finalize();




}
