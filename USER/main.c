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
  float temp;//温度
	float	Humi;//湿度

	delay_init();	
  LED_Init();          	//LED初始化
	PWR_Init();          	//开关控制引脚初始化	
	SHT2x_Init();       	//SHT2x初始化
	OLED_Init();
	KEY_Init();        		   //按键初始化
	USART1_Init(9600);			 //PA2 PA3串口初始化
	wifi_protocol_init();	   //wifi初始化函数	
	
	PWR_ON;  //开机
	OLED_Clear();//清屏函数	
	delay_ms(2000);

	while(1)
	{	
		wifi_uart_service();  //SDK函数
		//按键检测
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
		//配网状态
		switch(mcu_get_wifi_work_state())
    {
			case SMART_CONFIG_STATE: 
					 LED_Flash_fast(); //处于 Smart 配置状态，即 LED 快闪
					 break;
			case AP_STATE:  
					 LED_Flash_low();//处于 AP 配置状态，即 LED 慢闪
					 break;
			case WIFI_NOT_CONNECTED:
					 LED_OFF;//Wi-Fi 配置完成，正在连接路由器，即 LED 常暗
					 break;
			case WIFI_CONNECTED:
					 LED_ON;//路由器连接成功，即 LED 常亮
					 break;
			default:break;
    }
		//控制OLED显示
		if(i%2==0) OLED_Display_On();
		   else    OLED_Display_Off();
		
		//温湿度采集
  	temp=SHT2x_GetTempPoll();//获取SHT20 温度
		Humi=SHT2x_GetHumiPoll();//获取SHT20 湿度
		//温湿度上报
		mcu_dp_value_update(1,(long)temp*10); //温度数据上报，采集的 float 数据转换为 long;
    mcu_dp_value_update(2,(long)Humi); //湿度数据上报，float 转换为 long ;
   
		//温湿度OLED显示
		  OLED_WS_DIS(temp,Humi);
	}
}

void OLED_WS_DIS( float temp,float	Humi)
{
		OLED_Clear();//清屏函数		
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
