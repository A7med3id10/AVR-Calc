/*
 * PAD_interface.h
 *
 *  Created on: Aug 29, 2022
 *      Author: ahmedeid
 */

#ifndef EHAL_KEYPAD_HEADER_PAD_INTERFACE_H_
#define EHAL_KEYPAD_HEADER_PAD_INTERFACE_H_

u8 KPD_u8GetKey(u8 * Copy_pu8ReturnedKey);

#define KPD_NOT_PRESSED    0xFF

#endif /* EHAL_KEYPAD_HEADER_PAD_INTERFACE_H_ */
