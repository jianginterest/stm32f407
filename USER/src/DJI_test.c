#include<include.h>

void USART2_3_NVIC_Configuration(void)//���ڽ�����Ҫ�жϣ����Ͳ���
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitStructure.NVIC_IRQChannel=USART2_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1; 
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel=USART3_IRQn; 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0; 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0; 
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

void usart2_3_init(void) 
{
 GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
  GPIO_PinAFConfig(GPIOB,GPIO_PinSource10,GPIO_AF_USART3); //��F1ϵ�в�ͬ
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource11,GPIO_AF_USART3); 
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_2|GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
  GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2); 
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_USART2); 
	
  USART_InitTypeDef USART_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	
  USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	
  USART_Init(USART2, &USART_InitStructure); 
	
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	
  USART_Init(USART3, &USART_InitStructure); 
	
	
	USART_ClearFlag(USART2, USART_FLAG_TC);//���жϱ�־λ
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//ʹ���ж�
	
	USART_ClearFlag(USART3, USART_FLAG_TC);//���жϱ�־λ
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);//ʹ���ж�

  USART_Cmd(USART2, ENABLE);  
	USART_Cmd(USART3, ENABLE);  
	USART2_3_NVIC_Configuration();

}
/*******************************************************************************
* Function Name  : void USART1_Send_data(uint8_t* str,uint8_t len)
* Description    : ���ڷ����ַ���
* Input          : str�ַ���ָ�� len����
* Output         : None
* Return         : None
*******************************************************************************/
void USART2_Send_data(uint8_t* str,uint8_t len)
{
		unsigned char i;
    for(i=0;i<len;i++)
    {
        USART_SendData(USART2,*str);
        while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
        str++;
    }
	}

	
	
/*******************************************************************************
* Function Name  : void USART_Send_single(uint8_t usart,uint8_t date)
* Description    : 
* Input          : str�ַ���ָ�� len����
* Output         : None
* Return         : None
*******************************************************************************/
void USART_Send_single(uint8_t usart,uint8_t date)//�ַ�
{if(usart==1)
{USART_SendData(USART1,date);
while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);}//TXE?

 else if(usart==2)
 {USART_SendData(USART2,date);
 while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);}

 else if(usart==3)
 {USART_SendData(USART3,date);
 while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);}

 else if(usart==4)
 {USART_SendData(UART4,date);
 while(USART_GetFlagStatus(UART4, USART_FLAG_TXE) == RESET);}
}

/*******************************************************************************
* Function Name  : void USART_Send_number(unsigned int number)
* Description    : ���ڷ���num
* Input          : str�ַ���ָ�� len����
* Output         : None
* Return         : None
*******************************************************************************/
void USART_Send_number_5(int16_t number)
{
//if((number&0x80000)==0x80000)
//USART_Send_single(2,'-');
//else
//USART_Send_single(2,'+');

//number&=0x7ffff;
		if(number<0)
	{
		USART_Send_single(2,'-');
		number*=-1;
	}
	else
		USART_Send_single(2,'+');
 int W,S,B,Q,G,SW;
SW=number/100000+0x30;
W=number%100000/10000+0x30;
S=number%10000/1000+0x30;
B=number%1000/100+0x30;
Q=number%100/10+0x30;
G=number%10+0x30;
USART_SendData(USART2,SW);
while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);
USART_SendData(USART2,W);
while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);
USART_SendData(USART2,S);
while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);
USART_SendData(USART2,B);
while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);
USART_SendData(USART2,Q);
while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);
USART_SendData(USART2,G);
while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);
}


void USART_Send_number_3(int16_t number)
{
		 int B,Q,G;
	if(number<0)
	{
		USART_Send_single(2,'-');
		number*=-1;
	}
	else
		USART_Send_single(2,'+');
	

	B=number/100+0x30;
	Q=number%100/10+0x30;
	G=number%10+0x30;

	USART_SendData(USART2,B);
	 while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);
	USART_SendData(USART2,Q);
	 while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);
	USART_SendData(USART2,G);
	 while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);
}
