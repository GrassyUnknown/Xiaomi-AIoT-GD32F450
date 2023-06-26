/*!
    \file    main.c
    \brief   main routine		comb2

    \version 2021-08, V0.1
*/

#include "gd32f4xx.h"
#include "main.h"
#include "systick.h"

#include "pca9685.h"
#include "i2c.h"
#include "ht16k33.h"
#include "i2c_test.h"
#include <math.h>

i2c_addr_def e1_nixie_tube_addr;
i2c_addr_def e1_rgb_led_addr;
i2c_addr_def e2_fan_addr;
i2c_addr_def e3_curtain_addr;
i2c_addr_def s1_key_addr;
i2c_addr_def s5_nfc_addr;
i2c_addr_def s6_ult_addr;
i2c_addr_def s7_ir_addr;
i2c_addr_def s2_sensor_addr;

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
	return 0;
}

struct s2_para{
	float temperature;
	float humidity;
} s2_data;
void s2_read_sht3x(void){
	uint8_t th_value[6];
	uint16_t tmp;
  i2c_byte_write(s2_sensor_addr.periph,s2_sensor_addr.addr,0x2C,0x06);
	delay_1ms(100);
	i2c_read(s2_sensor_addr.periph,s2_sensor_addr.addr,0x21,th_value,6);
	
	tmp=(th_value[0]<<8)+ th_value[1];
	s2_data.temperature=(float)tmp*175/(65536-1)-45; 
	
  tmp=(th_value[3]<<8) + th_value[4];
	s2_data.humidity=(float)tmp*100/(65536-1); 
	
}


int get_s6_data(void){
	uint8_t	recvdata[2];
	uint8_t sts;
	uint16_t display;
	sts = i2c_read(s6_ult_addr.periph,s6_ult_addr.addr,GD32F330_READ_CMD,recvdata,2);
	if(sts)
	{
		display = (recvdata[0] << 8) | recvdata[1];
	}
	return display;
}

void i2c_init(void){
		i2c0_gpio_config();
		/* configure I2C */
    i2c0_config(); 			
		/* configure I2C GPIO */
    i2c1_gpio_config();
		/* configure I2C */
    i2c1_config(); 	
		systick_config();
		i2c_addr_init();
}
int main(void)
{

		i2c_init();
		int motorstate=0;
		int time=0;//time spent
		int settime=1;//time set
		int digitalst=0;//show which :
		//0 - time spent(timing)
		//1 - time set
		//2 - motor mode
		//3 - temperture
		int temptime=0;
		int s6_data;
		
		s2_read_sht3x();
    while(1){
			s6_data=get_s6_data();
			//s2_read_sht3x();

			if(time>=0){//timing
				if(digitalst==0){//show time
					digital_control(time);
				}
				if(settime>0)settime--;
				if(time==0){//STOP motor
					pc9685_motor_control(e2_fan_addr.periph,e2_fan_addr.addr,0);
					motorstate=0;
				}
			}
			if(digitalst==1){//show SET time
				digital_control(settime);
				temptime++;
				if(temptime==3){//STOP show SET time
					digitalst=0;
				}
			}
			if(digitalst==2){//show mode
				digital_control(motorstate);
			}
			if(digitalst==3){//show temperture
				int temperture=(int)(1.07*s2_data.temperature-2.7+exp((17.27*s2_data.temperature)/(237.27+s2_data.temperature)));
				digital_control(temperture);
				if(temperture<25){
					pc9685_motor_control(e2_fan_addr.periph,e2_fan_addr.addr,0);
					motorstate=0;
				}
				if(temperture>=25&&temperture<=27){
					pc9685_motor_control(e2_fan_addr.periph,e2_fan_addr.addr,1);
					motorstate=1;
				}
				if(temperture>27&&temperture<=30){
					pc9685_motor_control(e2_fan_addr.periph,e2_fan_addr.addr,2);
					motorstate=2;
				}
				if(temperture>30){
					pc9685_motor_control(e2_fan_addr.periph,e2_fan_addr.addr,3);
					motorstate=3;
				}
				
			}
			if(digitalst==4){//show distance
				digital_control(s6_data);
				if(s6_data<50){
					pc9685_motor_control(e2_fan_addr.periph,e2_fan_addr.addr,0);
					motorstate=0;
				}
				if(s6_data>=50&&s6_data<=300){
					pc9685_motor_control(e2_fan_addr.periph,e2_fan_addr.addr,1);
					motorstate=1;
				}
				if(s6_data>300&&s6_data<=600){
					pc9685_motor_control(e2_fan_addr.periph,e2_fan_addr.addr,2);
					motorstate=2;
				}
				if(s6_data>600){
					pc9685_motor_control(e2_fan_addr.periph,e2_fan_addr.addr,3);
					motorstate=3;
				}
			}
			
			i2c_read(s1_key_addr.periph,s1_key_addr.addr,KEYKS0,keyvalue,6);//get key status
			switch(key_trans()){
					case 1:
					{
						settime+=10;
						digitalst=1;//show SET time
						temptime=0;
					 break;
					}
					case 2: 
					{
						if(settime>=10)settime=settime-10;
						digitalst=1;//show SET time
						temptime=0;
					 break;
					}
					case 3:
					{
						time=settime;
						digitalst=0;//show timing
						if(motorstate==0)motorstate=2;
						pc9685_motor_control(e2_fan_addr.periph,e2_fan_addr.addr,motorstate);
						break;
					}
					case 4:
					{
						motorstate=(motorstate+1)%4;
						pc9685_motor_control(e2_fan_addr.periph,e2_fan_addr.addr,motorstate);
						digital_control(motorstate);
						digitalst=2;//show motor mode
						break;
					}
					case 5:
					{
						digitalst=3;//show temperture
						break;
					}
					case 6:
					{
						digitalst=4;//show distance
						break;
					}
			}
			delay_1ms(1000);
			time--;
    }
}


	

