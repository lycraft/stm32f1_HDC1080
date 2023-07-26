# stm32f103c8t6控制hdc1080
### 文件目录

* hardware：AD工程（最小系统和HDC1080小板）
* firmware：Keil工程
* images
* documents：datasheet

### 实物

程序中进度条读完后进入菜单

![2](\images\2.jpg)

菜单**选项一**是hdc1080的读取界面，显示出温度与湿度。

![1](\images\1.jpg)

**选项二**是两个通道的ADC采集

![3](\images\3.jpg)

电压和电流是瞎打的，因为之前是打算搞个采样电路测电流的，搞了两个ADC通道。最上边和最下边那两行的值分别是两个通道的AD值。

**选项三**是一个动画的播放界面。

按键使用的五向开关。向右拨是进入选项，向左拨是返回上一级。

##### PCB

<img src="\images\4.png" alt="4" style="zoom:50%;" />

<img src="\images\5.png" alt="5" style="zoom:50%;" />


### 引脚说明

| Pin  | 定义     | 说明    |
| ---- | -------- | ------- |
| PB6  | IIC_SCL  | HDC1080 |
| PB5  | IIC_SDA  | HDC1080 |
| PA8  | OLED_SCL |         |
| PB15 | OLED_SDA |         |
| PB14 | OLED_RES |         |
| PB13 | OLED_DC  |         |
| PA2  | ADC      |         |
| PA3  | ADC      |         |



##### 更新于23.7.26

准备把该工程基于HAL库重新实现一下，在Firmware_HAL文件夹。