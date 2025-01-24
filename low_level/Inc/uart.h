#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "exti.h"

typedef struct 
{
    volatile uint8_t size;
    volatile uint8_t array[5];
	volatile uint8_t data;
    volatile bool haveISR;
}Handle_variable_t;

extern Handle_variable_t myData;

int __io_putchar(int ch);
uint8_t readData();
void uart1_rxtx(void);
void debug(char *str);
void print(uint8_t data);
void check_receive_uart_and_send();
