#include "uart.h"
#include "define.h"
#include <stdio.h>
#include "adc.h"
#include "systick.h"

int __io_putchar(int ch)
{	
	USART1->USART_DR = (ch & 0xFF);
	while(!(USART1->USART_SR & (1U << 7)));
	return ch;
}
uint8_t readData()
{
	while(!(USART1->USART_SR & (1U << 5))); // position 5 == 1
	//if(!(USART1->USART_SR & (1U << 5)));
	return USART1->USART_DR;
}

void uart1_rxtx(void)
{
	// PA9 TX 
	// 1. enable clock gpioa
	RCC->RCC_AHB1ENR |= GPIOA_ENABLE;
	//2 . set mode alternate 
	GPIOA->GPIO_MODER &= ~(1U << 18); 
	GPIOA->GPIO_MODER |= (1U << 19);
	// 3.  SET ALTERNATE PIN FOR PA9
	GPIOA->GPIO_AFR[1] &= ~ (0xF << 4);
	GPIOA->GPIO_AFR[1] |= (1U << 6) | (1U << 5) | (1U << 4);
	// PA10 RX 
	// set mode alternate
	GPIOA->GPIO_MODER &= ~(3U << 20);
	GPIOA->GPIO_MODER |= (2U << 20); 

	// set alternate pin for PA10
	GPIOA->GPIO_AFR[1] &= ~ (0xF << 8);
	GPIOA->GPIO_AFR[1] |= (7U << 8);

	// 1. enable clock usart 1
	RCC->RCC_APB2ENR |= USART1_ENABLE;
	// over8 = 0
	USART1->USART_CR1 &= ~ (1U << 15); // OVER8 ==0 
	// 2. set baudrate
	USART1->USART_BRR |= (8U << 4) | (11U << 0);
	// 3. SET MODE TE
	USART1->USART_CR1 |= (1U << 3);

	// SET MODE RX 
	USART1->USART_CR1 |= (1U << 2);

	// 4. 1 bit start, 8 bit data, 1 stop bit
	USART1->USART_CR1 &= ~ (1U << 12);
	USART1->USART_CR2 &= ~(3U << 12);
	//  5. enable usart
	USART1->USART_CR1 |= (1U<<13);//enable uart
}
void check_receive_uart_and_send()
{
	switch(readData())
	{
		case 'R':
		{
			printf("channel 6 adc: %d\n",read_analog());
			delay_ms(1000);
			//for(int i = 0; i < 100000; i++);
			//printf("Hello world\n");
			break;
		}
		default:
		{
			break;
		}
	}
}
