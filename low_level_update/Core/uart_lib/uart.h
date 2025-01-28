/*
 * uart.h
 *
 *  Created on: Jan 26, 2025
 *      Author: Phat
 */

#ifndef UART_LIB_UART_H_
#define UART_LIB_UART_H_

#include "exti.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "define.h"
#include "adc.h"


/**
 * formula for calculate baudrate
 * baudrate = flck/(8*(2-OVER8)*USARTDIV)
 */

#define TX_EN           (1U << 3)
#define RX_EN           (1U << 2)
#define USART1_EN       (1U << 13)

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

#define USART1 		((USART_Typedef*)USART1_BASE)
#define TRANSMISSION_COMPLETE       (1U << 7)

#define USART1_CLOCK_EN             (1U << 4)       
#define RECEIVER_DATA_RXNE			(1U << 5)



typedef struct 
{
    volatile uint8_t size;
    volatile uint8_t array[5];
	volatile uint8_t data;
    volatile bool haveISR;
}Handle_variable_t;

extern Handle_variable_t myData;
void printCharacter(uint8_t c);

class Usart1 : public ADC
{
private:

public:
    Usart1();
    void uart1_txrx(void);
    void myPrintf(const char *fmt,...);
    uint8_t readData();
	void check_receive_uart_and_send();
	void processDataOfInterruptRx(Handle_variable_t *_data);
};




#endif /* UART_LIB_UART_H_ */
