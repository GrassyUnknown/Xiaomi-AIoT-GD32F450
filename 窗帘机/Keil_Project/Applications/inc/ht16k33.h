/*!
    \file  ht16k33.h
    \brief the header file of HT16K33
*/



#ifndef HT16K33_H
#define HT16K33_H

#include "gd32f4xx.h"


#define HT16K33_ADDRESS_E1    0xE0
#define HT16K33_ADDRESS_S1    0xE8

/* HT16K33  CMD */
#define	SYSTEM_ON				0x21
#define	SET_INT_NONE		0xA0
#define	DISPLAY_ON			0x81
#define	DISPLAY_OFF			0x80
#define	DIMMING_SET_DEFAULT		0xEF

#define	KEYKS0				0x40

extern uint8_t keyvalue[6];
void ht16k33_init(uint32_t i2c_periph,uint8_t i2c_addr);
void ht16k33_display_off(uint32_t i2c_periph,uint8_t i2c_addr);
void ht16k33_display_data(uint32_t i2c_periph,uint8_t i2c_addr,uint8_t bit,uint8_t data);
void ht16k33_key_scan(uint32_t i2c_periph,uint8_t i2c_addr);
#endif  /* HT16K33_H */
