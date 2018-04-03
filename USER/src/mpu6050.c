#include "include.h"
u8	ACC_OFFSET_OK = 0;
struct _sensor sensor;
//**************************************
//初始化MPU6050
//**************************************
/*u8 InitMPU6050(void)
{
	u8 date;
	date = Single_Write(MPU6050_ADDRESS, PWR_MGMT_1, 0x00);  	//解除休眠状态
	date += Single_Write(MPU6050_ADDRESS, SMPLRT_DIV, 0x07);     
	date += Single_Write(MPU6050_ADDRESS, cONFIG, 0x03);         //低通滤波
	date += Single_Write(MPU6050_ADDRESS, GYRO_CONFIG, 0x10);    //陀螺仪量程 +-1000
	date += Single_Write(MPU6050_ADDRESS, ACCEL_CONFIG, 0x09);   //加速度量程 +-4G
	return date;
}*/
void MPU6050_Init(void)
{
	Single_Write(0xd0, 0x6b, 0x00);      //   110100X 7位  从机地址0xd0(1101000)，寄存器地址0x6b(01101011),数据
	Single_Write(0xd0, 0x19, 0x07);       //采样频率分频器
	Single_Write(0xd0, 0x1a, 0x03);     //过滤
	Single_Write(0xd0, 0x1b, 0x10);    //满量程+ -1000度
  Single_Write(0xd0, 0x1c, 0x09);    //满量程+ -4g
}
//**************************实现函数********************************************
//将iic读取到得数据分拆,放入相应寄存器,更新MPU6050_Last
//******************************************************************************
void MPU6050_Read(int16_t* buf)
{
signed a,b;  
	a=Single_Read(MPU6050_ADDRESS, 0x3B);//XH加速度计   (0x3B为寄存器地址；X轴加速度计测量值高8位)
	b=Single_Read(MPU6050_ADDRESS, 0x3C);//XL加速度计   (低8位)
        buf[0]=(a << 8) | b;
	a=Single_Read(MPU6050_ADDRESS, 0x3D);//YH加速度计
	b=Single_Read(MPU6050_ADDRESS, 0x3E);//YL加速度计
        buf[1]=(a << 8) | b;
	a=Single_Read(MPU6050_ADDRESS, 0x3F);//ZH加速度计
	b=Single_Read(MPU6050_ADDRESS, 0x40);//ZL加速度计
        buf[2]=(a << 8) | b;
	a=Single_Read(MPU6050_ADDRESS, 0x43);//XH陀螺仪
	b=Single_Read(MPU6050_ADDRESS, 0x44);//XL陀螺仪
        buf[3]=(a << 8) | b;
	a=Single_Read(MPU6050_ADDRESS, 0x45);//YH陀螺仪
	b=Single_Read(MPU6050_ADDRESS, 0x46);//YL陀螺仪
        buf[4]=(a << 8) | b;
	a=Single_Read(MPU6050_ADDRESS, 0x47);//ZH陀螺仪
	b=Single_Read(MPU6050_ADDRESS, 0x48);//Z陀螺仪
        buf[5]=(a << 8) | b;
}
//**************************实现函数********************************************
//将iic读取到得数据分拆,放入相应寄存器,更新MPU6050_Last
//******************************************************************************
void Read_MPU6050(MPU6050_XYZ* buf)
{
signed a,b;  
	a=Single_Read(MPU6050_ADDRESS, 0x3B);//XH加速度计
	b=Single_Read(MPU6050_ADDRESS, 0x3C);//XL加速度计
        buf->MPU6050_JX=(a << 8) | b;
	a=Single_Read(MPU6050_ADDRESS, 0x3D);//YH加速度计
	b=Single_Read(MPU6050_ADDRESS, 0x3E);//YL加速度计
        buf->MPU6050_JY=(a << 8) | b;
	a=Single_Read(MPU6050_ADDRESS, 0x3F);//ZH加速度计
	b=Single_Read(MPU6050_ADDRESS, 0x40);//ZL加速度计
        buf->MPU6050_JZ=(a << 8) | b;
	a=Single_Read(MPU6050_ADDRESS, 0x43);//XH陀螺仪
	b=Single_Read(MPU6050_ADDRESS, 0x44);//XL陀螺仪
        buf->MPU6050_TX=(a << 8) | b;
	a=Single_Read(MPU6050_ADDRESS, 0x45);//YH陀螺仪
	b=Single_Read(MPU6050_ADDRESS, 0x46);//YL陀螺仪
        buf->MPU6050_TY=(a << 8) | b;
	a=Single_Read(MPU6050_ADDRESS, 0x47);//ZH陀螺仪
	b=Single_Read(MPU6050_ADDRESS, 0x48);//Z陀螺仪
        buf->MPU6050_TZ=(a << 8) | b;
}
/**************************实现函数********************************************
//将iic读取到得数据分拆,放入相应寄存器
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
	
	sensor.acc.origin.x = ((((int16_t)mpu6050_buffer[0]) << 8) | mpu6050_buffer[1]) - sensor.acc.quiet.x;   //原始值-静态值
	sensor.acc.origin.y = ((((int16_t)mpu6050_buffer[2]) << 8) | mpu6050_buffer[3]) - sensor.acc.quiet.y;
	sensor.acc.origin.z = ((((int16_t)mpu6050_buffer[4]) << 8) | mpu6050_buffer[5]);

	sensor.gyro.origin.x = ((((int16_t)mpu6050_buffer[8]) << 8) | mpu6050_buffer[9]);
	sensor.gyro.origin.y = ((((int16_t)mpu6050_buffer[10]) << 8)| mpu6050_buffer[11]);
	sensor.gyro.origin.z = ((((int16_t)mpu6050_buffer[12]) << 8)| mpu6050_buffer[13]);
  
	sensor.gyro.radian.x = sensor.gyro.origin.x * Gyro_Gr - sensor.gyro.quiet.x * Gyro_Gr;
	sensor.gyro.radian.y = sensor.gyro.origin.y * Gyro_Gr - sensor.gyro.quiet.y * Gyro_Gr;
	sensor.gyro.radian.z = sensor.gyro.origin.z * Gyro_Gr - sensor.gyro.quiet.z * Gyro_Gr;


////////////////////////////////////////////////////
//    	The calibration  of  gyro and  acc  (校准)//
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
					//EE_SAVE_ACC_OFFSET();//保存数据
					return;
				}
				cnt_a++;		
			}	
  }
	else ACC_OFFSET_OK = 1;
}
*/
/**************************实现函数********************************************
//陀螺仪零点校准
*******************************************************************************/

void Gyro_OFFEST(void)
{
   int cnt_g=2000;
   u8 mpu6050_buffer[14];

	 int32_t  tempgx=0,tempgy=0,tempgz=0;
	 sensor.gyro.averag.x=0;    //零点偏移清零
	 sensor.gyro.averag.y=0;  
	 sensor.gyro.averag.z=0;
	 while(cnt_g--)       //循环采集2000次   求平均
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



