/*!
    \file  gd32f330.c
    \brief  GD32F330.c
*/
#include "gd32f330.h"
#include "i2c.h"
#include <stdio.h>
void gd32f330_init(uint32_t i2c_periph,uint8_t i2c_addr)
{
	i2c_cmd_write(i2c_periph,i2c_addr,SYSTEM);
}
void gd32f330_mov(uint32_t i2c_periph,uint8_t i2c_addr,uint8_t data)
{
	i2c_byte_write(i2c_periph,i2c_addr,CONTROL,data);
}