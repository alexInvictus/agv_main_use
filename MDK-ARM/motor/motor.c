#ifndef _C_MOTOR_
#define _C_MOTOR_
#include "all.h"

void Motor_Ahead_Wait(void)
{
  switch(Motor_Status)
	{
	  case Setup:
		   	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);      //暂定前进
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);  
		    Set_Motor(430,430);
		    printf("yes");
		    delay_ms(1000);
//		    Motor_Status=Run;
		    break;
		
		case Run:
         Find_Rfid();			
			   Ahead_Trailing();
		    break;
				
		case Arrive:
			   Set_Motor(460,460);//控制占空比的方式。暂定为0时就是不走
		     Voltage_Test();
		     free_array();
		     Command_State=Store_State;                 //进入等待接收地图并且存地图的状态
		     Motor_Status=Setup;
		     break;
		
		default:
        
		     break;			
	}
}

void Motor_Ahead(void)                                    //向前循迹
{
  switch(Motor_Status)
	{
	  case Setup:
			  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);      //暂定前进
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_RESET);
			  Set_Motor(430,430);
		    Motor_Status=Run;
		    break;
		
		case Run:
			       	Find_Rfid();		       
			        Ahead_Trailing();			
		    break;
		
		case Left_90:
			       Set_Motor(0,150);
		         delay_ms(Turn_time);
		         Set_Motor(0,0);
		         Motor_Status=Setup;
		    break;
	  
		case Right_90:
			       Set_Motor(150,0);
		         delay_ms(Turn_time);
		         Set_Motor(0,0);
		         Motor_Status=Setup;		
		    break;
		
		case Arrive:
						 Set_Motor(460,460);
						 Voltage_Test();
		         free_array();
		         HAL_UART_Transmit(&huart3,(u8*)Tsk,4,1000);                        
					   HAL_UART_Transmit(&huart3,(u8*)Bm,3,1000);          //发送请求返回地图的指令
						 Command_State=Store_State;
						 Motor_Status=Setup;
		    break;
				
		default:
        break;			
	}
}

void Motor_Back(void)                                           //返回的循迹函数
{
  switch(Motor_Status)
	{
	  case Setup:
			  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);    //暂定反向
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
        Set_Motor(430,430);
		    Motor_Status=Run;
		    break;
		
		case Run:
			       	Find_Rfid();	       
			        Back_Trailing();
			
		    break;
		
		case Left_90:
			       Set_Motor(0,150);
		         delay_ms(Turn_time);
		         Set_Motor(0,0);
		         Motor_Status=Setup;	
		    break;
	  
		case Right_90:
			       Set_Motor(150,0);
		         delay_ms(Turn_time);
		         Set_Motor(0,0);
		         Motor_Status=Setup;			
		    break;
		case Arrive:
						 Set_Motor(460,460);
						 Voltage_Test();
		         free_array();
		         HAL_UART_Transmit(&huart3,(u8*)Tsk,4,1000);                        
					   HAL_UART_Transmit(&huart3,(u8*)Rm,3,1000);          //发送请求入库地图的指令
						 Command_State=Store_State;
						 Motor_Status=Setup;
		    break;			
		default:
        break;			
	}
}

void Motor_Ruku(void)                                     //入库的循迹函数
{
  switch(Motor_Status)
	{
	  case Setup:
			  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);     //暂定前进
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, GPIO_PIN_SET);
        Set_Motor(430,430);		    
		    Motor_Status=Run;
		    break;
		
		case Run:
			       	Find_Rfid();                    
			        Back_Trailing();
			
		    break;
		
		case Left_90:
			       Set_Motor(0,150);
		         delay_ms(Turn_time);
		         Set_Motor(0,0);
		         Motor_Status=Setup;				
		    break;
	  
		case Right_90:
			       Set_Motor(150,0);
		         delay_ms(Turn_time);
		         Set_Motor(0,0);
		         Motor_Status=Setup;			
		    break;
		case Arrive:
						 Set_Motor(460,460);
						 Voltage_Test();
		         free_array();
						 Command_State=Store_State;         //达到起始点，进入缓存地图的状态。
						 Motor_Status=Setup;
		    break;
		default:
        break;			
	}
}

void Ahead_Trailing(void)
{
	static int num=0,count1=0,count2=0;
	if((protect_ahead==0)||(protect_back==0))                     //检测安全触边
	{
		num++;
		if(num>2000)
		{
		 if((protect_ahead==0)||(protect_back)==0)
		 {
		    Set_Motor(460,460);//关闭
			  LED_ON;
		 }
		}
	}
	else
		{
			num=0;
		if((Ahead_Senor_1==1)&&(Ahead_Senor_2==1)&&(Ahead_Senor_3==1)&&(Ahead_Senor_4==1)&&(Ahead_Senor_5==1))
		{
		count1++;
			if(count1>TEST_TIM)
			{			 
				if((Ahead_Senor_1==1)&&(Ahead_Senor_2==1)&&(Ahead_Senor_3==0)&&(Ahead_Senor_4==1)&&(Ahead_Senor_5==1))
				{
					count2++;
					if(count2>TEST_TIM)
					{
				  if((Ahead_Senor_1==1)&&(Ahead_Senor_2==1)&&(Ahead_Senor_3==0)&&(Ahead_Senor_4==1)&&(Ahead_Senor_5==1))  //冲出轨道停止
				  {
					  Set_Motor(460,460);//关闭
					  LED_ON;
				  }
				  }
			  }
			}		
		}
	  if((Ahead_Senor_1==1)&&(Ahead_Senor_2==1)&&(Ahead_Senor_3==0)&&(Ahead_Senor_4==1)&&(Ahead_Senor_5==1))
		{
		 Set_Motor(20,20);//直行
		}
		else if((Ahead_Senor_1==1)&&(Ahead_Senor_2==0)&&(Ahead_Senor_4==1)&&(Ahead_Senor_5==1))
		{
		 	 Set_Motor(30,20);//右小偏
		}
		else if((Ahead_Senor_1==1)&&(Ahead_Senor_2==1)&&(Ahead_Senor_4==0)&&(Ahead_Senor_5==1))
		{
		 	Set_Motor(20,30);//左小偏
		}
		else if((Ahead_Senor_1==0)&&(Ahead_Senor_2==1)&&(Ahead_Senor_4==1)&&(Ahead_Senor_5==1))
		{
		 Set_Motor(40,20);;//右大偏
		}
		else if((Ahead_Senor_1==1)&&(Ahead_Senor_2==1)&&(Ahead_Senor_4==1)&&(Ahead_Senor_5==0))
		{
		Set_Motor(20,40);//左大偏
		}
}
}

void Back_Trailing(void)
{
	static int num=0,count1=0,count2=0;
	if((protect_ahead==0)||(protect_back==0))               //检测安全触边
	{
		num++;
		if(num>2000)
		{
		 if((protect_ahead==0)||(protect_back)==0)
		 {
		    Set_Motor(460,460);//关闭
			 LED_ON;
		 }
		}
	}
	else
		{
			num=0;
		if((Ahead_Senor_1==1)&&(Ahead_Senor_2==1)&&(Ahead_Senor_3==1)&&(Ahead_Senor_4==1)&&(Ahead_Senor_5==1))
		{
		count1++;
			if(count1>TEST_TIM)
			{			 
				if((Ahead_Senor_1==1)&&(Ahead_Senor_2==1)&&(Ahead_Senor_3==0)&&(Ahead_Senor_4==1)&&(Ahead_Senor_5==1))
				{
					count2++;
					if(count2>TEST_TIM)
					{
				  if((Ahead_Senor_1==1)&&(Ahead_Senor_2==1)&&(Ahead_Senor_3==0)&&(Ahead_Senor_4==1)&&(Ahead_Senor_5==1))     //冲出轨道停止
				  {
					  Set_Motor(0,0);//关闭
					  LED_ON;
				  }
				}
			}
			}
		
		}
	  if((Back_Senor_1==1)&&(Back_Senor_2==1)&&(Back_Senor_3==0)&&(Back_Senor_4==1)&&(Back_Senor_5==1))
		{
      Set_Motor(20,20);//直行
		}
		else if((Back_Senor_1==1)&&(Back_Senor_2==0)&&(Back_Senor_4==1)&&(Back_Senor_5==1))
		{
		 	Set_Motor(30,20);//右小偏
		}
		else if((Back_Senor_1==1)&&(Back_Senor_2==1)&&(Back_Senor_4==0)&&(Back_Senor_5==1))
		{
		 Set_Motor(20,30);//左小偏
		}
		else if((Back_Senor_1==0)&&(Back_Senor_2==1)&&(Back_Senor_4==1)&&(Back_Senor_5==1))
		{
		 	 Set_Motor(40,20);//右大偏
		}
		else if((Back_Senor_1==1)&&(Back_Senor_2==1)&&(Back_Senor_4==1)&&(Back_Senor_5==0))
		{
		 	 Set_Motor(20,40);//左大偏
		}  
}

}
void Answer(void)                                  //回复给上位机RFID信息
{                                                                                                                                                                                                                                                                                                                                            						
		HAL_UART_Transmit(&huart3,(u8*)Loc,4,1000);   //上报位置
		HAL_UART_Transmit(&huart3,&Rx_buff_2[4],4,1000);
	  HAL_UART_Transmit(&huart3,(u8*)GG,1,1000);
}
                                                                                                                                                               
void Find_Rfid(void)
{
		if(data_rec_flag==1)
			{
				HAL_UART_Transmit(&huart2,(u8*)Find_cmd,4,1000);
				data_rec_flag=0;
			}
			
			if(packflag_2==1)
					{
					  if((Rx_buff_2[1]==0x03)&&(Rx_buff_2[2]==0x10)&&(Rx_buff_2[3]==0x01))		
						{
							// HAL_UART_Transmit(&huart1,(u8*)Rx_buff_2,4,1000);							
						}
						else if((Rx_buff_2[1]==0x03)&&(Rx_buff_2[2]==0x12)&&(Rx_buff_2[3]==0x00))	  //停止成功
						{
						 //HAL_UART_Transmit(&huart1,(u8*)Rx_buff_2,4,1000);
						   HAL_UART_Transmit(&huart2,(u8*)Read_cmd,11,1000);
						}
						else if(Rx_buff_2[1]==0x15)									                                //读成功
						{
							//HAL_UART_Transmit(&huart1,&Rx_buff_2[4],4,1000);					
							Answer();
							Find_Rfid_Match();
							data_rec_flag=1;
						}
						else if((Rx_buff_2[1]==0x03)&&(Rx_buff_2[2]==0x20)&&(Rx_buff_2[3]==0x80))		//读失败
						{
							data_rec_flag=1;
						}
						else																				//
						{
							//HAL_UART_Transmit(&huart1,(u8*)Rx_buff_2,11,1000);
								HAL_UART_Transmit(&huart2,(u8*)Stop_cmd,4,1000);
						}							
						packflag_2=0;
					}			
}

void Find_Rfid_Match(void)
{
  static int i=0;
	  for(i=0;i<=n;i++)
	{
	  if((Track_buff[i][0]==Rx_buff_2[4])&&(Track_buff[i][1]==Rx_buff_2[5])&&(Track_buff[i][2]==Rx_buff_2[6])&&(Track_buff[i][3]==Rx_buff_2[7]))
		{
			if((Track_buff[i][4]=='p')&&(Track_buff[i][5]=='l'))
			{
			   Command_State=Stop_State;//Stop，下次启动直接向左转弯
				 Motor_Status=Left_90;
			}
			else if((Track_buff[i][4]=='p')&&(Track_buff[i][5]=='r'))
			{
			  Command_State=Stop_State;//Stop，下次启动直接向右转弯
				Motor_Status=Right_90;
			}
			else if((Track_buff[i][4]=='p')&&(Track_buff[i][5]=='f'))
			{
			  Command_State=Stop_State;      //Stop，下次启动向前循迹状态
			}
			else if((Track_buff[i][4]=='p')&&(Track_buff[i][5]=='s'))
			{
				Motor_Status=Arrive;           //达到地图终点
			}
			else if((Track_buff[i][4]=='n')&&(Track_buff[i][5]=='l'))
			{
			   Motor_Status=Left_90;         //no stop ,just turn left
			}
			else if((Track_buff[i][4]=='n')&&(Track_buff[i][5]=='r'))
			{
			  Motor_Status=Right_90;         //no stop ,just turn right
			}
			else if((Track_buff[i][4]=='n')&&(Track_buff[i][5]=='f'))
			{
			  //前进
			}
		}
	}	
}

void Stop(void)
{
		Set_Motor(460,460);//关闭
		Voltage_Test();
}

void Set_Motor(int left,int right)
{
    __HAL_TIM_SET_COMPARE(&htim13,TIM_CHANNEL_1,left);
		__HAL_TIM_SET_COMPARE(&htim14,TIM_CHANNEL_1,right);
}

void Set_Acc(int target)
{
	  int i=0;
	  for(i=target;i>50;i--)
	{
		__HAL_TIM_SET_COMPARE(&htim14,TIM_CHANNEL_1,i); 
    __HAL_TIM_SET_COMPARE(&htim13,TIM_CHANNEL_1,i);		
		HAL_Delay(8);
	}
}

void Set_Slowdown(int target)
{
    int i=0;
	  for(i=0;i<target;i++)
	{
		__HAL_TIM_SET_COMPARE(&htim14,TIM_CHANNEL_1,i);
    __HAL_TIM_SET_COMPARE(&htim13,TIM_CHANNEL_1,i);		
		HAL_Delay(8);
	}
}

#endif
