/**
  ******************************************************************************
  * @file       NRF24L01.c
  * @author  	Qin xingpeng
  * @version 	V1.0
  * @date     	2017年9月27日09:29:44
  * @brief      NRF功能实现
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */


#include "include.h"

/**
 * @brief   发送地址，接收地址，数据缓存区域
			初始化完成PA15输出低电平
 * @param  	None
 * @retval	None
 */	 
uint8_t TX_ADDRESS[5]={0x11,0x22,0x33,0x44,0x55}; //发送地址
uint8_t RX_ADDRESS[5]={0x55,0x44,0x33,0x22,0x11}; //接收地址


uint8_t  NRF_Buff[TX_PLOAD_WIDTH]={32,'0'};




/**
 * @brief   用于NRF延时
 * @param  	None
 * @retval	None
 */	
void Delay(vu32 nCount){
	for(; nCount != 0; nCount--);
}


/**
 * @brief   模拟SPI读写数据函数
 * @param  	写入的数据
 * @retval	对应时刻总线返回的数据
 */
u8 SPI_ReadWriteByte(u8 TxData){		
	u16 bit_ctr;
   	for(bit_ctr=0;bit_ctr<8;bit_ctr++) {
		if(TxData & 0x80)
		MOSI_H;         
		else
		MOSI_L;
		TxData = (TxData << 1);           
		SCK_H; 
		Delay(0xff);
		if(READ_MISO)                     
		TxData |= 0x01;       		  
		SCK_L; 
		Delay(0xff);           		 
   	}
    return(TxData);           		  		    
}

	 	 

/**
 * @brief   模拟SPI写寄存器
 * @param  	寄存器地址，写入的数据
 * @retval	写入的到的数据
 */	
u8 NRF24L01_Write_Reg(u8 reg_addr,u8 data){
	u8 status;	
    CSN_L;                   
  	status =SPI_ReadWriteByte(reg_addr); 
  	SPI_ReadWriteByte(data);            
  	CSN_H;                   	   
  	return(status);       		        
}

/**
 * @brief   模拟SPI读寄存器值
 * @param  	寄存器地址
 * @retval	收到的数据
 */	
u8 NRF24L01_Read_Reg(u8 reg_addr){
	u8 reg_val;	    
 	CSN_L;                	
  	SPI_ReadWriteByte(reg_addr);     
  	reg_val=SPI_ReadWriteByte(0);

  	CSN_H;                    
  	return(reg_val);                
}	

/**
 * @brief   在指定位置读出指定长度的数据
 * @param  	寄存器地址，存储地址，数据长度
 * @retval	收到的数据
 */	
u8 NRF24L01_Read_Buf(u8 reg_addr,u8 *pBuf,u8 data_len){
	u8 status,i;	       
  	CSN_L;                     
  	status=SPI_ReadWriteByte(reg_addr);      
 	for(i=0;i<data_len;i++)
		pBuf[i]=SPI_ReadWriteByte(0);

  	CSN_H;                     
  	return status;                       
}

/**
 * @brief   在指定位置写指定长度的数据
 * @param  	寄存器地址，写入的数据，数据长度
 * @retval	收到的数据
 */	
u8 NRF24L01_Write_Buf(u8 reg_addr, u8 *pBuf, u8 data_len){
	u8 status,i;	    
 	CSN_L;                                    
  	status = SPI_ReadWriteByte(reg_addr);                
  	for(i=0; i<data_len; i++)
		SPI_ReadWriteByte(*pBuf++);  
  	CSN_H;                                    
  	return status;                                       
}	

/**
 * @brief   发送数据
 * @param   需要发送的数据缓存
 * @retval	是否成功
 */
u8 NRF24L01_TxPacket(u8 *tx_buf){
	u8 state;   
	CE_L;
  	NRF24L01_Write_Buf(WR_TX_PLOAD,tx_buf,TX_PLOAD_WIDTH);
 	CE_H;                                   	   
	while(READ_IRQ != 0);                         
	state=NRF24L01_Read_Reg(STATUS);                       
	NRF24L01_Write_Reg(SPI_WRITE_REG+STATUS,state);     
	if(state&MAX_TX){
		NRF24L01_Write_Reg(FLUSH_TX,0xff);               
		return MAX_TX; 
	}
	if(state&TX_OK){
		return TX_OK;
	}
	return 0xff;                                        
}

/**
 * @brief   接收数据
 * @param   存储的位置
 * @retval	是否成功
 */
u8 NRF24L01_RxPacket(u8 *rx_buf)
{
	u8 state;		    							      
	state=NRF24L01_Read_Reg(STATUS);                	 
	NRF24L01_Write_Reg(SPI_WRITE_REG+STATUS,state); 
	if(state&RX_OK)                               {
		NRF24L01_Read_Buf(RD_RX_PLOAD,rx_buf,RX_PLOAD_WIDTH);
		NRF24L01_Write_Reg(FLUSH_RX,0xff);          
		return 0; 
	}	   
	return 1;                            
}

/**
 * @brief   使NRF进入收数据模式
 * @param   None
 * @retval	None
 */	   
void NRF_RX_Mode(void){
	CE_L;	  
  	NRF24L01_Write_Buf(SPI_WRITE_REG+RX_ADDR_P0,(uint8_t*)RX_ADDRESS,RX_ADR_WIDTH);  
  	NRF24L01_Write_Reg(SPI_WRITE_REG+EN_AA,0x01);    	 
  	NRF24L01_Write_Reg(SPI_WRITE_REG+EN_RXADDR,0x01);	  
  	NRF24L01_Write_Reg(SPI_WRITE_REG+RF_CH,NRF_Channel);	       
  	NRF24L01_Write_Reg(SPI_WRITE_REG+RX_PW_P0,RX_PLOAD_WIDTH);
  	NRF24L01_Write_Reg(SPI_WRITE_REG+RF_SETUP,0x0f);
  	NRF24L01_Write_Reg(SPI_WRITE_REG+CONFIG, 0x0f); 
  	CE_H;                                
}			

/**
 * @brief   使NRF进入发数据模式
 * @param   None
 * @retval	None
 */	  
void NRF_TX_Mode(void){														 
	CE_L;	    
  	NRF24L01_Write_Buf(SPI_WRITE_REG+TX_ADDR,(uint8_t*)TX_ADDRESS,TX_ADR_WIDTH);     
  	NRF24L01_Write_Buf(SPI_WRITE_REG+RX_ADDR_P0,(uint8_t*)RX_ADDRESS,RX_ADR_WIDTH); 
  	NRF24L01_Write_Reg(SPI_WRITE_REG+EN_AA,0x01);     
  	NRF24L01_Write_Reg(SPI_WRITE_REG+EN_RXADDR,0x01); 
  	NRF24L01_Write_Reg(SPI_WRITE_REG+SETUP_RETR,0x1a);
  	NRF24L01_Write_Reg(SPI_WRITE_REG+RF_CH,NRF_Channel);         
  	NRF24L01_Write_Reg(SPI_WRITE_REG+RF_SETUP,0x0f);  
  	NRF24L01_Write_Reg(SPI_WRITE_REG+CONFIG,0x0e);    
	CE_H;                                  
}

/**
 * @brief   检测NEF是否连接正常
 * @param  	None
 * @retval	1不正常，0正常
 */	
u8 NRF24L01_Check(void){
	u8 buf[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
	u8 buf1[5];
	u8 i;   	 
	NRF24L01_Write_Buf(SPI_WRITE_REG+TX_ADDR,buf,5);
	NRF24L01_Read_Buf(TX_ADDR,buf1,5); 	
	for(i=0;i<5;i++)
		if(buf1[i]!=0XA5) break;					   
	if(i!=5) return 1;                              	
	return 0;		                            
}

/**
 * @brief   初始化NRF所用端口，模拟SPI驱动
 * @param  	None
 * @retval	None
 */
void NRF24L01_init(void){
	GPIO_InitTypeDef GPIO_InitStructure;			
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOC,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_5|GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_9|GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP; 	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	CE_H;                                    				
  CSN_H;                                   				

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_6;//SPI输入和IRQ中断引脚
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;	
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
		
	IRQ_H; 			 
	CE_L; 	                                
	CSN_H;     
/*	
	if(Set_Mode_D){  //单纯的接收模式 交换发送地址和接收地址
		RX_ADDRESS[0]=0x54;
		RX_ADDRESS[1]=0x69;
		RX_ADDRESS[2]=0x6D;
		RX_ADDRESS[3]=0x65;
		RX_ADDRESS[4]=0x72;
		
		TX_ADDRESS[0]=0x51;
		TX_ADDRESS[1]=0x58;
		TX_ADDRESS[2]=0x50;
		TX_ADDRESS[3]=0x4E;
		TX_ADDRESS[4]=0x42;
	}
	*/
	
	while(NRF24L01_Check()){
	  GPIO_WriteBit(GPIOC,GPIO_Pin_14,(BitAction)(1-(GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_14))));
		  //GPIO_WriteBit(GPIOC,GPIO_Pin_13,(BitAction)(1-(GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_13))));
		Delay_ms(500);
    }
	  NRF_Buff[0]=31;


}


/******************* (C) COPYRIGHT 2017 Qin xingpeng *****END OF FILE****/
