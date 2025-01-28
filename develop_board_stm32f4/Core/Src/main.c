#include <stdint.h>
#include "define.h"

#include "../lib/exti.h"
#include "../lib/uart.h"
#include "../lib/systick.h"
#include "../lib/adc.h"


int main(void)
{
	/**
	 * how to generate interrupt using systick ? see code below 
	 */
	uart1_rxtx();
	//init_channel5();
	//start_conversion_continous_single_channel();
	//float a= 3.14;
	create_1hz_interrupt_systick();

	while(1)
	{
		//myPrintf("hello world: %.2f\n",a);
		//processDataOfInterruptRx(&_data);
		//delay_ms(500);
		
	}
	//return 0;
}

