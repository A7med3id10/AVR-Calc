/*
 * LCD.c
 *
 *  Created on: Aug 28, 2022
 *      Author: ahmedeid
 */
#include"../../../LIB/BIT_MATH.h"
#include"../../../LIB/STD_TYPES.h"
#include"../header/LCD_config.h"
#include"../header/LCD_interface.h"
#include"../header/LCD_private.h"
#include"../../../MCAL/DIO/header/DIO_interface.h"
#define F_CPU 8000000UL
#include <util/delay.h>

void LCD_voidInit() {
#if Mode == _8_Mode
	_delay_ms(35);
	LCD_voidCommand(Function_Set_1_Line);
	_delay_us(40);
	LCD_voidCommand(Diplay_On_Cusror_On_Blink_On);
	LCD_voidClear();
	_delay_ms(2);
	LCD_voidCommand(Enrty_Mode_Set);
#elif Mode == _4_Mode
	// 4-bit Mode
#endif
}

void LCD_voidCommand(u8 copy_u8Cmd) {
	//RS = 0
	DIO_u8SetPinValue(Control_Port, RS_PIN, DIO_u8_LOW);
	//RW = 0
	DIO_u8SetPinValue(Control_Port, RW_PIN, DIO_u8_LOW);
	//Send Cmd Byte
	DIO_u8SetPortValue(Data_Port, copy_u8Cmd);
	//Enable Pin needs a pulse { E = 1 , E = 0 }  , 500 ns delay
	DIO_u8SetPinValue(Control_Port, E_PIN, DIO_u8_HIGH);
	_delay_us(1);
	DIO_u8SetPinValue(Control_Port, E_PIN, DIO_u8_LOW);
	_delay_us(1);
}

void LCD_voidSendCharacter(u8 copy_u8Char) {
	//RS = 1
	DIO_u8SetPinValue(Control_Port, RS_PIN, DIO_u8_HIGH);
	//RW = 0
	DIO_u8SetPinValue(Control_Port, RW_PIN, DIO_u8_LOW);
	//Send Cmd Byte
	DIO_u8SetPortValue(Data_Port, copy_u8Char);
	//Enable Pin needs a pulse { E = 1 , E = 0 }  , 500 ns delay
	DIO_u8SetPinValue(Control_Port, E_PIN, DIO_u8_HIGH);
	_delay_us(1);
	DIO_u8SetPinValue(Control_Port, E_PIN, DIO_u8_LOW);
	_delay_us(1);
}

void LCD_voidClear() {
	_delay_us(40);
	LCD_voidCommand(Diplay_Clear);
}

void LCD_voidGoToXY(u8 Copy_u8Row, u8 Copy_u8Col) {
	if ((Copy_u8Row <= LCD_u8_LINE2) && (Copy_u8Col <= 15)) {
		switch (Copy_u8Row) {
		case LCD_u8_LINE1:
			LCD_voidCommand(0x80 + Copy_u8Col);
			break;
		case LCD_u8_LINE2:
			LCD_voidCommand(0xC0 + Copy_u8Col);
			break;
		}
	}

}

void LCD_voidSpecialChar(u8 *copy_Au8Char) {
	LCD_voidCommand(0b01000000);
	_delay_us(40);
	for (u8 i = 0; i < 8; i++) {
		LCD_voidSendCharacter(copy_Au8Char[i]);
	}

	LCD_voidGoToXY(LCD_u8_LINE1, 0);
	LCD_voidSendCharacter(0);
}

void LCD_AvoidString(u8 * copy_Au8Char) {
	u8 i = 0;
	while (copy_Au8Char[i]) {
		LCD_voidSendCharacter(copy_Au8Char[i++]);
	}
}

void LCD_voidNumber(u32 copy_u8Num) {
	u8 Local_Au8Num[10]={0}, i = 0;
	if(copy_u8Num==0){LCD_voidSendCharacter('0');}
	while (copy_u8Num>0) {
		Local_Au8Num[i++] = copy_u8Num % 10 + 48;
		copy_u8Num /= 10;
	}

	while (i) {
		LCD_voidSendCharacter(Local_Au8Num[--i]);
	}
}
