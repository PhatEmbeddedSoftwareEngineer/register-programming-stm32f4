#include <stdint.h>
#include "define.h"
#include <stdio.h>
#include "uart.h"
#include "adc.h"
#include <stdbool.h>

// hello my name is Phat ^^ to day I intoduce uart rx config 
#define PIN5					(1U<<5)
#define LED_PIN					PIN5


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
	uart1_rxtx();
	init_pa5();
	// uint8_t data;
	// bool readData;
	while(1)
	{
		// printf("wait receive data\n");
		// check_receive_uart_and_send(data,&readData);
		// if(readData)
		// {
		// 	start_conversion_single_channel();
		// 	printf("analog channel 5: %d\n",read_analog());
		// 	for(int i = 0; i < 1000; i++);
		// }
		// else 
		// {
		// 	printf("stop convertsion single mode\n");
		// }
			start_conversion_single_channel();
			printf("analog channel 5: %d\n",read_analog());
			for(int i = 0; i < 100000; i++);


		// if((GPIOC->GPIO_IDR & BTN_PIN)==0)
		// {
		// 	GPIOA->GPIO_ODR ^= LED_PIN;
		// 	for(int i = 0; i < 1000000; i++);
		// }
		
	}
}

