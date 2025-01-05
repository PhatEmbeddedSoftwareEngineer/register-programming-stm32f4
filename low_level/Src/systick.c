#include "systick.h"

void delay_ms(int ms)
{
    SYSTICK->SYST_RVR = 16000; 
    SYSTICK->SYST_CVR = 0;
    SYSTICK->SYST_CSR |= (1U << 0) | (1U << 2);

    for(int i=0; i <ms;i++)
    {
        while(!(SYSTICK->SYST_CSR & (1U << 16)));
    }
    SYSTICK->SYST_CSR = 0;
}

