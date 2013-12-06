
#include "stm32f4xx_it.h"
#include "stm32f4_discovery.h"
#include "lcd.h"

extern __IO uint32_t ADC3ConvertedVoltage;
extern __IO uint16_t ADC3ConvertedValue;


void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

void TIM3_IRQHandler(void)
{

  if(TIM_GetITStatus(TIM3, TIM_IT_Update)!=RESET)
  {
    TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
     
     GPIOC->BSRRH = GPIO_Pin_3;
     
     
    /* ADC3ConvertedVoltage = ADC3ConvertedValue *3300/0xFFF;
     uint32_t i=ADC3ConvertedVoltage;
     cog_write_number(i%10,105,90);
     i/=10;
     cog_write_number(i%10,90,90);
     i/=10;
     cog_write_number(i%10,75,90);
     i/=10;
     cog_write_number(i%10,60,90);
     */
  }
    
  else if (TIM_GetITStatus(TIM3, TIM_IT_CC1) != RESET)
  {
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC1);
    ADC_SoftwareStartConv(ADC3);
    ADC3ConvertedVoltage = ADC3ConvertedValue *3300/0xFFF;
 
 }
  
  else if (TIM_GetITStatus(TIM3, TIM_IT_CC2) != RESET)
  {
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC2);
    GPIOC->BSRRL = GPIO_Pin_3;
    
    }
}
/*
void TIM2_IRQHandler(void)
{
  if(TIM_GetITStatus(TIM2, TIM_IT_Update)!=RESET)
  {
     TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
     ADC_SoftwareStartConv(ADC3);
     ADC3ConvertedVoltage = ADC3ConvertedValue *3300/0xFFF;
     uint32_t i = ADC3ConvertedVoltage;
     cog_write_number(i%10,105,90);
     i/=10;
     cog_write_number(i%10,90,90);
     i/=10;
     cog_write_number(i%10,75,90);
     i/=10;
     cog_write_number(i%10,60,90);
  }
     
}
*/


/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
