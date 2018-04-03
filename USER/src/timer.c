#include<include.h>

//TIM1 PWM���ֳ�ʼ�� 
//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM1_PWM_Init(uint32_t arr,uint32_t psc)
{     
	  //�˲������ֶ��޸�IO������
    GPIO_InitTypeDef  GPIO_InitStructure;	
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
     
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);    //TIM1ʱ��ʹ��  
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);   //ʹ��PORTAʱ��
	
	  GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4);  //GPIOA8����Ϊ��ʱ��1
	
     
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;  //GPIOA8/A7
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;       //���ù���
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     //���츴�����
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   //��������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //�ٶ�100MHz
    GPIO_Init(GPIOD,&GPIO_InitStructure);              //��ʼ��PA8
     
	  TIM_TimeBaseStructure.TIM_Prescaler = psc;             //Timer clock = sysclock /(TIM_Prescaler+1) = 168M ��ʱ����Ƶ
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;    //���ϼ���ģʽ
	  TIM_TimeBaseStructure.TIM_Period = arr;                        //�Զ���װ��ֵ
	  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;        
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);          //��ʼ����ʱ��1
		
 	  //��ʼ��TIM1 Channel1 PWMģʽ	
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;     //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  //�Ƚ����ʹ��
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;    //�����������
    TIM_OCInitStructure.TIM_Pulse = (arr+1)/2;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //HighΪռ�ձȸ߼��ԣ���ʱռ�ձ�Ϊ50%��Low��Ϊ�����ԣ�ռ�ձ�Ϊ50%
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;  //����������������෴
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
 
    TIM_OC1Init(TIM4,&TIM_OCInitStructure);   //����Tָ���Ĳ�����ʼ������TIM1OC1
 	  TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM1��CCR1�ϵ�Ԥװ�ؼĴ�����CR�Զ�װ��Ĭ���Ǵ򿪵ģ�
    TIM_ARRPreloadConfig(TIM4,ENABLE);//ARPEʹ��(ARR�Զ�װ��Ĭ���Ǵ򿪵ģ����Բ�����)
    TIM_Cmd(TIM4,ENABLE);
    TIM_CtrlPWMOutputs(TIM4,ENABLE); //ʹ��TIM1��PWM���
                               
}



