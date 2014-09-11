/*
 * 		Driver for the accelerometer lis331
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

#define LIS331_ADDR			0x18
#define LIS331_CONF_REG1		0x20
#define LIS331_CONF_REG2		0x21
#define LIS331_CONF_REG3		0x22
#define LIS331_CONF_REG4		0x23
#define LIS331_CONF_REG5		0x24
#define LIS331_FILTER_RESET 		0x25
#define LIS331_REFERENCE 		0x26
#define LIS331_STATUS_REG 		0x27
#define LIS331_REG_X_L			0x28
#define LIS331_REG_X_H			0x29
#define LIS331_REG_Z_L			0x2C
#define LIS331_REG_Z_H			0x2D
#define LIS331_REG_Y_L			0x2A
#define LIS331_REG_Y_H			0x2B


void lis331_Init();
float lis331_xval();
float lis331_yval();
float lis331_zval();
