/*
 * exti.h
 *
 *  Created on: Jan 27, 2025
 *      Author: Phat
 */

#ifndef LIB_EXTI_H_
#define LIB_EXTI_H_

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

#define NVIC_ADDRESS_BASE                0xE000E100

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

#define NVIC                        ((NVIC_Config_t*)NVIC_ADDRESS_BASE)

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

#define UNMASK_LINE_13              (1U << 13)
#define FALLING_TRIGGER_LINE_13     (1U << 13)

typedef struct
{
    volatile bool evenISR;
    volatile int cnt;
}event_t;
extern event_t _even;

void pc13_init_exti(void);


#endif /* LIB_EXTI_H_ */
