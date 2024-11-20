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
	GPIO_Config_t gpio[]={
		{GPIOA,PIN_6,OUTPUT,HIGH_SPEED,TYPE_OUTPUT_PUPL},
		{GPIOA,PIN_5,OUTPUT,HIGH_SPEED,TYPE_OUTPUT_PUPL},

	};
	// GPIO_Typedef gpio;
	// gpio.pGPIO=GPIOA;
	// gpio.GPIO_Config.mode = OUTPUT;
	// gpio.GPIO_Config.pinNumber = PIN_5;
	// gpio.GPIO_Config.otype = TYPE_OUTPUT_PUPL;
	// gpio.GPIO_Config.speed = HIGH_SPEED;
	// gpio.GPIO_Config.pull_up_down = NO_PUPD;
	// ETP_Output(&gpio);
	for(int i=0;i<sizeof(gpio)/sizeof(gpio[0]);i++)
		ETP_Output(&gpio[i]);
	ETP_RCC_SetSystemClockByPLL84MHZ();
	ETP_GPIO_WritePin(GPIOA,PIN_5,GPIO_PIN_SET);
    /* Loop forever */
	while(1)
	{
		// ETP_GPIO_TogglePin(GPIOA,PIN_5);
		// delay();
	}
}
