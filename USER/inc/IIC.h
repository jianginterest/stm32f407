#ifndef __IIC_H__
#define __IIC_H__

#include <stdint.h>

#define FALSE 0
#define TRUE  1

#define SCL_PIN     GPIO_Pin_4
#define SDA_PIN     GPIO_Pin_5

#define SCL_H       GPIO_SetBits(GPIOC, SCL_PIN)   
#define SCL_L       GPIO_ResetBits(GPIOC , SCL_PIN) 

#define SDA_H       GPIO_SetBits(GPIOC , SDA_PIN)   
#define SDA_L       GPIO_ResetBits(GPIOC , SDA_PIN) 

#define SCL_read    GPIO_ReadInputDataBit(GPIOC , SCL_PIN) 
#define SDA_read    GPIO_ReadInputDataBit(GPIOC , SDA_PIN) 

void I2C_INIT(void);

void I2C_SDA_IN(void);
void I2C_SDA_OUT(void);

void I2C_delay(void);
void delay5ms(void);
uint16_t I2C_Start(void);
void I2C_Stop(void);
void I2C_Ack(void); 
void I2C_NoAck(void);
uint16_t I2C_WaitAck(void);
void I2C_SendByte(unsigned char SendByte);
unsigned char I2C_RadeByte(void);
uint16_t Single_Write(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data);
uint16_t Single_Write_MS5611(unsigned char SlaveAddress,unsigned char REG_Address);	
unsigned char Single_Read(unsigned char SlaveAddress,unsigned char REG_Address);


#endif // __MYI2C_H__
