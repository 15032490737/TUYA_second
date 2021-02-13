
#include "EXTI.h"
#include "LED.h"
#include "pwr.h"
#include "sys.h"
#include "oled.h"
#include "wifi.h"
#include "delay.h"

void EXTI_PA0_Init(void)
{ 
		EXTI_InitTypeDef EXTI_InitStruct;
		NVIC_InitTypeDef NVIC_InitStruct;
		GPIO_InitTypeDef GPIO_InitStruct; 

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
					 
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0; 
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP; //上拉模式
		GPIO_Init(GPIOA, &GPIO_InitStruct);      
		 
		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);  //GPIO与中断线的映射

		EXTI_ClearITPendingBit(EXTI_Line0);

		EXTI_InitStruct.EXTI_Line = EXTI_Line0;
		EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
		EXTI_InitStruct.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStruct); 

		NVIC_InitStruct.NVIC_IRQChannel = EXTI0_1_IRQn;
		NVIC_InitStruct.NVIC_IRQChannelPriority = 0x00;
		NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStruct);
}


void EXTI_PA1_Init(void)
{ 
		EXTI_InitTypeDef EXTI_InitStruct;
		NVIC_InitTypeDef NVIC_InitStruct;
		GPIO_InitTypeDef GPIO_InitStruct; 

		RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1; 
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_Level_2;
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP; //上拉模式
		GPIO_Init(GPIOA, &GPIO_InitStruct);      

		SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource1);

		EXTI_ClearITPendingBit(EXTI_Line1);

		EXTI_InitStruct.EXTI_Line = EXTI_Line1;
		EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
		EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
		EXTI_InitStruct.EXTI_LineCmd = ENABLE;
		EXTI_Init(&EXTI_InitStruct); 

		NVIC_InitStruct.NVIC_IRQChannel = EXTI0_1_IRQn;
		NVIC_InitStruct.NVIC_IRQChannelPriority =1;
		NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStruct);
}

//=============================================================================
//文件名称：EXTI0_1_IRQHandler
//功能概要：按键中断函数
//参数说明：无
//函数返回：无
//=============================================================================
void EXTI0_1_IRQHandler(void)
{
	unsigned int i = 0x02;
	if ( EXTI_GetITStatus(EXTI_Line0)!= RESET ) //进入smart配网
	{
		LED_ON;
		delay_ms(100);
		LED_OFF;
		delay_ms(100);
		
//		mcu_reset_wifi();
		mcu_set_wifi_mode(SMART_CONFIG);		
    
//		EXTI_ClearITPendingBit(EXTI_Line0);
	}		
	
	if ( EXTI_GetITStatus(EXTI_Line1)!= RESET ) //打开与关闭OLED控制
	{		
	  i++;
		
		if(i%2==0)
		{
			OLED_Display_On();
		}		
		else if(i%2==0)
		{
			OLED_Display_Off();
		}	
		EXTI_ClearITPendingBit(EXTI_Line1);
	}		
	
}	
	
