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

#define RCC_CLOCK_ENABLE			((volatile RCC_Config*)RCC_BASE_ADDRESS)
#define RCC_BASE_ADDRESS	 					0x40023800

#define HSI_PLL_CLOCK       FALSE
#define HSE_PLL_CLOCK       TRUE
#if HSI_PLL_CLOCK == TRUE && HSE_PLL_CLOCK == FALSE
#define PLL_M           8
#define PLL_N           84
#define PLL_P           2
#endif
#if HSE_PLL_CLOCK == TRUE && HSI_PLL_CLOCK == FALSE
#define PLL_M           4
#define PLL_N           84
#define PLL_P           2
#endif

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




void ETP_RCC_AHB1_Clock(u8 periph)
{
	RCC_CLOCK_ENABLE->RCC_AHB1ENR |= (1<<periph);
}

void ETP_RCC_AHB2_Enable(u8 periph)
{
	RCC_CLOCK_ENABLE->RCC_AHB2ENR |= (1<<periph);
}

void ETP_RCC_APB1_Enable(u8 periph)
{
	RCC_CLOCK_ENABLE->RCC_APB1ENR |= (1<<periph);
}
void ETP_RCC_APB2_Enable(u8 periph)
{
	RCC_CLOCK_ENABLE->RCC_APB2ENR |= (1<<periph);
}

void ETP_RCC_SetSystemClockByPLL84MHZ()
{
#if HSE_PLL_CLOCK
	RCC_CLOCK_ENABLE->RCC_CR |= (1<<16);
    while(!(RCC_CLOCK_ENABLE->RCC_CR & (1<<17)));
	// ahb1 prescaler =/1 ,, abp1 prescaler = /2, apb2 prescaler = /1
	RCC_CLOCK_ENABLE->RCC_CFGR &= (0<<7);
	RCC_CLOCK_ENABLE->RCC_CFGR |= (4<<10);
	RCC_CLOCK_ENABLE->RCC_CFGR |= (0<<15);
	// PLL_Q == 2
	RCC_CLOCK_ENABLE->RCC_PLLCFGR |= (0x02<<24);
	// PLL_M 
	RCC_CLOCK_ENABLE->RCC_PLLCFGR |= (0x04<<0);
	// PLL_N = 84 
	RCC_CLOCK_ENABLE->RCC_PLLCFGR |= (84<<6);
	// PLL_P 
	RCC_CLOCK_ENABLE->RCC_PLLCFGR &= ~(3<<16);
	RCC_CLOCK_ENABLE->RCC_PLLCFGR |= (1<<22); 
	// PLL CLOCK
	RCC_CLOCK_ENABLE->RCC_CR |= (1<<24);
    while(!(RCC_CLOCK_ENABLE->RCC_CR &(1<<25)));
	// SW
	RCC_CLOCK_ENABLE->RCC_CFGR |= (2<<0);
	//SWS
	while(!((RCC_CLOCK_ENABLE->RCC_CFGR & (1<<2)) == 0 && ((RCC_CLOCK_ENABLE->RCC_CFGR)&(1<<1))));
#else 
	RCC_CLOCK_ENABLE->RCC_CR |= (1<<0);
    while(!(RCC_CLOCK_ENABLE->RCC_CR & (1<<1)));
	// ahb1 = /1 , abp1 = /2 , apb2 = /1 
	RCC_CLOCK_ENABLE->RCC_CFGR &= (0<<7);
	RCC_CLOCK_ENABLE->RCC_CFGR |= (4<<10);
	RCC_CLOCK_ENABLE->RCC_CFGR |= (0<<15);
	// PLL_Q == 2
	RCC_CLOCK_ENABLE->RCC_PLLCFGR |= (0x02<<24);
	// PLL_M =8
	RCC_CLOCK_ENABLE->RCC_PLLCFGR |= (8<<0);
	// PLL_N = 84 
	RCC_CLOCK_ENABLE->RCC_PLLCFGR |= (84<<6);
	// PLL_P 
	RCC_CLOCK_ENABLE->RCC_PLLCFGR &= ~(3<<16);
	RCC_CLOCK_ENABLE->RCC_PLLCFGR &= (0<<22); 
	// PLL CLOCK
	RCC_CLOCK_ENABLE->RCC_CR |= (1<<24);
    while(!(RCC_CLOCK_ENABLE->RCC_CR &(1<<25)));
	// SW
	RCC_CLOCK_ENABLE->RCC_CFGR |= (0x00<<0);
	//SWS
	while(!((RCC_CLOCK_ENABLE->RCC_CFGR & 1) == 0 && ((RCC_CLOCK_ENABLE->RCC_CFGR>>1)&1)==0));
#endif
}

void ETP_RCC_SetSystemClock8MHZ()
{
    RCC_CLOCK_ENABLE->RCC_CR |= (1<<16);
    while(!(RCC_CLOCK_ENABLE->RCC_CR & (1<<17)));
    RCC_CLOCK_ENABLE->RCC_CFGR &=~ (7<13);
    RCC_CLOCK_ENABLE->RCC_CFGR &= ~(7<<10);
    RCC_CLOCK_ENABLE->RCC_CFGR &= ~(15<<10);
}

void ETP_RCC_SetSystemClock16MHZ()
{
    RCC_CLOCK_ENABLE->RCC_CR |= (1<<0);
    while(!(RCC_CLOCK_ENABLE->RCC_CR & (1<<1)));
    RCC_CLOCK_ENABLE->RCC_CFGR &=~ (7<13);
    RCC_CLOCK_ENABLE->RCC_CFGR &= ~(7<<10);
    RCC_CLOCK_ENABLE->RCC_CFGR &= ~(15<<10);
}




#endif /* ETP_STM32F401_RCC_H_ */
