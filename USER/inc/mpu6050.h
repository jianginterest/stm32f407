#ifndef __MPU6050_H_
#define __MPU6050_H_
#include<stdint.h>



//****************************************
// 定义MPU6050内部地址
//****************************************

#define	SMPLRT_DIV		0x19	//陀螺仪采样率，典型值：0x07(125Hz)
#define	cONFIG			0x1A	//低通滤波频率，典型值：0x06(5Hz)
#define	GYRO_CONFIG		0x1B	//陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
#define	ACCEL_CONFIG	0x1C	//加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)
#define	ACCEL_XOUT_H	0x3B
#define	ACCEL_XOUT_L	0x3C
#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40
#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42
#define	GYRO_XOUT_H		0x43
#define	GYRO_XOUT_L		0x44	
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48
#define	PWR_MGMT_1		0x6B	//电源管理，典型值：0x00(正常启用)
#define	WHO_AM_I		0x75	//IIC地址寄存器(默认数值0x68，只读)
#define MPU6050_ADDRESS 0xD0    //IIC写入时的地址字节数据，+1为读取
typedef struct{
        int16_t	MPU6050_JX;
        int16_t	MPU6050_JY;
        int16_t	MPU6050_JZ;
        
        int16_t	MPU6050_TX;
        int16_t	MPU6050_TY;
        int16_t	MPU6050_TZ;
			
}MPU6050_XYZ;	

typedef struct{
	float X;
	float Y;
	float Z;
}FLOAT_XYZ;

struct _float {
	float x;
	float y;
	float z;
};

struct _int16{
        int16_t x;
	int16_t y;
	int16_t z;
};		

struct _trans{
     	struct _int16 origin;  //原始值
	struct _int16 averag;  //平均值
	struct _int16 histor;  //历史值
	struct _int16 quiet;   //静态值
	struct _float radian;  //弧度值 
} ;

struct _sensor{   
	struct _trans acc;        //加速度计
	struct _trans gyro;       //陀螺仪
} ;

extern struct _sensor sensor;


void MPU6050_Init(void);

void MPU6050_Read(int16_t* buf);
void Read_MPU6050(MPU6050_XYZ* buf);	

void MPU6050_Dataanl(void);

void Gyro_OFFEST(void);



#define Gyro_G 	0.03051756	//  1/32768/1000      陀螺仪量程为 +—1000			
#define Gyro_Gr	0.0005327   //  1/32768/1000/57.3 

#endif // __MPU6050_H__
