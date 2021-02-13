#include "LED.h"
#include "delay.h"
#include "sys.h"
void LED_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure;
  
  /* ʹ��GPIOBʱ�� */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

  /* ����LED��Ӧ����PB1*/
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
}


void LED_Flash_fast(void)  //LED����һ��
{	
			LED_ON;
			delay_ms(250);
			LED_OFF;
			delay_ms(250);
}

void LED_Flash_low(void)  //LED����һ��
{
			LED_ON;
			delay_ms(1500);
			LED_OFF;
			delay_ms(1500);
}

