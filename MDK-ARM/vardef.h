#ifndef _H_VARDEF_
#define _H_VARDEF_
#define uchar unsigned char
#define uint  unsigned int
#ifdef _C_MAIN_
u16 USART_RX_STA_1=0;                 //接收标志位
u16 USART_RX_STA_33=0;                //缓存地图数组
u8 Rx_buff_1[USART_REC_LEN_1];        //暂存数组
u8 Rx_buff_33[USART_REC_LEN_3];       //存储地图的数组，只有在到达终点才清零
int **Track_buff;
u8 aRxBuffer_1[RXBUFFERSIZE];         //HAL库使用的串口1接收缓冲一个字节

u16 USART_RX_STA_2=0;                 //接收标志位
u8 Rx_buff_2[USART_REC_LEN_2];
u8 aRxBuffer_2[RXBUFFERSIZE];         //HAL库使用的串口2接收缓冲

u16 USART_RX_STA_3=0;                 //接收标志位
u8 Rx_buff_3[USART_REC_LEN_3];
u8 aRxBuffer_3[RXBUFFERSIZE];         //HAL库使用的串口3接收缓冲
/*句柄的定义*/
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;
TIM_HandleTypeDef htim13;
TIM_HandleTypeDef htim14;
ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;
/*全局变量的声明*/
u8 len;                               //反馈数组的长度
u16 times=0;                          //统计时间
u16 flag_usart_1=0;                   //收到包头标志位
u16 packflag_1=0;                     //收到包尾标志位.
u16 flag_usart_2=0;                   //收到包头标志位
u16 packflag_2=0;                     //收到包尾标志位.
u16 flag_usart_3=0;                   //收到包头标志位
u16 packflag_3=0;                     //收到包尾标志位.
int tim13_val;                        //控制定时器13输出频率
int tim14_val;                        //控制定时器14输出频率
u16 n=0;
uchar ptr[6];                         //显示用的数组
uint Temp=0;                          //通过ADC_Average函数求平均后得到的值
uchar shuzi[]={"0123456789.v"};   
uint16_t uhADCxConvertedValue2[100];  //存取的ADC的采样值
/*小车主动向中控发送的数据*/
u8 Obj[4]={'*','O','B','J'};
u8 Tra[4]={'*','T','R','A'};
u8 Tsk[4]={'*','T','S','K'};
u8 Loc[4]={'*','L','O','C'};
u8 Fw[3]={'f','w','#'};
u8 Bk[3]={'b','k','#'};
u8 Rk[3]={'r','k','#'};
u8 GG[1]={'#'};
u8 Rm[3]={'r','m','#'};
u8 Bm[3]={'b','m','#'};
u8 Id[3]={'0','1','2'};               //预存的ID号
u8 Read_Id[3]={'0','0','0'};          //保存从EEPROM读到的车的ID号
u8 Read_Rfid[4]={'0','0','0','0'};      //保存RFID读到的卡号信息
u8 Read_cmd[11]={0xaa,0x09,0x20,0x00,0x00,0x00,0x00,0x03,0x00,0x02,0x55};
u8 Find_cmd[4]={0xaa,0x02,0x10,0x55};
u8 Stop_cmd[4]={0xaa,0x02,0x12,0x55};
u8 data_rec_flag=1;
enum
{
 Wait_State,                          //等待中控命令
 Read_State,                          //读取eeprom值，并且发送ID给中控
 Push_State,                          //在暂定点，主动发送信息给中控
 Analyse_State,                       //分析道路的状态
 Run_Ahead_State,                     //分析完道路开始循迹的状态
 Run_Wt_State,
 Run_Back_State,
 Run_Ruku_State,
 Store_State,
 Stop_State
}Command_State=Read_State;

enum
{
 Left_90,                            //检测到左转RFID
 Right_90,                           //检测到右转RFID
 Run,                                //直走的RFID
 Setup,
 Arrive
}Motor_Status=Setup;
#else
extern u16 USART_RX_STA_1;           //接收标志位串口1 
extern u16 USART_RX_STA_22;
extern u8 Rx_buff_1[USART_REC_LEN_1];
extern u8 Rx_buff_33[USART_REC_LEN_3];
extern int **Track_buff;
extern u8 aRxBuffer_1[RXBUFFERSIZE]; //HAL库USART1接收Buffer

extern u16 USART_RX_STA_2;           //接收标志位串口2
extern u8 Rx_buff_2[USART_REC_LEN_2];
extern u8 aRxBuffer_2[RXBUFFERSIZE]; //HAL库USART2接收Buffer

extern u16 USART_RX_STA_3;           //接收标志位串口3
extern u8 Rx_buff_3[USART_REC_LEN_3];
extern u8 aRxBuffer_3[RXBUFFERSIZE]; //HAL库USART接收Buffer

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern TIM_HandleTypeDef htim13;
extern TIM_HandleTypeDef htim14;
extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;
extern u8 len;                       //反馈数组的长度
extern u16 times;
extern u16 flag_usart_1;
extern u16 n;
extern u16 packflag_1;
extern u16 flag_usart_2;             //收到包头标志位
extern u16 packflag_2;               //收到包尾标志位.
extern u16 flag_usart_3;             //收到包头标志位
extern u16 packflag_3;               //收到包尾标志位.
extern int tim13_val;
extern int tim14_val;
extern uchar ptr[6];                 //显示用的数组
extern uint Temp;                    //ADC检测后保存值
extern vu32 ADC_ConvertedValue;      //ADC传输的值
extern uchar shuzi[];
extern uint16_t uhADCxConvertedValue2[100];
extern u8 Obj[3];
extern u8 Tra[3];
extern u8 Tsk[3];
extern u8 Loc[3];
extern u8 Rk[2];
extern u8 Fw[2];
extern u8 Bk[2];
extern u8 GG[1];
extern u8 Rm[3];
extern u8 Bm[3];
extern u8 Id[3];
extern u8 Read_Id[3];
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
 Run_Wt_State,
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

