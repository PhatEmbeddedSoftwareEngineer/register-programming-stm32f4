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
#include "ETP_GPIO.h"

int main(void)
{
	ETP_RCC_AHB1_Clock(RCC_GPIOA);
	ETP_RCC_AHB1_Clock(RCC_GPIOC);
	GPIO_Typedef gpio;
	gpio.pGPIO=GPIOA;
	gpio.GPIO_Config.mode = OUTPUT;
	gpio.GPIO_Config.pinNumber = PIN_5;
	gpio.GPIO_Config.otype = TYPE_OUTPUT_PUPL;
	gpio.GPIO_Config.speed = HIGH_SPEED;
	Etp_output(&gpio);
	SET_BIT(GPIOA->BSRR,5);
	//Etp_output(GPIOA,PIN_5,OUTPUT);

	// GPIOA->MODER |= (1<<10);
	// GPIOA->OTYPER &= (0<<10);
	// GPIOA->OSPEEDR |= (3<<10);
	// SET_BIT(GPIOA->BSRR,5);
	// PIN_GPIOC->MODER &= (3<<26);
    /* Loop forever */
	while(1)
	{
		// if(GET_BIT(PIN_GPIOC->IDR,13))
		// {
		// 	PIN_GPIOA->BSRR |= (1<<5);
		// }
		// else
		// {
		// 	PIN_GPIOA->BSRR |= (1<<21);
		// }
	}
}
