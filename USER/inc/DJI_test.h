#ifndef _DJI_test_H_
#define _DJI_test_H_
#include <stdint.h>  //定义int8_t之类

void USART2_3_NVIC_Configuration(void);
void usart2_3_init(void);

void USART2_Send_data(uint8_t* str,uint8_t len);
#endif

