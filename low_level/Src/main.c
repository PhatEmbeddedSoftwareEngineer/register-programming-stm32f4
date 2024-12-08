#include <stdint.h>
#include "define.h"

typedef struct 
{
	volatile uint32_t GPIO_MODER; // 0x00
	volatile uint32_t GPIO_OTYPER; // 0x04
	volatile uint32_t GPIO_OSPEEDR; // 0x08
	volatile uint32_t GPIO_PUPDR; // 0x0C
	volatile uint32_t GPIO_IDR; // 0x10
	volatile uint32_t GPIO_ODR; // 0x14
	volatile uint32_t GPIO_BSRR; // 0x18
	volatile uint32_t GPIO_LCKR; // 0x1C
	volatile uint32_t GPIO_AFR[2]; // 0x20 - 0x24  // 0 is low and 1 is high 
}GPIO_Typedef;

typedef struct 
{
	volatile uint32_t RCC_CR; 
	volatile uint32_t RCC_PLLCFGR;
	volatile uint32_t RCC_CFGR;
	volatile uint32_t RCC_CIR;
	volatile uint32_t RCC_AHB1RSTR;
	volatile uint32_t RCC_AHB2RSTR;
	uint32_t RESERVED[2];
	volatile uint32_t RCC_APB1RSTR;
	volatile uint32_t RCC_APB2RSTR;
	uint32_t RESERVED1[2];
	volatile uint32_t RCC_AHB1ENR;
	volatile uint32_t RCC_AHB2ENR;
	uint32_t RESERVED2[2];
	volatile uint32_t RCC_APB1ENR;
	volatile uint32_t RCC_APB2ENR;
	uint32_t RESERVED3[2];
	volatile uint32_t RCC_AHB1LENR; 
	volatile uint32_t RCC_AHB2LENR;
	uint32_t RESERVED4[2];
	volatile uint32_t RCC_APB1LENR;
	volatile uint32_t RCC_APB2LENR;
	uint32_t RESERVED5[2];
	volatile uint32_t RCC_BDCR;
	volatile uint32_t RCC_CSR;
	uint32_t RESERVED6[2];
	volatile uint32_t RCC_SSCGR;
	volatile uint32_t RCC_PLLI2SCFGR;
	uint32_t RESERVED7;
	volatile uint32_t RCC_DCKCFGR;

}RCC_Typedef;

typedef struct 
{
	volatile uint32_t USART_SR;
	volatile uint32_t USART_DR;
	volatile uint32_t USART_BRR;
	volatile uint32_t USART_CR1;
	volatile uint32_t USART_CR2;
	volatile uint32_t USART_CR3;
	volatile uint32_t USART_GTPR;
}USART_Typedef;

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
	// 2. set baudrate
	USART1->USART_BRR |= (8U << 4) | (11U << 0);
	// 3. SET MODE TE
	USART1->USART_CR1 |= (1U << 3);
	// 4. 1 bit start, 8 bit data, 1 stop bit
	USART1->USART_CR1 |= (1U << 12);
	USART1->USART_CR2 &= ~(3U << 12);
	//  5. enable usart
	USART1->USART_CR1 |= (1U<<13);//enable uart


	while(1)
	{
		while (!(USART1->USART_SR & (1<<6)));
		USART1->USART_DR = ('P' & 0xFF);

		for(int i = 0; i < 1000000; i++);
		// if((GPIOC->GPIO_IDR & BTN_PIN)==0)
		// {
		// 	GPIOA->GPIO_ODR ^= LED_PIN;
		// 	for(int i = 0; i < 1000000; i++);
		// }
		
	}
}

