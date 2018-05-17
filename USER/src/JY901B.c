#include "include.h"


unsigned char data[30];


float Angle_speed[3]={0},Angle[3]={0};

float Air_Pressure=0;
/*******************************************************************************
*函数原型:		void ShortToChar(short sData,unsigned char cData[])
*功　　能:		数据类型转换
*******************************************************************************/
void ShortToChar(short sData,unsigned char cData[])
{
	cData[0]=sData&0xff;
	cData[1]=sData>>8;
}

/*******************************************************************************
*函数原型:		short CharToShort(unsigned char cData[])
*功　　能:		数据类型转换
*******************************************************************************/
short CharToShort(unsigned char cData[])
{
	return ((short)cData[1]<<8)|cData[0];
}

/*******************************************************************************
*函数原型:		void JY901B_Getdata(void)
*功　　能:		利用I2C获取传感器数据
*******************************************************************************/
void JY901B_Getdata(void)
{
	unsigned char i;
	I2C_Start();
    I2C_SendByte(JY901B_SlaveAddress);
	I2C_WaitAck();
	I2C_SendByte(0x37);
	I2C_WaitAck();
	I2C_Start();
	I2C_SendByte(JY901B_SlaveAddress+1);
	I2C_WaitAck();

	for(i=0;i<6;i++)
	{
		data[i]=I2C_RadeByte();	
		if(i==5) I2C_NoAck();
		else I2C_Ack();
	}
	I2C_Stop();
	
	//Delay_us(10);
	
	I2C_Start();
    I2C_SendByte(JY901B_SlaveAddress);
	I2C_WaitAck();
	I2C_SendByte(0x3d);
	I2C_WaitAck();
	I2C_Start();
	I2C_SendByte(JY901B_SlaveAddress+1);
	I2C_WaitAck();

	for(i=6;i<12;i++)
	{
		data[i]=I2C_RadeByte();	
		if(i==11) I2C_NoAck();
		else I2C_Ack();
	}
	I2C_Stop();
	
	//Delay_us(10);
	
	I2C_Start();
  I2C_SendByte(JY901B_SlaveAddress);
	I2C_WaitAck();
	I2C_SendByte(0x47);
	I2C_WaitAck();
	I2C_Start();
	I2C_SendByte(JY901B_SlaveAddress+1);
	I2C_WaitAck();

	for(i=12;i<20;i++)
	{
		data[i]=I2C_RadeByte();	
		if(i==19) I2C_NoAck();
		else I2C_Ack();
	}
	I2C_Stop();

	Angle_speed[0] = (float)CharToShort(&data[0])/32768*2000;
	Angle_speed[1] = (float)CharToShort(&data[2])/32768*2000;
	Angle_speed[2] = (float)CharToShort(&data[4])/32768*2000;
	
	Angle[0] = (float)CharToShort(&data[6])/32768*180;
	Angle[1] = (float)CharToShort(&data[8])/32768*180;
	Angle[2] = (float)CharToShort(&data[10])/32768*180;
	Air_Pressure= ( (int)(data[15]<<24)|(int)(data[14]<<16)|(int)(data[13]<<8)|(int)(data[12])); 	
}
