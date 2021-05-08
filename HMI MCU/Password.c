/*
 * Password.c
 *
 *  Created on: ??þ/??þ/????
 *      Author:Ikhlas Amgad
 */
#include"password.h"
uint8 count=0;
uint8 g_tick = 0;
uint8 * Get_Password_fromUser(void)
{
	uint8 key;
	uint8 i=0;

	while(i<4)
	{
	key=KeyPad_getPressedKey();
			if((key <= 9) && (key >= 0))
					{
				        password[i]=key;
						LCD_intgerToString(key); /* display the pressed keypad switch */

					}
					else
				{
						LCD_displayCharacter(key); /* display the pressed keypad switch */

						 password[i]=key;
					}
					_delay_ms(500);
					i++;
	}

return password;
}

void Enter_Password(void)
{
	 uint8 *new_pass_ptr;
	 uint8 j;
	LCD_clearScreen();
	LCD_displayString("Enter New ");
    LCD_goToRowColumn(1,0);
    LCD_displayString("Password:");
    LCD_goToRowColumn(1,9);

 /*Get password from the User*/

  new_pass_ptr=Get_Password_fromUser();
  /*Send Password to  Control_MCU */
 for(j=0;j<4;j++)
	{
		UART_sendByte(new_pass_ptr[j]);
	}

}
/***********************************************************************************/
void Renter_Password(void)
{
  uint8 *re_pass_ptr;

	LCD_clearScreen();
	LCD_displayString("Renter");
	LCD_goToRowColumn(1,0);
	LCD_displayString("Password: ");
	LCD_goToRowColumn(1,10);
	 /*Get password from the User*/
	re_pass_ptr=Get_Password_fromUser();

if(check_password(re_pass_ptr))
{

	LCD_clearScreen();
	LCD_displayString(" Matched ");
	_delay_ms(1000);

}
else
{
	    LCD_clearScreen();
		LCD_displayString("UNMatched !! ");
		_delay_ms(1000);
		Enter_Password();
		Renter_Password();
}

}
/*****************************************************************************/


uint8 check_password(uint8 *enterd_password_ptr)
{

	uint8 i=0;
	for(i=0;i<4;i++)
	{
		if(enterd_password_ptr[i]==get_password_from_EEPROM[i])
		{
			continue;
		}
		else
		{
			return 0;
		}
		}



	return 1;
}
/*******************************************/
void ChangePassword(void)
{
	 uint8 *old_pass_ptr;
	    LCD_clearScreen();
		LCD_displayString("Enter Old");
		LCD_goToRowColumn(1,0);
		LCD_displayString("Password: ");
		LCD_goToRowColumn(1,10);
		old_pass_ptr=Get_Password_fromUser();


		if(check_password(old_pass_ptr))
		{

			LCD_clearScreen();
			LCD_displayString(" Matched ");
			_delay_ms(1000);
			Enter_Password();
			Renter_Password();
		}
		else
		{
			if(count==2)
						{
						LCD_clearScreen();
						//LCD_displayString("5als w2fsystem ");
						Timer_init_Hanging();
						Show_Two_Options();
						///*rg3 options
						}
						else{
							count++;
						    LCD_clearScreen();
							LCD_displayString("UNMatched !! ");
							_delay_ms(1000);
							ChangePassword();
		     }

		}
}
/****************************************/
void Show_Two_Options(void)
{

	    uint8 key=0;
	    LCD_clearScreen();
		LCD_displayString("'+'ChangePassword ");
		LCD_goToRowColumn(1,0);
		LCD_displayString("'-'Open The Door ");

		while((key!='+')||(key!='-'))
		{
			key=KeyPad_getPressedKey();
			LCD_clearScreen();
					if(key=='+')
					{
						LCD_displayCharacter(key);
						ChangePassword();
					}
					else
					if(key=='-')
						{
						LCD_displayCharacter(key);
						enter_password_motor();



						}
					else
					{
						        LCD_displayString("Wrong Enter");
						        _delay_ms(1000);
						        LCD_clearScreen();
						       LCD_displayString("'+'ChangePassword ");
						       LCD_goToRowColumn(1,0);
						       LCD_displayString("'-'Open The Door ");

					}

		}

}
 /************************************/




void enter_password_motor(void)
{
	        uint8 *re_pass_ptr;
	        LCD_clearScreen();
			LCD_displayString("Please Enter");
			LCD_goToRowColumn(1,0);
			LCD_displayString("Password: ");
			LCD_goToRowColumn(1,10);
			re_pass_ptr=Get_Password_fromUser();

			if(check_password(re_pass_ptr))
			{
                  /*Password is Correct*/
				LCD_clearScreen();
				LCD_displayString("Door is Opening");
				_delay_ms(1000);
				UART_sendByte('-');
				LCD_clearScreen();
				LCD_displayString("ClockWise Opening");
				Timer_init_LCD();




			}
			else
			{
				/*Password is inCorrect*/
				if(count==2)
							{
										LCD_clearScreen();
										//LCD_displayString("5als w2fsystem ");
										Timer_init_Hanging();
										///*rg3 options
								}
										else
										{
											count++;
										    LCD_clearScreen();
											LCD_displayString("UNMatched !! ");
											_delay_ms(1000);
											enter_password_motor();

			                                    }

			}
}

/*****************************************************/
void Timer_init_LCD(void)

{
	 Timer_Config Timer1Config={F_CPU_1024,Timer1,OC0_disconnected,CTC};
			        Timer_init(&Timer1Config);
			        Timer_Set_init_value(Timer1,0);
			        Timer_Set_OutPut_Compare_value(Timer1,40000);
			        Timer_Enable_Interrupt(Timer1,CTC);


			         Timer1_setCallBack(LCD_Display_Timer);
			         Timer_Start(Timer1);
}
/*************************************************/
void LCD_Display_Timer(void)
{
	g_tick++;
			if(g_tick == 2)
				{
					LCD_clearScreen();
					LCD_displayString("AntiClockWise Opening");
				}

				else
					if(g_tick == 4)
								{
						LCD_clearScreen();
						Timer_Stop(Timer1);
					}

}



