/*
 * 		Driver for Differential Pressure sensor ms5611
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
#define MS5611_ADDR				0x76
#define MS5611_CAL_REG1			0x20
#define MS5611_CAL_REG2			0x21
#define MS5611_CAL_REG3			0x22
#define MS5611_CAL_REG4			0x23
#define MS5611_CAL_REG5			0x24
#define MS5611_CAL_REG5			0x24
#define MS5611_REG_TEMP			0x26
#define MS5611_REG_PRES			0x26
#define	MS5611_REG_X_L			0x28
#define MS5611_REG_X_H			0x29
#define MS5611_REG_Y_L			0x2A
#define MS5611_REG_Y_H			0x2B
#define MS5611_REG_Z_L			0x2C
#define MS5611_REG_Z_H			0x2D
#define	MS5611_FIFO_CAL_REG		0x2E
#define MS5611_FIFO_SRC_REG		0x2F


void ms5611_GetcalData(unsigned int C[6]);
//void ms5611_GetValues(unsigned int C[6],double PRESS , double TEMP);
void ms5611_GetValues(unsigned int C[6],float val[2]);

