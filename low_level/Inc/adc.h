#pragma once
#include <stdint.h>
#include "define.h"
#include <stdbool.h>

typedef struct 
{
    volatile uint32_t ADC_SR;
    volatile uint32_t ADC_CR1;
    volatile uint32_t ADC_CR2;
    volatile uint32_t ADC_SMPR1;
    volatile uint32_t ADC_SMPR2;
    volatile uint32_t ADC_JOFR1;
    volatile uint32_t ADC_JOFR2;
    volatile uint32_t ADC_JOFR3;
    volatile uint32_t ADC_JOFR4;
    volatile uint32_t ADC_HTR;
    volatile uint32_t ADC_LTR;
    volatile uint32_t ADC_SQR1;
    volatile uint32_t ADC_SQR2;
    volatile uint32_t ADC_SQR3;
    volatile uint32_t ADC_JSQR;
    volatile uint32_t ADC_JDR1;
    volatile uint32_t ADC_JDR2;
    volatile uint32_t ADC_JDR3;
    volatile uint32_t ADC_JDR4;
    volatile uint32_t ADC_DR;
    volatile uint32_t ADC_CCR;

}ADC_Typedef;

#define ADC1 ((ADC_Typedef*)ADC1_BASE)

void init_pa5(void);
void start_conversion_single_channel(void);
uint16_t read_analog(void);
