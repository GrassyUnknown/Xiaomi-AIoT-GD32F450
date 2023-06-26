/*!
    \file  pc9685.h
    \brief the header file of pc9685
*/



#ifndef PC9685_H
#define PC9685_H

#include "gd32f4xx.h"


#define PCA9685_ADDRESS_E1    0xC0			//0xC0、0xC2、0xC4、0xC6
#define PCA9685_ADDRESS_E2    0xC8			//0xC8、0xCA、0xCC、0xCE


#define PCA9685_SUBADR1 0x2
#define PCA9685_SUBADR2 0x3
#define PCA9685_SUBADR3 0x4
#define PCA9685_MODE1 0x0
#define PCA9685_PRESCALE 0xFE
#define LED0_ON_L 0x6
#define LED0_ON_H 0x7
#define LED0_OFF_L 0x8
#define LED0_OFF_H 0x9
#define ALLLED_ON_L 0xFA
#define ALLLED_ON_H 0xFB
#define ALLLED_OFF_L 0xFC
#define ALLLED_OFF_H 0xFD

void pc9685_init(uint32_t i2c_periph,uint8_t i2c_addr);
void setPWM_off(uint32_t i2c_periph,uint8_t i2c_addr);
void setPWM(uint32_t i2c_periph,uint8_t i2c_addr,uint8_t num, uint16_t on, uint16_t off);

#endif  /* PC9685_H */
