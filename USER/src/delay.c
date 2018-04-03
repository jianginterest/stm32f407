#include<include.h>

/*
�˷���������
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
 * @brief   Systick��ʱ���ܳ�ʼ����Ĭ��ѡ��72
 * @param  	None
 * @retval	None
 */
void Delay_init(void){
	SysTick->CTRL&=0xfffffffb;
	fac_us=72/8;		    
	fac_ms=(u16)fac_us*1000;
}	

/**
 * @brief   Systick��ʱ���ܣ���ʱ��λms
 * @param  	��Ҫ��ʱ��ʱ�䣬���ֵ1864
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
//nusΪҪ��ʱ��us��.	
//ע��:nus��ֵ,��Ҫ����798915us
void delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; //ʱ�����	  		 
	SysTick->VAL=0x00;        //��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;//��ʼ���� 
	do
	{
		temp=SysTick->CTRL;
	}
	while((temp&0x01)&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;       //�رռ�����
	SysTick->VAL =0X00;       //��ռ�����	 
}

