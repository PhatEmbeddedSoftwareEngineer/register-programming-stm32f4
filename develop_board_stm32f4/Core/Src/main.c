#include <stdint.h>
#include "define.h"
#include <string.h>
#include "../lib/exti.h"
#include "../lib/uart.h"
#include "../lib/systick.h"
#include "../lib/adc.h"
#include "../lib/timer.h"
#include "../lib/dma.h"
#include "../lib/i2c.h"
#include "../lib/adxl345.h"

/**
 * how to use dma for transmit data in peripheral usart1 
 * // step 1 init uart1 
 * // step 2 init dma for tx 
 */

extern uint8_t data_rec[6];
const float SCALE_FACTOR = 0.0078;
int main(void)
{
	int16_t x,y,z;
	double xg, yg, zg;
	// char msg[] = "hello world\r\n";
	// int leng = strlen(msg);
	uart1_rxtx();
	adxl_init();
	//init_dma2_usart1_tx((uint32_t)&USART1->USART_DR,(uint32_t)&msg,leng);
	while(1)
	{
		adxl_read_values(DATA_START_ADDR);
		x = ((data_rec[1] << 8) | data_rec[0]);
		y = ((data_rec[3] << 8) | data_rec[2]);
		z = ((data_rec[5] << 8) | data_rec[4]);

		xg = (double)(x * SCALE_FACTOR);
		yg = (double)(y * SCALE_FACTOR);
		zg = (double)(z * SCALE_FACTOR);

		myPrintf("x: %d\n"
				"y: %d\n"
				"z: %d\n"
				"xg: %.2f\n"
				"yg: %.2f\n"
				"zg: %.2f\n",x,y,z,xg,yg,zg);
		delay_ms(100);
		
	}
}


