#include <stdint.h>
#include "define.h"
#include <stdio.h>
#include "uart.h"
#include "adc.h"
#include <stdbool.h>
#include "systick.h"
#include "timer.h"
#include "exti.h"
event_t _even;
Handle_variable_t myData;
void printNumberFloat(float *num);
// hello my name is Phat ^^ to day I intoduce uart rx config 
#define PIN5					(1U<<5)
#define LED_PIN					PIN5
void processDataFromISRUsart(Handle_variable_t *_data);

int main()
{
//	myData.data=0;
//	myData.haveISR=false;
//	myData.size=0;
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
	// init_pa5();
	// start_conversion_single_channel();
	//init_pa6();
	//start_conversion_continous_single_channel();
	// init_pa5_timer2_1hz();
	// init_pa6_input_capture();
	//init_timer2_1hz();
	
	//uint32_t timeStamp = 0;
	/********************************************************************* */
	//pc13_init_exti();
	//debug("test\n");
	//int num = 1234;
//	printNumberFloat(&a);
//	printf("\n");
	//printf("hello world %d %.2f\n",10,3.14);
	while(1)
	{
		myPrintf("%c\n",myData.data);
		//processDataFromISRUsart(&myData);
		// if(_even.cnt ==10)
		// {
		 	//printf("hello world ^^\n");
		// }
		// while(!(TIM3->TIMx_SR & (1U << 1)));
		// timeStamp = TIM3->TIMx_CCR1;
		// printf("timestamp:= %ld\n",timeStamp);
//		 while(!(TIM2->TIMx_SR & TIM2_SR_UIF));
//		 TIM2->TIMx_SR &= ~ (TIM2_SR_UIF);
		//check_receive_uart_and_send();
		//printf("hello world\n");
		//delay_ms(1000);
		// if((GPIOC->GPIO_IDR & BTN_PIN)==0)
		// {
		// 	GPIOA->GPIO_ODR ^= LED_PIN;
		// 	for(int i = 0; i < 1000000; i++);
		// }
		
	}
}
void printNumberFloat(float *num)
{
	int int_part = (int)(*num);
	printInt(int_part);
	print('.');
	int decimal_part = (*num-int_part)*100;
	printInt(decimal_part);
}
void display(volatile uint8_t *data, uint16_t leng)
{
	for(int i=0;i<leng;i++)
	{
		printf("%c",data[i]);
	}
	printf("\n");
}
void processDataFromISRUsart(Handle_variable_t *_data)
{
	if(_data->haveISR )
	{
		//debug((char*)&myData.data);
		print(_data->data);
		_data->haveISR=false;
	}
}

