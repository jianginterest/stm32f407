/**
  ******************************************************************************
  * @file    STM32F4xx_Low_Power_Application_Case/src/stm32f4xx_it.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    17-January-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.  
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
#include<include.h>

/** @addtogroup STM32F4xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup I2C_DataExchangeDMA
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint8_t Counter = 0x00;
extern __IO uint8_t DMA_TC;
extern __IO uint32_t TimeOut;
extern __IO uint8_t DMAItStatus;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
 
}

/*********************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                      */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the     */
/*  available peripheral interrupt handler's name please refer to the startup    */
/*  file (startup_stm32f40xx.s/startup_stm32f401xx.s/startup_stm32f429_439xx.s). */
/*********************************************************************************/

/**
  * @brief  This function handles DMA2_Stream0 interrupt request.
  * @param  None
  * @retval None
  */
void DMA2_Stream0_IRQHandler(void)
{
 
}

 /**
   * @brief  This function handles DMA1_Stream0 interrupt request.
   * @param  None
   * @retval None
   */
void DMA1_Stream0_IRQHandler(void)
{
 
}
 
 /**
   * @brief  This function handles DMA1_Stream6 interrupt request.
   * @param  None
   * @retval None
   */
void DMA1_Stream6_IRQHandler(void)
{
 
}

/**
  * @brief  This function handles RTC Auto wake-up interrupt request.
  * @param  None
  * @retval None
  */
void RTC_WKUP_IRQHandler(void)
{
 
}
/**
  * @}
  */ 

/**
  * @}
  */



void EXTI0_IRQHandler (void)
{
    Delay_ms(5000);	
  	if(EXTI_GetITStatus(EXTI_Line0) != RESET)	  
	{	  
	GPIO_WriteBit(GPIOD,GPIO_Pin_12,(BitAction)(1-(GPIO_ReadOutputDataBit(GPIOD,GPIO_Pin_12))));
	GPIO_WriteBit(GPIOD,GPIO_Pin_13,(BitAction)(1-(GPIO_ReadOutputDataBit(GPIOD,GPIO_Pin_13))));
	GPIO_WriteBit(GPIOD,GPIO_Pin_14,(BitAction)(1-(GPIO_ReadOutputDataBit(GPIOD,GPIO_Pin_14))));
	GPIO_WriteBit(GPIOD,GPIO_Pin_15,(BitAction)(1-(GPIO_ReadOutputDataBit(GPIOD,GPIO_Pin_15))));
}
	EXTI_ClearITPendingBit(EXTI_Line0);  
}	

/**
  * @brief  �ô���1����GPS��Ϣ
  * @param  None
  * @retval None
  */
uint16_t USART1_RX_STA=0;
char USART1_RX_BUF[600]={0};
uint8_t res;
void USART1_IRQHandler(void)
{
	//uint8_t res;
if (USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) //���յ�����
		{
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		res=USART_ReceiveData(USART1);
		//USART1_RX_BUF[1]=USART_ReceiveData(USART1);
			GPIO_WriteBit(GPIOD,GPIO_Pin_14,(BitAction)(1-(GPIO_ReadOutputDataBit(GPIOD,GPIO_Pin_14))));
			if((	USART1_RX_STA&(1<<15))==0)//�������һ������,��û�б�����,���ٽ�����������
			{
			 if(USART1_RX_STA<600)   //�����Խ�������  USART3_MAX_RECV_LEN = 600    �����ջ����ֽ���
            {
               // TIM_SetCounter(TIM7,0);//���������                         
               // if(USART1_RX_STA==0)                //ʹ�ܶ�ʱ��7���ж� 
                //{
                //    TIM_Cmd(TIM7,ENABLE);//ʹ�ܶ�ʱ��7
                //}
                USART1_RX_BUF[USART1_RX_STA++]=res; //��¼���յ���ֵ    
            }else 
            {
                //USART1_RX_STA|=1<<15;               //ǿ�Ʊ�ǽ������
							USART1_RX_STA=0;
            } 

			}
			
		USART_ClearFlag(USART1,USART_FLAG_TC);
		}
	}

	
/**
 * @brief  �ô���2���ͺͽ���web����Ӧ��ģʽ2��
 * @param  None
 * @retval ������յ���Ӧ��������һ����γ����Ϣ
 */
	
uint8_t USART2_RX_BUF[5];
void USART2_IRQHandler(void)
{
if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) 
		{
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
		USART_ClearFlag(USART2,USART_FLAG_TC);
   
		USART2_RX_BUF[0]=USART_ReceiveData(USART2);
			
			if(USART2_RX_BUF[0]=='A')
			{
		   GPIO_WriteBit(GPIOD,GPIO_Pin_15,(BitAction)(1-(GPIO_ReadOutputDataBit(GPIOD,GPIO_Pin_15))));
			USART2_Send_data(m[1],10);
			USART2_RX_BUF[0]=0;
			}
	//	USART_SendData(USART2,USART_ReceiveData(USART2));
		}

}
/**
 * @brief ����3��ģʽһ��
 * @param  None
 * @retval ��ͬ����ľ�γ��
 */

void USART3_IRQHandler(void)
{

if (USART_GetITStatus(USART3, USART_IT_RXNE) != RESET) 
		{
		USART_ClearITPendingBit(USART3, USART_IT_RXNE);
		USART_ClearFlag(USART3,USART_FLAG_TC);
			
   	
	  GPIO_WriteBit(GPIOC,GPIO_Pin_14,(BitAction)(1-(GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_14))));
			
			
	 
		USART_SendData(USART3,USART_ReceiveData(USART3));
			
			
		}


}




/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
