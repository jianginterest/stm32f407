#ifndef _DJI_test_H_
#define _DJI_test_H_
#include <stdint.h>  //����int8_t֮��

void USART2_3_NVIC_Configuration(void);
void usart2_3_init(void);

void USART2_Send_data(uint8_t* str,uint8_t len);
#endif

