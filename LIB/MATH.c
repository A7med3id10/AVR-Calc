/*
 * MATH.c
 *
 *  Created on: Sep 2, 2022
 *      Author: ahmedeid
 */
#include"STD_TYPES.h"

u32 power(u32 base, u32 exponent) {
	int result = 1;
	while (exponent) {
		result *= base;
		exponent--;
	}
	return result;

}
