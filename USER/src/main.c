#include<include.h>
#include <bmp.h>


u8 RxBuffer[32]={0};
u8 TxBuffer[32]={'6'};
uint16_t hmc_msg;

uint8_t m[][10]={{"111.830975"},{"830975"}};

MPU6050_XYZ *MPU6050_INFO;
int16_t MPU6050_buf[6];

GPS_INFO *GPS1;
	
uint8_t NRF_Channel=67;   //通信频率等于 2.400+ NRF_Channel   范围 0 - 100;
uint32_t i=0;

int main()
{
	
	ALL_init();
	uint8_t str[]="gps_message:";
	uint8_t lng[]="lng:";
	uint8_t lat[]="lat:";
	//uint8_t t;
  OLED_Clear(); 
	led();	
	//	t=' ';
  //	USART2_Send_data(m[0],10);
  //NRF_TX_Mode();
 // NRF_Buff[1]='A';
	while(1)
	{
	//NRF24L01_TxPacket(NRF_Buff);
		JY901B_Getdata();
	//Delay_ms(60000);
	//i=GetDistance(111.689321,40.813243,111.69067,40.813614);
	//GPS_RMC_Parse(USART1_RX_BUF,GPS1);

// GPS_output(gps1);
		
//	TIM_SetCompare1(TIM4,i);
	//	Delay_ms(500);
		
	
		//printf("\r\n纬度：%d,经度%d\r\n",gps1.latitude,gps1.longitude);
    //printf("gpsgpsgpsgpsgps");
	//	OLED_ShowString(1,2,str);
	//	OLED_ShowString(0,4,lng);
	//	OLED_ShowString(0,6,lat);
		
	
	}
}


