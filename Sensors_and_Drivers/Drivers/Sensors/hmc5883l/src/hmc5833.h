/*
 * 		Driver for the 3D Magnetometer 5833l
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

#define HMC5883L_ADDR				0x1E
#define HMC5883L_REG_X_L			0x04
#define HMC5883L_REG_X_H			0x03
#define HMC5883L_REG_Z_L			0x06
#define HMC5883L_REG_Z_H			0x05
#define HMC5883L_REG_Y_L			0x08
#define HMC5883L_REG_Y_H			0x07
#define HMC5883L_CONF_REG			0x02
#define	HMC5883L_CONF_VAL			0x01

void HMC5833_Init();
float HMC5833_xvalue();
float HMC5833_yvalue();
float HMC5833_zvalue();
