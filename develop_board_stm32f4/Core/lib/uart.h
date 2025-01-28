/*
 * uart.h
 *
 *  Created on: Jan 27, 2025
 *      Author: Phat
 */

#ifndef LIB_UART_H_
#define LIB_UART_H_

#include <stdint.h>
#include "define.h"
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>

#include "../lib/exti.h"

/**
 * formula for calculate baudrate
 * baudrate = flck/(8*(2-OVER8)*USARTDIV)
 */

#define TX_EN           (1U << 3)
#define RX_EN           (1U << 2)
#define USART1_EN       (1U << 13)

#define USART1_CLOCK_EN             (1U << 4)
#define RECEIVER_DATA_RXNE			(1U << 5)
#define TRANSMISSION_COMPLETE       (1U << 7)



typedef struct
{
	volatile uint8_t data;
	volatile bool haveData;
}myStruct;
extern myStruct _data;

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



void uart1_rxtx(void);
//void print(uint8_t data);
uint8_t readData();
void myPrintf(const char *fmt,...);
void check_receive_uart_and_send();
void processDataOfInterruptRx(myStruct *myData);



#endif /* LIB_UART_H_ */
