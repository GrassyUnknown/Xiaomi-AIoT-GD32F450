/*!
    \file  bh1750.c
    \brief bh1750control
*/
#include "bh1750.h"
#include "i2c.h"
#include "systick.h"
#include <stdio.h>
void bh1750_init(uint32_t i2c_periph,uint8_t i2c_addr)
{
	i2c_cmd_write(i2c_periph,i2c_addr,SYS_ON);
}
void bh1750_off(uint32_t i2c_periph,uint8_t i2c_addr)
{
	i2c_cmd_write(i2c_periph,i2c_addr,SYS_OFF);
}
void bh1750_mode(uint32_t i2c_periph,uint8_t i2c_addr,int i)
{
	switch(i)
	{
		case 0:
			i2c_cmd_write(i2c_periph,i2c_addr,CON_HIGH_1);
		case 1:
			i2c_cmd_write(i2c_periph,i2c_addr,CON_HIGH_2);
		case 2:
			i2c_cmd_write(i2c_periph,i2c_addr,CON_LOW);
		case 3:
			i2c_cmd_write(i2c_periph,i2c_addr,ONE_HIGH_1);
		case 4:
			i2c_cmd_write(i2c_periph,i2c_addr,ONE_HIGH_2);
		case 5:
			i2c_cmd_write(i2c_periph,i2c_addr,ONE_LOW);
		
	}	
}
void bh1750_return(uint32_t i2c_periph,uint8_t i2c_addr)
{
	i2c_cmd_write(i2c_periph,i2c_addr,SYS_RETURN);
}

int bh1750_get_light_value(uint32_t i2c_periph,uint8_t i2c_addr){
	uint8_t r_light_data[2];
	bh1750_mode(i2c_periph,i2c_addr,1);
	delay_1ms(180);
	i2c_read(i2c_periph,i2c_addr,0x46,r_light_data,2);
	return ((r_light_data[0] << 8) | r_light_data[1]);
}


