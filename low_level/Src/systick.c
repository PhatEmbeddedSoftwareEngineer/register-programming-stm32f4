#include "systick.h"

#define INTERNAL_CLOCK          (1U << 2)
#define COUNTER_EN              (1U << 0)
#define COUNTFLAG               (1U<<16)

void delay_ms(int ms)
{
    /**
     * muốn tạo delay 1ms áp dụng công thức do đang chọn oscilicator clock là xung nhịp nội nên ta có hsi = 16mhz mới tính được ở dưới 
     * N = delay_achieved * SYSCLK (defalut SYSCLK == frequency default hsi = 16 000 000)
     * N = 1ms * 16 000 000 = 16 000
     * N will value reload for SYStick reload register
     * so SYSTICK->SYST_RVR = 16000 
     */
    SYSTICK->SYST_RVR = 16000; // 16 000 000 / 16 000 
    SYSTICK->SYST_CVR = 0; // value current =0 
    //SYSTICK->SYST_CSR |= (1U << 0) | (1U << 2); // 
    SYSTICK->SYST_CSR |= INTERNAL_CLOCK | COUNTER_EN;


    for(int i=0; i <ms;i++)
    {
        while(!(SYSTICK->SYST_CSR & COUNTFLAG));
    }
    SYSTICK->SYST_CSR = 0;
}

