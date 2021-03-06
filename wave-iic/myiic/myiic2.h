#ifndef _MYIIC2_H
#define _MYIIC2_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32F429开发板
//IIC驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//创建日期:2016/1/13
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
//IO方向设置
#define SDA_IN_2()  {GPIOB->MODER&=~(3<<(7*2));GPIOB->MODER|=0<<7*2;}	//PH7输入模式
#define SDA_OUT_2() {GPIOB->MODER&=~(3<<(7*2));GPIOB->MODER|=1<<7*2;} //PH7输出模式  
//IO操作
#define IIC_SCL_2   PHout(6) //SCL
#define IIC_SDA_2   PHout(7) //SDA
#define READ_SDA_2  PHin(7)  //输入SDA

//IIC所有操作函数
void IIC_Init_2(void);                //初始化IIC的IO口				 
void IIC_Start_2(void);				//发送IIC开始信号
void IIC_Stop_2(void)                                                   ;	  			//发送IIC停止信号
void IIC_Send_Byte_2(u8 txd);			//IIC发送一个字节
u8 IIC_Read_Byte_2(unsigned char ack);//IIC读取一个字节
u8 IIC_Wait_Ack_2(void); 				//IIC等待ACK信号
void IIC_Ack_2(void);					//IIC发送ACK信号
void IIC_NAck_2(void);				//IIC不发送ACK信号

void IIC_Write_One_Byte_2(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte_2(u8 daddr,u8 addr);	 
#endif

