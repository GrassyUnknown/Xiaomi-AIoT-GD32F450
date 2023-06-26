/*!
    \file  bh1750.h
    \brief the header file of BH1750
*/
#ifndef BH1750_H
#define BH1750_H

#include "gd32f4xx.h"
#define  BH1750_LIGHT_ADDRESS_1 0x46
#define  BH1750_LIGHT_ADDRESS_2 0xB8

#define SYS_OFF    0x00
#define SYS_ON     0x01
#define SYS_RETURN 0x07
#define CON_HIGH_1 0x10
#define CON_HIGH_2 0x11
#define CON_LOW    0x13
#define ONE_HIGH_1 0x20
#define ONE_HIGH_2 0x21
#define ONE_LOW    0x23
void bh1750_init(uint32_t i2c_periph,uint8_t i2c_addr);
void bh1750_off(uint32_t i2c_periph,uint8_t i2c_addr);
void bh1750_mode(uint32_t i2c_periph,uint8_t i2c_addr,int i);
void bh1750_return(uint32_t i2c_periph,uint8_t i2c_addr);
int bh1750_get_light_value(uint32_t i2c_periph,uint8_t i2c_addr);
#endif
