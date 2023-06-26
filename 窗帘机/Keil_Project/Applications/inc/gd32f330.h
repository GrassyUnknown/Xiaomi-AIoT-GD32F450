/*!
    \file  gd32f330.h
    \brief the header file of GD32F330
*/
#ifndef GD32F330_H
#define GD32F330_H

#include "gd32f4xx.h"
#define SYSTEM 0x01
#define DATA 0x02
#define CONTROL 0x03
void gd32f330_init(uint32_t i2c_periph,uint8_t i2c_addr);
void gd32f330_mov(uint32_t i2c_periph,uint8_t i2c_addr,uint8_t data);
#endif 
