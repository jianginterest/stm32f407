#include<include.h>

//TIM4 PWM���ֳ�ʼ�� 
//PWM�����ʼ�� 6·
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
void TIM4_PWM_Init(uint32_t psc)
{     
	  //�˲������ֶ��޸�IO������
    GPIO_InitTypeDef  GPIO_InitStructure;	
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
     
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);    //TIM4ʱ��ʹ��  
	
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);   //ʹ��PORTDʱ��
	
	
	
     
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;  //PD12 TIM4 ch1
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;       //���ù���
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     //���츴�����
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   //��������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //�ٶ�100MHz
	
    GPIO_Init(GPIOD,&GPIO_InitStructure);              //��ʼ��PD
	
	  GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4);  //GPIOA12����Ϊ��ʱ��4  ������
	  GPIO_PinAFConfig(GPIOD,GPIO_PinSource13,GPIO_AF_TIM4);  //GPIOA12����Ϊ��ʱ��4  ������
	  GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_TIM4);  //GPIOA12����Ϊ��ʱ��4  ������
		GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_TIM4);  //GPIOA12����Ϊ��ʱ��4  ������
	
     
	  TIM_TimeBaseStructure.TIM_Prescaler = psc;            //�˲���ΪԤ��Ƶ  Timer clock = sysclock /(TIM_Prescaler+1) = 168M ��ʱ����Ƶ
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;    //���ϼ���ģʽ
	  TIM_TimeBaseStructure.TIM_Period = 99;                        //�Զ���װ��ֵ��ÿ�����ڼ���ֵ����Ϊ��0��ʼ�����Լ�������Ϊ�����ֵ-1��
	  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;        
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;                //ֻ��TIM1��TIM8��Ч��F4�������ܣ���˼Ϊÿ��TIM_RepetitionCounter+1�����ڲ���һ���ж�
    TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);          //��ʼ����ʱ��1
		
 	  //��ʼ��TIM1 Channel1 PWMģʽ	
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;     //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  //�Ƚ����ʹ��
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;    //�����������
    TIM_OCInitStructure.TIM_Pulse = 7;                      //ռ�ձȣ����������ֵ��pwm��ת ��(arr+1)/2��
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //HighΪռ�ձȸ߼��ԣ���ʱռ�ձ�Ϊ50%��Low��Ϊ�����ԣ�ռ�ձ�Ϊ50%
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;  //����������������෴(TIM_OCNPolarity_Low���ͬ�࣬TIM_OCNPolarity_Highʱ�������)
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
 
 
 
    TIM_OC1Init(TIM4,&TIM_OCInitStructure);   //����Tָ���Ĳ�����ʼ������TIM1OC1
 	  TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM1��CCR1�ϵ�Ԥװ�ؼĴ�����CR�Զ�װ��Ĭ���Ǵ򿪵ģ�
    TIM_ARRPreloadConfig(TIM4,ENABLE);//ARPEʹ��(ARR�Զ�װ��Ĭ���Ǵ򿪵ģ����Բ�����)
		
		
		TIM_OC2Init(TIM4,&TIM_OCInitStructure);   //����Tָ���Ĳ�����ʼ������TIM1OC1
 	  TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM1��CCR1�ϵ�Ԥװ�ؼĴ�����CR�Զ�װ��Ĭ���Ǵ򿪵ģ�
    TIM_ARRPreloadConfig(TIM4,ENABLE);//ARPEʹ��(ARR�Զ�װ��Ĭ���Ǵ򿪵ģ����Բ�����)
		
		TIM_OC3Init(TIM4,&TIM_OCInitStructure);   //����Tָ���Ĳ�����ʼ������TIM1OC1
 	  TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM1��CCR1�ϵ�Ԥװ�ؼĴ�����CR�Զ�װ��Ĭ���Ǵ򿪵ģ�
    TIM_ARRPreloadConfig(TIM4,ENABLE);//ARPEʹ��(ARR�Զ�װ��Ĭ���Ǵ򿪵ģ����Բ�����)
		
		TIM_OC4Init(TIM4,&TIM_OCInitStructure);   //����Tָ���Ĳ�����ʼ������TIM1OC1
 	  TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM1��CCR1�ϵ�Ԥװ�ؼĴ�����CR�Զ�װ��Ĭ���Ǵ򿪵ģ�
    TIM_ARRPreloadConfig(TIM4,ENABLE);//ARPEʹ��(ARR�Զ�װ��Ĭ���Ǵ򿪵ģ����Բ�����)
		
		
    TIM_Cmd(TIM4,ENABLE);
		
    TIM_CtrlPWMOutputs(TIM4,ENABLE); //ʹ��TIM1��PWM���
                               
}


void TIM2_PWM_Init(uint32_t psc)
{
    GPIO_InitTypeDef  GPIO_InitStructure;	
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
     
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);    //TIM4ʱ��ʹ��  
	
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);   //ʹ��PORTDʱ��
	
	
	
     
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3;  //PD12 TIM4 ch1
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;       //���ù���
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     //���츴�����
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   //��������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //�ٶ�100MHz
	
    GPIO_Init(GPIOA,&GPIO_InitStructure);              //��ʼ��PD
	
	  GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_TIM2);  //GPIOA12����Ϊ��ʱ��2  3CHL SWC
	  GPIO_PinAFConfig(GPIOA,GPIO_PinSource3,GPIO_AF_TIM2);  //GPIOA12����Ϊ��ʱ��2  4CHL VRB
		
		
	    
	  TIM_TimeBaseStructure.TIM_Prescaler = psc;            //�˲���ΪԤ��Ƶ  Timer clock = sysclock /(TIM_Prescaler+1) = 168M ��ʱ����Ƶ
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;    //���ϼ���ģʽ
	  TIM_TimeBaseStructure.TIM_Period = 99;                        //�Զ���װ��ֵ��ÿ�����ڼ���ֵ����Ϊ��0��ʼ�����Լ�������Ϊ�����ֵ-1��
	  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;        
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;                //ֻ��TIM1��TIM8��Ч��F4�������ܣ���˼Ϊÿ��TIM_RepetitionCounter+1�����ڲ���һ���ж�
    TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);          //��ʼ����ʱ��1
		
 	  //��ʼ��TIM1 Channel1 PWMģʽ	
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;     //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  //�Ƚ����ʹ��
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;    //�����������
    TIM_OCInitStructure.TIM_Pulse = 5;                      //ռ�ձȣ����������ֵ��pwm��ת ��(arr+1)/2��
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //HighΪռ�ձȸ߼��ԣ���ʱռ�ձ�Ϊ50%��Low��Ϊ�����ԣ�ռ�ձ�Ϊ50%
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;  //����������������෴(TIM_OCNPolarity_Low���ͬ�࣬TIM_OCNPolarity_Highʱ�������)
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
 
 
 
    TIM_OC3Init(TIM2,&TIM_OCInitStructure);   //����Tָ���Ĳ�����ʼ������TIM1OC1
 	  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);  //ʹ��TIM1��CCR1�ϵ�Ԥװ�ؼĴ�����CR�Զ�װ��Ĭ���Ǵ򿪵ģ�
    TIM_ARRPreloadConfig(TIM2,ENABLE);//ARPEʹ��(ARR�Զ�װ��Ĭ���Ǵ򿪵ģ����Բ�����)
		
		
		TIM_OC4Init(TIM2,&TIM_OCInitStructure);   //����Tָ���Ĳ�����ʼ������TIM1OC1
 	  TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);  //ʹ��TIM1��CCR1�ϵ�Ԥװ�ؼĴ�����CR�Զ�װ��Ĭ���Ǵ򿪵ģ�
    TIM_ARRPreloadConfig(TIM2,ENABLE);//ARPEʹ��(ARR�Զ�װ��Ĭ���Ǵ򿪵ģ����Բ�����)
		
		
    TIM_Cmd(TIM2,ENABLE);
		
    TIM_CtrlPWMOutputs(TIM2,ENABLE); //ʹ��TIM1��PWM���	
	 


}

void Start(void)
{

 TIM_SetCompare3(TIM4,5);//���� 5
 TIM_SetCompare4(TIM4,10); //�� ��10
 TIM_SetCompare1(TIM4,5);
 TIM_SetCompare2(TIM4,10); 
	

}



