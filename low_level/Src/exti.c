#include "exti.h"
#include "uart.h"
#include <stdio.h>

extern event_t _even;
//event_t _even;
void initVariable(event_t *init);
void pc13_init_exti(void)
{
    //1
    __disable_irq();
    //2
    RCC->RCC_AHB1ENR |= (1U <<2);
    //3
    GPIOC->GPIO_MODER &= ~(3U << 26); // input 
    GPIOC->GPIO_PUPDR &= ~(3U << 26);
    GPIOC->GPIO_PUPDR |= (1U <<26);
    //4
    RCC->RCC_APB2ENR |= (1U << 14); // enable clock systick
    //5
    SYSCFG->SYSCFG_EXTICR4 &= ~(15U << 4); // clear
    SYSCFG->SYSCFG_EXTICR4 |= (1U << 5);
    // 6
    EXTI->EXTI_IMR |= (1U << 13); 
    // 7
    EXTI->EXTI_FTSR |= (1U << 13);
    // 8
    __NVIC_EnableIRQ(EXTI15_10);
    // 9
    __enable_irq();
    
    // event_t init ={
    //     .evenISR = false,
    //     .cnt =0,
    // };
    initVariable(&_even);

}

void initVariable(event_t *init)
{
    init->evenISR = false;
    init->cnt =0;   
}
// we are continue , demo code with even external interrupt on gpio 

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
