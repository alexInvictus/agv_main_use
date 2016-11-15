#include "all.h"

void Motor_Ahead_Wait(void)
{
  switch(Motor_Status)
	{
	  case Setup:
			  tim13_val=20;
		    tim14_val=20;
		    __HAL_TIM_SET_COMPARE(&htim13,TIM_CHANNEL_1,tim13_val);
        __HAL_TIM_SET_COMPARE(&htim14,TIM_CHANNEL_1,tim14_val);
		    Motor_Status=Run;
		    break;
		
		case Run:
              Find_Rfid();			
			        Ahead_Trailing();
		    break;
				
		case Arrive:
			   tim13_val=0;
		     tim14_val=0;
			   __HAL_TIM_SET_COMPARE(&htim13,TIM_CHANNEL_1,tim13_val);
         __HAL_TIM_SET_COMPARE(&htim14,TIM_CHANNEL_1,tim14_val);//����ռ�ձȵķ�ʽ���ݶ�Ϊ0ʱ���ǲ���
		     Voltage_Test();
		     Command_State=Store_State;                 //����ȴ����յ�ͼ���Ҵ��ͼ��״̬
		     Motor_Status=Setup;
		     break;
		
		default:
        
		     break;			
	}
}

void Motor_Ahead(void)
{
  switch(Motor_Status)
	{
	  case Setup:
			  tim13_val=20;
		    tim14_val=20;
		    __HAL_TIM_SET_COMPARE(&htim13,TIM_CHANNEL_1,tim13_val);
        __HAL_TIM_SET_COMPARE(&htim14,TIM_CHANNEL_1,tim14_val);
		    Motor_Status=Run;
		    break;
		
		case Run:
			       	Find_Rfid();		       
			        Ahead_Trailing();			
		    break;
		
		case Left_90:
			       tim13_val=0;
		         tim14_val=150;
		         __HAL_TIM_SET_COMPARE(&htim13,TIM_CHANNEL_1,tim13_val);
             __HAL_TIM_SET_COMPARE(&htim14,TIM_CHANNEL_1,tim14_val);
		         delay_ms(Turn_time);
		         tim13_val=0;
						 tim14_val=0;
						 __HAL_TIM_SET_COMPARE(&htim13,TIM_CHANNEL_1,tim13_val);
						 __HAL_TIM_SET_COMPARE(&htim14,TIM_CHANNEL_1,tim14_val);
		         Motor_Status=Setup;
		    break;
	  
		case Right_90:
			       tim13_val=150;
		         tim14_val=0;
		         __HAL_TIM_SET_COMPARE(&htim13,TIM_CHANNEL_1,tim13_val);
             __HAL_TIM_SET_COMPARE(&htim14,TIM_CHANNEL_1,tim14_val);
		         delay_ms(Turn_time);
		         tim13_val=0;
						 tim14_val=0;
						 __HAL_TIM_SET_COMPARE(&htim13,TIM_CHANNEL_1,tim13_val);
						 __HAL_TIM_SET_COMPARE(&htim14,TIM_CHANNEL_1,tim14_val);
		         Motor_Status=Setup;		
		    break;
		
		case Arrive:
			   tim13_val=0;
				 tim14_val=0;
				 __HAL_TIM_SET_COMPARE(&htim13,TIM_CHANNEL_1,tim13_val);
				 __HAL_TIM_SET_COMPARE(&htim14,TIM_CHANNEL_1,tim14_val);
		     Voltage_Test();
		     Command_State=Store_State;
		     Motor_Status=Setup;
		    break;
				
		default:
        break;			
	}
}

void Motor_Back(void)
{
  switch(Motor_Status)
	{
	  case Setup:
			  HAL_TIM_PWM_Start(&htim13, TIM_CHANNEL_1);
		    HAL_TIM_PWM_Start(&htim14, TIM_CHANNEL_1);
		    Motor_Status=Run;
		    break;
		
		case Run:
			       	Find_Rfid();	       
			        Back_Trailing();
			
		    break;
		
		case Left_90:
			       tim13_val=0;
		         tim14_val=150;
		         __HAL_TIM_SET_COMPARE(&htim13,TIM_CHANNEL_1,tim13_val);
             __HAL_TIM_SET_COMPARE(&htim14,TIM_CHANNEL_1,tim14_val);
		         delay_ms(Turn_time);
		         tim13_val=0;
						 tim14_val=0;
						 __HAL_TIM_SET_COMPARE(&htim13,TIM_CHANNEL_1,tim13_val);
						 __HAL_TIM_SET_COMPARE(&htim14,TIM_CHANNEL_1,tim14_val);
		         Motor_Status=Setup;	
		    break;
	  
		case Right_90:
			       tim13_val=150;
		         tim14_val=0;
		         __HAL_TIM_SET_COMPARE(&htim13,TIM_CHANNEL_1,tim13_val);
             __HAL_TIM_SET_COMPARE(&htim14,TIM_CHANNEL_1,tim14_val);
		         delay_ms(Turn_time);
		         tim13_val=0;
						 tim14_val=0;
						 __HAL_TIM_SET_COMPARE(&htim13,TIM_CHANNEL_1,tim13_val);
						 __HAL_TIM_SET_COMPARE(&htim14,TIM_CHANNEL_1,tim14_val);
		         Motor_Status=Setup;			
		    break;
		case Arrive:
			   tim13_val=0;
				 tim14_val=0;
				 __HAL_TIM_SET_COMPARE(&htim13,TIM_CHANNEL_1,tim13_val);
				 __HAL_TIM_SET_COMPARE(&htim14,TIM_CHANNEL_1,tim14_val);
		     Voltage_Test();
		     Command_State=Store_State;
		     Motor_Status=Setup;
		    break;			
		default:
        break;			
	}
}

void Motor_Ruku(void)
{
  switch(Motor_Status)
	{
	  case Setup:
			  HAL_TIM_PWM_Start(&htim13, TIM_CHANNEL_1);
		    HAL_TIM_PWM_Start(&htim14, TIM_CHANNEL_1);
		    Motor_Status=Run;
		    break;
		
		case Run:
			       	Find_Rfid();             //Ψһһ�㲻ͬ�������һ��RFID����⡣       
			        Back_Trailing();
			
		    break;
		
		case Left_90:
			       tim13_val=0;
		         tim14_val=150;
		         __HAL_TIM_SET_COMPARE(&htim13,TIM_CHANNEL_1,tim13_val);
             __HAL_TIM_SET_COMPARE(&htim14,TIM_CHANNEL_1,tim14_val);
		         delay_ms(Turn_time);
		         tim13_val=0;
						 tim14_val=0;
						 __HAL_TIM_SET_COMPARE(&htim13,TIM_CHANNEL_1,tim13_val);
						 __HAL_TIM_SET_COMPARE(&htim14,TIM_CHANNEL_1,tim14_val);
		         Motor_Status=Setup;				
		    break;
	  
		case Right_90:
			       tim13_val=0;
		         tim14_val=150;
		         __HAL_TIM_SET_COMPARE(&htim13,TIM_CHANNEL_1,tim13_val);
             __HAL_TIM_SET_COMPARE(&htim14,TIM_CHANNEL_1,tim14_val);
		         delay_ms(Turn_time);
		         tim13_val=0;
						 tim14_val=0;
						 __HAL_TIM_SET_COMPARE(&htim13,TIM_CHANNEL_1,tim13_val);
						 __HAL_TIM_SET_COMPARE(&htim14,TIM_CHANNEL_1,tim14_val);
		         Motor_Status=Setup;			
		    break;
		case Arrive:
			   tim13_val=0;
				 tim14_val=0;
				 __HAL_TIM_SET_COMPARE(&htim13,TIM_CHANNEL_1,tim13_val);
				 __HAL_TIM_SET_COMPARE(&htim14,TIM_CHANNEL_1,tim14_val);
		     Voltage_Test();
		     Command_State=Store_State;         //�ﵽ��ʼ�㣬���뻺���ͼ��״̬��
		     Motor_Status=Setup;
		    break;
		default:
        break;			
	}
}

void Ahead_Trailing(void)
{
	  if((Ahead_Senor_1==1)&&(Ahead_Senor_2==1)&&(Ahead_Senor_3==0)&&(Ahead_Senor_4==1)&&(Ahead_Senor_5==1))
		{
		 	 tim13_val=20;
			 tim14_val=20;
			 __HAL_TIM_SET_COMPARE(&htim13,TIM_CHANNEL_1,tim13_val);
			 __HAL_TIM_SET_COMPARE(&htim14,TIM_CHANNEL_1,tim14_val);//ֱ��
		}
		else if((Ahead_Senor_1==1)&&(Ahead_Senor_2==0)&&(Ahead_Senor_4==1)&&(Ahead_Senor_5==1))
		{
		 	 tim13_val=30;
			 tim14_val=20;
			 __HAL_TIM_SET_COMPARE(&htim13,TIM_CHANNEL_1,tim13_val);
			 __HAL_TIM_SET_COMPARE(&htim14,TIM_CHANNEL_1,tim14_val);//��Сƫ
		}
		else if((Ahead_Senor_1==1)&&(Ahead_Senor_2==1)&&(Ahead_Senor_4==0)&&(Ahead_Senor_5==1))
		{
		 	 tim13_val=20;
			 tim14_val=30;
			 __HAL_TIM_SET_COMPARE(&htim13,TIM_CHANNEL_1,tim13_val);
			 __HAL_TIM_SET_COMPARE(&htim14,TIM_CHANNEL_1,tim14_val);//��Сƫ
		}
		else if((Ahead_Senor_1==0)&&(Ahead_Senor_2==1)&&(Ahead_Senor_4==1)&&(Ahead_Senor_5==1))
		{
		 	 tim13_val=40;
			 tim14_val=20;
			 __HAL_TIM_SET_COMPARE(&htim13,TIM_CHANNEL_1,tim13_val);
			 __HAL_TIM_SET_COMPARE(&htim14,TIM_CHANNEL_1,tim14_val);//�Ҵ�ƫ
		}
		else if((Ahead_Senor_1==1)&&(Ahead_Senor_2==1)&&(Ahead_Senor_4==1)&&(Ahead_Senor_5==0))
		{
		 	 tim13_val=20;
			 tim14_val=40;
			 __HAL_TIM_SET_COMPARE(&htim13,TIM_CHANNEL_1,tim13_val);
			 __HAL_TIM_SET_COMPARE(&htim14,TIM_CHANNEL_1,tim14_val);//���ƫ
		}
}

void Back_Trailing(void)
{
	  if((Back_Senor_1==1)&&(Back_Senor_2==1)&&(Back_Senor_3==0)&&(Back_Senor_4==1)&&(Back_Senor_5==1))
		{
		 	 tim13_val=20;
			 tim14_val=20;
			 __HAL_TIM_SET_COMPARE(&htim13,TIM_CHANNEL_1,tim13_val);
			 __HAL_TIM_SET_COMPARE(&htim14,TIM_CHANNEL_1,tim14_val);//ֱ��
		}
		else if((Back_Senor_1==1)&&(Back_Senor_2==0)&&(Back_Senor_4==1)&&(Back_Senor_5==1))
		{
		 	 tim13_val=30;
			 tim14_val=20;
			 __HAL_TIM_SET_COMPARE(&htim13,TIM_CHANNEL_1,tim13_val);
			 __HAL_TIM_SET_COMPARE(&htim14,TIM_CHANNEL_1,tim14_val);//��Сƫ
		}
		else if((Back_Senor_1==1)&&(Back_Senor_2==1)&&(Back_Senor_4==0)&&(Back_Senor_5==1))
		{
		 	 tim13_val=20;
			 tim14_val=30;
			 __HAL_TIM_SET_COMPARE(&htim13,TIM_CHANNEL_1,tim13_val);
			 __HAL_TIM_SET_COMPARE(&htim14,TIM_CHANNEL_1,tim14_val);//��Сƫ
		}
		else if((Back_Senor_1==0)&&(Back_Senor_2==1)&&(Back_Senor_4==1)&&(Back_Senor_5==1))
		{
		 	 tim13_val=40;
			 tim14_val=20;
			 __HAL_TIM_SET_COMPARE(&htim13,TIM_CHANNEL_1,tim13_val);
			 __HAL_TIM_SET_COMPARE(&htim14,TIM_CHANNEL_1,tim14_val);//�Ҵ�ƫ
		}
		else if((Back_Senor_1==1)&&(Back_Senor_2==1)&&(Back_Senor_4==1)&&(Back_Senor_5==0))
		{
		 	 tim13_val=20;
			 tim14_val=40;
			 __HAL_TIM_SET_COMPARE(&htim13,TIM_CHANNEL_1,tim13_val);
			 __HAL_TIM_SET_COMPARE(&htim14,TIM_CHANNEL_1,tim14_val);//���ƫ
		}  
}

void Answer(void)                                  //�ظ�����λ��RFID��Ϣ
{
                                                                                                                                                                                                                                                                                                                                             						
		HAL_UART_Transmit(&huart3,(u8*)Loc,3,1000);   //�ϱ�λ��
		HAL_UART_Transmit(&huart3,&Rx_buff_2[4],4,1000);
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
						else if((Rx_buff_2[1]==0x03)&&(Rx_buff_2[2]==0x12)&&(Rx_buff_2[3]==0x00))	//ֹͣ�ɹ�
						{
						 //HAL_UART_Transmit(&huart1,(u8*)Rx_buff_2,4,1000);
						   HAL_UART_Transmit(&huart2,(u8*)Read_cmd,11,1000);
						}
						else if(Rx_buff_2[1]==0x15)									//���ɹ�
						{
							//HAL_UART_Transmit(&huart1,&Rx_buff_2[4],4,1000);					
							Answer();
							Find_Rfid_Match();
							data_rec_flag=1;
						}
						else if((Rx_buff_2[1]==0x03)&&(Rx_buff_2[2]==0x20)&&(Rx_buff_2[3]==0x80))		//��ʧ��
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
			   Command_State=Stop_State;//Stop���´�����ֱ������ת��
				 Motor_Status=Left_90;
			}
			else if((Track_buff[i][4]=='p')&&(Track_buff[i][5]=='r'))
			{
			  Command_State=Stop_State;//Stop���´�����ֱ������ת��
				Motor_Status=Right_90;
			}
			else if((Track_buff[i][4]=='p')&&(Track_buff[i][5]=='f'))
			{
			  Command_State=Stop_State;//Stop���´�����ֱ������ת��
			}
			else if((Track_buff[i][4]=='n')&&(Track_buff[i][5]=='f'))
			{
			  Command_State=Stop_State;//Stop���´�������ǰѭ��״̬
				Motor_Status=Setup;//left
			}
			else if((Track_buff[i][4]=='n')&&(Track_buff[i][5]=='l'))
			{
			   Motor_Status=Left_90;//left
			}
			else if((Track_buff[i][4]=='n')&&(Track_buff[i][5]=='r'))
			{
			  Motor_Status=Right_90;//right
			}
			else if((Track_buff[i][4]=='n')&&(Track_buff[i][5]=='f'))
			{
			  //ǰ��
			}
      else if((Track_buff[i][4]=='p')&&(Track_buff[i][5]=='s'))
			{
			  Motor_Status=Arrive;//right
			}			
		}
	}	
}

void Stop(void)
{
		HAL_TIM_PWM_Stop(&htim13, TIM_CHANNEL_1);  //�ر�PWM
		HAL_TIM_PWM_Stop(&htim14, TIM_CHANNEL_1);  //�ر�ʹ�������ַ�ʽ������(�ر�ʹ�ܵ�����Զ���ס)
		Voltage_Test();
}
