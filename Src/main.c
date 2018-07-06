#include "hw_stm32f051r8.h"
unsigned int ledStatus = 0;
volatile unsigned char rxData = 0;
void GpioHigh(unsigned char pinNum);
void GpioLow(unsigned char pinNum);
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
        GpioLow(LED3);
        ledStatus = 0;
      }
      else
      {
        GpioHigh(LED3);
        ledStatus = 1;
      }
  }

  /* Xóa cờ ngắt */
  write_reg(EXTI_PR, (1 << EXTI0));
  write_reg(NVIC_ICPR, (1 << 5));
    
} 

void USART1_IRQHandler(void){
  /* Tx - TC flag */
  if (0 != read_reg(USART_ISR, 1 << 6)) 
  {
    write_reg(USART_ICR, (1<<6));
  }

  /* Rx - RXNE flag */
  if (0 != read_reg(USART_ISR, 1 << 5))  
  {
    rxData = read_reg(USART_RDR, 0x000000FF);
    write_reg(USART_RQR, (1<<3));
  /* Ghi giá trị 1 tới USART_RQR[RXFRQ] để xóa cờ USART_ISR[RXNE] */
  }
} 
/*************************************************************************************************/

/**
  * @brief  Setup the microcontroller system.
  *         Initialize the default HSI clock source, vector table location and the PLL configuration is reset.
  * @param
  *         hsi_prediv: hệ số chia clock từ HSI RC đưa vào PLL Source Mux
  *         pullmux: hệ số chia clock trong khối PLL
  *         pllsrc: hệ số chia clock trong khối PLL
  *         ahb_div: hệ số chia clock cho AHB prescaler
  *         system_source: lựa chọn source clock cho system thông qua System Clock Mux
  *         apb1_div: hệ số chia clock cho APB1 prescaler
  * @retval None
  */
void SystemInit(u32_t hsi_prediv, u32_t pullmux, u32_t pllsrc, u32_t ahb_div, u32_t system_source, u32_t apb1_div)
{
    volatile u32_t timeOut;
    u32_t temporaryReg;
    /* Disable all interrupts */
    write_reg(RCC_CIR, 0x00000000U);


    /* This infomation gets from SystemClock_Config() function which was generated from STM32CubeMX */
    /* Disable the Internal High Speed oscillator (HSI). */
    write_reg(RCC_CR, read_reg(RCC_CR, ~0x00000001U));
    
    /* Wait till HSI is disabled */
    timeOut = 0xFFF;
    do {
        temporaryReg = read_reg(RCC_CR, 0x00000002U);
        --timeOut;
    } while ((0 != temporaryReg) && (timeOut > 0));
    
    /* Disable the main PLL. */
    write_reg(RCC_CR, read_reg(RCC_CR, ~(1 << 24)));
    
    /* Wait till PLL is disabled */
    timeOut = 0xFFFFFFFF;
    do {
        temporaryReg = read_reg(RCC_CR, (1 << 25));
        --timeOut;
    } while ((0 != temporaryReg) && (timeOut > 0));
    
    /* Configure the main PLL clock source, predivider and multiplication factor. */
    write_reg(RCC_CFGR2, read_reg(RCC_CFGR2, ~0xFFFFFFF0U) | hsi_prediv);
    
    write_reg(RCC_CFGR, read_reg(RCC_CFGR, ~(0xF << 18)) | pullmux << 18);

    write_reg(RCC_CFGR, read_reg(RCC_CFGR, ~(0x3 << 15)) | pllsrc << 15);
    
    /* Enable the main PLL. */
    write_reg(RCC_CR, read_reg(RCC_CR, ~(1 << 24)) | 1 << 24);
    
    /* Wait till PLL is ready */
    timeOut = 0xFFFFFFFF;
    do {
      temporaryReg = read_reg(RCC_CR, (1 << 25));
      --timeOut;
    } while ((0 == temporaryReg) && (timeOut > 0));

    /* Initializes the CPU, AHB and APB busses clocks */
    /* HCLK configration */
    write_reg(RCC_CFGR, read_reg(RCC_CFGR, ~(0xF << 4)) | ahb_div << 4);

    /* HSE is selected as System Clock Source */
    write_reg(RCC_CFGR, read_reg(RCC_CFGR, ~(0x3 << 0)) | system_source << 0);
    
    /* Wait till System clock switch is ready */
    timeOut = 0xFFFFFFFF;
    do {
      temporaryReg = read_reg(RCC_CFGR, (0x3 << 2));
      --timeOut;
    } while (((2<<2) != temporaryReg) && (timeOut > 0));

    /* APB1 prescaler */
    write_reg(RCC_CFGR, read_reg(RCC_CFGR, ~(0x7 << 8)) | apb1_div << 8);
    
    /* USART1 */
    /* PCLK1 */
    write_reg(RCC_CFGR3, read_reg(RCC_CFGR3, ~(0x3 << 0)) | 0 << 0);

}

void EnabledClock(void){
  /* Enable clock PORT C*/
	write_reg(RCC_AHBENR, read_reg(RCC_AHBENR, ~(1 << 19)) | (1 << 19));

  /* Enable clock PORT A*/
  write_reg(RCC_AHBENR, read_reg(RCC_AHBENR, ~(1 << 17)) | (1 << 17));

  /* Enable clock USART1 */
  write_reg(RCC_APB2ENR, read_reg(RCC_APB2ENR, ~(1 << 14)) | (1 << 14));
}

void InitGpio(void){
  /* Init PC9 ~ OUTPUT*/
	write_reg(GPIOC_MODER, read_reg(GPIOC_MODER, ~(0x03u << 18))|(GPIO_MODER_OUTPUT << 18));
  /* Init PC8 ~ OUTPUT*/
  write_reg(GPIOC_MODER, read_reg(GPIOC_MODER, ~(0x03u << 16))|(GPIO_MODER_OUTPUT << 16));
  /* Init PA0 ~ INPUT*/
  write_reg(GPIOA_MODER, read_reg(GPIOA_MODER, ~(0x03u << 0))|(GPIO_MODER_INPUT << 0));
  /* PA10 - Rx */
  write_reg(GPIOA_MODER, read_reg(GPIOA_MODER, ~(0x03 << 20)) | (GPIO_MODER_ATL << 20));
  write_reg(GPIOA_AFRH, read_reg(GPIOA_AFRH, ~(0xF << 8)) | (AF1 << 8));
  /* PA9 - Tx */
  write_reg(GPIOA_MODER, read_reg(GPIOA_MODER, ~(0x03 << 18)) | (GPIO_MODER_ATL << 18));
  write_reg(GPIOA_AFRH, read_reg(GPIOA_AFRH, ~(0xF << 4)) | (AF1 << 4));
}

void InitInterrupt(){
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

  /* USART1 */
  write_reg(USART_ICR, 0xFFFFFFFF);
  write_reg(USART_RQR, 0xFFFFFFFF);

  /* Tx interrupt */
  write_reg(USART_CR1, read_reg(USART_CR1, ~(1 << 6)) | 1 << 6);

  /* Rx interrupt - RXNEIE */
  write_reg(USART_CR1, read_reg(USART_CR1, ~(1 << 5)) | 1 << 5);
  write_reg(NVIC_ISER, read_reg(NVIC_ISER, ~(1 << 27)) | 1 << 27);
  write_reg(NVIC_PRI7, read_reg(NVIC_PRI7, ~(0xFF << 24)) | 0x01 << 30);

  /* Enable global interrupt */
  asm("cpsie i");
}

void UsartInit(void)
{
    /* Disable USART1 */
    write_reg(USART_CR1, 0x00000000);

    /* Length data: 8 bits */
    write_reg(USART_CR1, read_reg(USART_CR1, ~((1<<28)||(1<<12))) | (0<<28)||(0<<12));

    /* Parity : none */
    write_reg(USART_CR1, read_reg(USART_CR1, ~(1<<10)) | (0<<10));

    /* Stop bit - 1 bit */
    write_reg(USART_CR2, read_reg(USART_CR2, ~(0x3<<12)) | (0<<12));

    /* Oversampling: 16 bits */
    write_reg(USART_CR1, read_reg(USART_CR1, ~(1<<15)) | (0<<15));

    /* Baudrate = 9600 bps; fCK = 8 MHz */
    write_reg(USART_BRR, 0x0341u);

    /* Enable usart1 */
    write_reg(USART_CR1, read_reg(USART_CR1, ~(1<<0)) | (1<<0));

    /* Tx Enable */
    write_reg(USART_CR1, read_reg(USART_CR1, ~(1<<3)) | (1<<3));

    /* Rx Enable */
    write_reg(USART_CR1, read_reg(USART_CR1, ~(1<<2)) | (1<<2));

}


void GpioHigh(unsigned char pinNum){
	write_reg(GPIOC_BSRR, 1u << pinNum);
}

void GpioLow(unsigned char pinNum){
	write_reg(GPIOC_BSRR, 1u << (pinNum + 16u));
}

char UsartSendByte(unsigned char dataInput)
{
    char state = 0;
    
    /* kiểm tra xem TDR sẵn sàng nhận dữ liệu mới chưa */
    if (0 != read_reg(USART_ISR, (1<<7)))
    {
        write_reg(USART_TDR, (unsigned int)dataInput);
    }
    else
    {
        state = -1;
    }
    return state;
}

char UsartSendString(unsigned char *strData)
{    
    char state = 0;
    while(*strData)
    {
        if (0 == UsartSendByte(*strData))
        {
            strData++;
        }
    }
    return state;
}
void main(void)
{
  SystemInit(PREDIV_1, PLL_MUL_12, PLL_SCR_HSI, PREDIV_1, SYSCLKSOURCE_PLLCLK, APB1_HCLK_1);
	EnabledClock();
	InitGpio();
  InitInterrupt();
  UsartInit();
  unsigned ledStatus = 0;
  /* Send "Hello world -MCU" to terminal app on PC */
  UsartSendString("Hello world - MCU\r\n");
  GpioHigh(LED4);
  Delay(0xff);
  GpioLow(LED4);
  Delay(0xff);
  while(1)
  {
      #if 1
      if (0 != rxData)
      {
          UsartSendByte(rxData);
          rxData = 0;
      }
      #else
      UsartSendByte(0x55);
      Delay(0xf);
      #endif
  }

}

