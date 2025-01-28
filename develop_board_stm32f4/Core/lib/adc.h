/*
 * adc.h
 *
 *  Created on: Jan 27, 2025
 *      Author: Phat
 */

#pragma once
#ifndef LIB_ADC_H_
#define LIB_ADC_H_

#include <stdint.h>
#include "define.h"
#include <stdbool.h>
#include "exti.h"

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

#define GPIOAEN         (1U << 0)
#define ANALOG_PA3      (3U << 6)
#define ADC1EN          (1U << 8)
#define ADC_CH3         (3U << 0)
#define SWSTART         (1U << 30)
#define CONVERT_CONTINUE    (1U << 1)
#define END_OF_CONVERT      (1U << 1)
#define CR1_EOCIE           (1U << 5)

/**
 * nếu không dùng chế độ chuyển đổi liên tục thì bạn có thể dùng chuyển đổi đơn như sau:
 * 1. init channel
 * 2. gọi hàm start_conversion_single_channel();
 * 3. myPrintf("analog : %d\n",read_analog());
 *  sau đó trong vòng lặp bạn mỗi lần bạn muốn đọc dữ liệu adc bạn đều sẽ phải gọi hàm start+conversion_single_channel()
 * thực hiện như sau:
 * while(1)
 * {
 *      start_conversion_single_channel();
 *      myPrintf("analog : %d\n",read_analog());
 * }
 */

void init_channel5(void);
void start_conversion_single_channel(void);

uint16_t read_analog(void);
void init_channel6(void);
void start_conversion_continous_single_channel(void);

#endif /* LIB_ADC_H_ */
