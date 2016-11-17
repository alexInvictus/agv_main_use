#ifndef _LCD_DRIVER_
#define _LCD_DRIVER_
#include "all.h"

void LCD_init(void)
{

	  CS_L;
    RST_L;
    delay_ms(100);
    RST_H;
    delay_ms(40);
	  LCD_Write(LCD_CMD,0x14);         
    delay_ms(40);
    LCD_Write(LCD_CMD,0x30);
    delay_ms(40);
    LCD_Write(LCD_CMD,0x0c);
    delay_ms(40);
    LCD_Write(LCD_CMD,0x01); 
    delay_ms(40);
    LCD_Write(LCD_CMD,0x06);         
    delay_ms(40);
}

void LCD_Write(u32 cmd,u8 ddata)
{
    u32 temp=cmd;
    u32 i;
    CS_L; 
    temp|=((u32)(ddata&(u8)0xf0)<<16)+((u32)(ddata&(u8)0x0f)<<12);
    CS_H; 
    for(i=0;i<24;i++)
    {
        if(temp&0x80000000)RW_H;
        else RW_L; 
        CLK_H;
        delay_ms(2);
        CLK_L;
        temp=temp<<1;
    }
    CS_L; 
}

void Display(u8 addr,u8 *hz)
{
   LCD_Write(LCD_CMD,addr);
   delay_ms(3);
   while(*hz!='\0')
   {
     LCD_Write(LCD_DATE,*hz);
     hz++;
     delay_ms(3);
   }
}

void Show_Static(void)
{
  LCD_init();

  delay_ms(1000);
//  Delay_Ms(3000);
  Display(Line1,"AGV");
  Display(Line2,"智能仓储");
  Display(Line3,"自动化工程部");
  Display(Line4,"电压:");
}

void Voltage_Test(void)            //电压检测
{
	 int w;
    Display(Line4,"电压:");
    Temp=(ADC_Average(uhADCxConvertedValue2,100,6)*830)/1024;
	  Temp=Temp+200;
    ptr[0]=Temp/10000;             //显示第一个字符
    ptr[1]=Temp%10000/1000;        //显示第二个字符
    ptr[2]=10;                     //.	
    ptr[3]=Temp%1000/100;          //显示第三个字符
    ptr[4]=Temp%100/10;            //显示第四个字符
    ptr[5]=11;                     //V
    for(w=0;w<6;w++)
    {			
     LCD_Write(LCD_DATE,shuzi[ptr[w]]);
     delay_ms(3);
    }
}

#endif

