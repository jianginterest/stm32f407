#include<include.h>

/*
此方法不能用
void delay(int count)
{
	int i;
for(i=0;i!=count;i++) ;
	
	if(count<0)
count=0;
}
*/

static u16  fac_ms=0;
static u16  fac_us=0;
/**
 * @brief   Systick延时功能初始化，默认选择72
 * @param  	None
 * @retval	None
 */
void Delay_init(void){
	SysTick->CTRL&=0xfffffffb;
	fac_us=72/8;		    
	fac_ms=(u16)fac_us*1000;
}	

/**
 * @brief   Systick延时功能，延时单位ms
 * @param  	需要延时的时间，最大值1864
 * @retval	None
 */
void Delay_ms(u16 nms){	 		  	  
	u32 temp;	
	if(nms>1800) nms=1800;	
	SysTick->LOAD=(u32)nms*fac_ms;
	SysTick->VAL =0x00;           
	SysTick->CTRL=0x01 ;           
	do{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));   
	SysTick->CTRL=0x00;       
	SysTick->VAL =0X00;         	    
} 
//nus为要延时的us数.	
//注意:nus的值,不要大于798915us
void delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; //时间加载	  		 
	SysTick->VAL=0x00;        //清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;//开始倒数 
	do
	{
		temp=SysTick->CTRL;
	}
	while((temp&0x01)&&!(temp&(1<<16)));//等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //关闭计数器
	SysTick->VAL =0X00;       //清空计数器	 
}

