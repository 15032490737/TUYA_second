#include "sys.h"
#include "TIMER.h"
#include "LED.h"
#include "delay.h"
#include "oled.h"

/*
	���������ⲿ����
*/
extern	float SHT2x_GetTempPoll(void);//��ȡSHT20 �¶�
extern  float SHT2x_GetHumiPoll(void);//��ȡSHT20 ʪ��
extern  unsigned char mcu_dp_value_update(unsigned char dpid,unsigned long value);//VALUE�������ϱ���long ������
float 	temp;//�¶�
float		Humi;//ʪ��

void TIM3_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//ʱ��ʹ��

  TIM_TimeBaseStructure.TIM_Period = arr;           	// �Զ���װ�ؼĴ������ڵ�ֵ(����ֵ) 
  TIM_TimeBaseStructure.TIM_Prescaler = psc;					//ʱ��Ԥ��Ƶ�� 
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;				//���ϼ���ģʽ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  TIM_ClearFlag(TIM3, TIM_FLAG_Update);			        // ��������ж�
  
	TIM_ITConfig(
								TIM3,
								TIM_IT_Update,
								ENABLE
							);
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;			//TIM3�ж�
  NVIC_InitStructure.NVIC_IRQChannelPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ����ʹ��
  NVIC_Init(&NVIC_InitStructure);
	
  TIM_Cmd(TIM3, ENABLE);	//ʹ��TIMx����
}

void TIM3_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
  {
		TIM_ClearITPendingBit(TIM3,TIM_FLAG_Update);

		temp=SHT2x_GetTempPoll();//��ȡSHT20 �¶�
		Humi=SHT2x_GetHumiPoll();//��ȡSHT20 ʪ��
		
//		mcu_dp_value_update(1,(long)temp); //�¶������ϱ����ɼ��� float ����ת��Ϊ long;
//    mcu_dp_value_update(2,(long)Humi); //ʪ�������ϱ���float ת��Ϊ long ;

		OLED_Clear();//��������		
    OLED_ShowFloatNumber(26,2,temp,16);
		OLED_ShowString(72,2,"'C",16);
		OLED_ShowFloatNumber(26,4,Humi,16);
		OLED_ShowString(72,4,"%",16);

  }
 
}
