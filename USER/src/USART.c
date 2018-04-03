#include<include.h>



/*******************************************************************************
* Function Name  : void USART_NVIC_Configuration(void)
* Description    : ���ڽ�����Ҫ�жϣ����Ͳ���
****************************************************************************** */
void USART_NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0; 
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}


/*******************************************************************************
* Function Name  : void usart_init(void)
* Description    : stm32F4-discovery����1��PA9��PA10������
  ����Ϊ����ΪUSB-OTG����������Ӱ���˲��Σ����õ�PB6��PB7��
****************************************************************************** */
void usart_init(void)  
{
 GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
  GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_USART1); //��F1ϵ�в�ͬ
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource7,GPIO_AF_USART1); 
	
  USART_InitTypeDef USART_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
	
  USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	
  USART_Init(USART1, &USART_InitStructure); 
	
	USART_ClearFlag(USART1, USART_FLAG_TC);//���жϱ�־λ
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//ʹ���ж�

  USART_Cmd(USART1, ENABLE);  
	USART_NVIC_Configuration();

}

/*******************************************************************************
* Function Name  : void drv_uart_tx_bytes( uint8_t* TxBuffer, uint8_t Length )
* Description    : 
****************************************************************************** */
void drv_uart_tx_bytes( uint8_t* TxBuffer, uint8_t Length )
{
	while( Length-- )
	{
		while( RESET == USART_GetFlagStatus( UART_PORT, USART_FLAG_TXE ));
		UART_PORT->DR = *TxBuffer;
		TxBuffer++;
	}
}
/*
 * ��������fputc
 * ����  ���ض���c�⺯��printf��USART1
 * ����  ����
 * ���  ����
 * ����  ����printf����
 */
#if 1
#pragma import(__use_no_semihosting)                              
struct __FILE 
{ 
	int handle; 
}; 
FILE __stdout;         
void _sys_exit(int x) 
{ 
	x = x; 
} 
int fputc(int ch, FILE *f)
{
  	USART_SendData(USART3, (u8) ch);
  	while (USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET);
  	return ch;
}
#endif


