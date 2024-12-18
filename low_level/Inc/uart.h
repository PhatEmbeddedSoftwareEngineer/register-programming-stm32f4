#pragma once
#include <stdint.h>
#include <stdbool.h>

int __io_putchar(int ch);
uint8_t readData();
void uart1_rxtx(void);

void check_receive_uart_and_send(uint8_t data,bool *read);
