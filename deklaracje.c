#define cs GPIO_Pin_3


void HI(uint16_t GPIO_Pin){
  GPIOB->BSRRH = GPIO_Pin;}


void LOW(uint16_t GPIO_Pin){
  GPIOB->BSRRL = GPIO_Pin;}