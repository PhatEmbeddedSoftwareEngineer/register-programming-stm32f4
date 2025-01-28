/*
 * exti.c
 *
 *  Created on: Jan 27, 2025
 *      Author: Phat
 */

#include "exti.h"
#include "uart.h"
event_t _even;
void initVariable(event_t *init)
{
    init->evenISR = false;
    init->cnt =0;
}

void pc13_init_exti(void)
{
	//1 diable irq
	__disable_irq();
	//2 enable clock GPIOC
	RCC->RCC_AHB1ENR |= EN_CLOCK_GPIOC;
	//3 config pin13 input
	GPIOC->GPIO_MODER &= ~(3U << 26); // input
	// config pull-up pin 13
	GPIOC->GPIO_PUPDR &= ~(3U << 26);
	GPIOC->GPIO_PUPDR |= (1U <<26);
	// enable clock syscfg
	RCC->RCC_APB2ENR |= EN_CLOCK_SYSCFG;
	// config external interrupt syscfg
	SYSCFG->SYSCFG_EXTICR4 |= (2U << 4);
	// disable mask in line 13
	EXTI->EXTI_IMR |= UNMASK_LINE_13;
	// choice falling trigger
	EXTI->EXTI_FTSR |= FALLING_TRIGGER_LINE_13;
	// enable irq nvic dòng ngắt nằm trong khoảng từ 10 đến 15
	__NVIC_EnableIRQ(EXTI15_10);
	// enable irq
	__enable_irq();
	initVariable(&_even);
}

static void callBack(event_t *process)
{
    printf("even come from EXTI13 line:= %d and cnt:= %d\n", process->evenISR= !process->evenISR, ++process->cnt);
}
void EXTI15_10_IRQHandler(void)
{
    if((EXTI->EXTI_PR & (1U << 13)))
    {
        EXTI->EXTI_PR |= (1U << 13);
        callBack(&_even);
    }
}

