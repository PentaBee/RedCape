/*
 * 		Demo for the gyroscope l3gd20
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
#include "l3gd20.h"

BOOL				DebugFlag;

int main(int argc, char *argv[])
{

float x_val,y_val,z_val;

	l3gd20_Init();


	while(1){
		x_val=l3gd20_xval();
		y_val = l3gd20_yval();
		z_val = l3gd20_zval();
		printf("The value of the angular acceleration vector is : %.0f X, %.0f Y, %.0f Z \n",x_val,y_val,z_val);

		usleep(1000000);
		system("clear");
	}


	i2c_finalize();

}







