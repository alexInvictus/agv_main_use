/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *文件名：SMT线AGV小车的驱动程序
	 作者：alex——li
	 实现功能：
	          1.实现PWM波的产生.小车的电机的控制
						2.与上位机通信协议的制定
						3.增加串口1无线通信的功能，能与上位机通信
						4.完成24C02的驱动，完成eeprom数据的读写函数
						5.完成超声波的驱动，可以实时反馈距离值。另一个模拟iic的配置。
						6.延迟的库的移植，可以实现us级的延迟。
						7.主程序框架的编写以及完善。
						8.重定义printf函数，实现串口1通过printf发送。
						9.电机控制精确化。采用占空比方式控制 10%-90%占空比有效。其中随着占空比变大，速度变慢。(50-450.460和0电机都会停止)
            10.防撞条、循迹程序的写入。实现控制。
						11.串口2可以读取RFID写入的信息。 （加入主程序）
	待验证：
	          1.wifi模块修改配置为client，去主动连接电脑的网络。
						2.超声波模块测定距离。
						3.主程序细节的商榷。
	*     
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#define _C_MAIN_
#include "all.h"
/* printff重定向函数重定向串口1 ---------------------------------------------------------*/
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif 
PUTCHAR_PROTOTYPE
{
HAL_UART_Transmit(&huart3 , (uint8_t *)&ch, 1, 0xFFFF);
return ch;
}               
/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

int main(void)
{
  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();
  delay_init(180);                                       //微秒级数据的配置
  /* Initialize all configured peripherals */
  MX_GPIO_Init();                                        //GPIO的初始化配置
  MX_DMA_Init();                                         //DMA通道的配置
  MX_USART2_UART_Init();                                 //串口2的配置  for RFID读写模块
  MX_USART3_UART_Init();                                 //串口3的配置  for wifi模块
  MX_TIM13_Init();                                       //定时器13产生左轮PWM波
  MX_TIM14_Init();                                       //定时器14产生右轮PWM波
  MX_ADC1_Init();                                        //ADC初始化设置
  IIC_Init_2();                                          //模拟iic for wave初始化
	IIC_Init();                                            //模拟iic for 24c02初始化
  /* Initialize interrupts */
  MX_NVIC_Init();                                        //中断优先级的设置

  /* USER CODE BEGIN WHILE */
  while (1)
  {
  switch(Command_State)
	{
		case Read_State:                                     //读取状态  该模式下读取eeprom里面的小车ID号(只执行一次)
			                                                                                                                                                                                                                                                                                                                                                                                              
		           if(packflag_3==1)
							 {	                                   								  
								if((Rx_buff_3[4]=='o')&&(Rx_buff_3[5]=='k')) 
								{
									Command_State=Store_State;
								}
								packflag_3=0;
								USART_RX_STA_3=0;
							 }
		
							 break;
	 
		case Wait_State:                                    //等待命令状态  (所有暂停点的判断case)
			    if(packflag_3==1)
					{
					 if((Rx_buff_3[4]=='f')&&(Rx_buff_3[5]=='w'))
					 {
						 Command_State=Run_Ahead_State;            //起始位置收到go前进模式
					 }
					 else if((Rx_buff_3[4]=='b')&&(Rx_buff_3[5]=='k'))
					 {
						 Command_State=Run_Back_State;             //起始位置收到rk前进模式
					 }
					  else if((Rx_buff_3[4]=='r')&&(Rx_buff_3[5]=='k'))
					 {
						 Command_State=Run_Ruku_State;             //起始位置收到rk前进模式
					 }
					   packflag_3=0;
					   USART_RX_STA_3=0;
					}
				
					     break;
	  
		case Store_State:                                                        //等待地图信息并分析的状态 换存地图。
			   
		      Uart_Store();                                                      //保存地图信息到Rx_buff_11
		     
		      
		           break;
		
    case Analyse_State:
		       Uart_Analyse();     						 //分析地图用二维动态数组去存储地图的值					 
			    if(Key_Start==1)
				{
					HAL_UART_Transmit(&huart3,(u8*)Tsk,4,1000);                        //完成分析后按下按钮，发送指令给中控表示启动任务
					HAL_UART_Transmit(&huart3,(u8*)Fw,3,1000);
		      Command_State=Wait_State;
	      }
				  if(Key_Stop==1)
				{
					HAL_UART_Transmit(&huart3,(u8*)Tsk,4,1000);                        //完成分析后按下按钮，发送指令给中控表示启动任务
					HAL_UART_Transmit(&huart3,(u8*)Bk,3,1000);
		      Command_State=Wait_State;
	      }	
         if((Rx_buff_33[4]=='w')&&(Rx_buff_33[5]=='t'))
					{
						 Command_State=Run_Wt_State;                                     //直接判断是否去取料点。收到去取料点地图去取料点
					}
					     break;
   				
	  case Run_Ahead_State:                                                    //解析完地图，正常向前循迹的状态
			   
		       Motor_Ahead();

		           break;
		case Run_Wt_State:
			   
		      Motor_Ahead_Wait();
		
		           break;
		case Run_Back_State:                                                     //到达终点时，切换的向后循迹的状态
			    
		       Motor_Back(); 		      
		      
		           break;
		
		case Stop_State:
			            Stop();
		              Command_State=Wait_State;
		           break;
		
		case Run_Ruku_State:
			
			     Motor_Ruku();
		      
		           break;
		
		default:
			
		           break;      
		}
  }
			
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
