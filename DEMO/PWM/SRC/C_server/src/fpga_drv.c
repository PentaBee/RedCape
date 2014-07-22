/*
 * fpga_drv.c
 *
 *  Created on: 6 May 2011
 *      Author: mchieak4
 */

#define _GNU_SOURCE
#include <stdio.h>

#ifdef __uClinux__
#else
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#endif

#include <math.h>

#include "fpga_regs.h"
#include "fpga_drv.h"
#include "errorcodes.h"

#ifndef __uClinux__
#include "omap_defs.h"
#endif


#ifndef __uClinux__
static int g_pgnumber = 0;
static int g_pgsize = 0;
static int g_memfiledesc = -1;
void *g_fpgamap = (void *)0;
#endif

extern	uint8_t	DebugFlag;

uint32_t InitFpga()
{
	uint16_t	wReg;

#ifndef __uClinux__
	void* 	configmap;
	volatile uint16_t* gpmc_clk_conf;
	OMAP_GPMC_REGS_T *gpmc_cfg;

	/* configure GPMC */
	if(!g_fpgamap)
	{
		g_pgsize = getpagesize();

		g_pgnumber = (int)ceil((double)(OMAP_MEM_MAP_MASK + 1) / (double)g_pgsize);

		g_memfiledesc = open("/dev/mem", O_RDWR | O_SYNC);
		if (g_memfiledesc < 0)
		{

			if(DebugFlag){

				perror("open(\"/dev/mem\")");

			}
			return XDS_E_MEM_INIT;
		}

		/* configure gpmc_clk to enable input (required for synchronous read) */
		/* map SCM registers' memory */

		configmap = mmap(0, (size_t)(g_pgnumber * g_pgsize), PROT_READ | PROT_WRITE,
				MAP_SHARED, g_memfiledesc, OMAP_CONF_BASE & ~OMAP_MEM_MAP_MASK);

		if (MAP_FAILED == configmap)
		{

			if(DebugFlag){

				perror("mmap()");

			}
			close(g_memfiledesc);
			return XDS_E_MEM_INIT;

		}
		/* set input enable bit of the gpmc_clk register */
		gpmc_clk_conf = (uint16_t *)((uint8_t *)configmap + OMAP_CONF_GPMC_CLK);
		*gpmc_clk_conf |= OMAP_CONF_BIT_IEN;
		/* unmap SCM registers memory */


		if (0 != munmap(configmap, (size_t)(g_pgnumber * g_pgsize)))
		{

			if(DebugFlag){

				perror("munmap()");

			}
			close(g_memfiledesc);
			return XDS_E_MEM_INIT;

		}

		/* configure OMAP GPMC chip select 0 (CS0) registers to communicate with FPGA */
		/* map GPMC registers' memory */

		configmap = mmap(0, (size_t)(g_pgnumber * g_pgsize), PROT_READ | PROT_WRITE,
				MAP_SHARED, g_memfiledesc, OMAP_GPMC_BASE & ~OMAP_MEM_MAP_MASK);

		if (MAP_FAILED == configmap)
		{

			if(DebugFlag)
				perror("mmap()");
			close(g_memfiledesc);
			return XDS_E_MEM_INIT;
		}

		/* get address of gpmc registers */
		gpmc_cfg = (OMAP_GPMC_REGS_T *) configmap;


		/* write CS0 configuration registers */

		gpmc_cfg->config = gpmc_cfg->config | OMAP_GPMC_CONF_LIMITEDADDRESS;
		gpmc_cfg->cs[0].config7 = 0; /* disable CS first */
		usleep(1000);				/* delay for settling */
		gpmc_cfg->cs[0].config1 = OMAP_ARMFLASH_FPGA_CONFIG1;
		gpmc_cfg->cs[0].config2 = OMAP_ARMFLASH_FPGA_CONFIG2;
		gpmc_cfg->cs[0].config3 = OMAP_ARMFLASH_FPGA_CONFIG3;
		gpmc_cfg->cs[0].config4 = OMAP_ARMFLASH_FPGA_CONFIG4;
		gpmc_cfg->cs[0].config5 = OMAP_ARMFLASH_FPGA_CONFIG5;
		gpmc_cfg->cs[0].config6 = OMAP_ARMFLASH_FPGA_CONFIG6;
		gpmc_cfg->cs[0].config7 = OMAP_ARMFLASH_FPGA_CONFIG7; /* complete configuration and enable CS */

		usleep(1000);				/* delay for settling */

		/* uumap GPMC registers' memory */
		if (0 != munmap(configmap, (size_t)(g_pgnumber * g_pgsize)))
		{
			if(DebugFlag)
				perror("munmap()");
			close(g_memfiledesc);
			return XDS_E_MEM_INIT;
		}

		/* map FPGA registers' memory */
		g_fpgamap = mmap(0, (size_t)(g_pgnumber * g_pgsize), PROT_READ | PROT_WRITE,
				MAP_SHARED, g_memfiledesc, OMAP_ARMFLASH_FPGA_BASE & ~OMAP_MEM_MAP_MASK);

		if (MAP_FAILED == g_fpgamap)
		{

			if(DebugFlag)
				perror("mmap()");
			close(g_memfiledesc);
			return XDS_E_MEM_INIT;
		}

	}
#endif

	fpga_write_short(FPGA_RESET, 0); /* reset FPGA */


	/* Read FPGA ID register */
	fpga_write_short(FPGA_ADDR, CS_HOST_CTRL);
	wReg = fpga_read_short(HOST_ID);
	if (wReg != FPGA_ID_CODE) {
		if(DebugFlag)
			printf ("\nFPGA ID code error - wrong FPGA code??\n");
		return XDS_E_FPGA_ID;
	}

	return XDS_OK;
}

