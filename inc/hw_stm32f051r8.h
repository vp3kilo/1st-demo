
#ifndef __HW_STM32F051R8_H__
#define __HW_STM32F051R8_H__

#include <../Lib/delay/delay.h>
//#include <../Lib/sorting_Algorithms/sorting_Algorithms.h>
#define write_reg(addr, value)    *((unsigned long int *)(addr)) = value
#define read_reg(addr, mask)      *((unsigned long int *)(addr)) & (mask)
typedef unsigned int            u32_t;
typedef unsigned short          u16_t;
typedef unsigned char           u8_t;
/* RCC - clock */

#define BASE_ADDR_RCC			0x40021000u
//AHB peripheral clock enable register 
#define RCC_AHBENR				(BASE_ADDR_RCC + 0x14u)
// APB peripheral clock enable register 2 
#define RCC_APB2ENR				(BASE_ADDR_RCC +  0x18u)

#define RCC_CR                  (BASE_ADDR_RCC + 0x00)

#define RCC_CIR                 (BASE_ADDR_RCC + 0x08)

#define RCC_CFGR                (BASE_ADDR_RCC + 0x04)

#define RCC_CFGR2               (BASE_ADDR_RCC + 0x2C)

#define RCC_CFGR3               (BASE_ADDR_RCC + 0x30)

#define PREDIV_1                0u
#define PREDIV_2                1u
#define PREDIV_3                2u
#define PREDIV_4                3u
#define PREDIV_5                4u
#define PREDIV_6                5u
#define PREDIV_7                6u
#define PREDIV_8                7u
#define PREDIV_9                8u
#define PREDIV_10               9u
#define PREDIV_11               10u
#define PREDIV_12               11u
#define PREDIV_13               12u
#define PREDIV_14               13u
#define PREDIV_15               14u
#define PREDIV_16               15u

#define PLL_MUL_2               0u
#define PLL_MUL_3               1u
#define PLL_MUL_12              10u

#define PLL_SCR_HSI             0u

#define SYSCLKSOURCE_PLLCLK     2u

#define APB1_HCLK_1             0u
#define APB1_HCLK_2             4u
#define APB1_HCLK_4             5u
#define APB1_HCLK_8             6u
#define APB1_HCLK_16            7u

/* GPIO MODE*/
//MODE: INPUT
#define GPIO_MODER_INPUT		0x00u
//MODE: OUTPUT
#define GPIO_MODER_OUTPUT		0x01u
//MODE: ALTERNATE
#define GPIO_MODER_ATL			0x02u
//
#define AF1						0x1u

//PORT C PC9
#define BASE_ADDR_GPIOC			0x48000800u
#define GPIOC_MODER				(BASE_ADDR_GPIOC + 0x00u)
#define GPIOC_BSRR				(BASE_ADDR_GPIOC + 0x18u)
//PORT A PA0
#define BASE_ADDR_GPIOA			0x48000000u
#define GPIOA_MODER				(BASE_ADDR_GPIOA + 0x00u)
#define GPIOA_IDR				(BASE_ADDR_GPIOA + 0x10u)
#define GPIOA_AFRH				(BASE_ADDR_GPIOA + 0x24u)


//External interrupts
/* EXTI */

#define BASE_ADDR_EXTI			0x40010400u
//Interrupt mask register
#define EXTI_IMR				(BASE_ADDR_EXTI + 0x00u)
//Rising trigger selection register 
#define EXTI_RTSR				(BASE_ADDR_EXTI + 0x08u)
//Pending register
#define EXTI_PR					(BASE_ADDR_EXTI + 0x14u)
#define IM0						0
#define EXTI0					0


/* SYSCFG */

#define BASE_ADDR_SYSCFG		0x40010000u

#define SYSCFG_EXTICR1			(BASE_ADDR_SYSCFG + 0x08u)



/* NVIC */

#define NVIC_ISER				0xE000E100u

#define NVIC_ICER				0xE000E180u

#define NVIC_ISPR				0xE000E200u

#define NVIC_ICPR				0xE000E280u

#define NVIC_PRI1				0xE000E404u

#define NVIC_PRI7     	        0xE000E418u

/* =================== USART =================== */
#define BASE_ADDR_USART1        0x40013800u

#define USART_CR1               (BASE_ADDR_USART1 + 0x00)
#define USART_CR2               (BASE_ADDR_USART1 + 0x04)
#define USART_CR3               (BASE_ADDR_USART1 + 0x08)
#define USART_BRR               (BASE_ADDR_USART1 + 0x0C)
#define USART_RQR               (BASE_ADDR_USART1 + 0x18)
#define USART_ISR               (BASE_ADDR_USART1 + 0x1C)
#define USART_ICR               (BASE_ADDR_USART1 + 0x20)
#define USART_RDR               (BASE_ADDR_USART1 + 0x24)
#define USART_TDR               (BASE_ADDR_USART1 + 0x28)

/* Led LED3 - PC9: Green*/
#define LED3					9
/* Led LED3 - PC8: Blue*/
#define LED4					8

/* User button PA0*/
#define	USER_BUTTON				0
/* end file */
#endif /* __HW_STM32F051R8_H__ */

