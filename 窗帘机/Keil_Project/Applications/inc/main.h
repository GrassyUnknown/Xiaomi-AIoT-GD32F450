/*!
    \file  main2.h
    \brief the header file of main2 
		\version 2023-06, V0.1
*/
#include "gd32f4xx.h"

//#define PRINT_DEBUG_INFO	

#define ETH				0
#define	USB				0
#define	I2S				0

#define	E1				1
#define	E2				1
#define	E3				1

#define	S1				1
#define S2        1
#define	S5				1
#define	S6				1
#define	S7				1

#define	KEYKS0				0x40

#define BH1750_ADDRESS_S2_1    0x46
#define BH1750_ADDRESS_S2_2    0xB8
#define GD32F330_ADDRESS_E3    0x38




#define PCA9685_MODE1 0x0

#define	SYSTEM_ON				0x21

#define ALLLED_ON_L 0xFA
#define ALLLED_ON_H 0xFB
#define ALLLED_OFF_L 0xFC
#define ALLLED_OFF_H 0xFD
//I2C address struct
typedef struct{
	uint8_t flag;
	uint32_t periph;
	uint8_t addr;
} i2c_addr_def;

//void setPWM(uint32_t i2c_periph,uint8_t i2c_addr,uint8_t num, uint16_t on, uint16_t off);//Set signal PWM
//void setPWM_off(uint32_t i2c_periph,uint8_t i2c_addr);
void i2c_addr_init(void);
void led_control(uint8_t color);//Control over target LED
void key_control(int key);//Control over 
int key_trans(void);//Translation from Array to Key number
