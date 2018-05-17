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


	
uint8_t NRF_Channel=67;   //通信频率等于 2.400+ NRF_Channel   范围 0 - 100;
uint32_t i=0;

uint8_t aaa[]={3,'J','Y','F'};

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
 
//	NRF_RX_Mode();
	
	
	//NRF_Buff[2]='a';
  //NRF_Buff[1]='A';
	
	while(1)
	{
	
	//NRF24L01_RxPacket(NRF_Buff);
		
 //if(NRF_Buff[1]==(uint8_t)'S')
	//{
	//Start();
	//}
		
		JY901B_Getdata();		
	
	
		Delay_ms(50);
		//USART_Send_number(Air_Pressure);
	//USART_Send_number_5(Air_Pressure);
		// USART_Send_number_3(( int)Angle[0]);
		// USART_Send_number_3(( int)Angle[1]);
	  USART_Send_number_3(( int)Angle[2]);
		
	}
}


