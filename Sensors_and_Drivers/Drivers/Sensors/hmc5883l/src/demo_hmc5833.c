/*
 * 		Demo for the 3D Magnetometer 5833l
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

BOOL				DebugFlag;

int main(int argc, char *argv[])
{

float xval,yval,zval;

	//HMC5833_Init();


	while(1){
		HMC5833_Init();
		xval=HMC5833_xvalue();
		yval = HMC5833_yvalue();
		zval = HMC5833_zvalue();
		printf("̣\n\n\n The magnetic vector is \t\t X:%f Y: %f Z: %f \n\n",xval,yval,zval);

		usleep(1000000);
		system("clear");
	}


	i2c_finalize();

}

