#include "adc.h"

#define GPIOAEN         (1U << 0)
#define ANALOG_PA3      (3U << 6)
#define ADC1EN          (1U << 8)
#define ADC_CH3         (3U << 0)


void init_pa5(void)
{
    // enable clock GPIOA 
    RCC->RCC_AHB1ENR |= GPIOAEN;
    // PA5 set mode analog 
    GPIOA->GPIO_MODER &= ~ (3U << 10);
    GPIOA->GPIO_MODER |= (3U << 10);

    // enable clock ADC1
    RCC->RCC_APB2ENR |= ADC1EN;
    // channel 3 is the fisrst conversion in regular channel group conversion 
    ADC1->ADC_SQR3 &= ~(0x1F << 0); // 0001 1111
    ADC1->ADC_SQR3 |= (5U << 0);
    // we are have single channel conversion 
    ADC1->ADC_SQR1 &= ~ (0xF << 20);
    // enable conversion 
    ADC1->ADC_CR2 |= (1U << 0); // adont 
}

void start_conversion_single_channel(void)
{
    ADC1->ADC_CR2 |= (1U << 30);
}

uint16_t read_analog(void)
{
    while(!(ADC1->ADC_SR & (1U <<1)));
    return ADC1->ADC_DR;
}
