/*
 * 		Register library for ClockGenerator Si5338
 * 		I2C device attached in RedCape A1, used I2C bus - 1
 *
 *
 * 		Code by: Bart Garcia
 *
 *
 * 		Date : 7 - 05 - 2014
 *
 *
 *
 *
 */
#define SI5338_ADDR				0x70
#define SI5338_REG_OEB_ALL		0xE6
#define SI5338_VAL_OEB_ALL		0x10
#define SI5338_REG_DIS_LOL		0xF1
#define SI5338_VAL_DIS_LOL		0x80
#define SI5338_VAL_DIS_LOL_RST	0x7F
#define SI5338_VAL_DIS_LOL_RST2	0x65
#define SI5338_REG_ALARMS		0xDA
#define SI5338_REG_PLL_LOCK		0x31
#define SI5338_VAL_PLL_LOCK		0x7F
#define SI5338_REG_PLL_LOCK_RES	0xF6
#define SI5338_VAL_PLL_LOCK_RES	0x02



#define SI5338_REG_237			0xED
#define SI5338_REG_236			0xEC
#define SI5338_REG_235			0xEB
#define SI5338_REG_47			0x2F
#define SI5338_REG_47_VAL		0x14
#define SI5338_REG_47_MASK		0x03
#define SI5338_REG_46			0x2E
#define SI5338_REG_45			0x2D
#define SI5338_REG_49			0x31
#define SI5338_VAL_49			0x80
