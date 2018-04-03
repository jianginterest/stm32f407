#ifndef _LED_H_
#define _LED_H_

void led_INIT(void);
void led(void);

#define DigitalToggle(p,i)		{p->ODR ^=i;}	
#define LEDTOGGLE()		DigitalToggle(GPIOC,GPIO_Pin_13)

#endif

