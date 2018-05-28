#ifndef _DJI_test_H_
#define _DJI_test_H_
#include <stdint.h>  //定义int8_t之类

void USART2_3_NVIC_Configuration(void);
void usart2_3_init(void);
void USART_Send_single(uint8_t usart,uint8_t date);
void USART_Send_number_5(int16_t number);
void USART_Send_number_3(int16_t number);
void USART2_Send_data(uint8_t* str,uint8_t len);
#endif

