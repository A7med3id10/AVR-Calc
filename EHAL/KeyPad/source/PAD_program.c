/*
 * PAD_program.c
 *
 *  Created on: Aug 29, 2022
 *      Author: ahmedeid
 */
#include"../../../LIB/BIT_MATH.h"
#include"../../../LIB/STD_TYPES.h"
#include"../header/PAD_config.h"
#include"../header/PAD_interface.h"
#include"../header/PAD_private.h"
#include"../../../MCAL/DIO/header/DIO_interface.h"
#define F_CPU 8000000UL
#include <util/delay.h>

u8 KPD_Au8Keys[4][4] = KPD_Au8_KEY_VALUE;

u8 KPD_Au8RowPins[4] = { KPD_u8_R1, KPD_u8_R2, KPD_u8_R3, KPD_u8_R4 };
u8 KPD_Au8ColPins[4] = { KPD_u8_C1, KPD_u8_C2, KPD_u8_C3, KPD_u8_C4 };

u8 KPD_u8GetKey(u8 * Copy_pu8ReturnedKey) {
	u8 Local_ErrorStatus = STD_TYPES_OK;
	u8 Local_u8RowsCounter, Local_u8ColsCounter, Local_u8ReturnedKey,
			Local_u8Flag = 0;
	/* pointer validation */
	if (Copy_pu8ReturnedKey != NULL) {
		*Copy_pu8ReturnedKey = KPD_NOT_PRESSED;
		for (Local_u8RowsCounter = 0; Local_u8RowsCounter <= 3;
				Local_u8RowsCounter++) {
			DIO_u8SetPinValue(KPD_u8_PORT, KPD_Au8RowPins[Local_u8RowsCounter],
			DIO_u8_LOW);

			/* Reading Columns */
			for (Local_u8ColsCounter = 0; Local_u8ColsCounter <= 3;
					Local_u8ColsCounter++) {
				DIO_u8GetPinValue(KPD_u8_PORT,
						KPD_Au8ColPins[Local_u8ColsCounter],
						&Local_u8ReturnedKey);
				/* Check if Switch is Pressed */
				if (Local_u8ReturnedKey == DIO_u8_LOW) {
					/* Debouncing */
					_delay_ms(20);
					while (Local_u8ReturnedKey == DIO_u8_LOW) {
						DIO_u8GetPinValue(KPD_u8_PORT,
								KPD_Au8ColPins[Local_u8ColsCounter],
								&Local_u8ReturnedKey);
					}
					*Copy_pu8ReturnedKey =
							KPD_Au8Keys[Local_u8RowsCounter][Local_u8ColsCounter];
					Local_u8Flag = 1;
					/* to terminate the loop if the switch is pressed */
					break;
				}
			}
			DIO_u8SetPinValue(KPD_u8_PORT, KPD_Au8RowPins[Local_u8RowsCounter],
			DIO_u8_HIGH);
			
			if (Local_u8Flag == 1) {
				break;
			}
		}
		/* Activate R1 */

		/* Read the four Cols */
		/* Activate R2 */
		/* Read the four Cols */

	} else {
		Local_ErrorStatus = STD_TYPES_NOK;
	}
	return Local_ErrorStatus;
}
