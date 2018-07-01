
#ifndef __HW_STM32F051R8_H__
#define __HW_STM32F051R8_H__

#include <../Lib/delay/delay.h>
#include <../Lib/sorting_Algorithms/sorting_Algorithms.h>
#define write_reg(addr, value)    *((unsigned long int *)(addr)) = value
#define read_reg(addr, mask)      *((unsigned long int *)(addr)) & (mask)

/* RCC - clock */
#define BASE_ADDR_RCC		0x40021000u
#define RCC_AHBENR			(BASE_ADDR_RCC + 0x14)

/* GPIO MODE*/
#define GPIO_MODER_INPUT	0x00u
#define GPIO_MODER_OUTPUT	0x01u

//PORT C PC9
#define BASE_ADDR_GPIOC		0x48000800u
#define GPIOC_MODER			(BASE_ADDR_GPIOC + 0x00u)
#define GPIOC_BSRR			(BASE_ADDR_GPIOC + 0x18u)
//PORT A PA0
#define BASE_ADDR_GPIOA		0x48000000u
#define GPIOA_MODER			(BASE_ADDR_GPIOA + 0x00u)
#define GPIOA_IDR			(BASE_ADDR_GPIOA + 0x10u)


//External interrupts
/* EXTI */

#define BASE_ADDR_EXTI		0x40010400u
//Interrupt mask register
#define EXTI_IMR			(BASE_ADDR_EXTI + 0x00u)
//Rising trigger selection register 
#define EXTI_RTSR			(BASE_ADDR_EXTI + 0x08u)
//Pending register
#define EXTI_PR				(BASE_ADDR_EXTI + 0x14u)
#define IM0					0
#define EXTI0				0


/* SYSCFG */

#define BASE_ADDR_SYSCFG	0x40010000u

#define SYSCFG_EXTICR1		(BASE_ADDR_SYSCFG + 0x08u)



/* NVIC */

#define NVIC_ISER			0xE000E100u

#define NVIC_ICER			0xE000E180u

#define NVIC_ISPR			0xE000E200u

#define NVIC_ICPR			0xE000E280u

#define NVIC_PRI1			0xE000E404u



/* Led LED3 - PC9: Green*/
#define LED3				9
/* Led LED3 - PC8: Blue*/
#define LED4				8

/* User button PA0*/
#define	USER_BUTTON			0
/* end file */
#endif /* __HW_STM32F051R8_H__ */

