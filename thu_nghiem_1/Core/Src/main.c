#include <stdint.h>
#include "define.h"
void uart1_rxtx(void)
{
#if 1
	// PA9 TX
	// 1. enable clock gpioa
	RCC->RCC_AHB1ENR |= (1UL<<0);
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
	/**
	 * baudrate = flck/(8*(2-OVER8)*USARTDIV)
	 */
	USART1->USART_BRR |= (8U << 4) | (11U << 0);
	// 3. SET MODE TE
	USART1->USART_CR1 |= (1U << 3);

	// SET MODE RX
	USART1->USART_CR1 |= (1U << 2);

	// 4. 1 bit start, 8 bit data, 1 stop bit
	USART1->USART_CR1 &= ~ (1U << 12);
	USART1->USART_CR2 &= ~(3U << 12);
	// 6 enable interrupt rx
	USART1->USART_CR1 |= (1U << 5);
	__NVIC_EnableIRQ(USART1_position);
	//  5. enable usart
	USART1->USART_CR1 |= (1U<<13);//enable uart
#endif

}
volatile uint8_t data;
void USART1_IRQHandler()
{

	if(USART1->USART_SR & (1U <<5))
	{
		//myData.haveISR=true;
		data = USART1->USART_DR;

		//printf("%c",myData.data);
		// if(myData.size < 5)
		// {
		// 	myData.array[myData.size++] = myData.data;
		// }
		// else
		// 	myData.size=0;
		//printf("%c\n",_var.data);
	}

}

void print(uint8_t data)
{
	USART1->USART_DR = (data & 0xFF);
	while(!(USART1->USART_SR & (1U << 7)));
}

int main(void)
{
	data=0;
	uart1_rxtx();
	print('p');
	while(1)
	{
		if(data != 0)
		{
			print(data);
		}
	}
	//return 0;
}
