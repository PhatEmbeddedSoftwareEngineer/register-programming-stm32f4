#include <stdint.h>
#include "define.h"
#include <string.h>
#include "../lib/exti.h"
#include "../lib/uart.h"
#include "../lib/systick.h"
#include "../lib/adc.h"
#include "../lib/timer.h"
#include "../lib/dma.h"

/**
 * how to use dma for transmit data in peripheral usart1 
 * // step 1 init uart1 
 * // step 2 init dma for tx 
 */


int main(void)
{
	char msg[] = "hello world\r\n";
	int leng = strlen(msg);
	uart1_rxtx();
	init_dma2_usart1_tx((uint32_t)&USART1->USART_DR,(uint32_t)&msg,leng);
	while(1)
	{
		//myPrintf("hello world: %.2f\n",a);
		//processDataOfInterruptRx(&_data);
		//delay_ms(500);
		
	}
	//return 0;
}


