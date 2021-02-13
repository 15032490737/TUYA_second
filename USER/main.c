#include "stm32f0xx.h"
#include "USART1.h"
#include "delay.h"
#include "LED.h"
#include "sys.h"
#include "SHT2x.h"
#include "oled.h"
#include "stdlib.h"
#include "pwr.h"
#include "key.h"
#include "wifi.h"

void OLED_WS_DIS( float temp,float	Humi);

int main(void)
{
	u8 i = 0; 
	u8 t = 0;
  float temp;//�¶�
	float	Humi;//ʪ��

	delay_init();	
  LED_Init();          	//LED��ʼ��
	PWR_Init();          	//���ؿ������ų�ʼ��	
	SHT2x_Init();       	//SHT2x��ʼ��
	OLED_Init();
	KEY_Init();        		   //������ʼ��
	USART1_Init(9600);			 //PA2 PA3���ڳ�ʼ��
	wifi_protocol_init();	   //wifi��ʼ������	
	
	PWR_ON;  //����
	OLED_Clear();//��������	
	delay_ms(2000);

	while(1)
	{	
		wifi_uart_service();  //SDK����
		//�������
		t = KEY_SCAN();
		switch(t)
		{				 
			case KEY1_PRES:
					 mcu_set_wifi_mode(SMART_CONFIG);
					 break;
			case KEY2_PRES:
					 LED_Flash_fast();
			     i++;
					 OLED_Display_On();
					 break;
			case KEY3_PRES:				
					 PWR_OFF;
					 break;
			default:
					delay_ms(10);	
		} 
		//����״̬
		switch(mcu_get_wifi_work_state())
    {
			case SMART_CONFIG_STATE: 
					 LED_Flash_fast(); //���� Smart ����״̬���� LED ����
					 break;
			case AP_STATE:  
					 LED_Flash_low();//���� AP ����״̬���� LED ����
					 break;
			case WIFI_NOT_CONNECTED:
					 LED_OFF;//Wi-Fi ������ɣ���������·�������� LED ����
					 break;
			case WIFI_CONNECTED:
					 LED_ON;//·�������ӳɹ����� LED ����
					 break;
			default:break;
    }
		//����OLED��ʾ
		if(i%2==0) OLED_Display_On();
		   else    OLED_Display_Off();
		
		//��ʪ�Ȳɼ�
  	temp=SHT2x_GetTempPoll();//��ȡSHT20 �¶�
		Humi=SHT2x_GetHumiPoll();//��ȡSHT20 ʪ��
		//��ʪ���ϱ�
		mcu_dp_value_update(1,(long)temp*10); //�¶������ϱ����ɼ��� float ����ת��Ϊ long;
    mcu_dp_value_update(2,(long)Humi); //ʪ�������ϱ���float ת��Ϊ long ;
   
		//��ʪ��OLED��ʾ
		  OLED_WS_DIS(temp,Humi);
	}
}

void OLED_WS_DIS( float temp,float	Humi)
{
		OLED_Clear();//��������		
	  OLED_ShowCHinese(14,0,0);
		OLED_ShowCHinese(34,0,1);
		OLED_ShowChar(60,0,'&',16);
		OLED_ShowCHinese(78,0,2);
		OLED_ShowCHinese(100,0,3);
	 
		OLED_ShowCHinese(6,3,4);
		OLED_ShowCHinese(24,3,5);
		OLED_ShowChar(42,3,':',16);		
    OLED_ShowFloatNumber(52,3,temp,16);
		OLED_ShowString(104,3,"'C",16);
		
		OLED_ShowCHinese(6,6,4);
		OLED_ShowCHinese(24,6,5);
		OLED_ShowChar(42,6,':',16);	
		OLED_ShowFloatNumber(52,6,Humi,16);
		OLED_ShowString(106,6,"%",16);			
	

}
