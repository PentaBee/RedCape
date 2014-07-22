/*
 * omap_defs.h
 *
 *  Created on: 20 Apr 2010
 *      Author: Anton Kachatkou
 *
 *  Contains register addresses and bit definitions for OMAP 35xx processor
 *
 */

#ifndef OMAP_DEFS_H_
#define OMAP_DEFS_H_

/* rechanged to 00000FFF from 00001FFF */
#define OMAP_MEM_MAP_MASK	0x00000FFF	/* map 4KB memory regions */


/*BBB registers, correct addresses of the registers for the beaglebone black, ARM335x */
#define OMAP_CONF_BASE		0x44E10000
#define OMAP_GPMC_BASE		0x50000000   /* BBB AM335x processor GPMC registers*/
/* SCM registers */
#define OMAP_CONF_GPMC_CLK	0x000000BE















/* GPMC registers */
typedef struct
#ifndef WIN32
__attribute__((packed))
#endif
{
	uint32_t config1;		/* 0x00 */
	uint32_t config2;		/* 0x04 */
	uint32_t config3;		/* 0x08 */
	uint32_t config4;		/* 0x0C */
	uint32_t config5;		/* 0x10 */
	uint32_t config6;		/* 0x14 */
	uint32_t config7;		/* 0x18 */
	uint32_t nand_cmd;		/* 0x1C */
	uint32_t nand_adr;		/* 0x20 */
	uint32_t nand_dat;		/* 0x24 */
	uint8_t res[8];			/* blow up to 0x30 byte */
} OMAP_GPMC_CS_T;

typedef struct
#ifndef WIN32
__attribute__((packed))
#endif
{
	uint8_t res1[0x10];
	uint32_t sysconfig;				/* 0x10 */
	uint32_t systatus;				/* 0x14 */
	uint32_t irqstatus;				/* 0x18 */
	uint32_t irqenable;				/* 0x1C */
	uint8_t res3[0x20];
	uint32_t timeout_control; 		/* 0x40 */
	uint32_t err_address;			/* 0x44 */
	uint32_t err_type;				/* 0x48 */
	uint8_t res4[0x4];
	uint32_t config;				/* 0x50 */
	uint32_t status;				/* 0x54 */
	uint8_t res5[0x8];				/* 0x58 */
	OMAP_GPMC_CS_T cs[8];					/* 0x60, 0x90, .. */
	uint8_t res6[0x14];				/* 0x1E0 */
	uint32_t ecc_config;			/* 0x1F4 */
	uint32_t ecc_control;			/* 0x1F8 */
	uint32_t ecc_size_config;		/* 0x1FC */
	uint32_t ecc1_result;			/* 0x200 */
	uint32_t ecc2_result;			/* 0x204 */
	uint32_t ecc3_result;			/* 0x208 */
	uint32_t ecc4_result;			/* 0x20C */
	uint32_t ecc5_result;			/* 0x210 */
	uint32_t ecc6_result;			/* 0x214 */
	uint32_t ecc7_result;			/* 0x218 */
	uint32_t ecc8_result;			/* 0x21C */
	uint32_t ecc9_result;			/* 0x220 */
} OMAP_GPMC_REGS_T;

/* GPMC memory size masks */
#define OMAP_GPMC_SIZE_128M			0x8
#define OMAP_GPMC_SIZE_64M			0xC
#define OMAP_GPMC_SIZE_32M			0xE
#define OMAP_GPMC_SIZE_16M			0xF

/* SCM registers' bits */
#define OMAP_CONF_BIT_IEN				(1 << 8)

/* GPMC registers' bits */
#define OMAP_GPMC_CONF_LIMITEDADDRESS	(1 << 1)

/* ARMFlash FPGA memory parameters */
#define OMAP_ARMFLASH_FPGA_BASE		0x0F000000			/* base address */
#define OMAP_ARMFLASH_FPGA_SIZE		OMAP_GPMC_SIZE_16M	/* memory size mask for 16 MB */

/*******************************************************************
 * GPMC CS1 (chip select 0) settings for ARMFlash FPGA communication
 * */

/* Register 1, value 0x28001000
 * Single-word synchronous address/data non-multiplexed read/write access */
#define OMAP_ARMFLASH_FPGA_CONFIG1	(0 << 30) | 			/* single read access */ \
									(1 << 29) |				/* sync read */ \
									(0 << 28) | 			/* single write access */ \
									(1 << 27) | 			/* sync write */ \
									((0x0 & 0x3) << 25) |	/* GPMC_CLK active at start access time */ \
									(0 << 22) |				/* no wait monitoring on read */ \
									(0 << 21) |				/* no wait monitoring on write */ \
									((0x1 & 0x3) << 12) |	/* 16-bit wide device */ \
									((0x0 & 0x3) << 10) |	/* NOR flash like device */ \
									(0 << 9) |				/* non-multiplexed device */ \
									((0x2 & 0x3))			/* GPMC_CLK = GPMC_FCLK (100 MHz) */

/* Register 2, value 0x000D1000
 * CS signal */
#define OMAP_ARMFLASH_FPGA_CONFIG2	((0x0D & 0x1F) << 16) |	/* CSWROFFTIME after 13th GPMC_FCLK cycle */ \
									((0x10 & 0x1F) << 8) |	/* CSRDOFFTIME after 16th GPMC_FCLK cycle */ \
									((0x0 & 0xF))			/* CSONTIME after 0th GPMC_FCLK cycle */
/* Register 3, value 0x00020201
 * nADV pin is not used -> just use default settings for GPMC_CONFIG3_1 register */
#define OMAP_ARMFLASH_FPGA_CONFIG3	((0x02 & 0x1F) << 16) |	/* ADVWROFFTIME on 2nd GPMC_FCLK cycle */ \
									((0x02 & 0x1F) << 8) |	/* ADVRDOFFTIME on 2nd GPMC_FCLK cycle */ \
									((0x1 & 0xF))			/* ADVONTIME on 1st GPMC_FCLK cycle */
/* Register 4, value 0x0D00100A
 * nWE and nOE (write and output enable signals) */
#define OMAP_ARMFLASH_FPGA_CONFIG4	((0x0D & 0x1F) << 24) |	/* WEOFFTIME after 13th GPMC_FCLK cycle */ \
									(0 << 23) |				/* no extra delay in nWE */ \
									((0x0 & 0xF) << 16) |	/* WEONTIME after 0th GPMC_FCLK cycle */ \
									((0x10 & 0x1F) << 8) |	/* OEOFFTIME after 16th GPMC_FCLK cycle */ \
									(0 << 7) |				/* no extra delay in nOE */ \
									((0xA & 0xF))			/* OEONTIME after 10th GPMC_FCLK cycle */
/* Register 5, value 0x000F0D10
 * RdAccessTime and CycleTime parameters */
#define OMAP_ARMFLASH_FPGA_CONFIG5	((0x0 & 0xF) << 24) |	/* no burst read (single access) -
															use 0x0 for PAGEBURSTACCESSTIME */ \
									((0x0F & 0x1F) << 16) |	/* 15 GPMC_FCLK cycle delay between start
															access time and first data valid
															on read (RDACCESSTIME) */ \
									((0x0D & 0x1F) << 8) |	/* 13 GPMC_FCLK cycles for total
															write cycle time (WRCYCLETIME)*/ \
									((0x10 & 0x1F))			/* 16 GPMC_FCLK cycles for total
															read cycle time (RDCYCLETIME)*/
/* Register 6, value 0x0C000000
 * WrAccessTime and delay between successive accesses */
#define OMAP_ARMFLASH_FPGA_CONFIG6	((0x0C & 0x1F) << 24) |	/* 12 GPMC_FCLK cycle delay between start
															access time and GPMC_FCLK rising edge
															corresponding to GPMC_CLK rising edge
															used by the FPGA for the first data
															capture (WRACCESSTIME) */ \
									((0x0 & 0xF) << 16) |	/* no address/data multiplexing -
															use 0x0 for WRDATAONADMUXBUS */ \
									((0x0 & 0xF) << 8) |	/* zero delay between successive
															accesses (CYCLE2CYCLEDELAY) */ \
									(0 << 7) |				/* don't add delay between successive
															accesses to the same CS
															(CYCLE2CYCLESAMECSEN) */ \
									(0 << 6) |				/* don't add delay between successive
															accesses to a different CS
															(CYCLE2CYCLEDIFFCSEN) */ \
									((0x0 & 0xF))			/* 0 bus turn around latency - no delay
															between nCS or nOE de-assertion time
															and the next access start-cycle time */
/* Register 7, value 0x00000F60
 * CS address mapping and CS enabling */
#define OMAP_ARMFLASH_FPGA_CONFIG7  ((OMAP_ARMFLASH_FPGA_SIZE & 0xF) << 8) | /* CS mask address
																corresponding to the size of
																the memory allocated to FPGA */ \
									(1 << 6) | 					/* enable CS */ \
									((OMAP_ARMFLASH_FPGA_BASE >> 24) & 0x3F) /* set CS base address with 16 MB
																granularity */
/* *
 * End of GPMC CS1 (chip select 1) settings for ARMFlash FPGA communication
 **************************************************************************/

#endif /* OMAP_DEFS_H_ */
