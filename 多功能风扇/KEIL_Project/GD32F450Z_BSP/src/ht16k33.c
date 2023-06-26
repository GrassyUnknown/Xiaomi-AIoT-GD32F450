/*!
    \file  ht16k33.c
    \brief pca9685 control
*/



#include "ht16k33.h"
#include "i2c.h"
#include <stdio.h>

uint8_t keyvalue[6];

//0-9
const uint8_t disdata[10][2] ={{0xF8,0x01},
															 {0x30,0x00},
															 {0xD8,0x02},
															 {0x78,0x02},
															 {0x30,0x03},
															 {0x68,0x03},
															 {0xE8,0x03},
															 {0x38,0x00},
															 {0xF8,0x03},
															 {0x78,0x03},};

/*!
    \brief      ht16k33 init
    \param[in]  none
    \param[out] none
    \retval     none
*/
void ht16k33_init(uint32_t i2c_periph,uint8_t i2c_addr)
{

		i2c_cmd_write(i2c_periph,i2c_addr,SYSTEM_ON);
		ht16k33_display_off(i2c_periph,i2c_addr);
}
/*!
    \brief      ht16k33_display_off init
    \param[in]  none
    \param[out] none
    \retval     none
*/
void ht16k33_display_off(uint32_t i2c_periph,uint8_t i2c_addr)
{

		i2c_byte_write(i2c_periph,i2c_addr,0x02,0x00);
		i2c_byte_write(i2c_periph,i2c_addr,0x03,0x00);
		i2c_byte_write(i2c_periph,i2c_addr,0x04,0x00);
		i2c_byte_write(i2c_periph,i2c_addr,0x05,0x00);
		i2c_byte_write(i2c_periph,i2c_addr,0x06,0x00);
		i2c_byte_write(i2c_periph,i2c_addr,0x07,0x00);
		i2c_byte_write(i2c_periph,i2c_addr,0x08,0x00);
		i2c_byte_write(i2c_periph,i2c_addr,0x09,0x00);
		i2c_cmd_write(i2c_periph,i2c_addr,DISPLAY_ON);
}

/*!
    \brief      ht16k33 display data
    \param[in]  none
    \param[out] none
    \retval     none
*/


void ht16k33_display_data(uint32_t i2c_periph,uint8_t i2c_addr,uint8_t bit,uint8_t data)
{
		switch(bit)
		{
			case 1:
				i2c_byte_write(i2c_periph,i2c_addr,0x02,disdata[data][0]);
				i2c_byte_write(i2c_periph,i2c_addr,0x03,disdata[data][1]);
			break;
			
			case 2:
				i2c_byte_write(i2c_periph,i2c_addr,0x04,disdata[data][0]);
				i2c_byte_write(i2c_periph,i2c_addr,0x05,disdata[data][1]);
			break;
			
			case 3:
				i2c_byte_write(i2c_periph,i2c_addr,0x06,disdata[data][0]);
				i2c_byte_write(i2c_periph,i2c_addr,0x07,disdata[data][1]);
			break;
			
			case 4:
				i2c_byte_write(i2c_periph,i2c_addr,0x08,disdata[data][0]);
				i2c_byte_write(i2c_periph,i2c_addr,0x09,disdata[data][1]);
			break;
			
		}
		i2c_cmd_write(i2c_periph,i2c_addr,DISPLAY_ON);
}



/*!
    \brief      ht16k33 key scan
    \param[in]  none
    \param[out] none
    \retval     none
*/
void ht16k33_key_scan(uint32_t i2c_periph,uint8_t i2c_addr)
{
		
		i2c_read(i2c_periph,i2c_addr,KEYKS0,keyvalue,6);
}

