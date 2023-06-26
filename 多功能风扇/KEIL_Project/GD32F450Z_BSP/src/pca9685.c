/*!
    \file  pca9685.c
    \brief pca9685 control
*/


#include "pca9685.h"
#include "i2c.h"
#include <stdio.h>

/*!
    \brief      pc9685 test program
    \param[in]  none
    \param[out] none
    \retval     none
*/
void pc9685_init(uint32_t i2c_periph,uint8_t i2c_addr)
{
		i2c_byte_write(i2c_periph,i2c_addr,PCA9685_MODE1,0x0);
		setPWM_off(i2c_periph,i2c_addr);    
}

/*!
    \brief      set pc9685 output pwm
		\param[in]  num: output ch
		\param[in]  on: LEDn ON cnt,12bits
		\param[in]  on: LEDn OFF cnt,12bits
    \param[out] none
    \retval     none
*/
void setPWM_off(uint32_t i2c_periph,uint8_t i2c_addr) 
{
    i2c_byte_write(i2c_periph,i2c_addr,ALLLED_ON_L,0);
    i2c_byte_write(i2c_periph,i2c_addr,ALLLED_ON_H,0);
    i2c_byte_write(i2c_periph,i2c_addr,ALLLED_OFF_L,0);
    i2c_byte_write(i2c_periph,i2c_addr,ALLLED_OFF_H,0x10);
}

/*!
    \brief      set pc9685 output pwm
		\param[in]  num: output ch
		\param[in]  on: LEDn ON cnt,12bits
		\param[in]  on: LEDn OFF cnt,12bits
    \param[out] none
    \retval     none
*/
void setPWM(uint32_t i2c_periph,uint8_t i2c_addr,uint8_t num, uint16_t on, uint16_t off) 
{
    i2c_byte_write(i2c_periph,i2c_addr,LED0_ON_L+4*num,on);
    i2c_byte_write(i2c_periph,i2c_addr,LED0_ON_H+4*num,on>>8);
    i2c_byte_write(i2c_periph,i2c_addr,LED0_OFF_L+4*num,off);
    i2c_byte_write(i2c_periph,i2c_addr,LED0_OFF_H+4*num,off>>8);
}




