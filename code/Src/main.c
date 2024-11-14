/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Phat
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <std_type.h>
#include <stdio.h>
#include "bit_mat.h"
#include "ETP_STM32F401_RCC.h"

int main(void)
{
	ETP_RCC_AHB1_Clock(RCC_GPIOA);
	ETP_RCC_AHB1_Clock(RCC_GPIOC);
	PIN_GPIOA->MODER |= (1<<10);
	PIN_GPIOA->OTYPER &= (1<<0);
	PIN_GPIOA->OSPEEDR |= (3<<10);
	SET_BIT(PIN_GPIOA->BSRR,5);
	PIN_GPIOC->MODER &= (3<<26);
    /* Loop forever */
	while(1)
	{
		if(GET_BIT(PIN_GPIOC->IDR,13))
		{
			PIN_GPIOA->BSRR |= (1<<5);
		}
		else
		{
			PIN_GPIOA->BSRR |= (1<<21);
		}
	}
}
