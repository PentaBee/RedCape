/*
 * 		Driver for the l3dg20
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

#define L3GD20_ADDR			0x6A
#define L3GD20_CTRL_REG1		0x20
#define L3GD20_CTRL_REG2		0x21
#define L3GD20_CTRL_REG3		0x22
#define L3GD20_CTRL_REG4		0x23
#define L3GD20_CTRL_REG5		0x24
#define	L3GD20_REFERENCE		0x25
#define L3GD20_REG_TEMP			0x26
#define	L3GD20_REG_X_L			0x28
#define L3GD20_REG_X_H			0x29
#define L3GD20_REG_Y_L			0x2A
#define L3GD20_REG_Y_H			0x2B
#define L3GD20_REG_Z_L			0x2C
#define L3GD20_REG_Z_H			0x2D
#define	L3GD20_FIFO_CTRL_REG		0x2E
#define L3GD20_FIFO_SRC_REG		0x2F

//Initialise the device and start giving values at a 95Hz frequency
void l3gd20_Init();
float l3gd20_xval();
float l3gd20_yval();
float l3gd20_zval();
