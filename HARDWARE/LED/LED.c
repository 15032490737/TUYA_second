#include "LED.h"
#include "delay.h"
#include "sys.h"
void LED_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  /* 使能GPIOB时钟 */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

  /* 配置LED相应引脚PB1*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
}


void LED_Flash_fast(void)  //LED快闪一次
{	
			LED_ON;
			delay_ms(250);
			LED_OFF;
			delay_ms(250);
}

void LED_Flash_low(void)  //LED慢闪一次
{
			LED_ON;
			delay_ms(1500);
			LED_OFF;
			delay_ms(1500);
}

