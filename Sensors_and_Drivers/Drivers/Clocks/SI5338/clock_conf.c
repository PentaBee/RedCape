/*
 * 		Test for ClockGenerator Si5338
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


#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "types.h"
#include "i2c_drv.h"
#include "errorcodes.h"
#include "si5338.h"
#include "register_map.h"
BOOL				DebugFlag;

int main(int argc, char *argv[])
{
	int		ArgPos,cont;
	float val_low;
	unsigned char buf[10] = {0};
	unsigned char current,clear_current,clear_new, combined,regi;
	Reg_Data regi2;
	// check flags
	DebugFlag = FALSE;
	for (ArgPos=1; ArgPos<argc; ArgPos++) {
		if (strcmp (argv[ArgPos],"-debug") == 0)
			DebugFlag = TRUE;
	}


	if (i2c_init() != XDS_OK)
		printf("I2C initialisation failed\n");

	printf ("\nInitialise hardware\n");
	cont= 0;




/*
 * Disable Outputs Set OEB_ALL = 1; reg230[4] , regE6 , Set DIS_LOL = 1; reg241[7] regF1
*/
	printf("Disable Outputs \n");
	i2c_read_register(SI5338_ADDR, SI5338_REG_OEB_ALL, buf, (uint16_t) 1);
	current = buf[0];
	printf("Original Value of reg E6 %x \n",current);
	combined = current | SI5338_VAL_OEB_ALL;
	i2c_write_register(SI5338_ADDR, SI5338_REG_OEB_ALL, &combined, (uint16_t) 1);
	printf("New Value of reg E6 %x \n",combined);
	printf("Pause LOL  \n");
		i2c_read_register(SI5338_ADDR, SI5338_REG_DIS_LOL, buf, (uint16_t) 1);
		current = buf[0];
		printf("Original Value of reg F1 %x \n",current);
		combined = current | SI5338_VAL_DIS_LOL;
		i2c_write_register(SI5338_ADDR, SI5338_REG_DIS_LOL, &combined, (uint16_t) 1);
		printf("New Value of reg F1 %x \n",combined);




/*
 * Update Register MAP
*/


	for(cont = 0;  cont<NUM_REGS_MAX; cont++)
	{
	regi2 = Reg_Store[cont];
	printf("value are = %x , %x , %x \n",regi2.Reg_Addr,regi2.Reg_Val,regi2.Reg_Mask);

	if(regi2.Reg_Mask!=0x00)
	{
		if(regi2.Reg_Mask == 0xFF) {
			i2c_write_register(SI5338_ADDR,regi2.Reg_Addr , &regi2.Reg_Val, (uint16_t) 1);
		}
		else
		{
			i2c_read_register(SI5338_ADDR, regi2.Reg_Addr, buf, (uint16_t) 1);

			current = buf[0];
			printf("%x\n",current);
			printf("MASK : %x\n",regi2.Reg_Mask);
			printf("NOT MASK : %x\n",~(regi2.Reg_Mask));
			clear_current = current & ~(regi2.Reg_Mask);
			printf("%x\n",clear_current);
			clear_new = regi2.Reg_Val & regi2.Reg_Mask ;
			printf("%x\n",clear_new);
			combined = clear_current | clear_new;// its supossed to be OR, not +
			printf("%x\n",combined);
			i2c_write_register(SI5338_ADDR,regi2.Reg_Addr , &combined, (uint16_t) 1);
		}
		usleep(100);

	}
	}

/*
 * Validate Input Clocks , read register SI5338_REG_ALARMS		0xDA [4]-PLL_LOL, [3]-LOS_FDBK, [2]-LOS_CLKIN , [0]-SYS_CAL
*/
	i2c_read_register(SI5338_ADDR, SI5338_REG_ALARMS, buf, (uint16_t) 1);
	current = buf[0];
	printf("Value of ALARM FLAGS %x\n",current);
	usleep(1000);
	i2c_read_register(SI5338_ADDR, SI5338_REG_ALARMS, buf, (uint16_t) 1);
	current = buf[0];
	printf("Value of ALARM FLAGS %x\n",current);
	usleep(10000);
	i2c_read_register(SI5338_ADDR, SI5338_REG_ALARMS, buf, (uint16_t) 1);
	current = buf[0];
	printf("Value of ALARM FLAGS %x\n",current);


/*
 * Configure PLL for locking , Set FCAL_OVRD_EN = 0; reg49[7]
*/
	printf("PLL LOCK \n");
	i2c_read_register(SI5338_ADDR, SI5338_REG_PLL_LOCK, buf, (uint16_t) 1);
	current = buf[0];
	printf("Original Value of reg %x, %x \n",SI5338_REG_PLL_LOCK,current);
	combined = current & SI5338_VAL_PLL_LOCK;// clear bit
	i2c_write_register(SI5338_ADDR, SI5338_REG_PLL_LOCK, &combined, (uint16_t) 1);
	printf("New Value of reg %x, %x \n",SI5338_REG_PLL_LOCK,combined);
/*
 * Initiate locking , Set SOFT_RESET = 1; reg246[1]
*/
	printf("Initiate Locking \n");
	i2c_read_register(SI5338_ADDR, SI5338_REG_PLL_LOCK_RES, buf, (uint16_t) 1);
	current = buf[0];
	printf("Original Value of reg %x, %x \n",SI5338_REG_PLL_LOCK_RES,current);
	combined = current | SI5338_VAL_PLL_LOCK_RES;// set bit
	i2c_write_register(SI5338_ADDR, SI5338_REG_PLL_LOCK_RES, &combined, (uint16_t) 1);
	printf("New Value of reg %x, %x \n",SI5338_REG_PLL_LOCK_RES,combined);
	usleep(2500);
/*
 * Restart LOL
*/
	printf("Restart LOL  \n");
	i2c_read_register(SI5338_ADDR, SI5338_REG_DIS_LOL, buf, (uint16_t) 1);
	current = buf[0];
	printf("Original Value of reg F1 %x \n",current);
	combined = current & SI5338_VAL_DIS_LOL_RST;
	i2c_write_register(SI5338_ADDR, SI5338_REG_DIS_LOL, &combined, (uint16_t) 1);
	printf("New Value of reg F1 %x \n",combined);
	combined = SI5338_VAL_DIS_LOL_RST2;
	i2c_write_register(SI5338_ADDR, SI5338_REG_DIS_LOL, &combined, (uint16_t) 1);
	printf("New Value of reg F1 %x \n",SI5338_VAL_DIS_LOL_RST2);
/*
 * Confirm PLL lock status , read register SI5338_REG_ALARMS		0xDA [4]-PLL_LOL, [3]-LOS_FDBK, [2]-LOS_CLKIN , [0]-SYS_CAL
*/
	i2c_read_register(SI5338_ADDR, SI5338_REG_ALARMS, buf, (uint16_t) 1);
	current = buf[0];
	printf("Value of ALARM FLAGS %x\n",current);
	usleep(1000);
	i2c_read_register(SI5338_ADDR, SI5338_REG_ALARMS, buf, (uint16_t) 1);
	current = buf[0];
	printf("Value of ALARM FLAGS %x\n",current);

/*
 * Copy FCAL values to active registers
 *
*/

	i2c_read_register(SI5338_ADDR, SI5338_REG_237, buf, (uint16_t) 1);
	current = buf[0];
	printf("Original Value of reg %x, %x \n",SI5338_REG_237,current);
	i2c_read_register(SI5338_ADDR, SI5338_REG_47, buf, (uint16_t) 1);
	clear_new = buf[0];
	clear_new = clear_new & ~(SI5338_REG_47_MASK);
	combined= current | clear_new;
	i2c_write_register(SI5338_ADDR, SI5338_REG_47, &combined, (uint16_t) 1);
	printf("New Value of reg %x, %x \n",SI5338_REG_47,combined);
	//Copy 236 to 46
	i2c_read_register(SI5338_ADDR, SI5338_REG_236, buf, (uint16_t) 1);
	current = buf[0];
	i2c_write_register(SI5338_ADDR, SI5338_REG_46, &current, (uint16_t) 1);
	printf("New Value of reg %x, %x \n",SI5338_REG_46,current);
	//Copy 235 to 45
	i2c_read_register(SI5338_ADDR, SI5338_REG_235, buf, (uint16_t) 1);
	current = buf[0];
	i2c_write_register(SI5338_ADDR, SI5338_REG_45, &current, (uint16_t) 1);
	printf("New Value of reg %x, %x \n",SI5338_REG_45,current);
	//Finish setting register 47, silly register
	i2c_read_register(SI5338_ADDR, SI5338_REG_47, buf, (uint16_t) 1);
	clear_new = buf[0];
	clear_new = clear_new & SI5338_REG_47_MASK;
	combined= SI5338_REG_47_VAL | clear_new;
	i2c_write_register(SI5338_ADDR, SI5338_REG_47, &combined, (uint16_t) 1);
	printf("New Value of reg %x, %x \n",SI5338_REG_45,combined);
/*
 * Set PLL to use FCAL values
Set FCAL_OVRD_EN = 1; reg49[7]
 *
*/
	printf("Set PLL to use FCAL, FCAL_OVRD_EN = 1 \n");
	i2c_read_register(SI5338_ADDR, SI5338_REG_49, buf, (uint16_t) 1);
	current = buf[0];
	printf("Original Value of reg %x, %x \n",SI5338_REG_49,current);
	combined = current | SI5338_VAL_49;
	i2c_write_register(SI5338_ADDR, SI5338_REG_49, &combined, (uint16_t) 1);
	printf("New Value of reg %x, %x \n",SI5338_REG_49,combined);
/*
 * Enable Outputs
 *Set OEB_ALL = 0;
*/
	printf("Enable Outputs \n");
	i2c_read_register(SI5338_ADDR, SI5338_REG_OEB_ALL, buf, (uint16_t) 1);
	current = buf[0];
	printf("Original Value of reg E6 %x \n",current);
	combined = current & ~(SI5338_VAL_OEB_ALL);
	i2c_write_register(SI5338_ADDR, SI5338_REG_OEB_ALL, &combined, (uint16_t) 1);
	printf("New Value of reg E6 %x \n",combined);
	printf("FINISHED \n");


	i2c_finalize();


	return 0;

}
