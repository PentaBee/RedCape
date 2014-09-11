/*
 * 		Register library for Real Time Clock DS1339
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
//Definitions
#define DS1339_ADDR				0x68
#define	DS1339_SEC				0x00
#define DS1339_MIN				0x01
#define DS1339_HR				0x02
#define DS1339_DAY				0x03
#define DS1339_DAT				0x04
#define DS1339_MON				0x05
#define DS1339_YR				0x06








//Functions
void test();
int Getsec();
int Getmin();
int Gethour();
int Getdate();
int Getmonth();
int Getyear();
