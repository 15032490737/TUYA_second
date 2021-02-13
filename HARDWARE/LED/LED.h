

#ifndef __LED_H
#define __LED_H

#include "stm32f0xx.h"
/*
#define LED_OFF                       GPIOA->BSRR = 0x02
#define LED_ON                        GPIOA->BRR = 0x02
#define LED_TURN                      GPIOA->ODR ^= 0x02
*/

#define LED_OFF                  			GPIO_SetBits(GPIOA,GPIO_Pin_4)
#define LED_ON                 				GPIO_ResetBits(GPIOA,GPIO_Pin_4)

void LED_Init(void);
void LED_Flash_fast(void);  //LED快闪一次
void LED_Flash_low(void);  //LED慢闪一次
#endif
