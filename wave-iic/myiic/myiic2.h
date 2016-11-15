#ifndef _MYIIC2_H
#define _MYIIC2_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F429������
//IIC��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2016/1/13
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	
//IO��������
#define SDA_IN_2()  {GPIOB->MODER&=~(3<<(7*2));GPIOB->MODER|=0<<7*2;}	//PH7����ģʽ
#define SDA_OUT_2() {GPIOB->MODER&=~(3<<(7*2));GPIOB->MODER|=1<<7*2;} //PH7���ģʽ  
//IO����
#define IIC_SCL_2   PHout(6) //SCL
#define IIC_SDA_2   PHout(7) //SDA
#define READ_SDA_2  PHin(7)  //����SDA

//IIC���в�������
void IIC_Init_2(void);                //��ʼ��IIC��IO��				 
void IIC_Start_2(void);				//����IIC��ʼ�ź�
void IIC_Stop_2(void)                                                   ;	  			//����IICֹͣ�ź�
void IIC_Send_Byte_2(u8 txd);			//IIC����һ���ֽ�
u8 IIC_Read_Byte_2(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack_2(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack_2(void);					//IIC����ACK�ź�
void IIC_NAck_2(void);				//IIC������ACK�ź�

void IIC_Write_One_Byte_2(u8 daddr,u8 addr,u8 data);
u8 IIC_Read_One_Byte_2(u8 daddr,u8 addr);	 
#endif

