/*
 * bit_mat.h
 *
 *  Created on: Nov 12, 2024
 *      Author: Phat
 */

#ifndef BIT_MAT_H_
#define BIT_MAT_H_


#define SET_BIT(var,bit)			var |= (1<<bit)
#define CLEAR_BIT(var,bit)			var &= ~(1<<bit)
#define AND(one,two)				one & two;
#define OR(one,two)					one | two;
#define XOR(one,two)				one ^two;
#define SHIFT_LEFT(value,position)			value<<position;
#define SHIFT_RIGHT(value,position)			value>>position;

#define GET_BIT(var,bit)			((var>>bit)&1)



#endif /* BIT_MAT_H_ */
