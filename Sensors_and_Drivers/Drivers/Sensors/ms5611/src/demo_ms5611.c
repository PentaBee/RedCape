/*
 * 		Demo for Diff. Pressure ms5611
 * 		I2C device attached in RedCape A2, used I2C bus - 1
 *
 *
 * 		Code by: Bart Garcia
 *
 *
 * 		Date : 10 - 9 - 2014
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

BOOL				DebugFlag;

void main(int argc, char *argv[])
{
	int CalData[6] = {0};
	float values[2]={0};
	int i;

	ms5611_GetcalData(CalData);
	for(i=0;i<6;i++)
		printf("C [%d] = %.d\n",i, CalData[i]);
	while(1){
		ms5611_GetValues(CalData , values);
		printf("Pressure Value : %.2f mb , \tTemp Value : %.2f C\n",values[1],values[0]);
		usleep(100000);
		system("clear");
	}


}
