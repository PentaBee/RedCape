//*******************************************************************************
//
//	File:		fpga_isp.c
//	Author:		Kevin Moon
//	Date:		6/4/04
//
//	FPGA ISP port definitions
//
//	Ported to ARMflash by Anton Kachatkou on 31/03/10
//	Modified by Bart for RedCapeA1	28/04/2014
//	The option BEAGLE_BONE_REVA1 was added
//
//*******************************************************************************
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/mman.h>
#include <math.h>
#include <unistd.h>
#include "fpga_isp.h"

#ifndef __uClinux__
static int g_pgnumber = 0;
static int g_pgsize = 0;
static int g_memfiledesc = -1;
void *g_gpiomap = (void *)0;
#if defined(BEAGLE_BONE) || defined(BEAGLE_BONE_REVA1)
void *g_gpiomap3 = (void *)0;
#endif
#endif

int FpgaIspInit (void)
{
#ifdef __uClinux__
	uint32_t	dwReg;

	// set initial data

	dwReg = mbar2_readLong(MCFSIM2_GPIOWRITE);
	dwReg = dwReg & ~ISP_TCK;
	mbar2_writeLong(MCFSIM2_GPIOWRITE, dwReg);

	dwReg = mbar2_readLong(MCFSIM2_GPIO1WRITE);
	dwReg = dwReg & ~(ISP_TMS|ISP_TDI);
	mbar2_writeLong(MCFSIM2_GPIO1WRITE, dwReg);

	// set port directions 1 = output

	dwReg = mbar2_readLong(MCFSIM2_GPIOENABLE);
	dwReg = dwReg | ISP_TCK;
	mbar2_writeLong(MCFSIM2_GPIOENABLE, dwReg);

	dwReg = mbar2_readLong(MCFSIM2_GPIO1ENABLE);
	dwReg = (dwReg | (ISP_TMS|ISP_TDI))
					  | (dwReg & ~ISP_TDO);
	mbar2_writeLong(MCFSIM2_GPIO1ENABLE, dwReg);

	// set port function 1 = gpio

	dwReg = mbar2_readLong(MCFSIM2_GPIOFUNC);
	dwReg = dwReg | ISP_TCK;
	mbar2_writeLong(MCFSIM2_GPIOFUNC, dwReg);

	dwReg = mbar2_readLong(MCFSIM2_GPIO1FUNC);
	dwReg = dwReg | (ISP_TMS|ISP_TDI|ISP_TDO);
	mbar2_writeLong(MCFSIM2_GPIO1FUNC, dwReg);
#else
	if(g_gpiomap)
	{
		printf("FPGA programming interface is already initialized!\n");
		return 0;
	}

	g_pgsize = getpagesize();
	g_pgnumber = (int)ceil((double)(MAP_MASK + 1) / (double)g_pgsize);

#if defined(AF_MINI) || defined(AF_MINI_REVA) || defined(BEAGLE_BONE) || defined(BEAGLE_BONE_REVA1)
	/* make sure that pads are configured correctly */
	void* configmap;
	volatile unsigned int* pad_conf;
	g_memfiledesc = open("/dev/mem", O_RDWR | O_SYNC);
	if (g_memfiledesc < 0)
	{
		perror("open(\"/dev/mem\")");
		return errno;
	}
	configmap = mmap(0, g_pgnumber * g_pgsize, PROT_READ | PROT_WRITE,
			MAP_SHARED, g_memfiledesc, AM335X_CONF_BASE & ~MAP_MASK);
	if (MAP_FAILED == configmap)
	{
		perror("mmap()");
		close(g_memfiledesc);
		return errno;
	}
	printf("Configuring pads\n");
	pad_conf = (unsigned int *) ((char *) configmap + AM335X_TMS);
	*pad_conf = 0x00000047;
	pad_conf = (unsigned int *) ((char *) configmap + AM335X_TDI);
	*pad_conf = 0x00000047;
	pad_conf = (unsigned int *) ((char *) configmap + AM335X_TCK);
	*pad_conf = 0x00000047;
	pad_conf = (unsigned int *) ((char *) configmap + AM335X_TDO);
	*pad_conf = 0x00000067;
	/* unmap SCM registers memory */
	if (0 != munmap(configmap, (size_t) (g_pgnumber * g_pgsize))) {
		perror("munmap()");
		close(g_memfiledesc);
		return errno;
	}

#if defined(BEAGLE_BONE) || defined(BEAGLE_BONE_REVA1)
	/* make sure GPIO3 module's clock is enabled */
	configmap = mmap(0, g_pgnumber * g_pgsize, PROT_READ | PROT_WRITE,
			MAP_SHARED, g_memfiledesc, AM335X_CM_PER & ~MAP_MASK);
	if (MAP_FAILED == configmap)
	{
		perror("mmap()");
		close(g_memfiledesc);
		return errno;
	}
	pad_conf = (unsigned int *) ((char *) configmap + GPIO3_CLK_CTRL);
	printf("GPIO3_CLKCTRL init value: 0x%08x\n", *pad_conf);
	*pad_conf |= 0x00000002; // enable clock
	printf("GPIO3_CLKCTRL new value: 0x%08x\n", *pad_conf);
	if (0 != munmap(configmap, (size_t) (g_pgnumber * g_pgsize))) {
		perror("munmap()");
		close(g_memfiledesc);
		return errno;
	}

#endif
	close(g_memfiledesc);
#endif
	
	g_memfiledesc = open("/dev/mem", O_RDWR | O_SYNC);
	if (g_memfiledesc < 0)
	{
		perror("open(\"/dev/mem\")");
		return errno;
	}

	g_gpiomap = mmap(0, g_pgnumber * g_pgsize, PROT_READ | PROT_WRITE,
			MAP_SHARED, g_memfiledesc, GPIO_BASE_ADDR & ~MAP_MASK);
	if (MAP_FAILED == g_gpiomap)
	{
		perror("mmap()");
		close(g_memfiledesc);
		return errno;
	}

#if	defined(BEAGLE_BONE) || defined(BEAGLE_BONE_REVA1)
	g_gpiomap3 = mmap(0, g_pgnumber * g_pgsize, PROT_READ | PROT_WRITE,
			MAP_SHARED, g_memfiledesc, GPIO_BASE_ADDR3 & ~MAP_MASK);
	if (MAP_FAILED == g_gpiomap3)
	{
		perror("mmap() 3");
		close(g_memfiledesc);
		return errno;
	}
#endif




	//disable wake-up and interrupt requests on GPIO pins
	writeTmsRegister(GPIO_CLEARIRQENABLE1, ISP_TMS);
	writeTmsRegister(GPIO_CLEARIRQENABLE2, ISP_TMS);
	writeTdoRegister(GPIO_CLEARIRQENABLE1, ISP_TDO);
	writeTdoRegister(GPIO_CLEARIRQENABLE2, ISP_TDO);
	writeTckRegister(GPIO_CLEARIRQENABLE1, ISP_TCK);
	writeTckRegister(GPIO_CLEARIRQENABLE2, ISP_TCK);
	writeTdiRegister(GPIO_CLEARIRQENABLE1, ISP_TDI);
	writeTdiRegister(GPIO_CLEARIRQENABLE2, ISP_TDI);
#if !defined(AF_MINI) && !defined(AF_MINI_REVA) && !defined(BEAGLE_BONE) && !defined(BEAGLE_BONE_REVA1)
	writeTmsRegister(GPIO_CLEARWKUENA, ISP_TMS);
	writeTckRegister(GPIO_CLEARWKUENA, ISP_TCK);
	writeTdoRegister(GPIO_CLEARWKUENA, ISP_TDO);
	writeTdiRegister(GPIO_CLEARWKUENA, ISP_TDI);
#endif

	// set initial data
	writeTckRegister(GPIO_CLEARDATAOUT, ISP_TCK);
	writeTmsRegister(GPIO_CLEARDATAOUT, ISP_TMS);
	writeTdiRegister(GPIO_CLEARDATAOUT, ISP_TDI);

	//set ISP_TCK, ISP_TMS, ISP_TDI pins as outputs and ISP_TDO as input
	printf("Initial OE: 0x%x (TCK), 0x%x (TMS), 0x%x (TDI), 0x%x (TDO)\n",
			readTckRegister(GPIO_OE), readTmsRegister(GPIO_OE),
			readTdiRegister(GPIO_OE), readTdoRegister(GPIO_OE));
	unsigned int enableout = readTckRegister(GPIO_OE);
	writeTckRegister(GPIO_OE, enableout & ~(ISP_TCK));
	enableout = readTmsRegister(GPIO_OE);
	writeTmsRegister(GPIO_OE, enableout & ~(ISP_TMS));
	enableout = readTdiRegister(GPIO_OE);
	writeTdiRegister(GPIO_OE, enableout & ~(ISP_TDI));
	enableout = readTdoRegister(GPIO_OE);
	writeTdoRegister(GPIO_OE, ISP_TDO | enableout);
	printf("New OE: 0x%x (TCK), 0x%x (TMS), 0x%x (TDI), 0x%x (TDO)\n",
			readTckRegister(GPIO_OE), readTmsRegister(GPIO_OE),
			readTdiRegister(GPIO_OE), readTdoRegister(GPIO_OE));
#endif

	printf("FPGA programming interface has been successfully initialized\n");

	return 0;
}

void FpgaIspFinalize (void)
{
#ifndef __uClinux__
	if(g_gpiomap){
		if (0 != munmap(g_gpiomap, g_pgnumber * g_pgsize)){
			perror("munmap()");
			close(g_memfiledesc);
			return;
		}
		g_gpiomap = 0;
	}

#if defined(BEAGLE_BONE) || defined(BEAGLE_BONE_REVA1)
	if(g_gpiomap3){
		if (0 != munmap(g_gpiomap3, g_pgnumber * g_pgsize)){
			perror("munmap() 3");
			close(g_memfiledesc);
			return;
		}
		g_gpiomap3 = 0;
	}
#endif



	close(g_memfiledesc);
#endif
	printf("FPGA programming interface has been successfully closed\n");
}
