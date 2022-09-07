/*
 * LCD_config.h
 *
 *  Created on: Aug 28, 2022
 *      Author: ahmedeid
 */

#ifndef EHAL_LCD_LCD_CONFIG_H_
#define EHAL_LCD_LCD_CONFIG_H_

#define Mode _8_Mode

#define Control_Port DIO_u8_PORTA
#define RS_PIN       DIO_u8_PIN0
#define RW_PIN       DIO_u8_PIN1
#define E_PIN        DIO_u8_PIN2

#define Data_Port    DIO_u8_PORTD

#define Function_Set_1_Line                0b00111000
#define Diplay_On_Cusror_On_Blink_On       0b00001111
#define Diplay_Clear                       0b00000001
#define Enrty_Mode_Set                     0b00001110

#endif /* EHAL_LCD_LCD_CONFIG_H_ */
