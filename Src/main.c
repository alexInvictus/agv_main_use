/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  *�ļ�����SMT��AGVС������������
	 ���ߣ�alex����li
	 ʵ�ֹ��ܣ�
	          1.ʵ��PWM���Ĳ���.С���ĵ���Ŀ���
						2.����λ��ͨ��Э����ƶ�
						3.���Ӵ���1����ͨ�ŵĹ��ܣ�������λ��ͨ��
						4.���24C02�����������eeprom���ݵĶ�д����
						5.��ɳ�����������������ʵʱ��������ֵ����һ��ģ��iic�����á�
						6.�ӳٵĿ����ֲ������ʵ��us�����ӳ١�
						7.�������ܵı�д�Լ����ơ�
						8.�ض���printf������ʵ�ִ���1ͨ��printf���͡�
						9.������ƾ�ȷ��������ռ�ձȷ�ʽ���� 10%-90%ռ�ձ���Ч����������ռ�ձȱ���ٶȱ�����(50-450.460��0�������ֹͣ)
            10.��ײ����ѭ�������д�롣ʵ�ֿ��ơ�
						11.����2���Զ�ȡRFIDд�����Ϣ�� ������������
	����֤��
	          1.wifiģ���޸�����Ϊclient��ȥ�������ӵ��Ե����硣
						2.������ģ��ⶨ���롣
						3.������ϸ�ڵ���ȶ��
	*     
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#define _C_MAIN_
#include "all.h"
/* printff�ض������ض��򴮿�1 ---------------------------------------------------------*/
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
  delay_init(180);                                       //΢�뼶���ݵ�����
  /* Initialize all configured peripherals */
  MX_GPIO_Init();                                        //GPIO�ĳ�ʼ������
  MX_DMA_Init();                                         //DMAͨ��������
  MX_USART2_UART_Init();                                 //����2������  for RFID��дģ��
  MX_USART3_UART_Init();                                 //����3������  for wifiģ��
  MX_TIM13_Init();                                       //��ʱ��13��������PWM��
  MX_TIM14_Init();                                       //��ʱ��14��������PWM��
  MX_ADC1_Init();                                        //ADC��ʼ������
  IIC_Init_2();                                          //ģ��iic for wave��ʼ��
	IIC_Init();                                            //ģ��iic for 24c02��ʼ��
  /* Initialize interrupts */
  MX_NVIC_Init();                                        //�ж����ȼ�������

  /* USER CODE BEGIN WHILE */
  while (1)
  {
  switch(Command_State)
	{
		case Read_State:                                     //��ȡ״̬  ��ģʽ�¶�ȡeeprom�����С��ID��(ִֻ��һ��)
			                                                                                                                                                                                                                                                                                                                                                                                              
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
	 
		case Wait_State:                                    //�ȴ�����״̬  (������ͣ����ж�case)
			    if(packflag_3==1)
					{
					 if((Rx_buff_3[4]=='f')&&(Rx_buff_3[5]=='w'))
					 {
						 Command_State=Run_Ahead_State;            //��ʼλ���յ�goǰ��ģʽ
					 }
					 else if((Rx_buff_3[4]=='b')&&(Rx_buff_3[5]=='k'))
					 {
						 Command_State=Run_Back_State;             //��ʼλ���յ�rkǰ��ģʽ
					 }
					  else if((Rx_buff_3[4]=='r')&&(Rx_buff_3[5]=='k'))
					 {
						 Command_State=Run_Ruku_State;             //��ʼλ���յ�rkǰ��ģʽ
					 }
					   packflag_3=0;
					   USART_RX_STA_3=0;
					}
				
					     break;
	  
		case Store_State:                                                        //�ȴ���ͼ��Ϣ��������״̬ �����ͼ��
			   
		      Uart_Store();                                                      //�����ͼ��Ϣ��Rx_buff_11
		     
		      
		           break;
		
    case Analyse_State:
		       Uart_Analyse();     						 //������ͼ�ö�ά��̬����ȥ�洢��ͼ��ֵ					 
			    if(Key_Start==1)
				{
					HAL_UART_Transmit(&huart3,(u8*)Tsk,4,1000);                        //��ɷ������°�ť������ָ����пر�ʾ��������
					HAL_UART_Transmit(&huart3,(u8*)Fw,3,1000);
		      Command_State=Wait_State;
	      }
				  if(Key_Stop==1)
				{
					HAL_UART_Transmit(&huart3,(u8*)Tsk,4,1000);                        //��ɷ������°�ť������ָ����пر�ʾ��������
					HAL_UART_Transmit(&huart3,(u8*)Bk,3,1000);
		      Command_State=Wait_State;
	      }	
         if((Rx_buff_33[4]=='w')&&(Rx_buff_33[5]=='t'))
					{
						 Command_State=Run_Wt_State;                                     //ֱ���ж��Ƿ�ȥȡ�ϵ㡣�յ�ȥȡ�ϵ��ͼȥȡ�ϵ�
					}
					     break;
   				
	  case Run_Ahead_State:                                                    //�������ͼ��������ǰѭ����״̬
			   
		       Motor_Ahead();

		           break;
		case Run_Wt_State:
			   
		      Motor_Ahead_Wait();
		
		           break;
		case Run_Back_State:                                                     //�����յ�ʱ���л������ѭ����״̬
			    
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
