/*
 * Password.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Ikhlas Amgad
 */

#ifndef PASSWORD_H_
#define PASSWORD_H_
#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"
#include "lcd.h"
#include "keypad.h"
#include"uart.h"
#include"Timer.h"
#include"Haging.h"


uint8 get_password_from_EEPROM[4];
uint8 password[4];

uint8 renter_password[4];
uint8 rentero_password[4];
void Enter_Password(void);
void Renter_Password(void);
uint8 check_password(uint8* enterd_password_ptr);
void ChangePassword(void);
void Show_Two_Options(void);
void enter_password_motor(void);
uint8* Get_Password_fromUser(void);
void LCD_Display_Timer(void);
void Timer_init_LCD(void);


#endif /* PASSWORD_H_ */
