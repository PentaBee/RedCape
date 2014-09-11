/*
 * 		Driver for Real Time Clock DS1339
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
#include "types.h"
#include "i2c_drv.h"
#include "errorcodes.h"
#include "ds1339.h"

BOOL				DebugFlag;

int main(int argc, char *argv[])
{

int sec,min,hour,date,month,year;
	test();
	while(1){
		sec=Getsec();
		min = Getmin();
		hour = Gethour();
		date= Getdate();
		month = Getmonth();
		year = Getyear();
		if(year>= 10)
			printf("̣\n The date is \t\t %i / %i / 20%i \n\n",date,month,year);
		else
			printf("̣\n The date is \t\t %i / %i / 200%i \n\n",date,month,year);
		printf("̣\n The time is \t\t %i : %i : %i \n",hour,min,sec);
		usleep(1000000);
		system("clear");
	}

}
