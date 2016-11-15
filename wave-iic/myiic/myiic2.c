#ifndef _C_MYIIC2_
#define _C_MYIIC2_
#include "all.h"
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

//IIC初始化
void IIC_Init_2(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOB_CLK_ENABLE();   //使能GPIOH时钟
    
    //PH4,5初始化设置
    GPIO_Initure.Pin=GPIO_PIN_6|GPIO_PIN_7;
    GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  //推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
    GPIO_Initure.Speed=GPIO_SPEED_FAST;     //快速
    HAL_GPIO_Init(GPIOH,&GPIO_Initure);
    
    IIC_SDA_2=1;
    IIC_SCL_2=1;  
}

//产生IIC起始信号
void IIC_Start_2(void)
{
	SDA_OUT_2();     //sda线输出
	IIC_SDA_2=1;	  	  
	IIC_SCL_2=1;
	delay_us(10);
 	IIC_SDA_2=0;//START:when CLK is high,DATA change form high to low 
	delay_us(10);
	IIC_SCL_2=0;//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void IIC_Stop_2(void)
{
	SDA_OUT_2();//sda线输出
	IIC_SCL_2=0;
	IIC_SDA_2=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(10);
	IIC_SCL_2=1; 
	IIC_SDA_2=1;//发送I2C总线结束信号
	delay_us(10);							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC_Wait_Ack_2(void)
{
	u8 ucErrTime=0;
	SDA_IN_2();      //SDA设置为输入  
	IIC_SDA_2=1;delay_us(6);	   
	IIC_SCL_2=1;delay_us(6);	 
	while(READ_SDA_2)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop_2();
			return 1;
		}
	}
	IIC_SCL_2=0;//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void IIC_Ack_2(void)
{
	IIC_SCL_2=0;
	SDA_OUT_2();
	IIC_SDA_2=0;
	delay_us(10);
	IIC_SCL_2=1;
	delay_us(10);
	IIC_SCL_2=0;
}
//不产生ACK应答		    
void IIC_NAck_2(void)
{
	IIC_SCL_2=0;
	SDA_OUT_2();
	IIC_SDA_2=1;
	delay_us(10);
	IIC_SCL_2=1;
	delay_us(10);
	IIC_SCL_2=0;
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte_2(u8 txd)
{                        
    u8 t;   
	  SDA_OUT_2(); 	    
    IIC_SCL_2=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        IIC_SDA_2=(txd&0x80)>>7;
        txd<<=1; 	  
		delay_us(10);   //对TEA5767这三个延时都是必须的
		IIC_SCL_2=1;
		delay_us(10); 
		IIC_SCL_2=0;	
		delay_us(10);
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 IIC_Read_Byte_2(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN_2();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        IIC_SCL_2=0; 
        delay_us(10);
		IIC_SCL_2=1;
        receive<<=1;
        if(READ_SDA_2)receive++;   
		delay_us(5); 
    }					 
    if (!ack)
        IIC_NAck_2();//发送nACK
    else
        IIC_Ack_2(); //发送ACK   
    return receive;
}

#endif
