#ifndef _TIMER_H_
#define _TIMER_H_
#include <stdint.h> 

void TIM4_PWM_Init(uint32_t psc);

void TIM2_PWM_Init(uint32_t psc);

void Start(void);

#endif

