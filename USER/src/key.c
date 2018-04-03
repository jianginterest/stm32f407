#include<include.h>

void key_init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;//上下拉电阻
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}


int key_scan(void)
{
 static char key_flag=0;
	if(KEY0==0)
	{
	  Delay_ms(5000);
		if(KEY0==0)
		key_flag=1;
		if(KEY0==1&&key_flag==1)
		{
			key_flag=0;
			return 1;
		}
	}
	return 0;
}
void key_test(void)
{
	if(key_scan()==1)
	{
	GPIO_WriteBit(GPIOD,GPIO_Pin_13,(BitAction)(1-(GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_13))));
	GPIO_WriteBit(GPIOD,GPIO_Pin_14,(BitAction)(1-(GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_14))));
}
}
