#ifndef _KEY_H_
#define _KEY_H_


#define KEY0 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)

void key_init(void);
int key_scan(void);
void key_test(void);

#endif
