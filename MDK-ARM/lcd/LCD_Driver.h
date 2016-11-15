#ifndef __LCD_Driver_H
#define __LCD_Driver_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"
#define ADC1_DR_Address    ((u32)0x4001244C)
#define uchar unsigned char
#define uint  unsigned int
//===================================================================
//                     LCD PINS DEFINE
//===================================================================

#define Line1   0x83
#define Line5   0x83
#define Line2   0x92
#define Line3   0x89
#define Line4   0x98

#define LCD_IO1  GPIOC
#define CS      GPIO_Pin_5

#define LCD_IO2  GPIOB
#define RW      GPIO_Pin_1

#define LCD_IO3  GPIOE
#define CLK      GPIO_Pin_7

#define LCD_IO4  GPIOD
#define PSB      GPIO_Pin_11
#define RST      GPIO_Pin_15
 
#define CS_H GPIO_SetBits(GPIOC,GPIO_Pin_5) 			//RS=1   4PIN
#define CS_L GPIO_ResetBits(GPIOC,GPIO_Pin_5) 			//RS=0 

#define RW_H GPIO_SetBits(GPIOB,GPIO_Pin_1) 			//RW=1    5PIN
#define RW_L GPIO_ResetBits(GPIOB,GPIO_Pin_1)  			//RW = 0

#define CLK_H GPIO_SetBits(GPIOE,GPIO_Pin_7) 			//RW=1    5PIN
#define CLK_L GPIO_ResetBits(GPIOE,GPIO_Pin_7)  		//RW = 0

#define PSB_H GPIO_SetBits(GPIOD,GPIO_Pin_11) 			//RW=1    5PIN
#define PSB_L GPIO_ResetBits(GPIOD,GPIO_Pin_11)  		//RW = 0

#define RST_H GPIO_SetBits(GPIOD,GPIO_Pin_15) 			//RW=1    5PIN
#define RST_L GPIO_ResetBits(GPIOD,GPIO_Pin_15)    		//RW = 0

#define LCD_CMD       (u32)0xf8000000 						//
#define LCD_DATE      (u32)0xfa000000 						// 

void LCD_init(void);
void Display(u8 addr,u8 *hz);
void LCD_Write(u32 cmd,u8 ddata);
void VD(void);  
#endif 



