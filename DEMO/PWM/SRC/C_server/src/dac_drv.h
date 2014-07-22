/////////////////////////////////////////////////////////////////////////////
//                                                           
//	File : dac_drv.h
//
//	Description : AD56x7R/AD56x7 DAC programming interface (header)
//
//  Authors :
//
//  Date Created :
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _DAC_DRV_H_
#define _DAC_DRV_H_

#include <stdint.h>

#define DAC_NUMBER_OF_CHANNELS 4

uint32_t dac_init();
/* tests DAC working by uploading some output value */
uint32_t dac_test();
/* sets DAC output voltage using a 16-bit binary code */
/* (D parameter from the D/A section of the AD56x7R/AD56x7 datasheet */
uint32_t dac_setvoltagecode(int channel, uint16_t code);

uint32_t set_dac(uint16_t addr, uint16_t dacA, uint16_t dacB);

#endif
