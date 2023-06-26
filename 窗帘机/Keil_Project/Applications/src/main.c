#include "gd32f4xx.h"
#include "main.h"
#include "i2c.h"
#include "systick.h"
#include "ht16k33.h"
#include "bh1750.h"
#include "gd32f330.h"

i2c_addr_def curtain_addr;//curtain address struct
i2c_addr_def light_addr;
i2c_addr_def key_addr;
i2c_addr_def digital_addr;
int status;


void i2c_addr_init(void)
{
	uint8_t i;
#if	S1	
	//S1 KEY I2C address init
	for(i=0;i<4;i++)
	{
		if(i2c_addr_poll(I2C0,HT16K33_ADDRESS_S1+i*2)){
			key_addr.periph = I2C0;
			key_addr.addr = HT16K33_ADDRESS_S1+i*2;	
			key_addr.flag = 1;
			break;
		}	
	}
	//address not read
	if(key_addr.flag != 1){			
		//poll I2C1,Verti1
		for(i=0;i<4;i++){
			if(i2c_addr_poll(I2C1,HT16K33_ADDRESS_S1+i*2)){
				key_addr.periph = I2C1;
				key_addr.addr = HT16K33_ADDRESS_S1+i*2;	
				key_addr.flag = 1;
				break;
			}	
		}
	}
	//read successful
		i2c_cmd_write(key_addr.periph,key_addr.addr,SYSTEM_ON);

	
#endif
#if S2
		//S2 Light address init
		if(i2c_addr_poll(I2C0, BH1750_ADDRESS_S2_1))
		{
			light_addr.periph = I2C0;
			light_addr.addr =  BH1750_ADDRESS_S2_1;
			light_addr.flag = 1;			
			
		}	
		else if (i2c_addr_poll(I2C0, BH1750_ADDRESS_S2_2))
		  {
			  light_addr.periph = I2C0;
			  light_addr.addr =  BH1750_ADDRESS_S2_2;
			  light_addr.flag = 1;			
			
		  }
	
	//address not read
	if(light_addr.flag != 1)
	{			
		//poll I2C1,Verti1
		
			if(i2c_addr_poll(I2C1, BH1750_ADDRESS_S2_1))
			{
				light_addr.periph = I2C1;
				light_addr.addr =  BH1750_ADDRESS_S2_1;
				light_addr.flag = 1;
			}	
			else if (i2c_addr_poll(I2C1, BH1750_ADDRESS_S2_2))
		  {
			  light_addr.periph = I2C1;
			  light_addr.addr =  BH1750_ADDRESS_S2_2;
			  light_addr.flag = 1;			
			
		  }
	}
#endif			
#if E1
	//E1 Digital address init
	for(i=0;i<4;i++)
	{
		if(i2c_addr_poll(I2C0,HT16K33_ADDRESS_E1+i*2))
		{
			digital_addr.periph = I2C0;
			digital_addr.addr = HT16K33_ADDRESS_E1+i*2;
			digital_addr.flag = 1;			
			break;
		}	
	}
	//address not read
	if(digital_addr.flag != 1)
	{			
		//poll I2C1,Verti1
		for(i=0;i<4;i++)
		{
			if(i2c_addr_poll(I2C1,HT16K33_ADDRESS_E1+i*2))
			{
				digital_addr.periph = I2C1;
				digital_addr.addr = HT16K33_ADDRESS_E1+i*2;
				digital_addr.flag = 1;
				break;
			}	
		}
	}
	//read successful
#endif
	#if E3
		//E3 Curtain address init
	for(int i=0;i<4;i++)
	{
		if(i2c_addr_poll(I2C0, GD32F330_ADDRESS_E3+i*2))
		{
			curtain_addr.periph = I2C0;
			curtain_addr.addr =  GD32F330_ADDRESS_E3+i*2;
			curtain_addr.flag = 1;			
			
		}	
	}
	
	//address not read
	if(curtain_addr.flag != 1)
	{			
		//poll I2C1,Verti1
		
			for(int i=0;i<4;i++)
	{
		if(i2c_addr_poll(I2C1, GD32F330_ADDRESS_E3+i*2))
		{
			curtain_addr.periph = I2C1;
			curtain_addr.addr =  GD32F330_ADDRESS_E3+i*2;
			curtain_addr.flag = 1;			
			
		}	
	}
	if(curtain_addr.flag){
		gd32f330_init(curtain_addr.periph,curtain_addr.addr);
	}
	//read successful		
	}
	if(light_addr.flag){
		//i2c_byte_write(sensor_addr.periph,sensor_addr.addr,0x30,0xA2);
		bh1750_return(light_addr.periph,light_addr.addr);
	}
	//read successful
#endif
}

int key_trans(void){//Translation from Array to Key number
	if(keyvalue[0]&0x01){
		return 1;
	}
	else if(keyvalue[2]&0x01){
		return 2;
	}
	else if(keyvalue[4]&0x01){
		return 3;
	}
	else if(keyvalue[0]&0x02){
		return 4;
	}
	else if(keyvalue[2]&0x02){
		return 5;
	}
	else if(keyvalue[4]&0x02){
		return 6;
	}
	else if(keyvalue[0]&0x04){
		return 7;
	}
	else if(keyvalue[2]&0x04){
		return 8;
	}
	else if(keyvalue[4]&0x04){
		return 9;
	}
	else if(keyvalue[0]&0x08){
		return 10;
	}
	else if(keyvalue[2]&0x08){
		return 11;
	}
	else if(keyvalue[4]&0x08){
		return 12;
	}
	return 0;
}

void key_control(int key){//Control over 
	if(status==0&&key==4){
		status=1;
		return;
	}
}

void digital_control(int num){
	for(int i=4;i>0;i--){
		ht16k33_display_data(digital_addr.periph,digital_addr.addr,i,num%10);
		num/=10;
	}
}
int main(void)
{
		/* configure I2C GPIO */
    i2c0_gpio_config();
		/* configure I2C */
    i2c0_config(); 
		/* configure I2C GPIO */
    i2c1_gpio_config();
		/* configure I2C */
    i2c1_config(); 	
		i2c_addr_init();//initializing i2c address of key and LED
		systick_config();//system tick configuration
		
		ht16k33_init(digital_addr.periph,digital_addr.addr);
		bh1750_init(light_addr.periph,light_addr.addr);
	  status=0;
		int light_value;
		
    while(1)
		{
			light_value=bh1750_get_light_value(light_addr.periph,light_addr.addr);
			digital_control(light_value);
			i2c_read(key_addr.periph,key_addr.addr,KEYKS0,keyvalue,6);//get key status
			if(status==1){
				gd32f330_mov(curtain_addr.periph,curtain_addr.addr,light_value/3);
			}
			if(key_trans()>1&key_trans()<12){
				gd32f330_mov(curtain_addr.periph,curtain_addr.addr,10*(key_trans()-1));//take action
			}
			if(key_trans()==1){
				gd32f330_mov(curtain_addr.periph,curtain_addr.addr,0);
			}
			if(key_trans()==12){
				status=1-status;
			}
			delay_1ms(1000);
    }
		
}
