#ifndef JY901B_H
#define	JY901B_H

#ifdef __cplusplus
extern "C"{
#endif
	
#include "include.h"
	
#define JY901B_SlaveAddress 0X50

void JY901B_Getdata(void);
extern  float Angle[3];
extern	float Angle_speed[3];

#endif
