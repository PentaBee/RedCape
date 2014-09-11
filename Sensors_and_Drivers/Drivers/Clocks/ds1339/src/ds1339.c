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

//int main(int argc, char *argv[])
//{
//
//	printf ("\nHello Real Time Clock!!!!\n");
//
//}

void test()
{

	printf ("\nHello Real Time Clock!!!!\n");

}

int Getsec()
{
	int tmp;
	unsigned char buf[10] = {0};
	if (i2c_init() != XDS_OK)
			printf("I2C initialisation failed\n");
	i2c_read_register(DS1339_ADDR, DS1339_SEC, buf, (uint16_t) 1);
	tmp = (int)((buf[0]& 0b01110000));
	tmp = (tmp >> 4)*10+(int)(buf[0] & 0b00001111);
	//sec = (int)((buf[0] & 0b01110000 )+(buf[0]& 0b00001111));
	//printf("̣\n The second is : %i \n",tmp);
	return(tmp);

}

int Getmin()
{
	int tmp;
	unsigned char buf[10] = {0};
	if (i2c_init() != XDS_OK)
			printf("I2C initialisation failed\n");
	i2c_read_register(DS1339_ADDR, DS1339_MIN, buf, (uint16_t) 1);
	tmp = (int)((buf[0]& 0b01110000));
	tmp = (tmp >> 4)*10+(int)(buf[0] & 0b00001111);
	return(tmp);

}
int Gethour()
{
	int tmp;
	unsigned char buf[10] = {0};
	if (i2c_init() != XDS_OK)
			printf("I2C initialisation failed\n");
	i2c_read_register(DS1339_ADDR, DS1339_HR, buf, (uint16_t) 1);
	tmp = (int)((buf[0]& 0b00110000));
	tmp = (tmp >> 4)*10+(int)(buf[0] & 0b00001111);
	return(tmp);

}
int Getdate()
{
	int tmp;
	unsigned char buf[10] = {0};
	if (i2c_init() != XDS_OK)
			printf("I2C initialisation failed\n");
	i2c_read_register(DS1339_ADDR, DS1339_DAT, buf, (uint16_t) 1);
	tmp = (int)((buf[0]& 0b00110000));
	tmp = (tmp >> 4)*10+(int)(buf[0] & 0b00001111);
	return(tmp);

}
int Getmonth()
{
	int tmp;
	unsigned char buf[10] = {0};
	if (i2c_init() != XDS_OK)
			printf("I2C initialisation failed\n");
	i2c_read_register(DS1339_ADDR, DS1339_MON, buf, (uint16_t) 1);
	tmp = (int)((buf[0]& 0b00010000));
	tmp = (tmp >> 4)*10+(int)(buf[0] & 0b00001111);
	return(tmp);

}
int Getyear()
{
	int tmp;
	unsigned char buf[10] = {0};
	if (i2c_init() != XDS_OK)
			printf("I2C initialisation failed\n");
	i2c_read_register(DS1339_ADDR, DS1339_YR, buf, (uint16_t) 1);
	tmp = (int)((buf[0]& 0b11110000));
	tmp = (tmp >> 4)*10+(int)(buf[0] & 0b00001111);
	return(tmp);

}
