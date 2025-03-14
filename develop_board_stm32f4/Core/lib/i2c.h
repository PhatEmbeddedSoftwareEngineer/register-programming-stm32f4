#pragma once
#ifndef I2C_H
#define I2C_H

#include "define.h"
/**
 * PB9 ---> I2C1_SDA
    PB8 ---> I2C1_SCL
 */
typedef struct 
{
    volatile uint32_t I2C_CR1;
    volatile uint32_t I2C_CR2;
    volatile uint32_t I2C_OAR1;
    volatile uint32_t I2C_OAR2;
    volatile uint32_t I2C_DR;
    volatile uint32_t I2C_SR1;
    volatile uint32_t I2C_SR2;
    volatile uint32_t I2C_CCR;
    volatile uint32_t I2C_TRISE;
    volatile uint32_t I2C_FLTR;
}I2C_Typedef_t;

#define I2C1    ((I2C_Typedef_t *)I2C1_BASE)
#define GPIOB_EN        (1U << 1)
#define I2C1_EN         (1U << 21)
#define I2C1_100KHZ_HSI     80
#define MAX_RISE_TIME_SM_MODE       17
#define SR2_BUSY        (1U << 1)
#define CR1_START       (1U << 8)
#define SR1_SB          (1U << 0)
#define SR1_ADDR        (1U << 1)
#define SR1_TXE         (1U << 7)
#define CR1_ACK         (1U << 10)
#define CR1_STOP        (1U << 9)
#define SR1_RXNE        (1U << 6)
#define SR1_BTF			(1U << 2)

void init_i2c1(void);
void I2C1_byteRead(char saddr, char maddr, char *data);

#endif
