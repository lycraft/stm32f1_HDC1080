/*******************************************************************************
 * 文字编码格式为:GB2312
 *
 *
 *
 *
 *******************************************************************************/
#include <stdint.h>
#include "HDC1080.h"

void HDC1080_Write_Buffer(uint8_t addr, uint8_t *buffer, uint8_t len)
{
    IIC_Start();
    IIC_Send_Byte(HDC1080_Device_Adderss);
    IIC_Wait_Ack();
    IIC_Send_Byte(addr);
    IIC_Wait_Ack();
    while (len--)
    {
        IIC_Send_Byte(*buffer);
        IIC_Wait_Ack();
        buffer++;
    }
    IIC_Stop();
}
/*******************************************************************************
 * @brief  HDC1080_Read_Buffer between triger and read there is no wait.
 * @param  uint8_t addr is point register
 * @param  uint8_t *buffer is the need to read data point
 * @param  uint8_t len is the read data length
 * @retval void
 *******************************************************************************/
void HDC1080_Read_Buffer(uint8_t addr, uint8_t *buffer, uint8_t len)
{
    uint8_t temp = 0;

    IIC_Start();
    IIC_Send_Byte(HDC1080_Device_Adderss);

    IIC_Wait_Ack();
    IIC_Send_Byte(addr);
    IIC_Wait_Ack();
    IIC_Stop();

    while (IIC_SCL)
    {
        HAL_Delay(1);
        temp++;
        if (temp >= 10) // 原来是100
        {
            break;
        }
    }
    IIC_Start();
    IIC_Send_Byte(HDC1080_Device_Adderss | 0x01); // read
    IIC_Wait_Ack();
    while (len--)
    {
        *buffer = IIC_Read_Byte(0);
        buffer++;
        if (len == 0)
            IIC_NAck();
        else
            IIC_Ack();
    }
    IIC_Stop();
}
/*******************************************************************************
 * @brief  HDC1080_Read_MBuffer becareful between triger and read there is a wait.
 * @param  uint8_t addr is point register
 * @param  uint8_t *buffer is the need to read data point
 * @param  uint8_t len is the read data length
 * @retval void
 *******************************************************************************/
void HDC1080_Read_MBuffer(uint8_t addr, uint8_t *buffer, uint8_t len)
{
    uint8_t temp = 0;

    IIC_Start();
    IIC_Send_Byte(HDC1080_Device_Adderss);

    IIC_Wait_Ack();
    IIC_Send_Byte(addr);
    IIC_Wait_Ack();
    IIC_Stop();

    while (IIC_SCL)
    {
        HAL_Delay(20);
        temp++;
        if (temp >= 10) // 原来是100
        {

            IIC_SCL_LOW;
        }
    }
    HAL_Delay(10); // after triger should wait at least 6.5ms
    IIC_Start();
    IIC_Send_Byte(HDC1080_Device_Adderss | 0x01); // read
    IIC_Wait_Ack();
    while (len--)
    {
        *buffer = IIC_Read_Byte(1);
        buffer++;
        if (len == 0)
            IIC_NAck();
        else
            IIC_Ack();
    }
    IIC_Stop();
}
/*******************************************************************************
 * @brief  HDC1080_Soft_Reset
 * @param  void
 * @retval void
 *******************************************************************************/
void HDC1080_Soft_Reset(void)
{
    uint8_t temp[2];
    temp[0] = 0x80;
    temp[1] = 0x00;
    HDC1080_Write_Buffer(HDC1080_Read_Config, temp, 2);
    HAL_Delay(20); // there should be waiting for more than 15 ms.
}
/*******************************************************************************
 * @brief  HDC1080_Setting
 * @param  void
 * @retval void
 *******************************************************************************/
void HDC1080_Setting(void)
{
    uint16_t tempcom = 0;
    uint8_t temp[2];

    tempcom |= 1 << HDC1080_Mode;
    temp[0] = (uint8_t)(tempcom >> 8);
    temp[1] = (uint8_t)tempcom;
    HDC1080_Write_Buffer(0x02, temp, 2);
}
/*******************************************************************************
 * @brief  HDC1080_Init
 * @param  void
 * @retval void
 *******************************************************************************/
void HDC1080_Init(void)
{
    uint8_t temp = 0;
    IIC_Init();
    HDC1080_Soft_Reset();
    HDC1080_Setting();

    while (IIC_SCL)
    {
        HAL_Delay(1);
        temp++;
        if (temp >= 100)
        {
            break;
        }
    }
}
/*******************************************************************************
 * @brief  HDC1080_Read_Temper
 * @param  void
 * @retval int16_t tempr value
 *******************************************************************************/
int16_t HDC1080_Read_Temper(void)
{
    uint8_t buffer[2];

    HDC1080_Read_MBuffer(HDC1080_Read_Temperature, buffer, 2);
    // return ((buffer[0] << 8) | buffer[1]);
    // return (int16_t)((((buffer[0] << 8) | buffer[1]) / 65536.0) * 165 - 40);
    return (int16_t)(((((buffer[0] << 8) | buffer[1]) / 65536.0) * 165 - 40) * 100);
}
/*******************************************************************************
 * @brief  HDC1080_Read_Humidity
 * @param  void
 * @retval int16_t Humidity value
 *******************************************************************************/
int16_t HDC1080_Read_Humidi(void)
{
    uint8_t buffer[2];

    HDC1080_Read_MBuffer(HDC1080_Read_Humidity, buffer, 2);

    // return (buffer[0] << 8) | buffer[1];
    return (int16_t)((((buffer[0] << 8) | buffer[1]) / 65536.0) * 10000);
}
/*******************************************************************************
 * @brief  HDC1080_Read_Configuration
 * @param  void
 * @retval Config value
 *******************************************************************************/
uint16_t HDC1080_Read_Conf(void)
{
    uint8_t buffer[2];

    HDC1080_Read_Buffer(HDC1080_Read_Config, buffer, 2);

    return ((buffer[0] << 8) | buffer[1]);
}
/*******************************************************************************
 * @brief  HDC1080_Read_ManufacturerID
 * @param  void
 * @retval ManufacturerID
 *******************************************************************************/
uint16_t HDC1080_Read_ManufacturerID(void)
{
    uint8_t buffer[2];

    HDC1080_Read_Buffer(0xfe, buffer, 2);

    return ((buffer[0] << 8) | buffer[1]);
}
/*******************************************************************************
 * @brief  HDC1080_Read_DeviceID
 * @param  void
 * @retval DeviceID
 *******************************************************************************/
uint16_t HDC1080_Read_DeviceID(void)
{
    uint8_t buffer[2];

    HDC1080_Read_Buffer(0xff, buffer, 2);

    return ((buffer[0] << 8) | buffer[1]);
}

/*******************************************************************************
IIC chengxu
 *******************************************************************************/
// 初始化IIC
void IIC_Init(void)
{
    // GPIO_InitTypeDef GPIO_InitStructure;
    // RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); // 使能GPIOB时钟

    // GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_5;
    // GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // 推挽输出
    // GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    // GPIO_Init(GPIOB, &GPIO_InitStructure);
    // GPIO_SetBits(GPIOB, GPIO_Pin_6 | GPIO_Pin_5); // PB6,PB7 输出高
}
// 产生IIC起始信号
void IIC_Start(void)
{
    SDA_OUT(); // sda线输出
    IIC_SDA_HIGH;
    IIC_SCL_HIGH;
    HAL_Delay(1);
    IIC_SDA_LOW; // START:when CLK is high,DATA change form high to low
    HAL_Delay(1);
    IIC_SCL_LOW; // 钳住I2C总线，准备发送或接收数据
}
// 产生IIC停止信号
void IIC_Stop(void)
{
    SDA_OUT(); // sda线输出
    IIC_SCL_LOW;
    IIC_SDA_LOW; // STOP:when CLK is high DATA change form low to high
    HAL_Delay(1);
    IIC_SCL_HIGH;
    IIC_SDA_HIGH; // 发送I2C总线结束信号
    HAL_Delay(1);
}
// 等待应答信号到来
// 返回值：1，接收应答失败
//         0，接收应答成功
uint8_t IIC_Wait_Ack(void)
{
    uint8_t ucErrTime = 0;
    SDA_IN(); // SDA设置为输入
    IIC_SDA_HIGH;
    HAL_Delay(1);
    IIC_SCL_HIGH;
    HAL_Delay(1);
    while (READ_SDA)
    {
        ucErrTime++;
        if (ucErrTime > 250)
        {
            IIC_Stop();
            return 1;
        }
    }
    IIC_SCL_LOW; // 时钟输出0
    return 0;
}
// 产生ACK应答
void IIC_Ack(void)
{
    IIC_SCL_LOW;
    SDA_OUT();
    IIC_SDA_LOW;
    HAL_Delay(1);
    IIC_SCL_HIGH;
    HAL_Delay(1);
    IIC_SCL_LOW;
}
// 不产生ACK应答
void IIC_NAck(void)
{
    IIC_SCL_LOW;
    SDA_OUT();
    IIC_SDA_HIGH;
    HAL_Delay(1);
    IIC_SCL_HIGH;
    HAL_Delay(1);
    IIC_SCL_LOW;
}
// IIC发送一个字节
// 返回从机有无应答
// 1，有应答
// 0，无应答
void IIC_Send_Byte(uint8_t txd)
{
    uint8_t t;
    SDA_OUT();
    IIC_SCL_LOW; // 拉低时钟开始数据传输
    for (t = 0; t < 8; t++)
    {
        // IIC_SDA=(txd&0x80)>>7;
        if ((txd & 0x80) >> 7)
            IIC_SDA_HIGH;
        else
            IIC_SDA_LOW;
        txd <<= 1;
        HAL_Delay(1); // 对TEA5767这三个延时都是必须的
        IIC_SCL_HIGH;
        HAL_Delay(1);
        IIC_SCL_LOW;
        HAL_Delay(1);
    }
}
// 读1个字节，ack=1时，发送ACK，ack=0，发送nACK
uint8_t IIC_Read_Byte(unsigned char ack)
{
    unsigned char i, receive = 0;
    SDA_IN(); // SDA设置为输入
    for (i = 0; i < 8; i++)
    {
        IIC_SCL_LOW;
        HAL_Delay(1);
        IIC_SCL_HIGH;
        receive <<= 1;
        if (READ_SDA)
            receive++;
        HAL_Delay(1);
    }
    if (!ack)
        IIC_NAck(); // 发送nACK
    else
        IIC_Ack(); // 发送ACK
    return receive;
}
