#ifndef __KEY_H
#define __KEY_H

#include "stm32f0xx.h"

#define KEY1 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)
#define KEY2 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_1)
#define KEY3 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)

#define KEY1_PRES	 1		//KEY1 
#define KEY2_PRES	 2		//KEY2 
#define KEY3_PRES	 3		//KEY3 

void KEY_Init(void);
uint8_t  KEY_SCAN(void);

#endif

