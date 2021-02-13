

#ifndef __PWR_H
#define __PWR_H

#include "stm32f0xx.h"

#define PWR_OFF                  			GPIO_ResetBits(GPIOA,GPIO_Pin_5)
#define PWR_ON                 				GPIO_SetBits(GPIOA,GPIO_Pin_5)

void PWR_Init(void);

#endif
