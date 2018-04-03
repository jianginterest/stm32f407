#include<include.h>

void led_INIT(void)
{

  GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_13|GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;//上下拉电阻
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;//推挽
	GPIO_Init(GPIOC,&GPIO_InitStructure);

}
void led(void)
{
	//GPIO_SetBits(GPIOC,GPIO_Pin_13);
  GPIO_ResetBits(GPIOC,GPIO_Pin_13);
  GPIO_SetBits(GPIOC,GPIO_Pin_14);
	//GPIO_ResetBits(GPIOC,GPIO_Pin_14);
}

