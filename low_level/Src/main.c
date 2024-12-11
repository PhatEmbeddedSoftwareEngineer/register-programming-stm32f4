#include <stdint.h>
#include "define.h"
#include <stdio.h>
// hello my name is Phat ^^ to day I intoduce use printf for bare metal 

#define RCC 		((RCC_Typedef*)RCC_BASE)
#define GPIOA		((GPIO_Typedef*)(GPIOA_BASE))
#define GPIOC      	((GPIO_Typedef*)(GPIOC_BASE))
#define GPIOC_ENABLE			(1U<<2)
#define PIN13		(1U<<13)
#define BTN_PIN		PIN13
#define USART2 		((USART_Typedef*)USART2_BASE)
#define USART1 		((USART_Typedef*)USART1_BASE)
#define USART2_ENABLE		(1U << 17)
#define USART1_ENABLE		(1U << 4)
#define BAUDRATE			115200	

#define SYS_FREQ			16000000
#define APB1_CLK			SYS_FREQ

#define GPIOA_ENABLE			(1UL<<0) // 0b 0000 0000 0000 0000 0000 0000 0000 0001
#define PIN5					(1U<<5)
#define LED_PIN					PIN5

int __io_putchar(int ch)
{
	while(!(USART1->USART_SR & (1U << 7)));
	USART1->USART_DR = (ch & 0xFF);
	return ch;
}

int main()
{
	// 1. enable clock gpioa
	// RCC->RCC_AHB1ENR |= GPIOA_ENABLE;
	// RCC->RCC_AHB1ENR |= GPIOC_ENABLE;
	// 2. set output for gpioa
	// GPIOA->GPIO_MODER |= (1U << 10); // set bit 10 to 1
	// GPIOA->GPIO_MODER &= ~ (1U << 11); // clear bit 11 to 0
	// GPIOC->GPIO_MODER &= ~(3U<<26); // input 
	//3. set pull up
	// set pin 26 to 1
	// set pin 27 to 0
	// GPIOC->GPIO_PUPDR |= (1U << 26);
	// GPIOC->GPIO_PUPDR &= ~(1U << 27);
	/***************************************************************************** */
	// PA9 TX 
	// 1. enable clock gpioa
	RCC->RCC_AHB1ENR |= GPIOA_ENABLE;
	//2 . set mode alternate 
	GPIOA->GPIO_MODER &= ~(1U << 18); 
	GPIOA->GPIO_MODER |= (1U << 19);
	// 3.  SET ALTERNATE PIN FOR PA9
	GPIOA->GPIO_AFR[1] &= ~ (0xF << 4);
	GPIOA->GPIO_AFR[1] |= (1U << 6) | (1U << 5) | (1U << 4);
	

	// 1. enable clock usart 1
	RCC->RCC_APB2ENR |= USART1_ENABLE;
	// over8 = 0
	USART1->USART_CR1 &= ~ (1U << 15); // OVER8 ==0 
	// 2. set baudrate
	USART1->USART_BRR |= (8U << 4) | (11U << 0);
	// 3. SET MODE TE
	USART1->USART_CR1 |= (1U << 3);
	// 4. 1 bit start, 8 bit data, 1 stop bit
	USART1->USART_CR1 &= ~ (1U << 12);
	USART1->USART_CR2 &= ~(3U << 12);
	//  5. enable usart
	USART1->USART_CR1 |= (1U<<13);//enable uart


	while(1)
	{
		printf("hello world \n");

		for(int i = 0; i < 1000000; i++);
		// if((GPIOC->GPIO_IDR & BTN_PIN)==0)
		// {
		// 	GPIOA->GPIO_ODR ^= LED_PIN;
		// 	for(int i = 0; i < 1000000; i++);
		// }
		
	}
}

