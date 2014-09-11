/*
 * 		Demo for the accelerometer lis331
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

BOOL				DebugFlag;

int main(int argc, char *argv[])
{

float x_val,y_val,z_val;

	lis331_Init();


	while(1){
		x_val=lis331_xval();
		y_val = lis331_yval();
		z_val = lis331_zval();
		printf("The value of the  acceleration vector is : %.0f X, %.0f Y, %.0f Z \n",x_val,y_val,z_val);

		usleep(22222);//To ensure we maintain the frequency under 50Hz
		system("clear");
	}


	i2c_finalize();

}







