#include<include.h>
void ALL_init(void)
{
	
led_INIT();
//key_init();
Delay_init();
usart_init();
usart2_3_init();
TIM4_PWM_Init(16799);
//TIM2_PWM_Init(16799);

//TIM1_PWM_Init(500-1,168-1);	//84M/84=1Mhz的计数频率,重装载值500，所以PWM频率为 1M/500=2Khz.
	
I2C_INIT();
OLED_Init();
//MPU6050_Init();
//Init_HMC5883L();
//NRF24L01_init();
	
}

