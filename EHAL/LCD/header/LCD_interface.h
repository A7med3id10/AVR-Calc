/*
 * LCD_interface.h
 *
 *  Created on: Aug 28, 2022
 *      Author: ahmedeid
 */

#ifndef EHAL_LCD_LCD_INTERFACE_H_
#define EHAL_LCD_LCD_INTERFACE_H_

#define LCD_u8_LINE1     0
#define LCD_u8_LINE2     1


// Prototypes of the LCD Driver
//SWC_returntypeDescVerb()
//copy_typeDescName
void LCD_voidInit();
void LCD_voidCommand(u8 copy_u8Cmd);
void LCD_voidSendCharacter(u8 copy_u8Char);
void LCD_AvoidString(u8 * copy_Au8Char);
void LCD_voidNumber(u32 copy_u8Num);
void LCD_voidGoToXY(u8 Copy_u8Row  , u8 Copy_u8Col);
void LCD_voidClear();
void LCD_voidSpecialChar(u8 *copy_Au8Char);
#endif /* EHAL_LCD_LCD_INTERFACE_H_ */
