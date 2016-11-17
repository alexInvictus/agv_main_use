#ifndef _C_ADCDMA_
#define _C_ADCDMA_
#include "all.h"
/** NVIC Configuration
*/
void MX_NVIC_Init(void)
{
  /* ADC_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(ADC_IRQn, 1, 0);
  HAL_NVIC_EnableIRQ(ADC_IRQn);
  /* USART1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(USART1_IRQn, 3, 0);
  HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USART2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(USART2_IRQn, 4, 0);
  HAL_NVIC_EnableIRQ(USART2_IRQn);
  /* USART3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(USART3_IRQn, 5, 0);
  HAL_NVIC_EnableIRQ(USART3_IRQn);
  /* DMA2_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 2, 0);
  HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);
	
	HAL_TIM_PWM_Start(&htim14, TIM_CHANNEL_1);                                                    //¿ªÆô×óÂÖPWM²¨
	HAL_TIM_PWM_Start(&htim14, TIM_CHANNEL_1);                                                    //¿ªÆôÓÒÂÖPWM²¨
	if(HAL_ADC_Start_DMA(&hadc1,(uint32_t*)&uhADCxConvertedValue2,100)!=HAL_OK)Error_Handler();   //¿ªÆôADC¡ª¡ªDMA´«ÊäÍ¨µÀ	
}

/* ADC1 init function */
void MX_ADC1_Init(void)
{

  ADC_ChannelConfTypeDef sConfig;

    /**Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion) 
    */
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = DISABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 1;
  hadc1.Init.DMAContinuousRequests = ENABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

    /**Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time. 
    */
  sConfig.Channel = ADC_CHANNEL_10;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
}
/** 
  * Enable DMA controller clock
  */
void MX_DMA_Init(void) 
{
  /* DMA controller clock enable */
  __HAL_RCC_DMA2_CLK_ENABLE();

}

uint16_t ADC_Average(uint16_t *buff,uint16_t num,uint16_t threshold)
{
   uint32_t sigma=0;
	 uint16_t i=0,j=0,temp=0;
	 uint16_t temp_buff[num];
	for(i=0;i<num;i++)temp_buff[i]=buff[i];
	for(i=0;i<(num-1);i++)  
	{
     for(j=0;j<(num-1);j++)
		{
     if(temp_buff[j]<temp_buff[j+1])
			  {
        temp=temp_buff[j];
        temp_buff[j]=temp_buff[j+1];
	      temp_buff[j+1]=temp;
	}
	}
	}
   for(i=threshold;i<(num-threshold);i++)
	{
       sigma=sigma+buff[i];
	}
   temp=(uint16_t)(sigma/(num-threshold*2));
  return(temp);
}

#endif
