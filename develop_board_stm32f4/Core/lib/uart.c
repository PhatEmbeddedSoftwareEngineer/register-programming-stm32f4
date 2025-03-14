/*
 * uart.c
 *
 *  Created on: Jan 27, 2025
 *      Author: Phat
 */

#include "../lib/uart.h"

myStruct _data;
#define USE_INTERRUPT_RECEIVER
static void printCharacter(uint8_t data);
void initStructData(myStruct *ptr)
{
	ptr->data = 0;
	ptr->haveData = false;
}

void uart1_rxtx(void)
{
	// 1. enable clock gpioa
	RCC->RCC_AHB1ENR |= GPIOA_ENABLE;
	// 2. set mode alternate for PA9 TX
	GPIOA->GPIO_MODER &= ~(3U << 18);
	GPIOA->GPIO_MODER |= (2U << 18);
	GPIOA->GPIO_AFR[1] |= (7U << 4);

	// 3.set mode alternate for P10 RX
	GPIOA->GPIO_MODER |= (2U << 20);
	GPIOA->GPIO_AFR[1] |= (7U << 8);

	// enable clock USART1
	RCC->RCC_APB2ENR |= USART1_CLOCK_EN;

	// config baudrate 115200
	// chose oversampling 16
	USART1->USART_CR1 &= ~ (1U << 15);
	USART1->USART_BRR |= (8U << 4) | (11U << 0);

	//configure 1 bit start, 8 bit data, 1 stop bit
	USART1->USART_CR1 &= ~(1U << 12);
	USART1->USART_CR2 &= ~(3U << 12);

	// enable transmit data
	USART1->USART_CR1 |= TX_EN;
	// enable receive data
	USART1->USART_CR1 |= RX_EN;

	#ifdef USE_INTERRUPT_RECEIVER
	USART1->USART_CR1 |= (1U << 5);
	__NVIC_EnableIRQ(USART1_position);
	initStructData(&_data);
	#endif

	// enable USART1
	USART1->USART_CR1 |= USART1_EN;

}

void USART1_IRQHandler()
{

	if(USART1->USART_SR & (1U <<5))
	{
		_data.haveData = true;
		_data.data = USART1->USART_DR;
		printCharacter(_data.data);
	}

}
static void printCharacter(uint8_t data)
{
	USART1->USART_DR = (data & 0xFF);
	while(!(USART1->USART_SR & (1U << 7)));
}
uint8_t readData(void)
{
    while(!(USART1->USART_SR & RECEIVER_DATA_RXNE ));
    return USART1->USART_DR;
}

static void tranmissionEachByte(char *str)
{
    int ch;
    while(*str)
    {
        ch = *str;
        USART1->USART_DR = ch & 0xFF;
        while(!(USART1->USART_SR & TRANSMISSION_COMPLETE));
        str++;
    }
}

void myPrintf(const char *fmt,...)
{
	va_list args;
	va_start(args,fmt);
	char buffer[256];
	vsnprintf(buffer,sizeof(buffer),fmt,args);
	tranmissionEachByte(buffer);
	va_end(args);
}
void check_receive_uart_and_send()
{
	 switch(readData())
	{
		case 'R':
		{
			//printf("channel 6 adc: %d\n",read_analog());
			//delay_ms(1000);
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
void processDataOfInterruptRx(myStruct *myData)
{
	if(myData->haveData )
	{
		//debug((char*)&myData.data);
		printCharacter(myData->data);
		myData->haveData=false;
	}
}
