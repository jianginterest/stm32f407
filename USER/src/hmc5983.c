#include "include.h"
#include  <math.h>
#define  FILL_NUM  10           //�شż�

double y_gain=0.967;

int16_t X_BUFF[FILL_NUM],Y_BUFF[FILL_NUM],Z_BUFF[FILL_NUM];
struct _HMC_XYZ  HMC_XYZ;


u8 Init_HMC5883L(void)
{
u8 date;
   date = Single_Write(HMC5883L_ADDRESS,0x02,0x00);//Ĭ�ϸ���Ϊ��������ģʽ
    return date;
} 

//******************************************************
//��������HMC5883�ڲ��Ƕ����ݣ���ַ��Χ0x3~0x5
//******************************************************
uint16_t Multiple_Read_HMC5883L(void)
{      	
u8 i;
int16_t x,y,z;
double Angle;
uint16_t Acr;
	 uint8_t BUF[8];
	 static uint8_t filter_cnt=0;
	 int32_t temp1=0,temp2=0,temp3=0;
	
    I2C_Start();                          //��ʼ�ź�
    I2C_SendByte(HMC5883L_ADDRESS);                   //�����豸��ַ+д�ź�
	  I2C_WaitAck();
    I2C_SendByte(0x03);                   //���ʹ洢��Ԫ��ַ����0x3��ʼ	  ��ַ03~0 8 ��ŵ���Ҫ������ȡ�����ݲ���ֵ
	  I2C_WaitAck();
    I2C_Start();                          //��ʼ�ź�
    I2C_SendByte(HMC5883L_ADDRESS+1);     //�����豸��ַ+���ź�
	  I2C_WaitAck();
	  for (i=0; i<6; i++)                   //������ȡ6����ַ���ݣ��洢��BUF
    {
        BUF[i] = I2C_RadeByte();          //BUF[0]�洢����
        if (i == 5)
           I2C_NoAck();                   //���һ��������Ҫ��NOACK
        else
           I2C_Ack();                     //��ӦACK
    }
    I2C_Stop();                           //ֹͣ�ź�
    I2C_delay();

	  X_BUFF[filter_cnt] = BUF[0] << 8 | BUF[1]; //Combine MSB and LSB of X Data output register;
	  Y_BUFF[filter_cnt] = BUF[4] << 8 | BUF[5]; //Combine MSB and LSB of Y Data output register;
	  Z_BUFF[filter_cnt] = BUF[2] << 8 | BUF[3]; //Combine MSB and LSB of Z Data output register;
	  for(i=0;i<FILL_NUM;i++)  //10��ȵĻ����˲�
	  {
		   temp1 += X_BUFF[i];
		   temp2 += Y_BUFF[i];
		   temp3 += Z_BUFF[i];
	  }
	  x = temp1 / FILL_NUM;
	  y = temp2 / FILL_NUM;
	  z = temp3 / FILL_NUM;
	  HMC_XYZ.HMC5883_X=x;
          HMC_XYZ.HMC5883_Y=y;
          HMC_XYZ.HMC5883_Z=z;	
	  filter_cnt++;
	  if(filter_cnt==FILL_NUM)	filter_cnt=0;
	
        Angle= atan2((double)y,(double)x)*(180/3.14159265)+180;//��λ���Ƕ� (0~360)      y/x��ֵ���з�����
        //Angle*=10;
        Acr=(uint16_t)Angle;
        return Acr;
}	   


