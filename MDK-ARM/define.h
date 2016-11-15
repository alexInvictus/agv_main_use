#ifndef _H_DEFINE_
#define _H_DEFINE_
//=====================================================
//                ���ڽ��յ������С�Ķ���
//=====================================================
#define USART_REC_LEN_1       200          //�������ֽ�
#define USART_REC_LEN_2       200          //�������ֽ�
#define USART_REC_LEN_3       200          //�������ֽ�
#define RXBUFFERSIZE   1
//=====================================================
//                 ��������(�����)
//=====================================================
#define Key_Start     HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_2)
#define Key_Stop      HAL_GPIO_ReadPin(GPIOG, GPIO_PIN_3)
//=====================================================
//                 ���⴫���������Ŷ���
//=====================================================
#define Ahead_Senor_1   HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_0)
#define Ahead_Senor_2   HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1)
#define Ahead_Senor_3   HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3)
#define Ahead_Senor_4   HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_4)
#define Ahead_Senor_5   HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14)

#define Back_Senor_1   HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_2)
#define Back_Senor_2   HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_3)
#define Back_Senor_3   HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_4)
#define Back_Senor_4   HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_5)
#define Back_Senor_5   HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_6)
//=====================================================
//                 ADC��ַ
//=====================================================
#define ADC1_DR_Address    ((u32)0x4001244C)
#define LCD_CMD       (u32)0xf8000000 						//
#define LCD_DATE      (u32)0xfa000000 						//
//=====================================================
//                 128*64����ʾ�������׵�ַ
//=====================================================
#define Line1   0x83
#define Line5   0x83
#define Line2   0x92
#define Line3   0x89
#define Line4   0x98
//=====================================================
//                 ��ʾ��������4����
//=====================================================
#define CS_H HAL_GPIO_WritePin(GPIOH,GPIO_PIN_13,GPIO_PIN_SET) 			//RS=1   4PIN
#define CS_L HAL_GPIO_WritePin(GPIOH,GPIO_PIN_13,GPIO_PIN_RESET) 			//RS=0 

#define RW_H HAL_GPIO_WritePin(GPIOH,GPIO_PIN_14,GPIO_PIN_SET)  			//RW=1    5PIN
#define RW_L HAL_GPIO_WritePin(GPIOH,GPIO_PIN_14,GPIO_PIN_RESET)   			//RW = 0

#define CLK_H HAL_GPIO_WritePin(GPIOH,GPIO_PIN_15,GPIO_PIN_SET)  			//RW=1    5PIN
#define CLK_L HAL_GPIO_WritePin(GPIOH,GPIO_PIN_15,GPIO_PIN_RESET)   		//RW = 0

//#define PSB_H HAL_GPIO_WritePin(GPIOC,GPIO_PIN_5,GPIO_PIN_SET)  			//RW=1    5PIN
//#define PSB_L HAL_GPIO_WritePin(GPIOC,GPIO_PIN_5,GPIO_PIN_RESET)   		//RW = 0

#define RST_H HAL_GPIO_WritePin(GPIOI,GPIO_PIN_8,GPIO_PIN_SET)  			//RW=1    5PIN
#define RST_L HAL_GPIO_WritePin(GPIOI,GPIO_PIN_8,GPIO_PIN_RESET)     		//RW = 0
//=====================================================
//                 ת���ӳٵ�ʱ��
//=====================================================
#define Turn_time   6500        //6500����

//=====================================================
//                 ��������
//=====================================================
void Error_Handler(void);
void MX_GPIO_Init(void);                        //gpio�ڳ�ʼ������ 
void MX_TIM13_Init(void);                       //��ʱ��13��ʼ�����ò���PWM��
void MX_TIM14_Init(void);                       //��ʱ��14��ʼ�����ò���PWM��
void SystemClock_Config(void);                  //ʱ�ӵ�����
void MX_USART1_UART_Init(void);                 //����1��ʼ��
void MX_USART2_UART_Init(void);                 //����2��ʼ��
void MX_USART3_UART_Init(void);                 //����3��ʼ��
void MX_ADC1_Init(void);
void MX_NVIC_Init(void);
void MX_DMA_Init(void);
void Uart_test(void);                           //���ڲ��Գ���
void Uart_Store(void);                           //����ת��
void Uart_Analyse(void);                        //������� ������浽��Ӧ�Ķ�ά����
void Eeprom_Read(void);                         //��ȡeeprom����ĳ���
void Send_Id(void);                             //����id�Ÿ��п�ϵͳ
/*����Ĳ�������غ���*/
void Motor_Ahead_Wait(void);                    //ǰ����ȡ�ϵ�ģʽ
void Motor_Ahead(void);                         //ǰ��ģʽ
void Motor_Back(void);                          //����ģʽ
void Motor_Ruku(void);                       //����ģʽ--ֱ��ȥ��ʼ��
void Ahead_Trailing(void);                      //ǰ��ѭ����
void Back_Trailing(void);                       //����ѭ����
void Answer(void);                              //�ҵ�֮�󱨸��п�
void Find_Rfid(void);                           //Ѱ��RFID��
void Find_Rfid_Match(void);                           //ƥ��RFID�ĺ���
void Stop(void);
/*��ʾ���Ĳ����ĺ���*/
void LCD_init(void);
void Display(u8 addr,u8 *hz);
void LCD_Write(u32 cmd,u8 ddata);
void Voltage_Test(void); 
uint16_t ADC_Average(uint16_t *buff,uint16_t num,uint16_t threshold);
#endif


