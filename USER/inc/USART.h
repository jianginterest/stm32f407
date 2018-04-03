#ifndef _USART_H_
#define _USART_H_
#include<include.h>

#define UART_PORT					USART2

void usart_init(void);
void USART_NVIC_Configuration(void);
void drv_uart_tx_bytes( uint8_t* TxBuffer, uint8_t Length );

#endif

