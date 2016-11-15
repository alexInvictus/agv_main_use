#include "all.h"


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance==USART1)//如果是串口1
	{
				if(aRxBuffer_1[0]==0x2a)   //*包头 开始接收
				{
					flag_usart_1=1;
				  packflag_1=0;
				}
				if(aRxBuffer_1[0]==0x23)      //#包尾packflag表示接收完成
				{
//					Rx_buff_1[USART_RX_STA_1&0X3FFF]=aRxBuffer_1[0] ;
//					USART_RX_STA_1++;
				  flag_usart_1=0;
				  packflag_1=1;
				}
				if(flag_usart_1==1)
				{
				  Rx_buff_1[USART_RX_STA_1&0X3FFF]=aRxBuffer_1[0] ;
					USART_RX_STA_1++;
					if(USART_RX_STA_1>(USART_REC_LEN_1-1))
					{
						flag_usart_1=0;//接收数据错误,重新开始接收	
					  USART_RX_STA_1=0;
					}
				}			
	} 
	 else if(huart->Instance==USART2)        //RFID
	{
	     if(aRxBuffer_2[0]==0xaa)   //0XAA包头 开始接收
				{
					flag_usart_2=1;
				  packflag_2=0;
					USART_RX_STA_2=0;
				}
				if(aRxBuffer_2[0]==0x55)      //0X55包尾packflag表示接收完成
				{
				  flag_usart_2=0;
				  packflag_2=1;
				}
				if(flag_usart_2==1)
				{
				  Rx_buff_2[USART_RX_STA_2&0X3FFF]=aRxBuffer_2[0] ;
					USART_RX_STA_2++;
					if(USART_RX_STA_2>(USART_REC_LEN_2-1))
					{flag_usart_2=0;//接收数据错误,重新开始接收	
						USART_RX_STA_2=0;
					}
				}			
	}
	else if(huart->Instance==USART3)                 //wifi
	{
	     if(aRxBuffer_3[0]==0x2a)   //*包头 开始接收
				{
					flag_usart_3=1;
				  packflag_3=0;
				}
				if(aRxBuffer_3[0]==0x23)      //#包尾packflag表示接收完成
				{
//					Rx_buff_1[USART_RX_STA_1&0X3FFF]=aRxBuffer_1[0] ;
//					USART_RX_STA_1++;
				  flag_usart_3=0;
				  packflag_3=1;
				}
				if(flag_usart_3==1)
				{
				  Rx_buff_3[USART_RX_STA_3&0X3FFF]=aRxBuffer_3[0] ;
					USART_RX_STA_3++;
					if(USART_RX_STA_3>(USART_REC_LEN_3-1))
					{flag_usart_3=0;//接收数据错误,重新开始接收	
				   USART_RX_STA_3=0;
					}			
			}
	}
}

void USART1_IRQHandler(void)                	
{ 
	u32 timeout=0;
#if SYSTEM_SUPPORT_OS	 	//使用OS
	OSIntEnter();    
#endif
	
	HAL_UART_IRQHandler(&huart1);	//调用HAL库中断处理公用函数
	
	timeout=0;
    while (HAL_UART_GetState(&huart1) != HAL_UART_STATE_READY)//等待就绪
	{
	 timeout++;////超时处理
     if(timeout>HAL_MAX_DELAY) break;		
	}
     
	timeout=0;
	while(HAL_UART_Receive_IT(&huart1, (u8 *)aRxBuffer_1, RXBUFFERSIZE) != HAL_OK)//一次处理完成之后，重新开启中断并设置RxXferCount为1
	{
	 timeout++; //超时处理
	 if(timeout>HAL_MAX_DELAY) break;	
	}
#if SYSTEM_SUPPORT_OS	 	//使用OS
	OSIntExit();  											 
#endif
} 

void USART2_IRQHandler(void)                	
{ 
	u32 timeout=0;
#if SYSTEM_SUPPORT_OS	 	//使用OS
	OSIntEnter();    
#endif
	
	HAL_UART_IRQHandler(&huart2);	//调用HAL库中断处理公用函数
	
	timeout=0;
    while (HAL_UART_GetState(&huart2) != HAL_UART_STATE_READY)//等待就绪
	{
	 timeout++;////超时处理
     if(timeout>HAL_MAX_DELAY) break;		
	}
     
	timeout=0;
	while(HAL_UART_Receive_IT(&huart2, (u8 *)aRxBuffer_2, RXBUFFERSIZE) != HAL_OK)//一次处理完成之后，重新开启中断并设置RxXferCount为1
	{
	 timeout++; //超时处理
	 if(timeout>HAL_MAX_DELAY) break;	
	}
#if SYSTEM_SUPPORT_OS	 	//使用OS
	OSIntExit();  											 
#endif
} 

void USART3_IRQHandler(void)                	
{ 
	u32 timeout=0;
#if SYSTEM_SUPPORT_OS	 	//使用OS
	OSIntEnter();    
#endif
	
	HAL_UART_IRQHandler(&huart3);	//调用HAL库中断处理公用函数
	
	timeout=0;
    while (HAL_UART_GetState(&huart3) != HAL_UART_STATE_READY)//等待就绪
	{
	 timeout++;////超时处理
     if(timeout>HAL_MAX_DELAY) break;		
	}
     
	timeout=0;
	while(HAL_UART_Receive_IT(&huart3, (u8 *)aRxBuffer_3, RXBUFFERSIZE) != HAL_OK)//一次处理完成之后，重新开启中断并设置RxXferCount为1
	{
	 timeout++; //超时处理
	 if(timeout>HAL_MAX_DELAY) break;	
	}
#if SYSTEM_SUPPORT_OS	 	//使用OS
	OSIntExit();  											 
#endif
} 	

void Uart_test(void)            //串口1测试子函数
{	
   	  if(packflag_2==1)            //串口缓存数据标志位
		{					   
			len=USART_RX_STA_2&0x3fff;//得到此次接收到的数据长度
			printf("\r\nthe news is:\r\n");
			HAL_UART_Transmit(&huart2,(uint8_t*)Rx_buff_2,len,1000);	//发送接收到的数据
			while(__HAL_UART_GET_FLAG(&huart2,UART_FLAG_TC)!=SET);		//等待发送结束
			printf("\r\n\r\n");//插入换行
			packflag_2=0;                                              //
			USART_RX_STA_2=0; 
		}else
		{
			times++;
			if(times%200==0)printf("please input char \r\n");  
			delay_ms(10); 
    }
}

void Uart_Store(void)                 //转存函数用Rx_buff_22来保存完好的地图
{
	static u16 i=0;                       //静态变量。。。可能有问题。。。。
 if(packflag_3==1)
 {
  len=USART_RX_STA_3&0x3fff;
	for(i=0;i<=len;i++)
	 {
	  Rx_buff_33[i]=Rx_buff_3[i];
	 }
	 packflag_3=0;
	 USART_RX_STA_3=0;
	 n=(Rx_buff_33[5]-'0')*10+(Rx_buff_33[6]-'0');
	 Command_State=Analyse_State;
 }
}	

void Uart_Analyse(void)
{
	 static int i=0;
	 static int j=0;
	 Track_buff=(int **)malloc(n*sizeof(int*));
	 for(i=0;i<n;i++)
	 {
	 Track_buff[i]=(int *)malloc(6*sizeof(int));//每6个为一组RFID信息
	 } 
   for(i=0;i<n;i++)
	 {
	   for(j=0;j<6;j++)
		 {
		  Track_buff[i][j]=Rx_buff_33[i*6+7+j];
		 }
	 }
}

