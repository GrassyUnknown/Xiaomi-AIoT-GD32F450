/*!
    \file  i2c_test.h
    \brief the header file of I2C
*/



#ifndef I2C_TEST_H
#define I2C_TEST_H

#include "gd32f4xx.h"

#define GD32F330_ADDRESS_S6    	0x58
#define	GD32F330_READ_CMD				0xAA
#define SHT35_ADDRESS_S2        0x88

//I2C address struct
typedef struct
{
	uint8_t flag;
	uint32_t periph;
	uint8_t addr;
} i2c_addr_def;
	

extern i2c_addr_def e1_nixie_tube_addr;
extern i2c_addr_def e1_rgb_led_addr;
extern i2c_addr_def e2_fan_addr;
extern i2c_addr_def e3_curtain_addr;
extern i2c_addr_def s1_key_addr;
extern i2c_addr_def s5_nfc_addr;
extern i2c_addr_def s6_ult_addr;
extern i2c_addr_def s7_ir_addr;
extern i2c_addr_def s2_sensor_addr;


void Ultra_Data_test(void);
void ht16k33_display_test(void);
void pc9685_rgb_led_control(uint32_t i2c_periph,uint8_t i2c_addr,uint8_t num);
void pc9685_motor_control(uint32_t i2c_periph,uint8_t i2c_addr,uint8_t num);
void e3_curtain_init(uint32_t i2c_periph,uint8_t i2c_addr);
void i2c_addr_init(void);
void i2c_test(void);

void digital_control(int num);
#endif  /* I2C_TEST_H */
