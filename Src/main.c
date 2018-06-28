
#include "hw_stm32f051r8.h"


/*************************************************************************************************/
void Reserved_IRQHandler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void NMI_Handler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void HardFault_Handler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void SVC_Handler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void PendSV_Handler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}

void SysTick_Handler(void)
{
  while(1)
  {
    /* nothing to be run here */
  }
}
/*************************************************************************************************/

void delay(unsigned int timeout)
{
    unsigned int t1, t2;
    for (t1 = 0; t1 < timeout; t1++)
    for (t1 = timeout; t1 > 0; --t1)
    {
        for (t2 = 0; t2 < 0xFFF; t2++)
        for (t2 = 0xFFF; t2 > 0; --t2)
        {
          asm(" nop");
        }
    }
}

void enabled_clock(void)
{
	write_reg(RCC_AHBENR, read_reg(RCC_AHBENR, ~(1 << 19)) | (1 << 19));
}

void init_pin(void)
{
	write_reg(GPIOC_MODER, read_reg(GPIOC_MODER, ~(0x03 << 18))|(GPIO_MODER_OUTPUT << 18));
}

void led_on(unsigned char pin_number)
{
	write_reg(GPIOC_BSRR, 1u << pin_number);
}

void led_off(unsigned char pin_number)
{
	write_reg(GPIOC_BSRR, 1u << (pin_number + 16u));
}

void main(void)
{
	enabled_clock();
	init_pin();
	while(1)
	{
		led_on(LD3_PIN);
		delay(0xff);
		led_off(LD3_PIN);
		delay(0xff);
	}
}

