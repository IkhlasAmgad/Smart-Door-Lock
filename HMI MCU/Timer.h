/*
 * Timer.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Ikhlas Amgad
 */

#ifndef TIMER_H_
#define TIMER_H_
#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"
uint8 persacler_value0;     /*Global Variable to Store prescaler of Timer0*/

uint8 persacler_value1;     /*Global Variable to Store prescaler of Timer1*/


                        /******Timer0 Macros******/

#define OC0_Pin PB3


/*********************************************************************************/

                      /******Timer1 Macros******/

/************Choose Which of 2 modes to Operate********/





#define OC1A_Pin PD5                        //Channel A
#define Timer1_Compare_value    (OCR1A=200)    //Channel A(16 bit REg.)
/*******************************************************************************/

#define Enable_Global_Interrupt (SREG  |= (1<<7))



/*********************************************************************************/
typedef enum     //Count starts from 0
{
 NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024    //open data sheet ,no_clk=0,f_cpu_clk=1...
}Timer_Prescaler;

/******************************************************************************/

typedef enum
{
	Timer0,Timer1,Timer2
}Timer_Id;
/***************************************************************************/
typedef enum
{
	Normal,PWM,CTC,FastPWM
}Timer_Mode;

/*******************************for Compare Match outPut Mode********************************************/
typedef enum
{
	OC0_disconnected,Toggle_OC0,Clear_OC0,Set_OC0
}OC_Pin_Mode;



typedef enum
{
	ChannelA,ChannelB
}Timer1_Channel;
/*************************************************************************/
typedef struct
{
	Timer_Prescaler prescaler;
	Timer_Id Timer_id;
	OC_Pin_Mode OC_Pin;
	Timer_Mode Timer_mode;
}Timer_Config;
/***********************************************************************/
void Timer_init(const Timer_Config * Config_Ptr);


/***********************************************************************/
void Timer0_setCallBack(void(*a_ptr)(void));
void Timer1_setCallBack(void(*a_ptr)(void));

/***********************************************************************/
void Timer_Start(Timer_Id tim_id);

/***********************************************************************/
void Timer_Stop(Timer_Id tim_id);
/***********************************************************************/
void Timer_Enable_Interrupt(Timer_Id tim_id,Timer_Mode mode);
/***********************************************************************/
void Timer_Set_OutPut_Compare_value(Timer_Id tim_id,  uint16 Cmp_vlaue);
/***********************************************************************/
void Timer_Set_init_value(Timer_Id tim_id,uint16 init_value);
/***********************************************************************/
#endif /* TIMER_H_ */
