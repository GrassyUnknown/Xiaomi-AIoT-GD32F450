#include "i2c.h"
#include "i2c_test.h"
#include <stdio.h>

#include "ht16k33.h"
#include "pca9685.h"
#include "main.h"
#include "systick.h"

//Each sub board I2C address





/*!
    \brief      ultrasonic sensor test
    \param[in]  none
    \param[out] none
    \retval     none
*/



/*!
    \brief      rgb led display
    \param[in]  i2c_periph,I2C0 or I2C1
		\param[in]  i2c_addr, e1 rgb led i2c address
	  \param[in]  num,1:Warm white;2:White;3:Cold white
    \param[out] none
    \retval     none
*/

void pc9685_rgb_led_control(uint32_t i2c_periph,uint8_t i2c_addr,uint8_t num)
{	
		
		switch(num)
		{
		case 0:
			setPWM_off(i2c_periph,i2c_addr);
			break;
		case 1:
			setPWM(i2c_periph,i2c_addr,0,0x0000,0x0010);
			setPWM(i2c_periph,i2c_addr,1,0x0199,0x0C00);
			setPWM(i2c_periph,i2c_addr,2,0x0000,0x0010);
			break;
		case 2:
			setPWM(i2c_periph,i2c_addr,0,0x0199,0x0800);
			setPWM(i2c_periph,i2c_addr,1,0x0199,0x0800);
			setPWM(i2c_periph,i2c_addr,2,0x0000,0x0010);
			break;		
		case 3:
			setPWM(i2c_periph,i2c_addr,0,0x0000,0x0010);
			setPWM(i2c_periph,i2c_addr,1,0x0000,0x0010);
			setPWM(i2c_periph,i2c_addr,2,0x0199,0x0C00);
			break;  
		default:
			setPWM_off(i2c_periph,i2c_addr);
			break;
		}
}

/*!
    \brief      pc9685_motor control program
		\param[in]  i2c_periph,I2C0 or I2C1
		\param[in]  i2c_addr, e2 rgb led i2c address
		\param[in]  num,0:off;1:low speed;2:Medium speed;3:high speed
    \param[out] none
    \retval     none
*/
void pc9685_motor_control(uint32_t i2c_periph,uint8_t i2c_addr,uint8_t num)
{
		i2c_byte_write(i2c_periph,i2c_addr,PCA9685_MODE1,0x0);
		switch(num)
		{
			//¹Ø±Õ
			case	0:
				setPWM(i2c_periph,i2c_addr,0x0,0x0199,0x1000);	
			break;
			//30%
			case 	1:
				setPWM(i2c_periph,i2c_addr,0x0,0x0199,0x0665);
			break;
			//60%
			case	2:
				setPWM(i2c_periph,i2c_addr,0x0,0x0199,0x0B32);
			break;
			//90%
			case	3:
				setPWM(i2c_periph,i2c_addr,0x0,0x0199,0x0FFF);
			break;
			//¹Ø±Õ
			default:
				setPWM(i2c_periph,i2c_addr,0x0,0x0199,0x1000);	
			break;
		}

}

/*!
		\brief      curtain init
		\param[in]  i2c_periph,I2C0 or I2C1
		\param[in]  i2c_addr, e3 curtain i2c address
    \param[out] none
    \retval     none
*/




void i2c_addr_init(void)
{
	uint8_t i;
#if	E1
	//E1 RGB LED I2C address init
	//poll I2C0,Horizontal
	for(i=0;i<4;i++)
	{
		if(i2c_addr_poll(I2C0,PCA9685_ADDRESS_E1+i*2))
		{
			e1_rgb_led_addr.periph = I2C0;
			e1_rgb_led_addr.addr = PCA9685_ADDRESS_E1+i*2;
			e1_rgb_led_addr.flag = 1;			
			break;
		}	
	}
	//address not read
	if(e1_rgb_led_addr.flag != 1)
	{			
		//poll I2C1,Verti1
		for(i=0;i<4;i++)
		{
			if(i2c_addr_poll(I2C1,PCA9685_ADDRESS_E1+i*2))
			{
				e1_rgb_led_addr.periph = I2C1;
				e1_rgb_led_addr.addr = PCA9685_ADDRESS_E1+i*2;
				e1_rgb_led_addr.flag = 1;
				break;
			}	
		}
	}
	//read successful
	//E1 NIXIE TUBE I2C address init
	//poll I2C0,Horizontal
	for(i=0;i<4;i++)
	{
		if(i2c_addr_poll(I2C0,HT16K33_ADDRESS_E1+i*2))
		{
			e1_nixie_tube_addr.periph = I2C0;
			e1_nixie_tube_addr.addr = HT16K33_ADDRESS_E1+i*2;
			e1_nixie_tube_addr.flag = 1;
			break;
		}	
	}
	//address not read
	if(e1_nixie_tube_addr.flag != 1)
	{	
		//poll I2C1,Verti1
		for(i=0;i<4;i++)
		{
			if(i2c_addr_poll(I2C1,HT16K33_ADDRESS_E1+i*2))
			{
				e1_nixie_tube_addr.periph = I2C1;
				e1_nixie_tube_addr.addr = HT16K33_ADDRESS_E1+i*2;
				e1_nixie_tube_addr.flag = 1;
				break;
			}	
		}
	}
	//read successful
	
#endif

#if	E2	
	//E2 I2C address init
	//poll I2C0,Horizontal
	for(i=0;i<4;i++)
	{
		if(i2c_addr_poll(I2C0,PCA9685_ADDRESS_E2+i*2))
		{
			e2_fan_addr.periph = I2C0;
			e2_fan_addr.addr = PCA9685_ADDRESS_E2+i*2;
			e2_fan_addr.flag = 1;
			break;
		}	
	}
	//address not read
	if(e2_fan_addr.flag != 1)
	{			
		//poll I2C1,Verti1
		for(i=0;i<4;i++)
		{
			if(i2c_addr_poll(I2C1,PCA9685_ADDRESS_E2+i*2))
			{
				e2_fan_addr.periph = I2C1;
				e2_fan_addr.addr = PCA9685_ADDRESS_E2+i*2;
				e2_fan_addr.flag = 1;
				break;
			}	
		}
	}
	//read successful
	if(e2_fan_addr.flag)
	{
		pc9685_init(e2_fan_addr.periph,e2_fan_addr.addr);
	}
#endif

#if S2
		//S2 Sensor address init
	for(i=0;i<2;i++)
	{
		if(i2c_addr_poll(I2C0,SHT35_ADDRESS_S2+i*2))
		{
			s2_sensor_addr.periph = I2C0;
			s2_sensor_addr.addr = SHT35_ADDRESS_S2+i*2;
			s2_sensor_addr.flag = 1;			
			break;
		}	
	}
	//address not read
	if(s2_sensor_addr.flag != 1)
	{			
		//poll I2C1,Verti1
		for(i=0;i<2;i++)
		{
			if(i2c_addr_poll(I2C1,SHT35_ADDRESS_S2+i*2))
			{
				s2_sensor_addr.periph = I2C1;
				s2_sensor_addr.addr = SHT35_ADDRESS_S2+i*2;
				s2_sensor_addr.flag = 1;
				break;
			}	
		}
	}
	if(s2_sensor_addr.flag){
		i2c_byte_write(s2_sensor_addr.periph,s2_sensor_addr.addr,0x30,0xA2);
	}
	//read successful
#endif

#if	E3	
	//E3 CURTAIN I2C address init
	//poll I2C0,Horizontal
	for(i=0;i<4;i++)
	{
		if(i2c_addr_poll(I2C0,PCA9557_ADDRESS_E3+i*2))
		{
			e3_curtain_addr.periph = I2C0;
			e3_curtain_addr.addr = PCA9557_ADDRESS_E3+i*2;
			e3_curtain_addr.flag = 1;
			break;
		}	
	}
	//address not read
	if(e3_curtain_addr.flag != 1)
	{			
		//poll I2C1,Verti1
		for(i=0;i<4;i++)
		{
			if(i2c_addr_poll(I2C1,PCA9557_ADDRESS_E3+i*2))
			{
				e3_curtain_addr.periph = I2C1;
				e3_curtain_addr.addr = PCA9557_ADDRESS_E3+i*2;
				e3_curtain_addr.flag = 1;
				break;
			}	
		}
	}
	//read successful
	if(e3_curtain_addr.flag)
	{
		#ifdef PRINT_DEBUG_INFO
			printf("E3-CURTAIN is initialization success!\n");
			if(e3_curtain_addr.periph == I2C0)
				printf("%s","I2C0");
			else
				printf("%s","I2C1");
			printf(":");
			printf("%X",e3_curtain_addr.addr);
			printf("\n");
		#endif
		pca9557_control_init(e3_curtain_addr.periph,e3_curtain_addr.addr);
		e3_curtain_init(e3_curtain_addr.periph,e3_curtain_addr.addr);
	}
	//read failure
	else
	{
		printf("E3-CURTAIN is initialization failed	!\n");
	}
#endif

#if	S1	
	//S1 KEY I2C address init
	//poll I2C0,Horizontal
	for(i=0;i<4;i++)
	{
		if(i2c_addr_poll(I2C0,HT16K33_ADDRESS_S1+i*2))
		{
			s1_key_addr.periph = I2C0;
			s1_key_addr.addr = HT16K33_ADDRESS_S1+i*2;	
			s1_key_addr.flag = 1;
			break;
		}	
	}
	//address not read
	if(s1_key_addr.flag != 1)
	{			
		//poll I2C1,Verti1
		for(i=0;i<4;i++)
		{
			if(i2c_addr_poll(I2C1,HT16K33_ADDRESS_S1+i*2))
			{
				s1_key_addr.periph = I2C1;
				s1_key_addr.addr = HT16K33_ADDRESS_S1+i*2;	
				s1_key_addr.flag = 1;
				break;
			}	
		}
	}
	//read successful
	if(s1_key_addr.flag)
	{
		ht16k33_init(s1_key_addr.periph,s1_key_addr.addr);
	}

		
#endif

#if	S5
	//S5 NFC I2C address init
	//poll I2C0,Horizontal
	for(i=0;i<4;i++)
	{
		if(i2c_addr_poll(I2C0,MS523_ADDRESS_S5+i*2))
		{
			s5_nfc_addr.periph = I2C0;
			s5_nfc_addr.addr = MS523_ADDRESS_S5+i*2;
			s5_nfc_addr.flag = 1;
			break;
		}	
	}
	//address not read
	if(s5_nfc_addr.flag != 1)
	{			
		//poll I2C1,Verti1
		for(i=0;i<4;i++)
		{
			if(i2c_addr_poll(I2C1,MS523_ADDRESS_S5+i*2))
			{
				s5_nfc_addr.periph = I2C1;
				s5_nfc_addr.addr = MS523_ADDRESS_S5+i*2;
				s5_nfc_addr.flag = 1;
				break;
			}	
		}
	}
	//read successful
	if(s5_nfc_addr.flag)
	{
		#ifdef PRINT_DEBUG_INFO
			printf("S5-NFC is initialization success!\n");
			if(s5_nfc_addr.periph == I2C0)
				printf("%s","I2C0");
			else
				printf("%s","I2C1");
			printf(":");
			printf("%X",s5_nfc_addr.addr);
			printf("\n");
		#endif
		MFRC522_Init(s5_nfc_addr.periph,s5_nfc_addr.addr);
	}
	//read failure
	else
	{
		#ifdef PRINT_DEBUG_INFO
			printf("S5-NFC is initialization failed	!\n");
		#endif
	}
#endif

#if	S6	
	//S6 ULT I2C address init
	//poll I2C0,Horizontal
	for(i=0;i<4;i++)
	{
		if(i2c_addr_poll(I2C0,GD32F330_ADDRESS_S6+i*2))
		{
			s6_ult_addr.periph = I2C0;
			s6_ult_addr.addr = GD32F330_ADDRESS_S6+i*2;
			s6_ult_addr.flag = 1;
			break;
		}	
	}
	//address not read
	if(s6_ult_addr.flag != 1)
	{			
		//poll I2C1,Verti1
		for(i=0;i<4;i++)
		{
			if(i2c_addr_poll(I2C1,GD32F330_ADDRESS_S6+i*2))
			{
				s6_ult_addr.periph = I2C1;
				s6_ult_addr.addr = GD32F330_ADDRESS_S6+i*2;
				s6_ult_addr.flag = 1;
				break;
			}	
		}
	}
	//read successful
#endif

#if	S7	
	//S7 IR I2C address init
	//poll I2C0,Horizontal
	for(i=0;i<4;i++)
	{
		if(i2c_addr_poll(I2C0,PCA9557_ADDRESS_S7+i*2))
		{
			s7_ir_addr.periph = I2C0;
			s7_ir_addr.addr = PCA9557_ADDRESS_S7+i*2;
			s7_ir_addr.flag = 1;
			break;
		}	
	}
	//address not read
	if(s7_ir_addr.flag != 1)
	{			
		//poll I2C1,Verti1
		for(i=0;i<4;i++)
		{
			if(i2c_addr_poll(I2C1,PCA9557_ADDRESS_S7+i*2))
			{
				s7_ir_addr.periph = I2C1;
				s7_ir_addr.addr = PCA9557_ADDRESS_S7+i*2;
				s7_ir_addr.flag = 1;
				break;
			}	
		}
	}
	//read successful
	if(s7_ir_addr.flag)
	{
		#ifdef PRINT_DEBUG_INFO
			printf("S7-IR is initialization success!\n");
			if(s7_ir_addr.periph == I2C0)
				printf("%s","I2C0");
			else
				printf("%s","I2C1");
			printf(":");
			printf("%X",s7_ir_addr.addr);
			printf("\n");
		#endif
		pca9557_ir_init(s7_ir_addr.periph,s7_ir_addr.addr);
	}
	
	else
	{
		printf("S7-IR is initialization failed	!\n");
	}
#endif
}

void digital_control(int num){
	ht16k33_init(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr);
	for(int i=4;i>0;i--){
		ht16k33_display_data(e1_nixie_tube_addr.periph,e1_nixie_tube_addr.addr,i,num%10);
		num/=10;
	}
}
