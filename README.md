立创&涂鸦训练营第二期--物联网温湿度传感器
==
### 基于涂鸦智能的小温湿度传感器，自动采集当前温湿度数据，并通过STM32 & wifi模块上传至云端，送至APP端显示
* This project is developed using Tuya SDK, which enables you to quickly develop branded
apps connecting and controlling smart scenarios of many devices.
For more information, please check Tuya Developer Website.
## 关键词  
物联网 温湿度 传感器 涂鸦智能 立创EDA 
### 主要内容
* 整体介绍
* 部分电路
* 部分程序
* 注意事项
* 实际效果
### 整体介绍
* 更加具体的介绍（硬件&软件），请转到[我的立创开源平台](https://oshwhub.com/mimiww/wu-lian-wang-wen-shi-du-zhuan-gan-qi)
* 本次工程是一个基于涂鸦智能的温湿度传感器，采用低代码 MCU 方案，将涂鸦物联网模块与ST32F0单片机结合使用，实现温湿度数据的采集和上报，并将数据可视化。
此外，还包含了一键开关机,OLED显示，手动采集等功能。
* 传感器由两块PCB构成，通过排针排母以及四颗固定柱连接，整体尺寸：56mm*55m*30mm。下层板包含了传感器所需的各种电路，上层是一块OLED模块，可以用来显示当前的温湿度数据或其他内容，另外，可以通过下层的按键来控制OLED熄灭与显示。
* 供电上，可以使用3.7V锂电池或者Type-C接口供电，当两者同时接入时，默认采用usb供电。
### 部分电路
* 供电：可通过3.7V锂电池或micro usb供电，借助于开关机电路，可以通过右下方的轻触按键实现一键开关机，电源流入后，经过一路LDO电路降压到3.3V后供给整个系统使用，为了保护电路，添加了PTC以及两个TVS二极管，整体需求的电流峰值在500mA左右，正常工作电流不超过200mA。
* wifi模块：采用涂鸦智能的WB3S模块，通过串口和STM32通讯
* STM32系统：本次使用的单片机型号为STM32F030F4P6，M0内核，TSSOP-20封装，体积小，负责处理SHT20传感器的数据，控制OLED显示，通过串口与WB3S通信等，包含了复位，晶振，SWD接口等电路，并充分地使用了它的所有引脚.
* SHT20:温湿度传感器，IIC通讯，为减少PCB本身的干扰，芯片周围挖槽。
* OLED模块：模块电路较为简单，包含一路LDO电路以及必要的阻容元件，使用IIC和STM32通讯，供电电压可使用5V或3.3V。
* 按键：PCB共包含3个侧贴按键，下方控制整体的开关，上方两个按键，左方按键可控制OLED是否显示，右方按键为手动按键，按下则立即测量当前温湿度并且进行显示和dp上传。
### 程序部分
* 得益于涂鸦的优良设计，只需要少量代码开发
* 官方文档教程请看[文档教程](https://developer.tuya.com/cn/docs/iot/device-development/embedded-software-development/mcu-development-access/wifi-mcu-sdk-solution/overview-of-migrating-tuyas-mcu-sdk?id=K9hhi0xr5vll9)
* 官方视频教程请看[MCU SDK 移植](https://developer.tuya.com/cn/docs/iot/device-development/embedded-software-development/mcu-development-access/wifi-mcu-sdk-solution/overview-of-migrating-tuyas-mcu-sdk?id=K9hhi0xr5vll9)
* 这次的程序思路较为清晰，创建F0工程后，按照教程将从涂鸦下载的MCU SDK移植到工程中，然后添加SHT20驱动，OLED驱动，按键程序以及控制开关机的程序。
* STM32 将各个模块初始化后，开机，进入while(1),利用按键触发配网，配网成功后，用SHT20采集数据，并将采集的数据上报，核心的程序为

```C
    // SDK函数
         wifi_uart_service(); 
    // 温湿度采集
         temp=SHT2x_GetTempPoll();//获取SHT20 温度
  	 Humi=SHT2x_GetHumiPoll();//获取SHT20 湿度
   // 温湿度上报
  	 mcu_dp_value_update(1,(long)temp*10); //温度数据上报，采集的 float 数据转换为 long;
         mcu_dp_value_update(2,(long)Humi); //湿度数据上报，float 转换为 long ;
   // 温湿度OLED显示
    	 OLED_WS_DIS(temp,Humi);
```
#### 注意事项

* 我手中的是micro usb接口，现在的图中已经改为了Type-C接口。
* 板子整体平均电流在200mA，峰值电流在500mA，所以选择LDO时，需要选择最大输出超过500mA的型号。
* 使用锂电池供电时，由于板子本身没有电池管理芯片，所以要选择带有放电保护板的锂电池，而且电池不宜长期使用，当电压不足时，应该及时充电。
* 关于OLED显示模块，使用常见的即可，这里是为了好看才又按照下板的尺寸做了一块驱动，计划使用的是1.3寸OLED裸屏，这里原理图直接使用技新的工程，几乎只是更改了整体的尺寸，实际上两个看起来都不错。
* 程序上，有几处需要注意的地方，例如，如果使用定时器，要注意串口和定时器的中断优先级，移植SDK时的串口发送函数是用的单字节函数等等，需要留心。
```C
void USART1_SendByte(unsigned char data)//单字节发送函数
{	
	while((USART1-&gt;ISR &amp; USART_FLAG_TXE) != USART_FLAG_TXE);
	USART1-&gt;TDR = data;
}
```

#### 实际效果

* 看几张图：

![IMG_20210213_000656.jpg](//image.lceda.cn/pullimage/hDHiENHaJSBoalSD0vLq9jO88BQEqlzLdnulawCS.jpeg)
![IMG_20210213_000510.jpg](//image.lceda.cn/pullimage/mMlXHKFd8WEo1OCOCLzjfG5F3co0tebgxfTUPiXT.jpeg)
![IMG_20210213_012921.jpg](//image.lceda.cn/pullimage/25mMEqdHge4a0p6YmGp98HTPAq7wPedrtWAqvqEu.jpeg)

#### 如果你喜欢的话，点个赞？
#### 演示视频会放在文件中 
