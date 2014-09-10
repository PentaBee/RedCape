//*******************************************************************************
//
//	File:		fpga_isp.h
//	Author:		Kevin Moon
//	Date:		6/4/04
//
//	FPGA ISP port definitions
//
//	Ported to ARMflash by Anton Kachatkou on 31/03/10
//
//
//	Modified by Bart for RedCapeA1	28/04/2014
//	The option BEAGLE_BONE_REVA1 was added
//
//*******************************************************************************

#ifndef FPGA_ISP_H
#define FPGA_ISP_H

#ifdef __uClinux__
#include "../include/arch/m68k/mcfdefs.h"
#include "../include/types.h"
/*
 * useful definitions for reading/writing MBAR offset memory
 */
#define mbar_readLong(x)      *((volatile unsigned long *) (MCF_MBAR + x))
#define mbar_writeLong(x,y)   *((volatile unsigned long *) (MCF_MBAR + x)) = y
#define mbar_writeShort(x,y)  *((volatile unsigned short *) (MCF_MBAR + x)) = y
#define mbar_writeByte(x,y)   *((volatile unsigned char *) (MCF_MBAR + x)) = y
#define mbar2_readLong(x)     *((volatile unsigned long *) (MCF_MBAR2 + x))
#define mbar2_writeLong(x,y)  *((volatile unsigned long *) (MCF_MBAR2 + x)) = y
#define mbar2_writeShort(x,y) *((volatile unsigned short *) (MCF_MBAR2 + x)) = y
#define mbar2_writeByte(x,y)  *((volatile unsigned char *) (MCF_MBAR2 + x)) = y

// jtag isp read write port bits

#define		ISP_TCK					0x00040000	// tck output bit to jtag chain
#define		ISP_TMS					0x00001000	// tms output bit to jtag chain
#define		ISP_TDI					0x00004000	// tdi output bit to jtag chain
#define		ISP_TDO					0x00010000	// tdo input bit from jtag chain

#else
#if defined(AF_MINI_REVA) || defined(AF_MINI) || defined(BEAGLE_BONE) || defined(BEAGLE_BONE_REVA1)

//EVS ARMflash Mini definitions (for TI AM335x processors)
#define MAP_MASK		0x00000FFF 		//for 4KB space (memory range of GPIO bank's registers)
#define AM335X_CONF_BASE	0x44E10000	/* OMAP processor SCM registers */

//pad config offset values
#ifdef AF_MINI_REVA
#define AM335X_TMS	0x8E8	/* LCDPCLK_GPIO2_24 */
#define AM335X_TDI	0x8E0	/* LCDVSYNC_GPIO2_22 */
#define AM335X_TDO	0x8E4	/* LCDHSYNC_GPIO2_23 */
#define AM335X_TCK	0x8EC	/* LCDPCLK_GPIO2_25 */

#define GPIO_BASE_ADDR		0x481AC000	//base address of the GPIO2 module

// jtag isp read write port bits
#define		ISP_TCK		(unsigned int)(1 << 25)	// tck output bit to jtag chain
#define		ISP_TMS		(unsigned int)(1 << 24)	// tms output bit to jtag chain
#define		ISP_TDI		(unsigned int)(1 << 22)	// tdi output bit to jtag chain
#define		ISP_TDO		(unsigned int)(1 << 23)	// tdo input bit from jtag chain

// all GPIO pins belong to the same GPIO controller (GPIO2)
#define g_gpiomapTck g_gpiomap
#define g_gpiomapTms g_gpiomap
#define g_gpiomapTdi g_gpiomap
#define g_gpiomapTdo g_gpiomap

#else
#if defined(BEAGLE_BONE) || defined(BEAGLE_BONE_REVA1)
//Definitions for both RedCape REV_A and REV_A1
#define AM335X_CM_PER		0x44E00000 //CM_PER registers
#define GPIO3_CLK_CTRL		0x0B4 //GPIO3 module clock control register offset from CM_PER address
#define GPIO_BASE_ADDR0		0x44E07000	//base address of the GPIO0 module
#define GPIO_BASE_ADDR1		0x4804C000	//base address of the GPIO1 module
#define GPIO_BASE_ADDR3		0x481AE000	//base address of the GPIO3 module
#define GPIO_BASE_ADDR		GPIO_BASE_ADDR1
/* BeagleBone specific definition (because we need to use 3 GPIO controllers on BeagleBone) */
extern void* g_gpiomap3;		//start address of the GPIO3 registers' mapped memory




#ifdef BEAGLE_BONE_REVA1
//Specific definitions for REV_A1
#define AM335X_TMS	0x848	/* GPMC_A2_GPIO1_18 --changed*/
#define AM335X_TDI	0x9A4	/* MCASP0_FSR_GPIO3_19 */
#define AM335X_TDO	0x844	/* GPMC_A1_GPIO1_17 */
#define AM335X_TCK	0x84C	/* GPMC_A3_GPIO1_19 --changed*/
// jtag isp read write port bits
#define		ISP_TCK		(unsigned int)(1 << 19)	// tck output bit to jtag chain --changed
#define		ISP_TMS		(unsigned int)(1 << 18)	// tms output bit to jtag chain --changed
#define		ISP_TDI		(unsigned int)(1 << 19)	// tdi output bit to jtag chain
#define		ISP_TDO		(unsigned int)(1 << 17)	// tdo input bit from jtag chain
#define g_gpiomapTck g_gpiomap		//start address of the GPIO registers' mapped memory
#define g_gpiomapTms g_gpiomap		//start address of the GPIO registers' mapped memory
#define g_gpiomapTdi g_gpiomap3		//start address of the GPIO registers' mapped memory
#define g_gpiomapTdo g_gpiomap		//start address of the GPIO registers' mapped memory


#else
//Specific definitions for REV_A
#define AM335X_TMS	0x840	/* GPMC_A0_GPIO1_16 */
#define AM335X_TDI	0x9A4	/* MCASP0_FSR_GPIO3_19 */
#define AM335X_TDO	0x844	/* GPMC_A1_GPIO1_17 */
#define AM335X_TCK	0x9AC	/* MCASP0_AHCLKX_GPIO3_21 */
// jtag isp read write port bits
#define		ISP_TCK		(unsigned int)(1 << 21)	// tck output bit to jtag chain
#define		ISP_TMS		(unsigned int)(1 << 16)	// tms output bit to jtag chain
#define		ISP_TDI		(unsigned int)(1 << 19)	// tdi output bit to jtag chain
#define		ISP_TDO		(unsigned int)(1 << 17)	// tdo input bit from jtag chain

#define g_gpiomapTck g_gpiomap3		//start address of the GPIO registers' mapped memory
#define g_gpiomapTms g_gpiomap		//start address of the GPIO registers' mapped memory
#define g_gpiomapTdi g_gpiomap3		//start address of the GPIO registers' mapped memory
#define g_gpiomapTdo g_gpiomap		//start address of the GPIO registers' mapped memory

#endif

#else

#define AM335X_TMS	0x9A0	/* MCASP0_ACLKR_GPIO3_18 */
#define AM335X_TDI	0x9A8	/* MCASP0_AXR1_GPIO3_20 */
#define AM335X_TDO	0x998	/* MCASP0_AXR0_GPIO3_16 */
#define AM335X_TCK	0x9A4	/* MCASP0_FSR_GPIO3_19 */

#define GPIO_BASE_ADDR		0x481AE000	//base address of the GPIO3 module

// jtag isp read write port bits (consult ARMflash documentation for GPIO-JTAG correspondence)
#define		ISP_TCK		(unsigned int)(1 << 19)	// tck output bit to jtag chain
#define		ISP_TMS		(unsigned int)(1 << 18)	// tms output bit to jtag chain
#define		ISP_TDI		(unsigned int)(1 << 20)	// tdi output bit to jtag chain
#define		ISP_TDO		(unsigned int)(1 << 16)	// tdo input bit from jtag chain

// all GPIO pins belong to the same GPIO controller (GPIO3)
#define g_gpiomapTck g_gpiomap
#define g_gpiomapTms g_gpiomap
#define g_gpiomapTdi g_gpiomap
#define g_gpiomapTdo g_gpiomap



#endif
#endif

//registers' offset values
#define GPIO_OE			0x134
#define GPIO_DATAIN		0x138
#define GPIO_DATAOUT		0x13C
#define GPIO_CLEARIRQENABLE1	0x03C
#define GPIO_CLEARIRQENABLE2	0x040
#define GPIO_CLEARDATAOUT	0x190
#define GPIO_SETDATAOUT		0x194

#else
//EVS ARMflash definitions (for TI OMAP3 and DM37xx processors)
#define MAP_MASK	0x00000FFF 				//for 4KB space (memory range of GPIO bank's registers)

#define GPIO5MODULE_BASE_ADDR	0x49056000		//base address of the 5th GPIO module
#define GPIO_BASE_ADDR		GPIO5MODULE_BASE_ADDR	//base address of the GPIO module

//registers' offset values
#define GPIO_IRQENABLE1			0x01C
#define GPIO_WAKEUPENABLE		0x020
#define GPIO_IRQENABLE2			0x02C
#define GPIO_OE					0x034
#define GPIO_DATAIN				0x038
#define GPIO_DATAOUT			0x03C
#define GPIO_CLEARIRQENABLE1	0x060
#define GPIO_CLEARIRQENABLE2	0x070
#define GPIO_CLEARWKUENA		0x080
#define GPIO_CLEARDATAOUT		0x090
#define GPIO_SETDATAOUT			0x094

//GPIO bits (identify corresponding pins)
#define GPIO_144				(unsigned int)(1 << (144 % 32))
#define GPIO_145				(unsigned int)(1 << (145 % 32))
#define GPIO_146				(unsigned int)(1 << (146 % 32))
#define GPIO_147				(unsigned int)(1 << (147 % 32))

// jtag isp read write port bits (consult ARMflash documentation for GPIO-JTAG correspondence)
#define		ISP_TCK					GPIO_147	// tck output bit to jtag chain
#define		ISP_TMS					GPIO_146	// tms output bit to jtag chain
#define		ISP_TDI					GPIO_144	// tdi output bit to jtag chain
#define		ISP_TDO					GPIO_145	// tdo input bit from jtag chain

// all GPIO pins belong to the same GPIO controller (GPIO5)
#define g_gpiomapTck g_gpiomap
#define g_gpiomapTms g_gpiomap
#define g_gpiomapTdi g_gpiomap
#define g_gpiomapTdo g_gpiomap

#endif

/*
 * useful definitions for reading/writing GPIO offset memory 
 */
//#define gpio_readRegister(reg)      *((volatile unsigned int *) ((unsigned char *)g_gpiomap + reg))
//#define gpio_writeRegister(reg, val)   *((volatile unsigned int *) ((unsigned char *)g_gpiomap + reg)) = val
extern void* g_gpiomap;		//start address of the GPIO registers' mapped memory
#define readTckRegister(reg)      *((volatile unsigned int *) ((unsigned char *)g_gpiomapTck + reg))
#define writeTckRegister(reg, val)   *((volatile unsigned int *) ((unsigned char *)g_gpiomapTck + reg)) = val
#define readTmsRegister(reg)      *((volatile unsigned int *) ((unsigned char *)g_gpiomapTms + reg))
#define writeTmsRegister(reg, val)   *((volatile unsigned int *) ((unsigned char *)g_gpiomapTms + reg)) = val
#define readTdiRegister(reg)      *((volatile unsigned int *) ((unsigned char *)g_gpiomapTdi + reg))
#define writeTdiRegister(reg, val)   *((volatile unsigned int *) ((unsigned char *)g_gpiomapTdi + reg)) = val
#define readTdoRegister(reg)      *((volatile unsigned int *) ((unsigned char *)g_gpiomapTdo + reg))
#define writeTdoRegister(reg, val)   *((volatile unsigned int *) ((unsigned char *)g_gpiomapTdo + reg)) = val

#endif

extern int FpgaIspInit (void);
extern void FpgaIspFinalize (void);

static inline void FpgaIspSetTCK (void)
{
#ifdef __uClinux__
	uint32_t	dwReg;
	dwReg = mbar2_readLong(MCFSIM2_GPIOWRITE);
	dwReg |= ISP_TCK;
	mbar2_writeLong(MCFSIM2_GPIOWRITE, dwReg);
#else
	writeTckRegister(GPIO_SETDATAOUT, ISP_TCK);
	/*printf("DATAOUT (TCK1): 0x%x\n", readTckRegister(GPIO_DATAOUT));*/
#endif
};


static inline void FpgaIspClearTCK (void)
{
#ifdef __uClinux__
	uint32_t	dwReg;
	dwReg = mbar2_readLong(MCFSIM2_GPIOWRITE);
	dwReg &= ~ISP_TCK;
	mbar2_writeLong(MCFSIM2_GPIOWRITE, dwReg);
#else
	writeTckRegister(GPIO_CLEARDATAOUT, ISP_TCK);
	/*printf("DATAOUT (TCK0): 0x%x\n", readTckRegister(GPIO_DATAOUT));*/
#endif
}


static inline void FpgaIspSetTMS (void)
{
#ifdef __uClinux__
	uint32_t	dwReg;
	dwReg = mbar2_readLong(MCFSIM2_GPIO1WRITE);
	dwReg |= ISP_TMS;
	mbar2_writeLong(MCFSIM2_GPIO1WRITE, dwReg);
#else
	writeTmsRegister(GPIO_SETDATAOUT, ISP_TMS);
	/*printf("DATAOUT (TMS1): 0x%x\n", readTmsRegister(GPIO_DATAOUT));*/
#endif
}


static inline void FpgaIspClearTMS (void)
{
#ifdef __uClinux__
	uint32_t	dwReg;
	dwReg = mbar2_readLong(MCFSIM2_GPIO1WRITE);
	dwReg &= ~ISP_TMS;
	mbar2_writeLong(MCFSIM2_GPIO1WRITE, dwReg);
#else
	writeTmsRegister(GPIO_CLEARDATAOUT, ISP_TMS);
	/*printf("DATAOUT (TMS0): 0x%x\n", readTmsRegister(GPIO_DATAOUT));*/
#endif
}


static inline void FpgaIspSetTDI (void)
{
#ifdef __uClinux__
	uint32_t	dwReg;
	dwReg = mbar2_readLong(MCFSIM2_GPIO1WRITE);
	dwReg |= ISP_TDI;
	mbar2_writeLong(MCFSIM2_GPIO1WRITE, dwReg);
#else
	writeTdiRegister(GPIO_SETDATAOUT, ISP_TDI);
	/*printf("DATAOUT (TDI1): 0x%x\n", readTdiRegister(GPIO_DATAOUT));*/
#endif
}


static inline void FpgaIspClearTDI (void)
{
#ifdef __uClinux__
	uint32_t	dwReg;
	dwReg = mbar2_readLong(MCFSIM2_GPIO1WRITE);
	dwReg &= ~ISP_TDI;
	mbar2_writeLong(MCFSIM2_GPIO1WRITE, dwReg);
#else
	writeTdiRegister(GPIO_CLEARDATAOUT, ISP_TDI);
	/*printf("DATAOUT (TDI0): 0x%x\n", readTdiRegister(GPIO_DATAOUT));*/
#endif
}


static inline unsigned int FpgaIspReadTDO (void)
{
#ifdef __uClinux__
	return (mbar2_readLong(MCFSIM2_GPIO1READ)) & ISP_TDO;
#else
	return (readTdoRegister(GPIO_DATAIN) & ISP_TDO);
#endif
}

#endif
