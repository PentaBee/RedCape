/////////////////////////////////////////////////////////////////////////////
//
//	File : i2c_drv.h
//
//	Description : I2C-bus programming interface (header)
//
//  Authors : Roelof van Silfhout, Anton Kachatkou
//
//  Date Created : 18/02/2009
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _I2C_DRV_H_
#define _I2C_DRV_H_

#include <stdint.h>
#include <sys/types.h>

#define BITSET(x,b) x = (x) | (1 << (b));
#define BITCLR(x,b) x = ((x) | (1 << (b))) ^ (1 << (b));
#define BITGET(x,b) (((x) & (1 << (b))) != 0)

//I2C-bus initialization (must be called before any communication via the bus)
uint32_t i2c_init();
//releases resources captured by i2c_init()
uint32_t i2c_finalize();
/* Select a I2C device to communicate with */
uint32_t i2c_select_dev(uint16_t addr);
/* Send a message to the device previously selected by i2c_select_dev() */
uint32_t i2c_transmit_msg(const uint8_t *msg, size_t len);
/* Receive a message from the device previously selected by i2c_select_dev() */
uint32_t i2c_receive_msg(uint8_t *msg, size_t len);
/* Read selected register from the selected device */
uint32_t i2c_read_register(uint8_t addr, uint8_t reg, uint8_t *data, size_t sz);
/* Write data to the selected register of the selected device */
uint32_t i2c_write_register(uint8_t addr, uint8_t reg, const uint8_t *data, size_t sz);
#endif
