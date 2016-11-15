#ifndef _H_VARDEF_
#define _H_VARDEF_
#define uchar unsigned char
#define uint  unsigned int
#ifdef _C_MAIN_
u16 USART_RX_STA_1=0;       //���ձ�־λ
u16 USART_RX_STA_33=0;
u8 Rx_buff_1[USART_REC_LEN_1];   //�ݴ�����
u8 Rx_buff_33[USART_REC_LEN_3];  //�洢��ͼ�����飬ֻ���ڵ����յ������
int **Track_buff;
u8 aRxBuffer_1[RXBUFFERSIZE];//HAL��ʹ�õĴ���1���ջ���һ���ֽ�

u16 USART_RX_STA_2=0;       //���ձ�־λ
u8 Rx_buff_2[USART_REC_LEN_2];
u8 aRxBuffer_2[RXBUFFERSIZE];//HAL��ʹ�õĴ���2���ջ���

u16 USART_RX_STA_3=0;       //���ձ�־λ
u8 Rx_buff_3[USART_REC_LEN_3];
u8 aRxBuffer_3[RXBUFFERSIZE];//HAL��ʹ�õĴ���3���ջ���
/*����Ķ���*/
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;
TIM_HandleTypeDef htim13;
TIM_HandleTypeDef htim14;
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;
/*ȫ�ֱ���������*/
u8 len;                       //��������ĳ���
u16 times=0;                  //ͳ��ʱ��
u16 flag_usart_1=0;                   //�յ���ͷ��־λ
u16 packflag_1=0;                 //�յ���β��־λ.
u16 flag_usart_2=0;                   //�յ���ͷ��־λ
u16 packflag_2=0;                 //�յ���β��־λ.
u16 flag_usart_3=0;                   //�յ���ͷ��־λ
u16 packflag_3=0;                 //�յ���β��־λ.
u16 tim13_val;                //���ƶ�ʱ��13���Ƶ��
u16 tim14_val;                //���ƶ�ʱ��14���Ƶ��
u16 n=0;
uchar ptr[6];                 //��ʾ�õ�����
uint Temp=0;                   //ADC���󱣴�ֵ
uchar shuzi[]={"0123456789.v"};   
uint16_t uhADCxConvertedValue2[100];  //��ȡ��ADC�Ĳ���ֵ
uint16_t a=0;                         //ͨ��ADC_Average������ƽ����õ���ֵ
/*С���������пط��͵�����*/
u8 Obj[3]={'O','B','J'};
u8 Tra[3]={'T','R','A'};
u8 Tsk[3]={'T','S','K'};
u8 Loc[3]={'L','O','C'};
u8 Fw[2]={'f','w'};
u8 Bk[2]={'b','k'};
u8 St[2]={'s','t'};
u8 Rk[2]={'r','k'};                
u8 Id[3]={'0','1','2'};             //Ԥ���ID��
u8 Read_Id[3]={'0','0','0'};        //�����EEPROM�����ĳ���ID��
u8 Read_Rfid[4]={'0','0','0','0'};      //����RFID�����Ŀ�����Ϣ
u8 Read_cmd[11]={0xaa,0x09,0x20,0x00,0x00,0x00,0x00,0x03,0x00,0x02,0x55};
u8 Find_cmd[4]={0xaa,0x02,0x10,0x55};
u8 Stop_cmd[4]={0xaa,0x02,0x12,0x55};
u8 data_rec_flag=1;
enum
{
 Wait_State,                      //�ȴ��п�����
 Read_State,                      //��ȡeepromֵ�����ҷ���ID���п�
 Push_State,                      //���ݶ��㣬����������Ϣ���п�
 Analyse_State,                   //������·��״̬
 Run_Ahead_State,                        //�������·��ʼѭ����״̬
 Run_Back_State,
 Run_Ruku_State,
 Store_State,
 Stop_State
}Command_State=Analyse_State;

enum
{
 Left_90,                         //��⵽��תRFID
 Right_90,                        //��⵽��תRFID
 Run,                            //ֱ�ߵ�RFID
 Setup,
 Arrive
}Motor_Status=Setup;
#else
extern u16 USART_RX_STA_1;       //���ձ�־λ
extern u16 USART_RX_STA_22;
extern u8 Rx_buff_1[USART_REC_LEN_1];
extern u8 Rx_buff_33[USART_REC_LEN_3];
extern int **Track_buff;
extern u8 aRxBuffer_1[RXBUFFERSIZE];//HAL��USART����Buffer

extern u16 USART_RX_STA_2;       //���ձ�־λ
extern u8 Rx_buff_2[USART_REC_LEN_2];
extern u8 aRxBuffer_2[RXBUFFERSIZE];//HAL��USART����Buffer

extern u16 USART_RX_STA_3;       //���ձ�־λ
extern u8 Rx_buff_3[USART_REC_LEN_3];
extern u8 aRxBuffer_3[RXBUFFERSIZE];//HAL��USART����Buffer

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern TIM_HandleTypeDef htim13;
extern TIM_HandleTypeDef htim14;
extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;
extern u8 len;                       //��������ĳ���
extern u16 times;
extern u16 flag_usart_1;
extern u16 n;
extern u16 packflag_1;
extern u16 flag_usart_2;                   //�յ���ͷ��־λ
extern u16 packflag_2;                 //�յ���β��־λ.
extern u16 flag_usart_3;                   //�յ���ͷ��־λ
extern u16 packflag_3;                 //�յ���β��־λ.
extern u16 tim13_val;
extern u16 tim14_val;
extern uchar ptr[6];                 //��ʾ�õ�����
extern uint Temp;                //ADC���󱣴�ֵ
extern vu32 ADC_ConvertedValue;      //ADC�����ֵ
extern uchar shuzi[];
extern uint16_t uhADCxConvertedValue2[100];
extern u8 Obj[3];
extern u8 Tra[3];
extern u8 Tsk[3];
extern u8 Loc[3];
extern u8 St[2];
extern u8 Rk[2];
extern u8 Fh[2];
extern u8 Yh[2];
extern u8 Id[3];
extern u8 Read_Id[3];
extern uint16_t a;
extern u8 Read_Rfid[4];
extern u8 Read_cmd[11];
extern u8 Find_cmd[4];
extern u8 Stop_cmd[4];
extern u8 data_rec_flag;
extern enum
{
 Wait_State,
 Read_State,
 Push_State,
 Analyse_State,
 Run_Ahead_State,
 Run_Back_State,
 Run_Ruku_State,
 Store_State,
 Stop_State
}Command_State;

extern enum
{
 Left_90,
 Right_90,
 Run,
 Setup,
 Arrive
}Motor_Status;

#endif
#endif
