#include "gd32f4xx.h"
//#include "gd32f450z_eval.h"
#include "systick.h"

void uart0_init()
{
   
    rcu_periph_clock_enable(RCU_GPIOA);
    rcu_periph_clock_enable(RCU_USART0);

    gpio_af_set(GPIOA, GPIO_AF_7, GPIO_PIN_9); 
    gpio_af_set(GPIOA, GPIO_AF_7, GPIO_PIN_10);

 
    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_9);
    gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_9);

    gpio_mode_set(GPIOA, GPIO_MODE_AF, GPIO_PUPD_PULLUP,GPIO_PIN_10);
    //gpio_output_options_set(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,GPIO_PIN_10);

    
    usart_deinit(USART0);	
    usart_baudrate_set(USART0,115200U);			
    usart_receive_config(USART0, USART_RECEIVE_ENABLE);
    usart_transmit_config(USART0, USART_TRANSMIT_ENABLE);
    usart_enable(USART0);
}

int main(void)
{
    uint16_t rx_data = 0;
	
	uart0_init();

    while(1){
        
        while (usart_flag_get(USART0, USART_FLAG_RBNE) == RESET);
		rx_data = usart_data_receive(USART0);  
           
        usart_data_transmit(USART0, (uint8_t)rx_data);
        while(RESET == usart_flag_get(USART0, USART_FLAG_TBE));
    }
}
