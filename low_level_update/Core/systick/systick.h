#pragma once
#include <stdint.h>

#define SYSTICK_CSR_BASE            0xE000E010
#define SYSTICK_BASE                SYSTICK_CSR_BASE

typedef struct 
{
    volatile uint32_t SYST_CSR; // control and status register
    volatile uint32_t SYST_RVR; // reload value register
    volatile uint32_t SYST_CVR; // current value register
    volatile uint32_t SYST_CALIB; // calibration value register
}Systick_config_t;

#define SYSTICK                    ((Systick_config_t*)SYSTICK_BASE)
void delay_ms(int ms);
