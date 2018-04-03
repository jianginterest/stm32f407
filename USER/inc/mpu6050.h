#ifndef __MPU6050_H_
#define __MPU6050_H_
#include<stdint.h>



//****************************************
// ����MPU6050�ڲ���ַ
//****************************************

#define	SMPLRT_DIV		0x19	//�����ǲ����ʣ�����ֵ��0x07(125Hz)
#define	cONFIG			0x1A	//��ͨ�˲�Ƶ�ʣ�����ֵ��0x06(5Hz)
#define	GYRO_CONFIG		0x1B	//�������Լ켰������Χ������ֵ��0x18(���Լ죬2000deg/s)
#define	ACCEL_CONFIG	0x1C	//���ټ��Լ졢������Χ����ͨ�˲�Ƶ�ʣ�����ֵ��0x01(���Լ죬2G��5Hz)
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
#define	PWR_MGMT_1		0x6B	//��Դ��������ֵ��0x00(��������)
#define	WHO_AM_I		0x75	//IIC��ַ�Ĵ���(Ĭ����ֵ0x68��ֻ��)
#define MPU6050_ADDRESS 0xD0    //IICд��ʱ�ĵ�ַ�ֽ����ݣ�+1Ϊ��ȡ
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
     	struct _int16 origin;  //ԭʼֵ
	struct _int16 averag;  //ƽ��ֵ
	struct _int16 histor;  //��ʷֵ
	struct _int16 quiet;   //��ֵ̬
	struct _float radian;  //����ֵ 
} ;

struct _sensor{   
	struct _trans acc;        //���ٶȼ�
	struct _trans gyro;       //������
} ;

extern struct _sensor sensor;


void MPU6050_Init(void);

void MPU6050_Read(int16_t* buf);
void Read_MPU6050(MPU6050_XYZ* buf);	

void MPU6050_Dataanl(void);

void Gyro_OFFEST(void);



#define Gyro_G 	0.03051756	//  1/32768/1000      ����������Ϊ +��1000			
#define Gyro_Gr	0.0005327   //  1/32768/1000/57.3 

#endif // __MPU6050_H__
