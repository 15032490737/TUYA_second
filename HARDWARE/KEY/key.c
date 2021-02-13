#include "key.h"
#include "delay.h"

void KEY_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	/* 使能GPIOA时钟 */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	/* 配置KEY相应引脚PA6*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

uint8_t  KEY_SCAN(void)
{
	if(KEY1==0||KEY2==0||KEY3==0)
	{
		delay_ms(10);
		
		if(KEY1==0)
		{
			while(KEY1==0) ;  return KEY1_PRES;
		}
  	else if (KEY2==0)
		{
			while(KEY2==0) ; return KEY2_PRES;
		}
		else if(KEY3==0)
		{
			while(KEY3==0) ; return KEY3_PRES;
		}
	}
	else if (KEY1==0&&KEY2==0&&KEY3==0)
		return 0;
  return 0;
}

