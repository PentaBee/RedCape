/////////////////////////////////////////////////////////////////////////////
//
//	File : i2c_drv.c
//
//	Description : I2C-bus programming interface (implementation)
//
//  Authors : Roelof van Silfhout, Anton Kachatkou
//
//  Date Created : 18/02/2009
//
/////////////////////////////////////////////////////////////////////////////

#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <linux/i2c-dev.h> /* for I2C_SLAVE */
#include <string.h>

#include "i2c_drv.h"
#include "errorcodes.h"

extern uint8_t DebugFlag;

static int g_i2cfiledesc = -1;
static int g_i2cerr = 0;		//internal error code (TODO: provide library callers with a read routine)
static uint8_t *g_buf = 0;
static size_t g_bufsz = 0;

//I2C-bus initialisation
uint32_t i2c_init()
{
	uint32_t res = XDS_OK;
#ifdef	__uClinux__
	char devstr[] = "/dev/i2c-0";
#else
	char devstr[] = "/dev/i2c-3";
#endif

	if(DebugFlag)
		printf("Initialising I2C\n");

	g_i2cfiledesc = open(devstr, O_RDWR | O_SYNC);
	if (g_i2cfiledesc < 0)
	{
		if(DebugFlag)
			perror(devstr);
		g_i2cerr = errno;
		res = XDS_E_I2C_INIT;
	}

	if(XDS_OK == res)
	{
		g_buf = malloc(4); /* 4 bytes - default buffer size */
		if (g_buf)
			g_bufsz = 4;
		else
		{
			i2c_finalize();
			res = XDS_E_OUT_OF_MEMORY;
		}
	}

	return res;
}

//releases resources captured by i2c_init()
uint32_t i2c_finalize()
{
	if(g_i2cfiledesc >= 0)
	{
		close(g_i2cfiledesc);
		g_i2cfiledesc = -1;
	}
	if (0 != g_bufsz)
	{
		free(g_buf);
		g_bufsz = 0;
	}
}

/* Select a I2C device to communicate with */
uint32_t i2c_select_dev(uint16_t addr)
{
	if (ioctl(g_i2cfiledesc, I2C_SLAVE, addr) < 0)
	{
		if(DebugFlag)
			perror("I2C: ioctl(I2C_SLAVE)");
		g_i2cerr = errno;
		return XDS_E_I2C;
	}
	return XDS_OK;
}
/* Send a message to the device previously selected by i2c_select_dev() */
uint32_t i2c_transmit_msg(const uint8_t *msg, size_t len)
{
	ssize_t ssz = (ssize_t)len;
	if (write(g_i2cfiledesc, msg, len) != ssz)
	{
		if(DebugFlag)
			perror("I2C: write message");
		g_i2cerr = errno;
		return XDS_E_I2C;
	}
	return XDS_OK;
}

/* Receive a message from the device previously selected by i2c_select_dev() */
uint32_t i2c_receive_msg(uint8_t *msg, size_t len)
{
	ssize_t retssz, ssz = (ssize_t)len;
	retssz = read(g_i2cfiledesc, msg, len);
	if(retssz != ssz)
	{
		if(DebugFlag)
			perror("I2C: read message");
		g_i2cerr = (retssz >= 0) ? 0 : errno;
		return XDS_E_I2C;
	}
	return XDS_OK;
}

/* Read selected register from the selected device */
uint32_t i2c_read_register(uint8_t addr, uint8_t reg, uint8_t *data, size_t sz)
{
	if(DebugFlag)
		printf("Reading from register 0x%.2x of device 0x%.2x\n", reg, addr);
	uint32_t dwRes = i2c_select_dev(addr);
	if(XDS_OK != dwRes)
		return dwRes;
	if(XDS_OK != (dwRes = i2c_transmit_msg(&reg, 1)))
		return dwRes;
	dwRes = i2c_receive_msg(data, sz);
	if(DebugFlag && XDS_OK == dwRes)
		printf("First byte of the returned message: 0x%.2x\n", data[0]);
	return dwRes;
}

/* Write data to the selected register of the selected device */
uint32_t i2c_write_register(uint8_t addr, uint8_t reg, const uint8_t *data, size_t sz)
{
	if(DebugFlag)
		printf("Writing %u bytes to register 0x%.2x of device 0x%.2x\n", sz, reg, addr);
	size_t msgsz = sz + 1;
	if (msgsz < g_bufsz)
	{
		free(g_buf);
		g_buf = malloc(msgsz);
		if (g_buf)
			g_bufsz = msgsz;
		else
		{
			g_bufsz = 0;
			return XDS_E_OUT_OF_MEMORY;
		}
	}
	uint32_t dwRes = i2c_select_dev(addr);
	if(XDS_OK != dwRes)
		return dwRes;

	g_buf[0] = reg;
	memcpy(&g_buf[1], data, sz);
	dwRes = i2c_transmit_msg(g_buf, msgsz);
	return dwRes;
}

/*
/////////////////////////////////////////////////////////////////////////////
//
//	File : i2c_drv.c
//
//	Description : I2C-bus programming interface (implementation)
//
//  Authors : Roelof van Silfhout, Anton Kachatkou
//
//  Date Created : 18/02/2009
//
/////////////////////////////////////////////////////////////////////////////

#ifdef WIN32

#include <stdio.h>
#include <windows.h>
#include <time.h> //to include timeval definition

#else

#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdint.h>

#ifndef __uClinux__
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <linux/i2c-dev.h> // for I2C_SLAVE
#endif

#endif

#include "i2c_drv.h"
#include "errorcodes.h"

extern uint8_t DebugFlag;

#ifdef WIN32 //define gettimeofday function here (doesn't exist on Windows)

#if defined(_MSC_VER) || defined(_MSC_EXTENSIONS)
  #define DELTA_EPOCH_IN_MICROSECS  11644473600000000Ui64
#else
  #define DELTA_EPOCH_IN_MICROSECS  11644473600000000ULL
#endif

struct timezone
{
  int  tz_minuteswest; //* minutes W of Greenwich
  int  tz_dsttime;     //* type of dst correction
};

int gettimeofday(struct timeval *tv, struct timezone *tz)
{
  FILETIME ft;
  unsigned __int64 tmpres = 0;
  static int tzflag;
  long tmp;

  if (NULL != tv)
  {
    GetSystemTimeAsFileTime(&ft);

    tmpres |= ft.dwHighDateTime;
    tmpres <<= 32;
    tmpres |= ft.dwLowDateTime;

    //*converting file time to unix epoch
    tmpres /= 10;  //*convert into microseconds
    tmpres -= DELTA_EPOCH_IN_MICROSECS;
    tv->tv_sec = (long)(tmpres / 1000000UL);
    tv->tv_usec = (long)(tmpres % 1000000UL);
  }

  if (NULL != tz)
  {
    if (!tzflag)
    {
      _tzset();
      tzflag++;
    }

    //*tz->tz_minuteswest = _timezone / 60;
    //*tz->tz_dsttime = _daylight;
	//call new safer functions instead
	_get_timezone(&tmp);
	tz->tz_minuteswest = tmp;
	_get_daylight(&tz->tz_dsttime);
  }

  return 0;
}

#endif //WIN32

#ifndef __uClinux__
static int g_i2cfiledesc = -1;
static int g_i2cerr = 0;		//internal error code (TODO: provide library callers with a read routine)
#endif

//I2C-bus initialisation
uint32_t i2c_init()
{
	uint32_t res;

	if(DebugFlag)
		printf("Initialising I2C\n");

#ifdef	__uClinux__
	// initialise the I2C channel 0 present on Coldfire
	*PLLCR = *PLLCR & 0xFFFFF7FF;//0xFFFFFF7FF;	// setup clock source
	*MFDR = 0x19;	//divide by 1280 to give just under 100khz i2c speed
	*MBCR = 0;
	*MBCR = 0x90;	//0b10010000  - enable I2C controller, no interrupts enabled
	res = i2c_waitbusfree();	//wait until bus is free
#else
	g_i2cfiledesc = open("/dev/i2c-3", O_RDWR | O_SYNC);
	if (g_i2cfiledesc < 0)
	{
		if(DebugFlag)
			perror("open(\"/dev/i2c-3\")");
		g_i2cerr = errno;
		res = XDS_E_I2C_INIT;
	}
#endif

	return res;
}

//releases resources captured by i2c_init()
uint32_t i2c_finalize()
{
#ifndef __uClinux__
	if(g_i2cfiledesc >= 0)
	{
		close(g_i2cfiledesc);
		g_i2cfiledesc = -1;
	}
#endif
}

#ifdef	__uClinux__
//call before writing to the bus
void i2c_startwriting()
{
	BITSET(*MBCR,5);	// set start condition
	BITSET(*MBCR,4);	// set write mode
}
//initiates I2C stop condition and waits until bus is free,
//must be called after any data transmission via the bus
uint32_t i2c_stopcondition()
{
	BITCLR(*MBCR,5);	// generate STOP condition on I2C bus
	return i2c_waitbusfree();
}

//call when you need to switch to reading during the data
//transfer cycle (between successive i2c_startwriting and
//i2c_stopcondition calls)
void i2c_switchtoreading()
{
	BITCLR(*MBCR,4);
}

// I2C wait for completion of task
uint32_t i2c_waitforinterruptflag() {
	struct timeval starttime;
	struct timeval now, waited;
	gettimeofday(&starttime,NULL);

	if (DebugFlag)
		printf("started waiting for intterrupt flag\n");
	while (!BITGET(*MBSR,1)) {
		gettimeofday(&now,NULL);
		waited.tv_sec = now.tv_sec - starttime.tv_sec;
		waited.tv_usec = now.tv_usec - starttime.tv_usec;
		if (now.tv_usec < starttime.tv_usec) {
			waited.tv_usec = waited.tv_usec + 1000000;
			waited.tv_sec = waited.tv_sec - 1;

		}
		if (waited.tv_sec > 1) {
			if(DebugFlag)
				printf("timed out waiting for intterrupt flag (*MBSR: 0x%x, MBCR: 0x%x)\n", *MBSR, *MBCR);
			return XDS_E_I2C;
		}
	}
	if (DebugFlag)
		printf("finished waiting for interrupt flag (*MBSR: 0x%x, MBCR: 0x%x)\n", *MBSR, *MBCR);
	return XDS_OK;
}

// I2C wait for bus to become free
uint32_t i2c_waitbusfree() {
	struct timeval starttime,now,waited;
	gettimeofday(&starttime,NULL);
	//if (DebugFlag)
	//	printf("waiting for the bus to become free\n");
	while (BITGET(*MBSR,5)) {
		gettimeofday(&now,NULL);
		waited.tv_sec = now.tv_sec - starttime.tv_sec;
		waited.tv_usec = now.tv_usec - starttime.tv_usec;
		if (now.tv_usec < starttime.tv_usec) {
			waited.tv_usec = waited.tv_usec + 1000000;
			waited.tv_sec = waited.tv_sec - 1;

		}
		if (waited.tv_sec > 1) {
			if(DebugFlag)
				printf("timed out waiting for i2c bus to become free, this most likely means there are no pullups on the bus\n");
			return XDS_E_I2C;
		}
	}
	//if (DebugFlag)
	//	printf("finished waiting for the bus to become free\n");
	return XDS_OK;
}

// Write I2C byte
uint32_t i2c_ffi2ctransmitbyte(uint8_t b) {
	uint32_t dwRes;

	BITCLR(*MBSR,1);  //clear iif bit
	*MBDR = b;		//send byte
	//wait for interrupt flag (interrupts are disabled so there will not actually be an interrupt)
	if (DebugFlag){
		//printf("*MBSR is 0x%x\n",BITGET(*MBSR,1));
		//printf("BITGET(128,7)==%i\n",BITGET(128,7));
	}
	dwRes = i2c_waitforinterruptflag();
	if (DebugFlag)
		printf("rxack is %i\n",BITGET(*MBSR,0));
	return dwRes;
}

// Receive I2C byte
uint32_t i2c_ffi2creceivebyte(uint8_t *pB) {

	if (DebugFlag)
		printf("in ffi2creceivebyte\n");
	BITCLR(*MBSR,1);	// clear iif bit
	*pB = *MBDR;    //send byte
	//wait for interrupt flag (interrupts are disabled so there will not actually be an interrupt)
	if (DebugFlag){
		//printf("*MBSR is 0x%x\n",BITGET(*MBSR,1));
		//printf("BITGET(128,7)==%i\n",BITGET(128,7));
	}
	return i2c_waitforinterruptflag();
}

//force interrupt I2C bus and resets I2C registers
//this is similar to i2c_stopcondition()
uint32_t i2c_interruptBus(){
	uint8_t dummy;

	//formal procedure on MCF5249 datasheet
    *MBCR = 0x00; //issue STOP condition
    *MBCR = 0xA0; //enable I2C, master mode (START condition), read mode
    dummy = *MBDR;  //dummy read from bus
    *MBCR = 0x00; //disable I2C and go to slave mode (STOP condition)
    *MBSR = 0x00; //clear status
    *MBCR = 0x90; //enable I2C, slave mode (STOP condition), write mode

	return i2c_waitbusfree();
}
#else //* ARM

//* Select a I2C device to communicate with
uint32_t i2c_select_dev(uint16_t addr)
{
	if (ioctl(g_i2cfiledesc, I2C_SLAVE, addr) < 0)
	{
		if(DebugFlag)
			perror("I2C: ioctl(I2C_SLAVE)");
		g_i2cerr = errno;
		return XDS_E_I2C;
	}
	return XDS_OK;
}
//* Send a message to the device previously selected by i2c_select_dev()
uint32_t i2c_transmit_msg(const uint8_t *msg, uint16_t len)
{
	ssize_t ssz = (ssize_t)len;
	if (write(g_i2cfiledesc, msg, len) != ssz)
	{
		if(DebugFlag)
			perror("I2C: write message");
		g_i2cerr = errno;
		return XDS_E_I2C;
	}
	return XDS_OK;
}

//* Receive a message from the device previously selected by i2c_select_dev()
uint32_t i2c_receive_msg(uint8_t *msg, uint16_t len)
{
	ssize_t retssz, ssz = (ssize_t)len;
	retssz = read(g_i2cfiledesc, msg, len);
	if(retssz != ssz)
	{
		if(DebugFlag)
			perror("I2C: read message");
		g_i2cerr = (retssz >= 0) ? 0 : errno;
		return XDS_E_I2C;
	}
	return XDS_OK;
}

#endif //*__uClinux__

*/
