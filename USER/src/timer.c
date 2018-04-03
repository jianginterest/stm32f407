#include<include.h>

//TIM1 PWM部分初始化 
//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
void TIM1_PWM_Init(uint32_t arr,uint32_t psc)
{     
	  //此部分需手动修改IO口设置
    GPIO_InitTypeDef  GPIO_InitStructure;	
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
     
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);    //TIM1时钟使能  
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);   //使能PORTA时钟
	
	  GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4);  //GPIOA8复用为定时器1
	
     
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;  //GPIOA8/A7
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;       //复用功能
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;     //推挽复用输出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;   //不上下拉
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; //速度100MHz
    GPIO_Init(GPIOD,&GPIO_InitStructure);              //初始化PA8
     
	  TIM_TimeBaseStructure.TIM_Prescaler = psc;             //Timer clock = sysclock /(TIM_Prescaler+1) = 168M 定时器分频
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;    //向上计数模式
	  TIM_TimeBaseStructure.TIM_Period = arr;                        //自动重装载值
	  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;        
    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);          //初始化定时器1
		
 	  //初始化TIM1 Channel1 PWM模式	
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;     //选择定时器模式:TIM脉冲宽度调制模式2
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;  //比较输出使能
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;    //互补输出允许
    TIM_OCInitStructure.TIM_Pulse = (arr+1)/2;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //High为占空比高极性，此时占空比为50%，Low则为反极性，占空比为50%
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;  //互补输出，与以上相反
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
 
    TIM_OC1Init(TIM4,&TIM_OCInitStructure);   //根据T指定的参数初始化外设TIM1OC1
 	  TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //使能TIM1在CCR1上的预装载寄存器（CR自动装载默认是打开的）
    TIM_ARRPreloadConfig(TIM4,ENABLE);//ARPE使能(ARR自动装载默认是打开的，可以不设置)
    TIM_Cmd(TIM4,ENABLE);
    TIM_CtrlPWMOutputs(TIM4,ENABLE); //使能TIM1的PWM输出
                               
}



