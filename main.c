#include "stm32f4_discovery.h"
#include "funkcje.h"
#include "lcd.h"

//extern __IO uint16_t ADC3ConvertedValue;
//extern __IO uint32_t ADC3ConvertedVoltage;
__IO uint16_t ADC3ConvertedValue;
__IO uint32_t ADC3ConvertedVoltage;

int main(void){
   

  Init_RCC();
  Init_GPIO();
  init_lcd();
  wait_ms(100);          //Daj mu czas na start po resecie
  init_cog();
  
  Init_TIM();
  NVIC_Config();
  Init_DMA();
  Init_ADC();

  cog_write_string("Grzegorz",10,5);
  cog_write_string("jest",10,25);
  cog_write_string("miszczem",10,45);
  cog_write_string("esteemow 32",10,65);
 
  cog_write_string("V : ",10,90);
  
  while (1)
  {

  }
}

