#pragma once

#include "define.h"

typedef struct 
{
    volatile uint32_t TIMx_CR1;
    volatile uint32_t TIMx_CR2;
    volatile uint32_t TIMx_SMCR;
    volatile uint32_t TIMx_DIER;
    volatile uint32_t TIMx_SR;
    volatile uint32_t TIMx_EGR;
    // in the video previous i code 
    /**
     * volatile uint32_t TIMx_CCMR1[2];
     * volatile uint32_t TIMx_CCMR2[2]; 
     * in fact, i make mistake , i change to below is correct
     */
    volatile uint32_t TIMx_CCMR1;
    volatile uint32_t TIMx_CCMR2;
    volatile uint32_t TIMx_CCER;
    volatile uint32_t TIMx_CNT;
    volatile uint32_t TIMx_PSC;
    volatile uint32_t TIMx_ARR;
    uint32_t reserved;
    volatile uint32_t TIMx_CCR1;
    volatile uint32_t TIMx_CCR2;
    volatile uint32_t TIMx_CCR3;
    volatile uint32_t TIMx_CCR4;
    uint32_t reserved1;
    volatile uint32_t TIMx_DCR;
    volatile uint32_t TIMx_DMAR;
    volatile uint32_t TIM2_OR;
    volatile uint32_t TIM5_OR;
}Timer_config_t;

#define TIM2            ((Timer_config_t*)TIM2_BASE)
#define TIM3            ((Timer_config_t*)TIM3_BASE)

#define TIM2_EN         (1U << 0)
#define TIM2_CEN        (1U << 0)
#define TIM2_SR_UIF     (1U << 0)   

void init_timer2_1hz();
void init_pa5_timer2_1hz();
void init_pa6_input_capture();

/**
 * in previous video i create 1hz in PA5 , today i measure signal from PA5 and show monitor
 */