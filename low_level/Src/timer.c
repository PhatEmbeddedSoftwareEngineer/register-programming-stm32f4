#include "timer.h"


void init_timer2_1hz()
{
    RCC->RCC_APB1ENR |= TIM2_EN;
    /**
     * in default , hsi have frequency = 16mhz, i want create 1hz then :
     * hz = fclk / ((PSC-1)*(ARR-1));
     * hz = 16 000 000 / ((1600-1)*(10000-1)) = 1
     * i will get 1s 
     */
    TIM2->TIMx_PSC = 1600-1;
    TIM2->TIMx_ARR = 10000-1; // max = 65535
    TIM2->TIMx_CNT = 0;
    TIM2->TIMx_CR1 |= TIM2_CEN;

}

void init_pa5_timer2_1hz()
{
    RCC->RCC_APB1ENR |= TIM2_EN;
    RCC->RCC_AHB1ENR |= (1U << 0);
    // set alternate pin for channel 5
    GPIOA->GPIO_MODER |= (2U << 10);
    GPIOA->GPIO_AFR[0] |= (1U << 20);

    /**
     * in default , hsi have frequency = 16mhz, i want create 1hz then :
     * hz = fclk / ((PSC-1)*(ARR-1));
     * hz = 16 000 000 / ((1600-1)*(10000-1)) = 1
     * i will get 1s 
     */
    /**
     * in channel 5 I create frequency 1hz with prescaler 1600 -1 and ARR = 10000 -1 
     * for measure signal i need width signal bigger than signal of channel 5
     */
    TIM2->TIMx_PSC = 1600-1;
    TIM2->TIMx_ARR = 10000-1; // max = 65535
    TIM2->TIMx_CNT = 0;

    TIM2->TIMx_CCMR1 |= (1U << 4) | (1U << 5);
    TIM2->TIMx_CCER |= (1U <<0);


    TIM2->TIMx_CR1 |= TIM2_CEN;

}
void init_pa6_input_capture()
{
    RCC->RCC_AHB1ENR |= (1U << 0); // enable clock A 

    GPIOA->GPIO_MODER &= ~(3U << 12); // clear 
    GPIOA->GPIO_MODER |= (2U << 12); // alternate function

    GPIOA->GPIO_AFR[0] &= ~(15U << 24); // clear
    GPIOA->GPIO_AFR[0] |= (2U << 24);

    RCC->RCC_APB1ENR |= (1U << 1); // enable clock TIM3
    TIM3->TIMx_PSC = 16000 -1 ; // 16 000 000 / 1600
    TIM3->TIMx_CCMR1 |= (1U << 0); 
    TIM3->TIMx_CCER |= (1U << 0);
    TIM3->TIMx_CR1 |= (1U << 0);

}


