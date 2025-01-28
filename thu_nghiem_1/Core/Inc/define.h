/*
 * define.h
 *
 *  Created on: Jan 27, 2025
 *      Author: Phat
 */

#ifndef INC_DEFINE_H_
#define INC_DEFINE_H_

#pragma once
#include <stdint.h>
#define PERIPH_BASE 			(0x40000000UL)

#define AHB1_BASE_OFFSET		(0x00020000UL)
#define AHB1_BASE  				(PERIPH_BASE + AHB1_BASE_OFFSET)

#define OFFSET_GPIOA			(0x0000UL)
#define GPIOA_BASE				(AHB1_BASE + OFFSET_GPIOA)

#define OFFSET_RCC				(0x3800UL)
#define RCC_BASE				(AHB1_BASE + OFFSET_RCC)

#define OFFSET_GPIOB			(0x0400UL)
#define GPIOB_BASE				(AHB1_BASE + OFFSET_GPIOB)

#define OFFSET_GPIOC			(0x0800UL)
#define GPIOC_BASE				(AHB1_BASE + OFFSET_GPIOC)

#define OFFSET_GPIOD			(0x0C00UL)
#define GPIOD_BASE				(AHB1_BASE + OFFSET_GPIOD)

#define OFFSET_GPIOE			(0x1000UL)
#define	GPIOE_BASE				(AHB1_BASE + OFFSET_GPIOE)

#define OFFSET_GPIOH			(0x1C00UL)
#define GPIOH_BASE				(AHB1_BASE + OFFSET_GPIOH)

#define OFFSET_CRC				(0x3000UL)
#define CRC_BASE				(AHB1_BASE + OFFSET_CRC)

#define OFFSET_FLASH			(0x3C00UL)
#define FLASH_BASE				(AHB1_BASE + OFFSET_FLASH)

#define OFFSET_DMA1				(0x6000UL)
#define DMA1_BASE				(AHB1_BASE + OFFSET_DMA1)

#define OFFSET_DMA2				(0x6400UL)
#define DMA2_BASE				(AHB1_BASE + OFFSET_DMA2)

#define OFFSET_APB1				(0x00000000UL)
#define APB1_BASE				(0x40000000UL)
#define TIM2_BASE				( 0x40000000UL)
#define TIM3_BASE				(0x40000400UL)
#define TIM4_BASE				(0x40000800UL)
#define TIM5_BASE				(0x40000C00UL )
#define RTC_REGISTER_BASE		(0x40002800UL)
#define WWDG_BASE				(0x40002C00UL)
#define IWDG_BASE				( 0x40003000UL)
#define I2S2ext_BASE			( 0x40003400UL)
#define SPI2_BASE				( 0x40003800UL )
#define SPI3_BASE				( 0x40003C00UL)
#define IS23_BASE				( 0x40004000UL)
#define USART2_BASE				( 0x40004400UL)
#define I2C1_BASE				(0x40005400UL)
#define I2C2_BASE				(0x40005800UL)
#define I2C3_BASE				( 0x40005C00UL)
#define PWR_BASE				(0x40007000UL)
#define APB2_BASE				( 0x40010000UL) // (0x40000000UL) + (0x00007400UL) = 0x40007400
#define TIM1_BASE				(0x40010000UL)
#define TIM8_BASE				(0x40010400UL)
#define USART1_BASE             (0x40011000UL)
#define USART6_BASE				(0x40011400UL)
#define ADC1_BASE				( 0x40012000UL)
#define SDIO_BASE				( 0x40012C00UL)
#define SPI1_BASE				(0x40013000UL)
#define SPI4_BASE				(0x40013400UL)
#define SYSCFG_BASE				(0x40013800UL)
#define EXTI_BASE				( 0x40013C00UL)
#define TIM9_BASE				(0x40014000UL)
#define TIM10_BASE				(0x40014400UL)
#define TIM11_BASE				(0x40014800UL)
#define AHB2_BASE				(0x50000000UL)
#define USB_OTG_FS_BASE 		(0x50000000UL)

// continue
#define RCC_AHB1ENR_OFFSET			(0x30UL)
#define BASE_RCC_AHB1ENR			(*(volatile unsigned int*)(RCC_BASE + RCC_AHB1ENR_OFFSET))

#define GPIO_MODER_OFFSET		(0x00UL)
#define GPIOA_MODER				(*(volatile unsigned int*)(GPIOA_BASE + GPIO_MODER_OFFSET))

#define GPIO_ODR_OFFSET			(0x14UL)
#define GPIOA_ODR				(*(volatile unsigned int*)(GPIO_ODR_OFFSET + GPIOA_BASE))

// uart
#define RCC 		((RCC_Typedef*)RCC_BASE)
#define GPIOA		((GPIO_Typedef*)(GPIOA_BASE))
#define GPIOC      	((GPIO_Typedef*)(GPIOC_BASE))
#define GPIOA_ENABLE			(1UL<<0) // 0b 0000 0000 0000 0000 0000 0000 0000 0001
#define GPIOC_ENABLE			(1U<<2)
#define PIN13		(1U<<13)
#define BTN_PIN		PIN13
#define USART2 		((USART_Typedef*)USART2_BASE)
#define USART1 		((USART_Typedef*)USART1_BASE)
#define USART2_ENABLE		(1U << 17)
#define USART1_ENABLE		(1U << 4)
#define BAUDRATE			115200

#define SYS_FREQ			16000000
#define APB1_CLK			SYS_FREQ

typedef struct
{
	volatile uint32_t USART_SR;
	volatile uint32_t USART_DR;
	volatile uint32_t USART_BRR;
	volatile uint32_t USART_CR1;
	volatile uint32_t USART_CR2;
	volatile uint32_t USART_CR3;
	volatile uint32_t USART_GTPR;
}USART_Typedef;

typedef struct
{
	volatile uint32_t GPIO_MODER; // 0x00
	volatile uint32_t GPIO_OTYPER; // 0x04
	volatile uint32_t GPIO_OSPEEDR; // 0x08
	volatile uint32_t GPIO_PUPDR; // 0x0C
	volatile uint32_t GPIO_IDR; // 0x10
	volatile uint32_t GPIO_ODR; // 0x14
	volatile uint32_t GPIO_BSRR; // 0x18
	volatile uint32_t GPIO_LCKR; // 0x1C
	volatile uint32_t GPIO_AFR[2]; // 0x20 - 0x24  // 0 is low and 1 is high
}GPIO_Typedef;

typedef struct
{
	volatile uint32_t RCC_CR;
	volatile uint32_t RCC_PLLCFGR;
	volatile uint32_t RCC_CFGR;
	volatile uint32_t RCC_CIR;
	volatile uint32_t RCC_AHB1RSTR;
	volatile uint32_t RCC_AHB2RSTR;
	uint32_t RESERVED[2];
	volatile uint32_t RCC_APB1RSTR;
	volatile uint32_t RCC_APB2RSTR;
	uint32_t RESERVED1[2];
	volatile uint32_t RCC_AHB1ENR;
	volatile uint32_t RCC_AHB2ENR;
	uint32_t RESERVED2[2];
	volatile uint32_t RCC_APB1ENR;
	volatile uint32_t RCC_APB2ENR;
	uint32_t RESERVED3[2];
	volatile uint32_t RCC_AHB1LENR;
	volatile uint32_t RCC_AHB2LENR;
	uint32_t RESERVED4[2];
	volatile uint32_t RCC_APB1LENR;
	volatile uint32_t RCC_APB2LENR;
	uint32_t RESERVED5[2];
	volatile uint32_t RCC_BDCR;
	volatile uint32_t RCC_CSR;
	uint32_t RESERVED6[2];
	volatile uint32_t RCC_SSCGR;
	volatile uint32_t RCC_PLLI2SCFGR;
	uint32_t RESERVED7;
	volatile uint32_t RCC_DCKCFGR;

}RCC_Typedef;
#pragma once
#include "define.h"
#include <stdbool.h>

/**
 * for code interrupt external we are perform step by step
 */

/**
 *  1. disable global interrupt
 *  2. enable clock asscess for GPIO
 *  3. set mode input
 *  4. enable clock access to SYSCFG (important)
 *  5. select port for EXTix line
 *  6. unmask EXTIx
 *  7. select falling edge trigger
 *  8. enable EXTIx line in NVIC
 *  9. enable global interrupt
 *
 * i writing code withou any library of manual arm , i want writting code from low layout, because i learn better than hardware mcu
* let go.
 */

#define __STATIC_FORCEINLINE                __attribute__ ((always_inline)) static __inline

#define __ASM                               __asm

#define NVIC_BASE                0xE000E100

__STATIC_FORCEINLINE void __disable_irq(void)
{
    __ASM volatile ("cpsid i" : : : "memory");
}

__STATIC_FORCEINLINE void __enable_irq(void)
{
    __ASM volatile ("cpsie i" : : : "memory");
}

#define __COMPILER_BARRIER()                __ASM volatile ("" : : : "memory")

typedef enum
{
    WWDG = 0,
    EXTI16_PVD = 1,
    EXTI21_TAMP_STAMP = 2,
    EXTI22_RTC_WKUP = 3,
    FLASH = 4,
    RCC_position = 5,
    EXTI0 = 6,
    EXTI1 = 7,
    EXTI2 = 8,
    EXTI3 = 9,
    EXTI4 = 10,
    DMA1_Stream0 = 11,
    DMA1_Stream1 = 12,
    DMA1_Stream2 = 13,
    DMA1_Stream3 = 14,
    DMA1_Stream4 = 15,
    DMA1_Stream5 = 16,
    DMA1_Stream6 = 17,
    ADC = 18,
    EXTI9_5 = 23,
    TIM1_BRK_TIM9 = 24,
    TIM1_UP_TIM10 = 25,
    TIM1_TRG_COM_TIM11 = 26,
    TIM1_CC = 27,
    TIM2_position = 28,
    TIM3_postion = 29,
    TIM4 = 30,
    I2C1_EV = 31,
    I2C1_ER = 32,
    I2C2_EV = 33,
    I2C2_ER = 34,
    SPI1 = 35,
    SPI2 = 36,
    USART1_position = 37,
    USART2_position = 38,
    EXTI15_10 = 40,
    EXTI17_RTC_Alarm = 41,
    EXTI18_OTG_FS_WKUP = 42,
    DMA1_Stream7 = 47,
    SDIO = 49,
    TIM5 = 50,
    SPI3= 51,
    DMA2_Stream0 = 56,
    DMA2_Stream1 = 57,
    DMA2_Stream2 = 58,
    DMA2_Stream3 = 59,
    DMA2_Stream4 = 60,
    OTG_FS = 67,
    DMA2_Stream5 = 68,
    DMA2_Stream6 = 69,
    DMA2_Stream7 = 70,
    USART6_position = 71,
    I2C3_EV = 72,
    I2C3_ER = 73,
    FPU=81,
    SPI4 = 84,

}IRQ_Priority_t;



typedef struct
{
    volatile uint32_t SYSCFG_MEMRMP;
    volatile uint32_t SYSCFG_PMC;
    volatile uint32_t SYSCFG_EXTICR1;
    volatile uint32_t SYSCFG_EXTICR2;
    volatile uint32_t SYSCFG_EXTICR3;
    volatile uint32_t SYSCFG_EXTICR4;
    volatile uint32_t SYSCFG_CMPCR;

}SYSCFG_config_t;

typedef struct
{
    volatile uint32_t EXTI_IMR;
    volatile uint32_t EXTI_EMR;
    volatile uint32_t EXTI_RTSR;
    volatile uint32_t EXTI_FTSR;
    volatile uint32_t EXTI_SWIER;
    volatile uint32_t EXTI_PR;

}EXTI_Config_t;

typedef struct
{
    volatile uint32_t NVIC_ISER[8];
    uint32_t RESERVED[25];
    volatile uint32_t NVIC_ICER[8];
    uint32_t RESERVED1[25];
    volatile uint32_t NVIC_ISPR[8];
    uint32_t RESERVED2[25];
    volatile uint32_t NVIC_ICPR[8];
    uint32_t RESERVED3[25];
    volatile uint32_t NVIC_IABR[8];
    uint32_t RESERVED4[57];
    volatile uint32_t NVIC_IPR[60];

}NVIC_Config_t;

#define NVIC                        ((NVIC_Config_t*)NVIC_BASE)

#define NVIC_STIR_Address           0xE000EF00
#define NVIC_Config_STIR            (*(volatile uint32_t*)NVIC_STIR_Address)


#define SYSCFG          ((SYSCFG_config_t*)SYSCFG_BASE)
#define EXTI            ((EXTI_Config_t*)EXTI_BASE)


__STATIC_FORCEINLINE void __NVIC_EnableIRQ(IRQ_Priority_t type_IRQ)
{
    if(((int32_t)type_IRQ) >=0)
    {
        __COMPILER_BARRIER();
        NVIC->NVIC_ISER[(((uint32_t)type_IRQ) >> 5U)] = (uint32_t) (1U << (uint32_t)(((uint32_t)type_IRQ) & 0x1F));
        __COMPILER_BARRIER();
    }
}

#define LINE13              (1U << 13)

void pc13_init_exti(void);
void EXTI15_10_IRQHandler(void);


typedef struct
{
    volatile bool evenISR;
    volatile int cnt;
}event_t;



#endif /* INC_DEFINE_H_ */
