/*=====================================================================================================*/
/*=====================================================================================================*/
#include "nrf51_system.h"
#include "nrf51_adc.h"
/*====================================================================================================*/
/*====================================================================================================*
**函數 : ADC_Init
**功能 : ADC Init
**輸入 : ADC_InitStruct
**輸出 : None
**使用 : ADC_Init(&ADC_InitStruct);
**====================================================================================================*/
/*====================================================================================================*/
void ADC_Init( ADC_InitTypeDef *ADC_InitStruct )
{
  NRF_ADC->CONFIG = (ADC_InitStruct->ADC_Resolution         << ADC_CONFIG_RES_Pos) | 
                    (ADC_InitStruct->ADC_ExternalReference  << ADC_CONFIG_EXTREFSEL_Pos) | 
                    (ADC_InitStruct->ADC_AnalogInput        << ADC_CONFIG_PSEL_Pos) | 
                    (ADC_InitStruct->ADC_ReferenceSelection << ADC_CONFIG_REFSEL_Pos) |
                    (ADC_InitStruct->ADC_InputSelection     << ADC_CONFIG_INPSEL_Pos);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : ADC_Cmd
**功能 : Enable / Disable ADC
**輸入 : NewState
**輸出 : None
**使用 : ADC_Cmd(ENABLE);
**====================================================================================================*/
/*====================================================================================================*/
void ADC_Cmd( FunctionalState NewState )
{
  if(NewState == ENABLE)
    NRF_ADC->ENABLE = (ADC_ENABLE_ENABLE_Enabled  << ADC_ENABLE_ENABLE_Pos);
  else
    NRF_ADC->ENABLE = (ADC_ENABLE_ENABLE_Disabled << ADC_ENABLE_ENABLE_Pos);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : ADC_IntCmd
**功能 : Enable / Disable ADC Interrupt
**輸入 : NewState
**輸出 : None
**使用 : ADC_IntCmd(ENABLE);
**====================================================================================================*/
/*====================================================================================================*/
void ADC_IntCmd( FunctionalState NewState )
{
  if(NewState == ENABLE)
    NRF_ADC->INTENSET = (ADC_INTENSET_END_Enabled << ADC_INTENSET_END_Pos);
  else
    NRF_ADC->INTENCLR = (ADC_INTENCLR_END_Enabled << ADC_INTENCLR_END_Pos);
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : ADC_StartConv
**功能 : ADC Start Conversion
**輸入 : None
**輸出 : None
**使用 : ADC_StartConv();
**====================================================================================================*/
/*====================================================================================================*/
void ADC_StartConv( void )
{
  NRF_ADC->TASKS_START = 1;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : ADC_StopConv
**功能 : ADC Stop Conversion
**輸入 : None
**輸出 : None
**使用 : ADC_StopConv();
**====================================================================================================*/
/*====================================================================================================*/
void ADC_StopConv( void )
{
  NRF_ADC->TASKS_STOP = 1;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : ADC_Busy
**功能 : ADC State
**輸入 : None
**輸出 : State
**使用 : State = ADC_Busy();
**====================================================================================================*/
/*====================================================================================================*/
uint8_t ADC_Busy( void )
{
  if(NRF_ADC->BUSY == 0)
    return SUCCESS;   // Ready
  else
    return ERROR;     // Busy
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : ADC_EvenCheck
**功能 : ADC Check Even
**輸入 : None
**輸出 : State
**使用 : State = ADC_EvenCheck();
**====================================================================================================*/
/*====================================================================================================*/
uint8_t ADC_EvenCheck( void )
{
  if(NRF_ADC->EVENTS_END == 1)
    return SUCCESS;
  else
    return ERROR;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : ADC_EvenClear
**功能 : ADC Clear Even
**輸入 : None
**輸出 : None
**使用 : ADC_EvenClear();
**====================================================================================================*/
/*====================================================================================================*/
void ADC_EvenClear( void )
{
  NRF_ADC->EVENTS_END = 0;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : ADC_GetResult
**功能 : Get Result
**輸入 : None
**輸出 : ReadADC
**使用 : ReadADC = ADC_GetResult();
**====================================================================================================*/
/*====================================================================================================*/
uint16_t ADC_GetResult( void )
{
  return NRF_ADC->RESULT;
}
/*====================================================================================================*/
/*====================================================================================================*
**函數 : ADC_ReadData
**功能 : Read Data
**輸入 : None
**輸出 : ReadADC
**使用 : ReadADC = ADC_ReadData();
**====================================================================================================*/
/*====================================================================================================*/
uint16_t ADC_ReadData( void )
{
  uint16_t ReadData = 0;

  ADC_StartConv();

  while(ADC_EvenCheck() != SUCCESS);
  ADC_EvenClear();

	ReadData = ADC_GetResult();

  ADC_StopConv();
  
  return ReadData;
}
/*=====================================================================================================*/
/*=====================================================================================================*/
