#ifndef _HMC5983_H
#define _HMC5983_H

#include <stdint.h>  

#define	HMC5883L_ADDRESS   0x3C	  //定义器件在IIC总线中的从地址
struct _HMC_XYZ{
        int16_t	HMC5883_X;
        int16_t	HMC5883_Y;
        int16_t	HMC5883_Z;
			
};	
extern struct _HMC_XYZ  HMC_XYZ;
uint8_t Init_HMC5883L(void);

uint16_t Multiple_Read_HMC5883L(void);
#endif

