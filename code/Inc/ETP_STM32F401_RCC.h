/*
 * ETP_STM32F401_RCC.h
 *
 *  Created on: Nov 12, 2024
 *      Author: Phat
 */

#ifndef ETP_STM32F401_RCC_H_
#define ETP_STM32F401_RCC_H_
#include "std_type.h"
#define RCC_GPIOA				(0x00U)
#define RCC_GPIOB				(0x01U)
#define RCC_GPIOC				(0x02U)
#define RCC_GPIOD				(0x03U)
#define RCC_GPIOE				(0x04U)
#define RCC_GPIOH				(0x07U)


#define RCC_BASE_ADDRESS	 					0x40023800

typedef struct 
{
	volatile u32 RCC_CR;// 0x00
	volatile u32 RCC_PLLCFGR;// 0x04
	volatile u32 RCC_CFGR; // 0x08 
	volatile u32 RCC_CIR; //0x0C
	volatile u32 RCC_AHB1RSTR; // 0x10
	volatile u32 RCC_AHB2RSTR;
	volatile u32 reverse1[2];
	volatile u32 RCC_APB1RSTR;	
	volatile u32 RCC_APB2RSTR;
	volatile u32 reverse2[2];
	volatile u32 RCC_AHB1ENR;
	volatile u32 RCC_AHB2ENR;
	volatile u32 reverse3[2];
	volatile u32 RCC_APB1ENR;
	volatile u32 RCC_APB2ENR;
	volatile u32 reverse4[2];
	volatile u32 RCC_AHB1LPENR;
	volatile u32 RCC_AHB2LPENR;
	volatile u32 reverse5[2];
	volatile u32 RCC_APB1LPENR;
	volatile u32 RCC_APB2LPENR;
	volatile u32 reverse6[2];
	volatile u32 RCC_BDCR;
	volatile u32 RCC_CSR;
	volatile u32 reverse7[2];
	volatile u32 RCC_SSCGR;
	volatile u32 RCC_PLLI2SCFGR;
	volatile u32 RCC_DCKCFGR;
}RCC_Config;


#define RCC_CLOCK_ENABLE			((volatile RCC_Config*)RCC_BASE_ADDRESS)

void ETP_RCC_AHB1_Clock(u8 periph)
{
	RCC_CLOCK_ENABLE->RCC_AHB1ENR |= (1<<periph);
}


#endif /* ETP_STM32F401_RCC_H_ */
