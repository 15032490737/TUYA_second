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
* 本次工程是一个基于涂鸦智能的温湿度传感器，采用低代码 MCU 方案，将涂鸦物联网模块与ST32F0单片机结合使用，实现温湿度数据的采集和上报，并将数据可视化。
此外，还包含了一键开关机,OLED显示，手动采集等功能。
* 传感器由两块PCB构成，通过排针排母以及四颗固定柱连接，整体尺寸：56mm*55m*30mm。下层板包含了传感器所需的各种电路，上层是一块OLED模块，可以用来显示当前的温湿度数据或其他内容，另外，可以通过下层的按键来控制OLED熄灭与显示。
* 供电上，可以使用3.7V锂电池或者micro usb供电，当两者同时接入时，默认采用usb供电。
### 部分电路
* 供电：可通过3.7V锂电池或micro usb供电，借助于开关机电路，可以通过右下方的轻触按键实现一键开关机，电源流入后，经过一路LDO电路降压到3.3V后供给整个系统使用，为了保护电路，添加了PTC以及两个TVS二极管，整体需求的电流峰值在500mA左右，正常工作电流不超过200mA。
* wifi模块：采用涂鸦智能的WB3S模块，通过串口和STM32通讯
* STM32系统：本次使用的单片机型号为STM32F030F4P6，M0内核，TSSOP-20封装，体积小，负责处理SHT20传感器的数据，控制OLED显示，通过串口与WB3S通信等，包含了复位，晶振，SWD接口等电路，并充分地使用了它的所有引脚.
* SHT20:温湿度传感器，IIC通讯，为减少PCB本身的干扰，芯片周围挖槽。
* OLED模块：模块电路较为简单，包含一路LDO电路以及必要的阻容元件，使用IIC和STM32通讯，供电电压可使用5V或3.3V。
* 按键：PCB共包含3个侧贴按键，下方控制整体的开关，上方两个按键，左方按键可控制OLED是否显示，右方按键为手动按键，按下则立即测量当前温湿度并且进行显示和dp上传。
### 程序部分
* 得益于涂鸦的优良设计，只需要少量代码开发，官方具体介绍请看[MCU SDK 移植](https://developer.tuya.com/cn/docs/iot/device-development/embedded-software-development/mcu-development-access/wifi-mcu-sdk-solution/overview-of-migrating-tuyas-mcu-sdk?id=K9hhi0xr5vll9)
