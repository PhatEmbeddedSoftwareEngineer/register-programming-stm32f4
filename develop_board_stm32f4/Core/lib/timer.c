/*
 * timer.c
 *
 *  Created on: Jan 27, 2025
 *      Author: Phat
 */

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
    TIM2->TIMx_PSC = 1600-1; // 16 000 000 / 1600 = 10000
    TIM2->TIMx_ARR = 10000-1; // max = 65535
    TIM2->TIMx_CNT = 0;
    TIM2->TIMx_CR1 |= TIM2_CEN;
    /**
     * kết hợp hàm ở dưới để tạo delay
     */
//		 while(!(TIM2->TIMx_SR & TIM2_SR_UIF));
//		 TIM2->TIMx_SR &= ~ (TIM2_SR_UIF);
}

void init_pa5_timer2_1hz()
{
    RCC->RCC_APB1ENR |= TIM2_EN;
    RCC->RCC_AHB1ENR |= CLOCK_GPIOA_EN;
    // set alternate pin for channel 5
    GPIOA->GPIO_MODER |= (2U << 10);
    // AF01 TIM2_CH1
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
    // choose toggle when TIMx_CNT == TIMx_CCR1
    TIM2->TIMx_CCMR1 |= (1U << 4) | (1U << 5); // toggle
    // capture/compare 1 output enable
    TIM2->TIMx_CCER |= (1U <<0); //
    // start  Counter enabled , bắt đầu đếm
    TIM2->TIMx_CR1 |= TIM2_CEN;
}

void init_pa6_input_capture()
{
    RCC->RCC_AHB1ENR |= (1U << 0); // enable clock A

    GPIOA->GPIO_MODER &= ~(3U << 12); // clear
    GPIOA->GPIO_MODER |= (2U << 12); // alternate function

    GPIOA->GPIO_AFR[0] &= ~(15U << 24); // clear
    // AF02 TIM3_CH1
    GPIOA->GPIO_AFR[0] |= (2U << 24);

    RCC->RCC_APB1ENR |= (1U << 1); // enable clock TIM3
    // độ rộng xung lớn hơn để có thể chụp được chân PA5
    TIM3->TIMx_PSC = 16000 -1 ; // 16 000 000 / 1600
    // configure input
    TIM3->TIMx_CCMR1 |= (1U << 0);
    // capture enable
    TIM3->TIMx_CCER |= (1U << 0);
    // start  Counter enabled , bắt đầu đếm
    TIM3->TIMx_CR1 |= TIM2_CEN;

}

void init_interrupt_timer_1hz()
{
    // enable clock timer2 in RCC 
    RCC->RCC_APB1ENR |= TIM2_EN;
    // caculate prescaler
    TIM2->TIMx_PSC = 1600-1; // 16 000 000 / 1600 = 10000
    // calculate arr
    TIM2->TIMx_ARR = 10000-1; // max = 65535
    // set value counter = zero
    TIM2->TIMx_CNT = 0;
    // enable update interrupt in TIMx_DIER register
    TIM2->TIMx_DIER |= UPDATE_INTERRUPT_EN;
    // enable timer interrupt in NVIC
    __NVIC_EnableIRQ(TIM2_position);
    // enable counter timer 2 
    TIM2->TIMx_CR1 |= TIM2_CEN;

}

static void callBackTimer(void)
{
    static int cnt=0;
    myPrintf("hello world:= %d\n",cnt++);
}

void TIM2_IRQHandler()
{
    // clear UIF bit when counter overflow 
    TIM2->TIMx_SR &= ~ TIM2_SR_UIF;
    // do function 
    callBackTimer();
}