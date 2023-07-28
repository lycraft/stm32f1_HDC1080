//////////////////////////////////////////////////////////////////////////////////
// ������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
// �о�԰����
// ���̵�ַ��http://shop73023976.taobao.com/?spm=2013.1.0.0.M4PqC2
//
//   �� �� ��   : main.c
//   �� �� ��   : v2.0
//   ��    ��   : HuangKai
//   ��������   : 2014-0101
//   ����޸�   :
//   ��������   : OLED 4�ӿ���ʾ����(51ϵ��)
//               ˵��:
//               ----------------------------------------------------------------
//               GND    ��Դ��
//               VCC  ��5V��3.3v��Դ
//               D0   ��PA8��SCL��
//               D1   ��PB15��SDA��
//               RES  ��PB14
//               DC   ��PB13
//               CS   ��PA3
//               ----------------------------------------------------------------
//  �޸���ʷ   :
//  ��    ��   :
//  ��    ��   : HuangKai
//  �޸�����   : �����ļ�
// ��Ȩ���У�����ؾ���
// Copyright(C) �о�԰����2014/3/16
// All rights reserved
//******************************************************************************/
#ifndef __OLED_H
#define __OLED_H
#include "main.h"
#include "stdlib.h"
// OLEDģʽ����
// 0:4�ߴ���ģʽ
// 1:����8080ģʽ
#define OLED_MODE 0
#define SIZE 16
#define XLevelL 0x00
#define XLevelH 0x10
#define Max_Column 128
#define Max_Row 64
#define Brightness 0xFF
#define X_WIDTH 128
#define Y_WIDTH 64
//-----------------OLED�˿ڶ���----------------
#define OLED_CS_Clr() GPIO_ResetBits(GPIOA, GPIO_Pin_3) //	CS
#define OLED_CS_Set() GPIO_SetBits(GPIOA, GPIO_Pin_3)

// #define OLED_RST_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_14)//RES
// #define OLED_RST_Set() GPIO_SetBits(GPIOB,GPIO_Pin_14)
#define OLED_RST_Clr() HAL_GPIO_WritePin(OLED_RST_GPIO_Port, OLED_RST_Pin, GPIO_PIN_RESET) //	RST	B14
#define OLED_RST_Set() HAL_GPIO_WritePin(OLED_RST_GPIO_Port, OLED_RST_Pin, GPIO_PIN_SET)

// #define OLED_DC_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_13)//DC
// #define OLED_DC_Set() GPIO_SetBits(GPIOB,GPIO_Pin_13)
#define OLED_DC_Clr() HAL_GPIO_WritePin(OLED_DI_GPIO_Port, OLED_DI_Pin, GPIO_PIN_RESET) //	DC  B13
#define OLED_DC_Set() HAL_GPIO_WritePin(OLED_DI_GPIO_Port, OLED_DI_Pin, GPIO_PIN_SET)

#define OLED_WR_Clr() GPIO_ResetBits(GPIOG, GPIO_Pin_14)
#define OLED_WR_Set() GPIO_SetBits(GPIOG, GPIO_Pin_14)

#define OLED_RD_Clr() GPIO_ResetBits(GPIOG, GPIO_Pin_13)
#define OLED_RD_Set() GPIO_SetBits(GPIOG, GPIO_Pin_13)

// PC0~7,��Ϊ������
#define DATAOUT(x) GPIO_Write(GPIOC, x); // ���
// ʹ��4�ߴ��нӿ�ʱʹ��

// #define OLED_SCLK_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_8)//CLK
// #define OLED_SCLK_Set() GPIO_SetBits(GPIOA,GPIO_Pin_8)
#define OLED_SCLK_Clr() HAL_GPIO_WritePin(OLED_DO_GPIO_Port, OLED_DO_Pin, GPIO_PIN_RESET) // PA8 DO
#define OLED_SCLK_Set() HAL_GPIO_WritePin(OLED_DO_GPIO_Port, OLED_DO_Pin, GPIO_PIN_SET)

// #define OLED_SDIN_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_15)//DIN
// #define OLED_SDIN_Set() GPIO_SetBits(GPIOB,GPIO_Pin_15)
#define OLED_SDIN_Clr() HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, GPIO_PIN_RESET) // PA15 DI
#define OLED_SDIN_Set() HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, GPIO_PIN_SET)

#define OLED_CMD 0  // д����
#define OLED_DATA 1 // д����

// OLED�����ú���
void OLED_WR_Byte(uint8_t dat, uint8_t cmd);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(uint8_t x, uint8_t y, uint8_t t);
void OLED_Fill(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t dot);
void OLED_ShowChar(uint8_t x, uint8_t y, uint8_t chr);
void OLED_ShowNum(uint8_t x, uint8_t y, uint32_t num, uint8_t len, uint8_t size);
void OLED_ShowString(uint8_t x, uint8_t y, uint8_t *p);
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(uint8_t x, uint8_t y, uint8_t no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char BMP[]);
#endif
