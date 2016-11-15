#ifndef _C_KS103_
#define _C_KS103_
#include "all.h"
/*模拟iic通信*/
u8 KS103_ReadOneByte(u8 address, u8 reg)
{
  u8 temp=0;
	
	IIC_Start_2();
	IIC_Send_Byte_2(address);  //发送低地址
	IIC_Wait_Ack_2();
	IIC_Send_Byte_2(reg);      //发送高地址
	IIC_Wait_Ack_2();
	IIC_Start_2();
	IIC_Send_Byte_2(address+1);  //进入接收模式
	IIC_Wait_Ack_2();
	
	delay_us(50);
	temp=IIC_Read_Byte_2(0);    
	IIC_Stop_2();              //产生一个停止条件
	return temp;
}

void KS103_WriteOneByte(u8 address,u8 reg,u8 command)
{
  IIC_Start_2();
	IIC_Send_Byte_2(address);
	IIC_Wait_Ack_2();
	IIC_Send_Byte_2(reg);      //发送高地址
	IIC_Wait_Ack_2();
	IIC_Send_Byte_2(command);
	IIC_Wait_Ack_2();
	IIC_Stop_2();              
}

u16 Wave_test(void)
{
	  static u16 range=0;
		KS103_WriteOneByte(0xe8,0x02,0xb0);
		delay_ms(80);
		range=KS103_ReadOneByte(0xe8,0x02);
		range<<=8; 
		range+=KS103_ReadOneByte(0xe8,0x03);
		return range*2;
}

#endif
