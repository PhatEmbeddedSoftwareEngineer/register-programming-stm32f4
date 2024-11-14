/*
 * bit_mat.h
 *
 *  Created on: Nov 12, 2024
 *      Author: Phat
 */

#ifndef BIT_MAT_H_
#define BIT_MAT_H_
typedef struct
{
	volatile u32 MODER;
	volatile u32 OTYPER;
	volatile u32 OSPEEDR;
	volatile u32 PUPDR;
	volatile u32 IDR;
	volatile u32 ODR;
	volatile u32 BSRR;
	volatile u32 LCKR;
	volatile u32 AFRL;
	volatile u32 AFRH;
}GPIO_t;
#define RCC_AHB1_ADDRESS_OFFSET 					0x30
#define REG(base, offset) 			((*((volatile unsigned int *)(base + offset))))
#define PIN_GPIOA 			((volatile GPIO_t*)GPIOA_ADDRESS)
#define PIN_GPIOC			((volatile GPIO_t*)GPIOC_ADDRESS)

#define GPIOA_ADDRESS						0x40020000
#define GPIOB_ADDRESS						0x40020400
#define GPIOC_ADDRESS						0x40020800
#define GPIOD_ADDRESS						0x40020C00
#define GPIOE_ADDRESS						0x40021000

#define SET_BIT(var,bit)			var |= (1<<bit)
#define CLEAR_BIT(var,bit)			var &= ~(1<<bit)
#define AND(one,two)				one & two;
#define OR(one,two)					one | two;
#define XOR(one,two)				one ^two;
#define SHIFT_LEFT(value,position)			value<<position;
#define SHIFT_RIGHT(value,position)			value>>position;

#define GET_BIT(var,bit)			((var>>bit)&1)



#endif /* BIT_MAT_H_ */
