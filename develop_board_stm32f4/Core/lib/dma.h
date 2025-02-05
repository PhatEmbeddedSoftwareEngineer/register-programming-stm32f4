#pragma once
#include "define.h"
#include "uart.h"
#include "exti.h"

#define CLOCK_DMA1_EN       (1U << 21)
#define CLOCK_DMA2_EN       (1U << 22)

typedef struct 
{
    /**
     *  DMA_LISR
        DMA_HISR
        DMA_LIFCR
        DMA_HIFCR
     */
    volatile uint32_t DMA_LISR;
    volatile uint32_t DMA_HISR;
    volatile uint32_t DMA_LIFCR;
    volatile uint32_t DMA_HIFCR;
    /**
     * DMA_S0CR
        DMA_D0NDTR
        DMA_S0PAR
        DMA_S0M0AR
        DMA_S0M1AR
        DMA_S0FCR
     */
    volatile uint32_t DMA_S0CR;
    volatile uint32_t DMA_D0NDTR;
    volatile uint32_t DMA_S0PAR;
    volatile uint32_t DMA_S0M0AR;
    volatile uint32_t DMA_S0M1AR;
    volatile uint32_t DMA_S0FCR;
    /**
     * DMA_S1CR
        DMA_S1NDTR
        DMA_S1PAR
        DMA_S1M0AR
        DMA_S1M1AR
        DMA_S1FCR
     */
    volatile uint32_t DMA_S1CR;
    volatile uint32_t DMA_S1NDTR;
    volatile uint32_t DMA_S1PAR;
    volatile uint32_t DMA_S1M0AR;
    volatile uint32_t DMA_S1M1AR;
    volatile uint32_t DMA_S1FCR;

    volatile uint32_t DMA_S2CR;
    volatile uint32_t DMA_S2NDTR;
    volatile uint32_t DMA_S2PAR;
    volatile uint32_t DMA_S2M0AR;
    volatile uint32_t DMA_S2M1AR;
    volatile uint32_t DMA_S2FCR;

    volatile uint32_t DMA_S3CR;
    volatile uint32_t DMA_S3NDTR;
    volatile uint32_t DMA_S3PAR;
    volatile uint32_t DMA_S3M0AR;
    volatile uint32_t DMA_S3M1AR;
    volatile uint32_t DMA_S3FCR;

    volatile uint32_t DMA_S4CR;
    volatile uint32_t DMA_S4NDTR;
    volatile uint32_t DMA_S4PAR;
    volatile uint32_t DMA_S4M0AR;
    volatile uint32_t DMA_S4M1AR;
    volatile uint32_t DMA_S4FCR;

    volatile uint32_t DMA_S5CR;
    volatile uint32_t DMA_S5NDTR;
    volatile uint32_t DMA_S5PAR;
    volatile uint32_t DMA_S5M0AR;
    volatile uint32_t DMA_S5M1AR;
    volatile uint32_t DMA_S5FCR;

    volatile uint32_t DMA_S6CR;
    volatile uint32_t DMA_S6NDTR;
    volatile uint32_t DMA_S6PAR;
    volatile uint32_t DMA_S6M0AR;
    volatile uint32_t DMA_S6M1AR;
    volatile uint32_t DMA_S6FCR;

    volatile uint32_t DMA_S7CR;
    volatile uint32_t DMA_S7NDTR;
    volatile uint32_t DMA_S7PAR;
    volatile uint32_t DMA_S7M0AR;
    volatile uint32_t DMA_S7M1AR;
    volatile uint32_t DMA_S7FCR;

}DMA_Typedef_t;

#define DMA1        ((DMA_Typedef_t*)DMA1_BASE)
#define DMA2        ((DMA_Typedef_t*)DMA2_BASE)

#define CR_EN       (1U << 0)
#define CHOOSE_CHANNEL_4        (4U << 25)
#define MEM_INC_MODE            (1U << 10)
#define MEM_TO_PER              (1U << 6)
#define TCIE_EN                 (1U << 4)
#define FIFO_ERROR_INTERRUPT_ENABLE         (1U << 7)
#define DIRECT_MODE_DISABLE                 (1U << 2)
#define DMA_ENABLE_TRANSMITTER              (1U << 7)
#define DMA_TCIF7                           (1U << 27)
#define DMA_CTCIF7                          (1U << 27)
/**
 * các bước để cấu hình một dma tx bare metal hiện tại các bước này là của usart2 mình cần 
 * phải chuyển thành usart1 
/ 
/*Enable clock access to DMA*/
/**
 * enable clock dma1 
 * RCC->RCC_AHB1ENR |= CLOCK_DMA1_EN
 * enable clock dma2 
 * RCC->RCC_AHB1ENR |= CLOCK_DMA2_EN 
 * 
 */
/*Disable DMA1 Stream6*/
/**
 * if use dma1 stream6 channel 4 
 * DMA1->DMA_S6CR &= ~ CR_EN;
 * if use USART1_TX DMA2 Stream 7 channel 4
 * DMA2->DMA_S7CR &= ~ CR_EN;
 * 
 */
/*wait until DMA1 Stream6 is disable */
/**
 * if use dma1 stream6 channel 4
 * while(DMA1->DMA_S6CR & CR_EN);
 * if use dma2 stream7 channel 4
 * while(DMA2->DMA_S7CR & CR_EN);
 */
/*Clear all interrupt flags of Stream6*/
/**
 * if use dma1 stream 6 
 * DMA1->DMA_HIFCR |= (1U << 16);
 * DMA1->DMA_HIFCR |= (1U << 18);
 * DMA1->DMA_HIFCR |= (1U << 19);
 * DMA1->DMA_HIFCR |= (1U << 20);
 * DMA1->DMA_HIFCR |= (1U << 21);
 * if use dma2 stream 7
 * DMA2->DMA_HIFCR |= (1U << 22);
 * DMA2->DMA_HIFCR |= (1U << 24);
 * DMA2->DMA_HIFCR |= (1U << 25);
 * DMA2->DMA_HIFCR |= (1U << 26);
 * DMA2->DMA_HIFCR |= (1U << 27);
 * 
 * 
 */
/*Set the destination buffer*/
/**
 * if use dma1 stream 6
 * DMA1->DMA_S6PAR |= dst;
 * if use dma2 stream 7 
 * DMA2->DMA_S7PAR |= dst;
 * 
 */
/*Set the source buffer*/
/**
 * if use dma1 stream 6
 * DMA1->DMA_S6M0AR |= src;
 * if use dma2 stream 7
 * DMA2->DMA_S7M0AR |= src;
 * 
 */
/*Set length*/
/**
 * if use dma6 stream 6
 * DMA1->DMA_S6NDTR = len;
 * if use dma2 stream 7
 * DMA2->DMA_S7NDTR = len;
 */
/*Select Stream6 CH4*/
/**
 * if use dma1 stream 6 channel 4
 * DMA1->DMA_S6CR |= CHOOSE_CHANNEL_4;
 * if use dma2 stream 7 channel 4
 * DMA2->DMA_S7CR |= CHOOSE_CHANNEL_4;
 * 
 */
/*Enable memory increment*/
/**
 * if use dma1 stream 6 channel 4
 * DMA1->DMA_S6CR |= MEM_INC_MODE;
 * if use dma2 stream 7 channel 4
 * DMA2->DMA_S7CR |= MEM_INC_MODE;
 */
/*Configure transfer direction*/
/**
 * if use dma1 stream 6 channel 4
 * DMA1->DMA_S6CR |= MEM_TO_PER;
 * if use dma2 stream 7 channel 4
 * DMA2->DMA_S7CR |= MEM_TO_PER;
 */
/*enable DMA transfer complete interrupt*/
/**
 * if use dma1 stream 6 channel 4
 * DMA1->DMA_S6CR |= TCIE_EN;
 * if use dma2 stream 7 channel 4
 * DMA2->DMA_S7CR |= TCIE_EN;
 * 
 */
/*Enable direct mode and disable FIFO*/
/**
 * if use dma1 stream 6 channel 4
 * DMA1->DMA_S6FCR &= ~ FIFO_ERROR_INTERRUPT_ENABLE ;
 * DMA1->DMA_S6FCR &= ~ DIRECT_MODE_DISABLE;
 * if use dma2 stream 7 channel 4
 * DMA2->DMA_S7FCR &= ~ FIFO_ERROR_INTERRUPT_ENABLE ;
 * DMA2->DMA_S7FCR &= ~ DIRECT_MODE_DISABLE;
 * 
 */
/*Enable DMA1 Stream6*/
/**
 * if use dma1 stream 6 channel 4
 * DMA1->DMA_S6CR |= CR_EN;
 * if use dma2 stream 7 channel 4
 * DMA2->DMA_S7CR |= CR_EN;
 */
/*Enable UART2 transmitter DMA*/
/**
 * USART2->UART_CR3 |= DMA_ENABLE_TRANSMITTER;
 */
/*Enable USART1 transmitter DMA*/
/**
 * USART1->UART_CR3 |= DMA_ENABLE_TRANSMITTER;
 */
/*DMA Interrupt enable in NVIC*/
/**
 * if use dma1 stream 6 channel 4
 * __NVIC_EnableIRQ(DMA1_Stream6);
 * if use dma2 stream 7 channel 4
 * __NVIC_EnableIRQ(DMA2_Stream7);
 */

void init_dma2_usart1_tx(uint32_t dst, uint32_t source, uint16_t len);