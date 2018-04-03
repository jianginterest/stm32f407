
#ifndef _INCLUDE_H
#define _INCLUDE_H


#ifdef __cplusplus
 extern "C" {
#endif
	 
/**
 * @brief   �ײ�⺯��ͷ�ļ�
 * @param  	None
 * @retval	None
 */
#include <stm32f4xx.h>
#include <stdio.h>
#include <stdint.h>  //����int8_t֮��
#include <stdlib.h>
#include <string.h>
#include <sys.h>	 
#include <math.h>

/**
 * @brief   �û��Զ���ͷ�ļ�
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
 * @brief   ȫ�ֱ���
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
