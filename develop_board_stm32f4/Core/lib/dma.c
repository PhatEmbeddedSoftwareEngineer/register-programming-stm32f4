#include "dma.h"

void init_dma2_usart1_tx(uint32_t dst, uint32_t source, uint16_t len)
{
    /*Enable clock access to DMA*/
    RCC->RCC_AHB1ENR |= CLOCK_DMA2_EN;
    /*Disable DMA2 Stream7*/
    DMA2->DMA_S7CR &= ~ CR_EN;
    /*wait until DMA2 Stream7 is disable */
    while(DMA2->DMA_S7CR & CR_EN);
    /*Clear all interrupt flags of Stream6*/
    DMA2->DMA_HIFCR |= (1U << 22);
    DMA2->DMA_HIFCR |= (1U << 24);
    DMA2->DMA_HIFCR |= (1U << 25);
    DMA2->DMA_HIFCR |= (1U << 26);
    DMA2->DMA_HIFCR |= (1U << 27);
    /*Set the destination buffer*/
    DMA2->DMA_S7PAR |= dst;
    /*Set the source buffer*/
    DMA2->DMA_S7M0AR |= source;
    /*Set length*/
    DMA2->DMA_S7NDTR = len;
    /*Select Stream7 CH4*/
    DMA2->DMA_S7CR |= CHOOSE_CHANNEL_4;
    /*Enable memory increment*/
    DMA2->DMA_S7CR |= MEM_INC_MODE;
    /*Configure transfer direction*/
    DMA2->DMA_S7CR |= MEM_TO_PER;
    /*enable DMA transfer complete interrupt*/
    DMA2->DMA_S7CR |= TCIE_EN;
    /*Enable direct mode and disable FIFO*/
    DMA2->DMA_S7FCR &= ~ FIFO_ERROR_INTERRUPT_ENABLE ;
    DMA2->DMA_S7FCR &= ~ DIRECT_MODE_DISABLE;
    /*Enable DMA2 Stream7*/
    DMA2->DMA_S7CR |= CR_EN;
    /*Enable USART1 transmitter DMA*/
    USART1->USART_CR3 |= DMA_ENABLE_TRANSMITTER;
    /*DMA Interrupt enable in NVIC*/
    __NVIC_EnableIRQ(DMA2_Stream7);
}

static void dma_callBack(void)
{

	myPrintf("\nDMA TX run success\n");
}

void DMA2_Stream7_IRQHandler(void)
{
	if(DMA2->DMA_HISR & (DMA_TCIF7))
	{
		DMA2->DMA_HIFCR |= DMA_CTCIF7;
		dma_callBack();
	}
}

