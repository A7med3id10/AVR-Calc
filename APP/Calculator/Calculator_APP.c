/*
 * Calculator_APP.c
 *
 *  Created on: Aug 31, 2022
 *      Author: ahmedeid
 *      Calculator Application using LCD and Key Pad
 *      The calculator can perform addition, subtraction, multiplication, and integer division
 */
#include"../../LIB/STD_TYPES.h"
#include"../../LIB/BIT_MATH.h"
#define F_CPU 8000000UL
#include <util/delay.h>
#include"../../EHAL/LCD/header/LCD_interface.h"
#include"../../EHAL/KeyPad/header/PAD_interface.h"
#include"../../MCAL/DIO/header/DIO_interface.h"
#include"Calculator_header.h"

void Calculator() {
	DIO_Init();
	u8 Key, operator,p=0, i = 0;
	u32 op1[7], op2[7];
	u32 operand1 = 0, operand2 = 0, res = 0;
	LCD_voidInit();
	LCD_AvoidString("  AE Calculator");
	_delay_ms(1000);
	LCD_voidClear();
	while (1) {
		//Getting the value of the first operand
		KPD_u8GetKey(&Key);
		while (Key != '+' && Key != '-' && Key != '*' && Key != '/') {
			if (Key != KPD_NOT_PRESSED) {
				LCD_voidSendCharacter(Key);
				op1[i++] = Key - 48;
			}
			KPD_u8GetKey(&Key);
		}
		while (i) {
			i--;
			operand1 += op1[i] * power(10, p++);
		}
		p=0;
		//Getting the operation
		LCD_voidSendCharacter(Key);
		operator = Key;
		//Getting the value of the second operand
		KPD_u8GetKey(&Key);
		while (Key != '=') {
			if (Key != KPD_NOT_PRESSED) {
				LCD_voidSendCharacter(Key);
				op2[i++] = Key - 48;
			}
			KPD_u8GetKey(&Key);
		}
		while (i) {
			i--;
			operand2 += op2[i] * power(10, p++);
		}
		p=0;
		//Performing the operation
		switch (operator) {
		case '+':
			res = operand1 + operand2;
			break;
		case '-':
			res = operand1 - operand2;
			break;
		case '*':
			res = operand1 * operand2;
			break;
		case '/':
			res = operand1 / operand2;
			break;
		}
		//Print the result
		LCD_voidSendCharacter(Key);
		LCD_voidGoToXY(LCD_u8_LINE2, 0);
		LCD_voidNumber(res);
		LCD_voidGoToXY(LCD_u8_LINE2, 12);
		LCD_AvoidString(".. C");
		while (Key != 'C') {
			KPD_u8GetKey(&Key);
		}
		LCD_voidClear();
		operand1 = 0, operand2 = 0;
	}
}
