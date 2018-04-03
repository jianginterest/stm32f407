
#ifndef _INCLUDE_H
#define _INCLUDE_H


#ifdef __cplusplus
 extern "C" {
#endif
	 
/**
 * @brief   底层库函数头文件
 * @param  	None
 * @retval	None
 */
#include <stm32f4xx.h>
#include <stdio.h>
#include <stdint.h>  //定义int8_t之类
#include <stdlib.h>
#include <string.h>
#include <sys.h>	 
#include <math.h>

/**
 * @brief   用户自定义头文件
 * @param  	None
 * @retval	None
 */
#include <led.h>
#include <USART.h>
#include <key.h>
#include <delay.h>
#include <exit.h>
#include <timer.h>
#include <DJI_test.h>

#include <NRF24L01.H>
#include <All_init.H>
#include <IIC.h>
#include <GPS.h>
#include <OLED.h>
#include <mpu6050.h>
#include <HMC5983.h>

#include <mode1.h>
#include <JY901B.h>
/**
 * @brief   全局变量
 * @param  	None
 * @retval	None
 */
 
extern uint8_t NRF_Channel;

extern uint8_t buf[5];

extern uint8_t read_buf[5];

extern char USART1_RX_BUF[600];

extern uint8_t m[][10];

extern uint8_t USART2_RX_BUF[5];


#ifdef __cplusplus
}
#endif	 

#endif
