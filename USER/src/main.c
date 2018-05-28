#include<include.h>
#include <bmp.h>


u8 RxBuffer[32]={0};
u8 TxBuffer[32]={'6'};
uint16_t hmc_msg;

uint8_t m[][10]={{"111.830975"},{"830975"}};

MPU6050_XYZ *MPU6050_INFO;
int16_t MPU6050_buf[6];

uint8_t W[]="Welcome!";
uint8_t acc[]="acc:";
uint8_t ang[]="ang:";
uint8_t magnetic[]="mag:";
uint8_t angle[]="angle:";
uint8_t Air_Pressur[]="Air_Pressure:";



	
uint8_t NRF_Channel=67;   //通信频率等于 2.400+ NRF_Channel   范围 0 - 100;
uint32_t i=0;

uint8_t aaa[]={3,'J','Y','F'};

static uint8_t a[2]={0x0d,0x0a};

int main()
{
	
	ALL_init();
	led();
		
//	u32 t;
	OLED_Clear(); 
	OLED_ShowString(24,3,W);
	///Delay_ms(1500);
  OLED_Clear(); 
	OLED_ShowString(0,0,acc);
	OLED_ShowString(0,2,ang);
	OLED_ShowString(0,4,magnetic);
	OLED_ShowString(0,6,angle);
	
	//	t=' ';
  //	USART2_Send_data(m[0],10);
 
	NRF_RX_Mode();
	
	
	//NRF_Buff[2]='a';
  //NRF_Buff[1]='A';
	
	while(1)
	{
	
	//NRF24L01_RxPacket(NRF_Buff);
		
 //if(NRF_Buff[1]==(uint8_t)'S')
	//{
	//Start();
	//}
	//if(NRF_Buff[1]==(uint8_t)'A')
	//{
		
	//	TIM_SetCompare3(TIM4,5);//左下 5
// TIM_SetCompare4(TIM4,5); //左 右10
// TIM_SetCompare1(TIM4,7);
// TIM_SetCompare2(TIM4,5); 
	//}
		
		 JY901B_Getdata();		
	
		 Delay_ms(500);
		
		 USART2_Send_data(Air_Pressur,13);
	   USART_Send_number_5(Air_Pressure);
	 	USART2_Send_data(a,2);
		
		 USART2_Send_data(angle,6);
		 USART_Send_number_3(( int)Angle[0]);
		 USART_Send_number_3(( int)Angle[1]);
	   USART_Send_number_3(( int)Angle[2]);
		 USART2_Send_data(a,2);
		
		 USART2_Send_data(ang,4);
	   USART_Send_number_3(( int)Angle_speed[0]);
		 USART_Send_number_3(( int)Angle_speed[1]);
		 USART_Send_number_3(( int)Angle_speed[2]);
		 USART2_Send_data(a,2);
		 
		 USART2_Send_data(acc,4);
		 USART_Send_number_3((int)(JSD[0]*100));
		 USART_Send_number_3((int)(JSD[1]*100));
		 USART_Send_number_3((int)(JSD[2]*100));
		 USART2_Send_data(a,2);
		 
		 USART2_Send_data(magnetic,4);
		 USART_Send_number_5( (int)c[0]);
		 USART_Send_number_5( (int)c[1]);
		 USART_Send_number_5( (int)c[2]);
		 
		 USART2_Send_data(a,2);
		 
		 USART2_Send_data(a,2);
		 
		 USART2_Send_data(a,2);
		 

//   // USART_Send_number_3( (int)QY[0]);
		 
	}
}

/******************* (C) COPYRIGHT 2018 Jiang yufan *****END OF FILE****/
