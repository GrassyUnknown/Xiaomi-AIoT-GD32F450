/*!
    \file  i2c.c
    \brief I2C configuration file
*/


#include "gd32f4xx.h"
#include "i2c.h"
#include "main.h"
#include <stdio.h>

/*!
    \brief      configure the I2C0 GPIO ports
    \param[in]  none
    \param[out] none
    \retval     none
*/
void i2c0_gpio_config(void)
{
    rcu_periph_clock_enable(RCU_GPIOB);
    
    /* connect PB8 to I2C0_SCL */
    gpio_af_set(GPIOB, GPIO_AF_4, GPIO_PIN_8);
    /* connect PB9 to I2C0_SDA */
    gpio_af_set(GPIOB, GPIO_AF_4, GPIO_PIN_9);

    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_8);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ,GPIO_PIN_8);
    gpio_mode_set(GPIOB, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_9);
    gpio_output_options_set(GPIOB, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ,GPIO_PIN_9);
}

/*!
    \brief      configure the I2C0 interfaces
    \param[in]  none
    \param[out] none
    \retval     none
*/
void i2c0_config(void)
{
    /* enable I2C clock */
    rcu_periph_clock_enable(RCU_I2C0);
    /* configure I2C clock */
    i2c_clock_config(I2C0,I2C0_SPEED,I2C_DTCY_2);
    /* configure I2C address */
    i2c_mode_addr_config(I2C0,I2C_I2CMODE_ENABLE,I2C_ADDFORMAT_7BITS,I2C0_SLAVE_ADDRESS7);
    /* enable I2C0 */
    i2c_enable(I2C0);
    /* enable acknowledge */
    i2c_ack_config(I2C0,I2C_ACK_ENABLE);
}

/*!
    \brief      configure the I2C1 GPIO ports
    \param[in]  none
    \param[out] none
    \retval     none
*/
void i2c1_gpio_config(void)
{
    rcu_periph_clock_enable(RCU_GPIOF);
    
    /* connect PF1 to I2C1_SCL */
    gpio_af_set(GPIOF, GPIO_AF_4, GPIO_PIN_1);
    /* connect PF0 to I2C1_SDA */
    gpio_af_set(GPIOF, GPIO_AF_4, GPIO_PIN_0);

    gpio_mode_set(GPIOF, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_0);
    gpio_output_options_set(GPIOD, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ,GPIO_PIN_0);
    gpio_mode_set(GPIOF, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_1);
    gpio_output_options_set(GPIOF, GPIO_OTYPE_OD, GPIO_OSPEED_50MHZ,GPIO_PIN_1);
}

/*!
    \brief      configure the I2C1 interfaces
    \param[in]  none
    \param[out] none
    \retval     none
*/
void i2c1_config(void)
{
    /* enable I2C clock */
    rcu_periph_clock_enable(RCU_I2C1);
    /* configure I2C clock */
    i2c_clock_config(I2C1,I2C1_SPEED,I2C_DTCY_2);
    /* configure I2C address */
    i2c_mode_addr_config(I2C1,I2C_I2CMODE_ENABLE,I2C_ADDFORMAT_7BITS,I2C1_SLAVE_ADDRESS7);
    /* enable I2C1 */
    i2c_enable(I2C1);
    /* enable acknowledge */
    i2c_ack_config(I2C1,I2C_ACK_ENABLE);
}

/*!
    \brief      i2c slave addr poll
    \param[in]  i2c_periph£ºI2C0 or I2C1
		\param[in]  poll_addr£ºpoll address
    \param[out] result; poll result
    \retval     none
*/
uint8_t i2c_addr_poll(uint32_t i2c_periph,uint8_t poll_addr)
{
		uint16_t i = 0;
		uint8_t result;
    /* wait until I2C bus is idle */
    while(i2c_flag_get(i2c_periph, I2C_FLAG_I2CBSY));

    /* send a start condition to I2C bus */
    i2c_start_on_bus(i2c_periph);
    
    /* wait until SBSEND bit is set */
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_SBSEND));
    
    /* send slave address to I2C bus */
		i2c_master_addressing(i2c_periph, poll_addr, I2C_TRANSMITTER);
    /* wait until ADDSEND bit is set */
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_ADDSEND))
		{
			i++ ;
			if(i > 60000)
			{
				break;
			}
		}
    
		if(i > 60000)
		{
			result = 0;
		}
		else
		{
			result = 1;
		}		

    /* send a stop condition to I2C bus */
    i2c_stop_on_bus(i2c_periph);
    
    /* wait until the stop condition is finished */
    while(I2C_CTL0(i2c_periph)&0x0200);
		
		return result;
}

/*!
    \brief      write command to slave
    \param[in]  cmd£ºcommand to control
    \param[out] none
    \retval     none
*/
void i2c_cmd_write(uint32_t i2c_periph,uint8_t i2c_addr,uint8_t cmd)
{
		uint16_t i;
    /* wait until I2C bus is idle */
    while(i2c_flag_get(i2c_periph, I2C_FLAG_I2CBSY));

    /* send a start condition to I2C bus */
    i2c_start_on_bus(i2c_periph);
    
    /* wait until SBSEND bit is set */
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_SBSEND));
    
    /* send slave address to I2C bus */
		i2c_master_addressing(i2c_periph, i2c_addr, I2C_TRANSMITTER);
    /* wait until ADDSEND bit is set */
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_ADDSEND))
		{
			i++ ;
			if(i > 60000)
			{
				/* send a stop condition to I2C bus */
				i2c_stop_on_bus(i2c_periph);
				return;
			}
		}    
    /* clear the ADDSEND bit */
    i2c_flag_clear(i2c_periph,I2C_FLAG_ADDSEND);
    
    /* wait until the transmit data buffer is empty */
    while(SET != i2c_flag_get(i2c_periph, I2C_FLAG_TBE));
    
    /* send the cmd to I2C bus */
    i2c_data_transmit(i2c_periph, cmd);
    
    /* wait until BTC bit is set */
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_BTC));    

    /* send a stop condition to I2C bus */
    i2c_stop_on_bus(i2c_periph);
    
    /* wait until the stop condition is finished */
    while(I2C_CTL0(i2c_periph)&0x0200);
}

/*!
    \brief      write one byte to slave
    \param[in]  p_buffer; data
    \param[in]  write_address; slave internal address to write to
    \param[out] none
    \retval     none
*/
void i2c_byte_write(uint32_t i2c_periph,uint8_t i2c_addr,uint8_t write_address,uint8_t buffer)
{
		uint16_t i;
    /* wait until I2C bus is idle */
    while(i2c_flag_get(i2c_periph, I2C_FLAG_I2CBSY));

    /* send a start condition to I2C bus */
    i2c_start_on_bus(i2c_periph);
    
    /* wait until SBSEND bit is set */
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_SBSEND));
    
    /* send slave address to I2C bus */
    i2c_master_addressing(i2c_periph, i2c_addr, I2C_TRANSMITTER);
    
    /* wait until ADDSEND bit is set */
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_ADDSEND))
		{
			i++ ;
			if(i > 60000)
			{
				/* send a stop condition to I2C bus */
				i2c_stop_on_bus(i2c_periph);
				return;
			}
		}   
    
    /* clear the ADDSEND bit */
    i2c_flag_clear(i2c_periph,I2C_FLAG_ADDSEND);
    
    /* wait until the transmit data buffer is empty */
    while(SET != i2c_flag_get(i2c_periph, I2C_FLAG_TBE));
    
    /* send the EEPROM's internal address to write to ; only one byte address */
    i2c_data_transmit(i2c_periph, write_address);
    
    /* wait until BTC bit is set */
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_BTC));
    
    /* send the byte to be written */
    i2c_data_transmit(i2c_periph, buffer); 
    
    /* wait until BTC bit is set */
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_BTC));

    /* send a stop condition to I2C bus */
    i2c_stop_on_bus(i2c_periph);
    
    /* wait until the stop condition is finished */
    while(I2C_CTL0(i2c_periph)&0x0200);
}

/*!
    \brief      write more than one byte to the slave with a single write cycle
    \param[in]  p_buffer; pointer to the buffer containing the data to be written 
    \param[in]  write_address; slave internal address to write to
    \param[in]  number_of_byte; number of bytes to write to 
    \param[out] none
    \retval     none
*/
void i2c_write(uint32_t i2c_periph,uint8_t i2c_addr,uint8_t write_address,uint8_t* p_buffer,  uint8_t number_of_byte)
{
		uint16_t i;
    /* wait until I2C bus is idle */
    while(i2c_flag_get(i2c_periph, I2C_FLAG_I2CBSY));
    
    /* send a start condition to I2C bus */
    i2c_start_on_bus(i2c_periph);
    
    /* wait until SBSEND bit is set */
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_SBSEND));
    
    /* send slave address to I2C bus */
    i2c_master_addressing(i2c_periph, i2c_addr, I2C_TRANSMITTER);
    
    /* wait until ADDSEND bit is set */
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_ADDSEND))
		{
			i++ ;
			if(i > 60000)
			{
				/* send a stop condition to I2C bus */
				i2c_stop_on_bus(i2c_periph);
				return;
			}
		}   
    
    /* clear the ADDSEND bit */
    i2c_flag_clear(i2c_periph,I2C_FLAG_ADDSEND);
    
    /* wait until the transmit data buffer is empty */
    while( SET != i2c_flag_get(i2c_periph, I2C_FLAG_TBE));
    
    /* send the EEPROM's internal address to write to ; only one byte address */
    i2c_data_transmit(i2c_periph, write_address);
    
    /* wait until BTC bit is set */
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_BTC));
    
    /* while there is data to be written */
    while(number_of_byte--){  
        i2c_data_transmit(i2c_periph, *p_buffer);
        
        /* point to the next byte to be written */
        p_buffer++; 
        
        /* wait until BTC bit is set */
        while(!i2c_flag_get(i2c_periph, I2C_FLAG_BTC));
    }
    /* send a stop condition to I2C bus */
    i2c_stop_on_bus(i2c_periph);
    
    /* wait until the stop condition is finished */
    while(I2C_CTL0(i2c_periph)&0x0200);
}


/*!
    \brief      read data from the slave
    \param[in]  p_buffer; pointer to the buffer that receives the data read from the slave
    \param[in]  read_address; slave internal address to start reading from
    \param[in]  number_of_byte; number of bytes to reads from the slave
    \param[out] none
    \retval     none
*/
uint8_t i2c_read(uint32_t i2c_periph,uint8_t i2c_addr,uint8_t read_address,uint8_t* p_buffer,  uint16_t number_of_byte)
{  
		uint8_t rt = 1;
		uint16_t i;
    /* wait until I2C bus is idle */
    while(i2c_flag_get(i2c_periph, I2C_FLAG_I2CBSY));

    if(2 == number_of_byte){
        i2c_ackpos_config(i2c_periph,I2C_ACKPOS_NEXT);
    }
    
    /* send a start condition to I2C bus */
    i2c_start_on_bus(i2c_periph);
    
    /* wait until SBSEND bit is set */
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_SBSEND));
    
    /* send slave address to I2C bus */
    i2c_master_addressing(i2c_periph, i2c_addr, I2C_TRANSMITTER);
    
    /* wait until ADDSEND bit is set */
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_ADDSEND))
		{
			i++ ;
			if(i > 60000)
			{
				/* send a stop condition to I2C bus */
				i2c_stop_on_bus(i2c_periph);
				rt = 0;
				return rt;
			}
		}   
    
    /* clear the ADDSEND bit */
    i2c_flag_clear(i2c_periph,I2C_FLAG_ADDSEND);
    
    /* wait until the transmit data buffer is empty */
    while(SET != i2c_flag_get( i2c_periph , I2C_FLAG_TBE ));

    /* enable i2c_periph*/
    i2c_enable(i2c_periph);
    
    /* send the slave internal address to write to */
    i2c_data_transmit(i2c_periph, read_address);  
    
    /* wait until BTC bit is set */
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_BTC));
    
    /* send a start condition to I2C bus */
    i2c_start_on_bus(i2c_periph);
    
    /* wait until SBSEND bit is set */
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_SBSEND));
    
    /* send slave address to I2C bus */
    i2c_master_addressing(i2c_periph, i2c_addr, I2C_RECEIVER);

    if(number_of_byte < 3){
        /* disable acknowledge */
        i2c_ack_config(i2c_periph,I2C_ACK_DISABLE);
    }
    
    /* wait until ADDSEND bit is set */
    while(!i2c_flag_get(i2c_periph, I2C_FLAG_ADDSEND));
    
    /* clear the ADDSEND bit */
    i2c_flag_clear(i2c_periph,I2C_FLAG_ADDSEND);
    
    if(1 == number_of_byte){
        /* send a stop condition to I2C bus */
        i2c_stop_on_bus(i2c_periph);
    }
    
    /* while there is data to be read */
    while(number_of_byte){
        if(3 == number_of_byte){
            /* wait until BTC bit is set */
            while(!i2c_flag_get(i2c_periph, I2C_FLAG_BTC));

            /* disable acknowledge */
            i2c_ack_config(i2c_periph,I2C_ACK_DISABLE);
        }
        if(2 == number_of_byte){
            /* wait until BTC bit is set */
            while(!i2c_flag_get(i2c_periph, I2C_FLAG_BTC));
            
            /* send a stop condition to I2C bus */
            i2c_stop_on_bus(i2c_periph);
        }
        
        /* wait until the RBNE bit is set and clear it */
        if(i2c_flag_get(i2c_periph, I2C_FLAG_RBNE)){
            /* read a byte from the EEPROM */
            *p_buffer = i2c_data_receive(i2c_periph);
            
            /* point to the next location where the byte read will be saved */
            p_buffer++; 
            
            /* decrement the read bytes counter */
            number_of_byte--;
        } 
    }
    
    /* wait until the stop condition is finished */
    while(I2C_CTL0(i2c_periph)&0x0200);
    
    /* enable acknowledge */
    i2c_ack_config(i2c_periph,I2C_ACK_ENABLE);

    i2c_ackpos_config(i2c_periph,I2C_ACKPOS_CURRENT);
		return rt;
}




