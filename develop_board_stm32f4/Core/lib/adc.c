/*
 * adc.c
 *
 *  Created on: Jan 27, 2025
 *      Author: Phat
 */

#include "adc.h"


void init_channel5()
{
    // enable clock GPIOA
    RCC->RCC_AHB1ENR |= GPIOAEN;
    // PA5 set mode analog
    GPIOA->GPIO_MODER &= ~ (3U << 10);
    GPIOA->GPIO_MODER |= (3U << 10);

    // enable clock ADC1
    RCC->RCC_APB2ENR |= ADC1EN;

    // enable interrupt when end of conversion
    ADC1->ADC_CR1 |= CR1_EOCIE;

    // enable NVIC for adc
    __NVIC_EnableIRQ(ADC);

    // channel 5 is the fisrst conversion in regular channel group conversion
    ADC1->ADC_SQR3 &= ~(0x1F << 0); // 0001 1111
    ADC1->ADC_SQR3 |= (5U << 0);
    // we are have single channel conversion
    ADC1->ADC_SQR1 &= ~ (0xF << 20);
    // enable conversion
    ADC1->ADC_CR2 |= (1U << 0); // adont
}

void init_channel6()
{
    // enable clock GPIOA
    RCC->RCC_AHB1ENR |= GPIOAEN;
    // PA6 set mode analog
    GPIOA->GPIO_MODER &= ~ (3U << 12);
    GPIOA->GPIO_MODER |= (3U << 12);

    // enable clock ADC1
    RCC->RCC_APB2ENR |= ADC1EN;
    // channel 6 is the fisrst conversion in regular channel group conversion
    ADC1->ADC_SQR3 &= ~(0x1F << 0); // 0001 1111
    ADC1->ADC_SQR3 |= (6U << 0);
    // we are have single channel conversion
    ADC1->ADC_SQR1 &= ~ (0xF << 20);
    // enable conversion
    ADC1->ADC_CR2 |= (1U << 0); // adont
}


void start_conversion_single_channel()
{
    ADC1->ADC_CR2 |= SWSTART;

}

void start_conversion_continous_single_channel()
{
    ADC1->ADC_CR2 |= CONVERT_CONTINUE; // continous conversion mode enable
    ADC1->ADC_CR2 |= SWSTART;
}

uint16_t read_analog()
{
    while(!(ADC1->ADC_SR & END_OF_CONVERT ));
    return ADC1->ADC_DR;
}

static void callBack(void)
{
	uint16_t adcValue = ADC1->ADC_DR;
	myPrintf("adcValue := %d\n",adcValue);
}

void ADC_IRQHandler(void)
{
    if(ADC1->ADC_SR & (END_OF_CONVERT))
	{
		ADC1->ADC_SR &= ~ END_OF_CONVERT;
		callBack();
	}
}


