#ifndef _HDC1080_H_
#define _HDC1080_H_

#include "main.h"

#define HDC1080_Device_Adderss 0x80
#define HDC1080_Read_Temperature 0x00
#define HDC1080_Read_Humidity 0x01
#define HDC1080_Read_Config 0x02

#define HDC1080_DEVICE_ID 0xff
#define HDC1080_ID 0x1000

#define HDC1080_Rst 15   // 0x8000
#define HDC1080_Enht 13  // 0x2000
#define HDC1080_Mode 12  // 0x1000
#define HDC1080_Trest 10 // 0x0000
#define HDC1080_Hres 8   // 0x0000 14 11 7bit

void HDC1080_Init(void);
int16_t HDC1080_Read_Temper(void);
int16_t HDC1080_Read_Humidi(void);
uint16_t HDC1080_Read_Conf(void);
uint16_t HDC1080_Read_ManufacturerID(void);
uint16_t HDC1080_Read_DeviceID(void);

/*******************************************************************************
以下是迁移进来的iic程序
 *******************************************************************************/
// IO方向设置

// SDA设置为输入
#define SDA_IN()                                            \
    {                                                       \
        GPIO_InitTypeDef GPIO_InitStruct = {0};             \
        GPIO_InitStruct.Pin = OLED_DO_Pin;                  \
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;         \
        GPIO_InitStruct.Pull = GPIO_NOPULL;                 \
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;        \
        HAL_GPIO_Init(OLED_DO_GPIO_Port, &GPIO_InitStruct); \
    }
// SDA设置为输出
#define SDA_OUT()                                           \
    {                                                       \
        GPIO_InitTypeDef GPIO_InitStruct = {0};             \
        GPIO_InitStruct.Pin = OLED_DO_Pin;                  \
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;         \
        GPIO_InitStruct.Pull = GPIO_NOPULL;                 \
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;        \
        HAL_GPIO_Init(OLED_DO_GPIO_Port, &GPIO_InitStruct); \
    }

// IO操作函数
#define IIC_SCL_HIGH // SCL
#define IIC_SCL_LOW  // SCL

#define IIC_SCL HAL_GPIO_ReadPin(OLED_DO_GPIO_Port,OLED_DO_Pin)// 读IIC

#define IIC_SDA_HIGH // SDA
#define IIC_SDA_LOW  // SDA

#define READ_SDA HAL_GPIO_ReadPin(OLED_DO_GPIO_Port,OLED_DO_Pin) // 输入SDA

// IIC所有操作函数
void IIC_Init(void);                      // 初始化IIC的IO口
void IIC_Start(void);                     // 发送IIC开始信号
void IIC_Stop(void);                      // 发送IIC停止信号
void IIC_Send_Byte(uint8_t txd);          // IIC发送一个字节
uint8_t IIC_Read_Byte(unsigned char ack); // IIC读取一个字节
uint8_t IIC_Wait_Ack(void);               // IIC等待ACK信号
void IIC_Ack(void);                       // IIC发送ACK信号
void IIC_NAck(void);                      // IIC不发送ACK信号

#endif
