#include <include.h>

/*******************************************************************************
* Function Name  : I2C_GPIO_Config
* Description    : Configration Simulation IIC GPIO
* Input          : None 
* Output         : None
* Return         : None
****************************************************************************** */
void I2C_INIT(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 
 
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);  //使能GPIOB时钟
  
	GPIO_InitStructure.GPIO_Pin =  SCL_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;//上下拉电阻
	GPIO_InitStructure.GPIO_OType=GPIO_OType_OD;
	
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin =  SDA_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;//上下拉电阻
	GPIO_InitStructure.GPIO_OType=GPIO_OType_OD;
	
  GPIO_Init(GPIOC, &GPIO_InitStructure);
//	SCL_H;
//	SDA_H;
}
void I2C_SDA_OUT(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 
 
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);  //使能GPIOB时钟

  GPIO_InitStructure.GPIO_Pin =  SDA_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;//上下拉电阻
	GPIO_InitStructure.GPIO_OType=GPIO_OType_OD;
	
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}
void I2C_SDA_IN(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 
 
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);  //使能GPIOB时钟

  GPIO_InitStructure.GPIO_Pin =  SDA_PIN;
 // GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;//上下拉电阻
	//GPIO_InitStructure.GPIO_OType=GPIO_OType_OD;
	
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}
/*******************************************************************************
* Function Name  : I2C_delay
* Description    : Simulation IIC Timing series delay
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void I2C_delay(void)
{

	uint8_t j = 1;
	uint16_t i = 0;

//	while(j>0)
//	{
		for(i=0;i<50;i++)
		{
		}
//		j--;
//	}
}

void delay5ms(void)
{
		
  uint16_t i=500;
	while(i)
		i--;
}
/*******************************************************************************
* Function Name  : I2C_Start
* Description    : Master Start Simulation IIC Communication
* Input          : None
* Output         : None
* Return         : Wheather	 Start
****************************************************************************** */
uint16_t I2C_Start(void)
{
	
	SDA_H;
	SCL_H;
	I2C_delay();
	SDA_L;
	I2C_delay();
	SCL_L;
	I2C_delay();
	return TRUE;
}
/*******************************************************************************
* Function Name  : I2C_Stop
* Description    : Master Stop Simulation IIC Communication
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void I2C_Stop(void)
{
	SDA_L;
	SCL_H;
	I2C_delay();
	SDA_H;
} 
/*******************************************************************************
* Function Name  : I2C_Ack
* Description    : Master Send Acknowledge Single
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void I2C_Ack(void)
{	
	SDA_L;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SCL_L;
	I2C_delay();
	SDA_H;
}   
/*******************************************************************************
* Function Name  : I2C_NoAck
* Description    : Master Send No Acknowledge Single
* Input          : None
* Output         : None
* Return         : None
****************************************************************************** */
void I2C_NoAck(void)
{	
	SDA_H;
	I2C_delay();
	SCL_H;
	I2C_delay();
	SCL_L;
	I2C_delay();
}
/*******************************************************************************
* Function Name  : I2C_WaitAck
* Description    : Master Reserive Slave Acknowledge Single
* Input          : None
* Output         : None
* Return         : Wheather	 Reserive Slave Acknowledge Single
****************************************************************************** */
uint16_t I2C_WaitAck(void) 	 //返回为:=1有ACK,=0无ACK
{
	uint8_t re;
	SDA_H;			
	I2C_delay();
	SCL_H;
	I2C_delay();
	if(SDA_read)
	{
		re = 1;
	}
	else
	{
		re = 0;
	}
	SCL_L;
	I2C_delay();
	return re;
}
/*******************************************************************************
* Function Name  : I2C_SendByte
* Description    : Master Send a Byte to Slave
* Input          : Will Send Date
* Output         : None
* Return         : None
****************************************************************************** */
void I2C_SendByte(unsigned char SendByte) //数据从高位到低位//
{
    u8 i;
    for(i=0;i<8;i++)
    {
		if(SendByte&0x80) SDA_H;  else SDA_L;   
		 I2C_delay();
		SCL_H;
		 I2C_delay();
		SCL_L;
		if (i == 7)
		{
			 SDA_H; // 释放总线
		}
		
        SendByte<<=1;
        I2C_delay();
    }
}  
/*******************************************************************************
* Function Name  : I2C_RadeByte
* Description    : Master Reserive a Byte From Slave
* Input          : None
* Output         : None
* Return         : Date From Slave 
****************************************************************************** */
unsigned char I2C_RadeByte(void)  //数据从高位到低位//
{ 
    u8 i=8;
    u8 ReceiveByte=0;
    SDA_H;				
   for (i = 0; i < 8; i++)
    {
      ReceiveByte<<=1;      
      SCL_H;
      I2C_delay();	
      if(SDA_read)
      {
        ReceiveByte|=0x01;
      }
	   SCL_L;
	  I2C_delay();	
    }
   
    return ReceiveByte;
} 
//ZRX          
//单字节写入*******************************************

uint16_t Single_Write(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data)		     //void
{
  	if(!I2C_Start())return FALSE;
    I2C_SendByte(SlaveAddress);   //发送设备地址+写信号//I2C_SendByte(((REG_Address & 0x0700) >>7) | SlaveAddress & 0xFFFE);//设置高起始地址+器件地址 
    if(!I2C_WaitAck()){I2C_Stop(); return FALSE;}
    I2C_SendByte(REG_Address );   //设置低起始地址      
    I2C_WaitAck();	
    I2C_SendByte(REG_data);
    I2C_WaitAck();   
    I2C_Stop(); 
    delay5ms();
    return TRUE;
}

u16 Single_Write_MS5611(unsigned char SlaveAddress,unsigned char REG_Address)		     //void
{
  	if(!I2C_Start())return FALSE;
    I2C_SendByte(SlaveAddress);   //发送设备地址+写信号//I2C_SendByte(((REG_Address & 0x0700) >>7) | SlaveAddress & 0xFFFE);//设置高起始地址+器件地址 
    if(!I2C_WaitAck()){I2C_Stop(); return FALSE;}
    I2C_SendByte(REG_Address );   //设置低起始地址      
    I2C_WaitAck();	 
    I2C_Stop(); 
    delay5ms();
    return TRUE;
}

//单字节读取*****************************************
unsigned char Single_Read(unsigned char SlaveAddress,unsigned char REG_Address)
{  
	unsigned char REG_data;     	
	if(!I2C_Start())
		   return FALSE;
    I2C_SendByte(SlaveAddress); //I2C_SendByte(((REG_Address & 0x0700) >>7) | REG_Address & 0xFFFE);//设置高起始地址+器件地址 
    if(!I2C_WaitAck())
    {
      I2C_Stop();return FALSE;
    }
    I2C_SendByte((u8) REG_Address);   //设置低起始地址      
    I2C_WaitAck();
    I2C_Start();
    I2C_SendByte(SlaveAddress+1);
    I2C_WaitAck();

	  REG_data= I2C_RadeByte();
    I2C_NoAck();
    I2C_Stop();
    
	return REG_data;
}	

