/*
 * fpga_drv.h
 *
 *  Created on: 6 May 2011
 *      Author: mchieak4
 */

#ifndef FPGA_DRV_H_
#define FPGA_DRV_H_

#include <stdint.h>

#ifdef __uClinux__
#define	FPGA_BASE	0x40000000		// base address for fpga registers
#else
extern void *g_fpgamap;
#define	FPGA_BASE	(unsigned char *)g_fpgamap
#endif

#define fpga_read_short(addr)		*((volatile uint16_t *) (FPGA_BASE + (addr)))
#define fpga_write_short(addr, data)	*((volatile uint16_t *) (FPGA_BASE + (addr))) = (uint16_t)(data)

uint32_t InitFpga();

#endif /* FPGA_DRV_H_ */
