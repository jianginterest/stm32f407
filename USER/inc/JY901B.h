#ifndef JY901B_H
#define	JY901B_H

#ifdef __cplusplus
extern "C"{
#endif
	
#include "include.h"
	
#define JY901B_SlaveAddress 0XA0

void JY901B_Getdata(void);
extern  float Angle[3];
extern	float Angle_speed[3];
extern	float h[3];
extern	float w[3];
extern	float	A[3];
extern	float	JSD[3];	
extern	float	c[3];		
extern	unsigned char data[40];	
extern float QY[3];	
extern float Air_Pressure;	

#endif
