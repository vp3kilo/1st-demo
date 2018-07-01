#include "hw_stm32f051r8.h"
unsigned int ledStatus = 0;
void gpioHigh(unsigned char pinNum);
void gpioLow(unsigned char pinNum);
void delay(unsigned int time);
/*************************************************************************************************/
void Reserved_IRQHandler(void){
  while(1)
  {
    /* nothing to be run here */
  }
}

void NMI_Handler(void){
  while(1)
  {
    /* nothing to be run here */
  }
}

void HardFault_Handler(void){
  while(1)
  {
    /* nothing to be run here */
  }
}

void SVC_Handler(void){
  while(1)
  {
    /* nothing to be run here */
  }
}

void PendSV_Handler(void){
  while(1)
  {
    /* nothing to be run here */
  }
}

void SysTick_Handler(void){
  while(1)
  {
    /* nothing to be run here */
  }
}

void EXTI0_0_IRQHandler(void){
  /*Ngắt PA0*/
  if(read_reg(EXTI_PR, (1 << EXTI0)) == 1)
  {
      if (ledStatus == 1)
      {
        gpioLow(LED3);
        ledStatus = 0;
      }
      else
      {
        gpioHigh(LED3);
        ledStatus = 1;
      }
  }

  /* Xóa cờ ngắt */
  write_reg(EXTI_PR, (1 << EXTI0));
  write_reg(NVIC_ICPR, (1 << 5));
    
} 
/*************************************************************************************************/

void enabledClock(void){
  /* Enable clock PORT C*/
	write_reg(RCC_AHBENR, read_reg(RCC_AHBENR, ~(1 << 19)) | (1 << 19));

  /* Enable clock PORT A*/
  write_reg(RCC_AHBENR, read_reg(RCC_AHBENR, ~(1 << 17)) | (1 << 17));
}

void initGpio(void){
  /* Init PC9 ~ OUTPUT*/
	write_reg(GPIOC_MODER, read_reg(GPIOC_MODER, ~(0x03u << 18))|(GPIO_MODER_OUTPUT << 18));
  /* Init PC8 ~ OUTPUT*/
  write_reg(GPIOC_MODER, read_reg(GPIOC_MODER, ~(0x03u << 16))|(GPIO_MODER_OUTPUT << 16));
  /* Init PA0 ~ INPUT*/
  write_reg(GPIOA_MODER, read_reg(GPIOA_MODER, ~(0x03u << 0))|(GPIO_MODER_INPUT << 0));
}

void initInterrupt(){
  //Note: The reset value for the internal lines is set to ‘1’ in order to enable the interrupt by default.
  /* Enable interrupt for EXTI0 */
  write_reg(EXTI_IMR, read_reg(EXTI_IMR, ~(1 << IM0))|(1 << IM0));
  // Setup sườn ngắt dương
  write_reg(EXTI_RTSR, read_reg(EXTI_RTSR, ~(1 << 0)) | (1 << 0));
  /* SYSCFG */
  write_reg(SYSCFG_EXTICR1, read_reg(SYSCFG_EXTICR1, ~(0x0Fu << 0))|(0x00u << 0));
  /* NVIC */
  write_reg(NVIC_PRI1, read_reg(NVIC_PRI1, ~(0xFF << 8)) | (0x01 << 14));
  write_reg(NVIC_ISER, read_reg(NVIC_ISER, ~(1 << 5)) | (1 << 5));
  /* Enable global interrupt */
  asm("cpsie i");

}

void gpioHigh(unsigned char pinNum){
	write_reg(GPIOC_BSRR, 1u << pinNum);
}

void gpioLow(unsigned char pinNum){
	write_reg(GPIOC_BSRR, 1u << (pinNum + 16u));
}
void delay(unsigned int time){
    unsigned int a, b;
    for (a = time; a > 0; --a)
    {
        for (b = 0xFFF; b > 0; --b)
        {
          asm(" nop");
        }
    }
}
void main(void)
{
	enabledClock();
	initGpio();
  initInterrupt();
  unsigned ledStatus = 0;
	while(1)
	{
    gpioHigh(LED4);
    delay(0xff);
    gpioLow(LED4);
    delay(0xff);
	}
}

