/**
  ******************************************************************************
  * @file       NRF24L01.c
  * @author  	Qin xingpeng
  * @version 	V1.0
  * @date     	2017��9��27��09:29:44
  * @brief      NRF����ʵ��
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */


#include "include.h"

/**
 * @brief   ���͵�ַ�����յ�ַ�����ݻ�������
			��ʼ�����PA15����͵�ƽ
 * @param  	None
 * @retval	None
 */	 
uint8_t TX_ADDRESS[5]={0x11,0x22,0x33,0x44,0x55}; //���͵�ַ
uint8_t RX_ADDRESS[5]={0x55,0x44,0x33,0x22,0x11}; //���յ�ַ


uint8_t  NRF_Buff[TX_PLOAD_WIDTH]={32,'0'};




/**
 * @brief   ����NRF��ʱ
 * @param  	None
 * @retval	None
 */	
void Delay(vu32 nCount){
	for(; nCount != 0; nCount--);
}


/**
 * @brief   ģ��SPI��д���ݺ���
 * @param  	д�������
 * @retval	��Ӧʱ�����߷��ص�����
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
 * @brief   ģ��SPIд�Ĵ���
 * @param  	�Ĵ�����ַ��д�������
 * @retval	д��ĵ�������
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
 * @brief   ģ��SPI���Ĵ���ֵ
 * @param  	�Ĵ�����ַ
 * @retval	�յ�������
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
 * @brief   ��ָ��λ�ö���ָ�����ȵ�����
 * @param  	�Ĵ�����ַ���洢��ַ�����ݳ���
 * @retval	�յ�������
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
 * @brief   ��ָ��λ��дָ�����ȵ�����
 * @param  	�Ĵ�����ַ��д������ݣ����ݳ���
 * @retval	�յ�������
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
 * @brief   ��������
 * @param   ��Ҫ���͵����ݻ���
 * @retval	�Ƿ�ɹ�
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
 * @brief   ��������
 * @param   �洢��λ��
 * @retval	�Ƿ�ɹ�
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
 * @brief   ʹNRF����������ģʽ
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
 * @brief   ʹNRF���뷢����ģʽ
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
 * @brief   ���NEF�Ƿ���������
 * @param  	None
 * @retval	1��������0����
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
 * @brief   ��ʼ��NRF���ö˿ڣ�ģ��SPI����
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

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_6;//SPI�����IRQ�ж�����
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;	
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
		
	IRQ_H; 			 
	CE_L; 	                                
	CSN_H;     
/*	
	if(Set_Mode_D){  //�����Ľ���ģʽ �������͵�ַ�ͽ��յ�ַ
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
