#include "include.h"
u8	ACC_OFFSET_OK = 0;
struct _sensor sensor;
//**************************************
//��ʼ��MPU6050
//**************************************
/*u8 InitMPU6050(void)
{
	u8 date;
	date = Single_Write(MPU6050_ADDRESS, PWR_MGMT_1, 0x00);  	//�������״̬
	date += Single_Write(MPU6050_ADDRESS, SMPLRT_DIV, 0x07);     
	date += Single_Write(MPU6050_ADDRESS, cONFIG, 0x03);         //��ͨ�˲�
	date += Single_Write(MPU6050_ADDRESS, GYRO_CONFIG, 0x10);    //���������� +-1000
	date += Single_Write(MPU6050_ADDRESS, ACCEL_CONFIG, 0x09);   //���ٶ����� +-4G
	return date;
}*/
void MPU6050_Init(void)
{
	Single_Write(0xd0, 0x6b, 0x00);      //   110100X 7λ  �ӻ���ַ0xd0(1101000)���Ĵ�����ַ0x6b(01101011),����
	Single_Write(0xd0, 0x19, 0x07);       //����Ƶ�ʷ�Ƶ��
	Single_Write(0xd0, 0x1a, 0x03);     //����
	Single_Write(0xd0, 0x1b, 0x10);    //������+ -1000��
  Single_Write(0xd0, 0x1c, 0x09);    //������+ -4g
}
//**************************ʵ�ֺ���********************************************
//��iic��ȡ�������ݷֲ�,������Ӧ�Ĵ���,����MPU6050_Last
//******************************************************************************
void MPU6050_Read(int16_t* buf)
{
signed a,b;  
	a=Single_Read(MPU6050_ADDRESS, 0x3B);//XH���ٶȼ�   (0x3BΪ�Ĵ�����ַ��X����ٶȼƲ���ֵ��8λ)
	b=Single_Read(MPU6050_ADDRESS, 0x3C);//XL���ٶȼ�   (��8λ)
        buf[0]=(a << 8) | b;
	a=Single_Read(MPU6050_ADDRESS, 0x3D);//YH���ٶȼ�
	b=Single_Read(MPU6050_ADDRESS, 0x3E);//YL���ٶȼ�
        buf[1]=(a << 8) | b;
	a=Single_Read(MPU6050_ADDRESS, 0x3F);//ZH���ٶȼ�
	b=Single_Read(MPU6050_ADDRESS, 0x40);//ZL���ٶȼ�
        buf[2]=(a << 8) | b;
	a=Single_Read(MPU6050_ADDRESS, 0x43);//XH������
	b=Single_Read(MPU6050_ADDRESS, 0x44);//XL������
        buf[3]=(a << 8) | b;
	a=Single_Read(MPU6050_ADDRESS, 0x45);//YH������
	b=Single_Read(MPU6050_ADDRESS, 0x46);//YL������
        buf[4]=(a << 8) | b;
	a=Single_Read(MPU6050_ADDRESS, 0x47);//ZH������
	b=Single_Read(MPU6050_ADDRESS, 0x48);//Z������
        buf[5]=(a << 8) | b;
}
//**************************ʵ�ֺ���********************************************
//��iic��ȡ�������ݷֲ�,������Ӧ�Ĵ���,����MPU6050_Last
//******************************************************************************
void Read_MPU6050(MPU6050_XYZ* buf)
{
signed a,b;  
	a=Single_Read(MPU6050_ADDRESS, 0x3B);//XH���ٶȼ�
	b=Single_Read(MPU6050_ADDRESS, 0x3C);//XL���ٶȼ�
        buf->MPU6050_JX=(a << 8) | b;
	a=Single_Read(MPU6050_ADDRESS, 0x3D);//YH���ٶȼ�
	b=Single_Read(MPU6050_ADDRESS, 0x3E);//YL���ٶȼ�
        buf->MPU6050_JY=(a << 8) | b;
	a=Single_Read(MPU6050_ADDRESS, 0x3F);//ZH���ٶȼ�
	b=Single_Read(MPU6050_ADDRESS, 0x40);//ZL���ٶȼ�
        buf->MPU6050_JZ=(a << 8) | b;
	a=Single_Read(MPU6050_ADDRESS, 0x43);//XH������
	b=Single_Read(MPU6050_ADDRESS, 0x44);//XL������
        buf->MPU6050_TX=(a << 8) | b;
	a=Single_Read(MPU6050_ADDRESS, 0x45);//YH������
	b=Single_Read(MPU6050_ADDRESS, 0x46);//YL������
        buf->MPU6050_TY=(a << 8) | b;
	a=Single_Read(MPU6050_ADDRESS, 0x47);//ZH������
	b=Single_Read(MPU6050_ADDRESS, 0x48);//Z������
        buf->MPU6050_TZ=(a << 8) | b;
}
/**************************ʵ�ֺ���********************************************
//��iic��ȡ�������ݷֲ�,������Ӧ�Ĵ���
*******************************************************************************/
/*
void MPU6050_Dataanl(void)
{
u8 mpu6050_buffer[14];
	mpu6050_buffer[0]=Single_Read(MPU6050_ADDRESS, 0x3B);
	mpu6050_buffer[1]=Single_Read(MPU6050_ADDRESS, 0x3C);
	mpu6050_buffer[2]=Single_Read(MPU6050_ADDRESS, 0x3D);
	mpu6050_buffer[3]=Single_Read(MPU6050_ADDRESS, 0x3E);
	mpu6050_buffer[4]=Single_Read(MPU6050_ADDRESS, 0x3F);
	mpu6050_buffer[5]=Single_Read(MPU6050_ADDRESS, 0x40);
	mpu6050_buffer[8]=Single_Read(MPU6050_ADDRESS, 0x43);
	mpu6050_buffer[9]=Single_Read(MPU6050_ADDRESS, 0x44);
	mpu6050_buffer[10]=Single_Read(MPU6050_ADDRESS, 0x45);
	mpu6050_buffer[11]=Single_Read(MPU6050_ADDRESS, 0x46);
	mpu6050_buffer[12]=Single_Read(MPU6050_ADDRESS, 0x47);
	mpu6050_buffer[13]=Single_Read(MPU6050_ADDRESS, 0x48);
	
	sensor.acc.origin.x = ((((int16_t)mpu6050_buffer[0]) << 8) | mpu6050_buffer[1]) - sensor.acc.quiet.x;   //ԭʼֵ-��ֵ̬
	sensor.acc.origin.y = ((((int16_t)mpu6050_buffer[2]) << 8) | mpu6050_buffer[3]) - sensor.acc.quiet.y;
	sensor.acc.origin.z = ((((int16_t)mpu6050_buffer[4]) << 8) | mpu6050_buffer[5]);

	sensor.gyro.origin.x = ((((int16_t)mpu6050_buffer[8]) << 8) | mpu6050_buffer[9]);
	sensor.gyro.origin.y = ((((int16_t)mpu6050_buffer[10]) << 8)| mpu6050_buffer[11]);
	sensor.gyro.origin.z = ((((int16_t)mpu6050_buffer[12]) << 8)| mpu6050_buffer[13]);
  
	sensor.gyro.radian.x = sensor.gyro.origin.x * Gyro_Gr - sensor.gyro.quiet.x * Gyro_Gr;
	sensor.gyro.radian.y = sensor.gyro.origin.y * Gyro_Gr - sensor.gyro.quiet.y * Gyro_Gr;
	sensor.gyro.radian.z = sensor.gyro.origin.z * Gyro_Gr - sensor.gyro.quiet.z * Gyro_Gr;


////////////////////////////////////////////////////
//    	The calibration  of  gyro and  acc  (У׼)//
////////////////////////////////////////////////////	


  if(!ACC_OFFSET_OK && Rc_Data.THROTTLE <= 1200 && Rc_Data.THROTTLE >= 900)
	{
		if(Rc_Data.ROLL <= 1200 && Rc_Data.PITCH >= 1750)
		{	
			//LED2_On();
			static int32_t	tempax=0,tempay=0,tempaz=0;
			static uint8_t cnt_a=0;

			if(cnt_a==0)
			{
				sensor.acc.quiet.x = 0;
				sensor.acc.quiet.y = 0;
				sensor.acc.quiet.z = 0;
				tempax = 0;
				tempay = 0;
				tempaz = 0;
				cnt_a = 1;
				return;
			}
				tempax+= sensor.acc.origin.x;
				tempay+= sensor.acc.origin.y;
				tempaz+= sensor.acc.origin.z;
				
				if(cnt_a==200)
				{
					sensor.acc.quiet.x = tempax/cnt_a;
					sensor.acc.quiet.y = tempay/cnt_a;
					sensor.acc.quiet.z = tempaz/cnt_a;
					cnt_a = 0;
					ACC_OFFSET_OK = 1;
					//EE_SAVE_ACC_OFFSET();//��������
					return;
				}
				cnt_a++;		
			}	
  }
	else ACC_OFFSET_OK = 1;
}
*/
/**************************ʵ�ֺ���********************************************
//���������У׼
*******************************************************************************/

void Gyro_OFFEST(void)
{
   int cnt_g=2000;
   u8 mpu6050_buffer[14];

	 int32_t  tempgx=0,tempgy=0,tempgz=0;
	 sensor.gyro.averag.x=0;    //���ƫ������
	 sensor.gyro.averag.y=0;  
	 sensor.gyro.averag.z=0;
	 while(cnt_g--)       //ѭ���ɼ�2000��   ��ƽ��
	 {
            mpu6050_buffer[0]=Single_Read(MPU6050_ADDRESS, 0x3B);
	    mpu6050_buffer[1]=Single_Read(MPU6050_ADDRESS, 0x3C);
	    mpu6050_buffer[2]=Single_Read(MPU6050_ADDRESS, 0x3D);
	    mpu6050_buffer[3]=Single_Read(MPU6050_ADDRESS, 0x3E);
	    mpu6050_buffer[4]=Single_Read(MPU6050_ADDRESS, 0x3F);
	    mpu6050_buffer[5]=Single_Read(MPU6050_ADDRESS, 0x40);
	    mpu6050_buffer[8]=Single_Read(MPU6050_ADDRESS, 0x43);
	    mpu6050_buffer[9]=Single_Read(MPU6050_ADDRESS, 0x44);
	    mpu6050_buffer[10]=Single_Read(MPU6050_ADDRESS, 0x45);
	    mpu6050_buffer[11]=Single_Read(MPU6050_ADDRESS, 0x46);
	    mpu6050_buffer[12]=Single_Read(MPU6050_ADDRESS, 0x47);
	    mpu6050_buffer[13]=Single_Read(MPU6050_ADDRESS, 0x48);
		 
            sensor.gyro.origin.x = ((((int16_t)mpu6050_buffer[8]) << 8) | mpu6050_buffer[9]);
	    sensor.gyro.origin.y = ((((int16_t)mpu6050_buffer[10]) << 8)| mpu6050_buffer[11]);
	    sensor.gyro.origin.z = ((((int16_t)mpu6050_buffer[12]) << 8)| mpu6050_buffer[13]);
            tempgx+= sensor.gyro.origin.x;
	    tempgy+= sensor.gyro.origin.y;
	    tempgz+= sensor.gyro.origin.z;
        }
	sensor.gyro.quiet.x=tempgx/2000;
	sensor.gyro.quiet.y=tempgy/2000;
	sensor.gyro.quiet.z=tempgz/2000;
	  
}



