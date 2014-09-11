/*
 * 		Register library for Integrated IMU MPU6000
 * 		I2C device attached in RedCape A1, used I2C bus - 1
 *
 *
 * 		Code by: Bart Garcia
 *
 *
 * 		Date : 6 - 05 - 2014
 *
 *
 *
 *
 */


#define MPU6000_ADDR				0x69
#define	MPU6000_PWR_MGMT_1      	0x6B
#define MPU6000_REG_ACCEL_X_H       0x3B
#define MPU6000_REG_ACCEL_X_L       0x3C   // R
#define MPU6000_REG_ACCEL_Y_H       0x3D   // R
#define MPU6000_REG_ACCEL_Y_L       0x3E   // R
#define MPU6000_REG_ACCEL_Z_H       0x3F   // R
#define MPU6000_REG_ACCEL_Z_L       0x40   // R
#define MPU6000_REG_TEMP_H         	0x41   // R
#define MPU6000_REG_TEMP_L         	0x42   // R
#define MPU6000_REG_GYRO_X_H        0x43   // R
#define MPU6000_REG_GYRO_X_L        0x44   // R
#define MPU6000_REG_GYRO_Y_H        0x45   // R
#define MPU6000_REG_GYRO_Y_L        0x46   // R
#define MPU6000_REG_GYRO_Z_H        0x47   // R
#define MPU6000_REG_GYRO_Z_L        0x48   //
#define MPU6000_REG_WHO_AM_I 		0x75


void mpu6000_Init();

void mpu6000_GetValues(float values[6]);
