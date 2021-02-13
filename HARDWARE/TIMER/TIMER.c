#include "sys.h"
#include "TIMER.h"
#include "LED.h"
#include "delay.h"
#include "oled.h"

/*
	声明调用外部函数
*/
extern	float SHT2x_GetTempPoll(void);//获取SHT20 温度
extern  float SHT2x_GetHumiPoll(void);//获取SHT20 湿度
extern  unsigned char mcu_dp_value_update(unsigned char dpid,unsigned long value);//VALUE型数据上报，long 型数据
float 	temp;//温度
float		Humi;//湿度

void TIM3_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//时钟使能

  TIM_TimeBaseStructure.TIM_Period = arr;           	// 自动重装载寄存器周期的值(计数值) 
  TIM_TimeBaseStructure.TIM_Prescaler = psc;					//时钟预分频数 
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;				//向上计数模式
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  TIM_ClearFlag(TIM3, TIM_FLAG_Update);			        // 允许更新中断
  
	TIM_ITConfig(
								TIM3,
								TIM_IT_Update,
								ENABLE
							);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;			//TIM3中断
  NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道被使能
  NVIC_Init(&NVIC_InitStructure);
	
  TIM_Cmd(TIM3, ENABLE);	//使能TIMx外设
}

void TIM3_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
  {
		TIM_ClearITPendingBit(TIM3,TIM_FLAG_Update);

		temp=SHT2x_GetTempPoll();//获取SHT20 温度
		Humi=SHT2x_GetHumiPoll();//获取SHT20 湿度
		
//		mcu_dp_value_update(1,(long)temp); //温度数据上报，采集的 float 数据转换为 long;
//    mcu_dp_value_update(2,(long)Humi); //湿度数据上报，float 转换为 long ;

		OLED_Clear();//清屏函数		
    OLED_ShowFloatNumber(26,2,temp,16);
		OLED_ShowString(72,2,"'C",16);
		OLED_ShowFloatNumber(26,4,Humi,16);
		OLED_ShowString(72,4,"%",16);

  }
 
}
