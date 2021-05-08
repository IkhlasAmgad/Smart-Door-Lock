/*
 * Timer.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Ikhlas Amgad
 */

#include "Timer.h"
/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtrTimer0)(void) = NULL_PTR;
/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtrTimer1)(void) = NULL_PTR;

/******************************Generic Function*********************************************/
        /**********maximum counting 0xFF*******************/
             /**Timer_intit()***
              * Choose which Timer module to operate
              * Timer mode(Normal, CTC, Compare Match Output Mode)
              * Timer clock/prescaler
              * Timer is Stopped
              *
              */
void Timer_init(const Timer_Config * Config_Ptr)

{
  switch(Config_Ptr->Timer_id)
  {

  case Timer0:

	           /****Normal Mode***/
	    TCNT0 =0;               // Set Timer initial value to 0
		TCCR0=0;                //Clear Timer ctrl Register
		OCR0=0;                //Clear Compare Value

       	      /* Configure the timer control register
       				 * 1. Non PWM mode FOC0=1
       				 * 2. Normal Mode WGM01=0 & WGM00=0
       				 * 3. Normal Mode COM00=0 & COM01=0
       				 * 4. Prescaler Bits CS00, CS01, CS02
       				 */
    if(Config_Ptr->Timer_mode==Normal)
    {
    	TCCR0 = (1<<FOC0);
    	persacler_value0=Config_Ptr->prescaler; //Timer is stopped+Store prescaler to a Global Variable used in Start_timer(
    }


    else if(Config_Ptr->Timer_mode==CTC)
		             /****CTC Mode***/
    {	/* Configure timer0 control register
			 * 1. Non PWM mode FOC0=1
			 * 2. CTC Mode WGM01=1 & WGM00=0
			 * 3. No need for OC0  COM00=0 & COM01=0
			 * 4. clock  CS00,CS01, CS02
			 */
    			TCCR0 = (1<<FOC0)| (1<<WGM01) ;
    			persacler_value0=Config_Ptr->prescaler;
    /**********************Check Output Compare mode *************************************/
      if(Config_Ptr->OC_Pin==OC0_disconnected)
      {
    	  TCCR0= (TCCR0 & 0xCF)|((Config_Ptr->OC_Pin)<<4);
      }
      else
      {
    	        DDRB = DDRB | (1<<OC0_Pin); /*Set OC0 pin as OUTPUT pin*/

    	        TCCR0= (TCCR0 & 0xCF)|((Config_Ptr->OC_Pin)<<4); /**Toggle or clear or Set a***/
      }
      }



		break;
		/********************************* Timer1 -16Bit-  **************************/

/*******************************************maximum counting 0xFFFF**********************************/

  case Timer1:
                     /*Clear Timer Registers*/
	  TCNT1=0;
	  TCCR1A=0;
	  TCCR1B=0;
	  OCR1A=0;
	  OCR1B=0;

	  if(Config_Ptr->Timer_mode==Normal)
	     {
		          TCCR1A = (1<<FOC1A) | (1<<FOC1B);

		       	  persacler_value1=Config_Ptr->prescaler; //Timer is stopped+Store prescaler to a Global Variable used in Start_timer(
	     }


	     else if(Config_Ptr->Timer_mode==CTC)
	 		             /****CTC Mode***/
	     {
	    	        TCCR1A = (1<<FOC1A) | (1<<FOC1B); //Non PWM mode
	    	 		TCCR1B=(1<<WGM12) ;               //CTC mode
	    	         persacler_value1=Config_Ptr->prescaler;
	     /**********************Check Output Compare mode *************************************/
	       if(Config_Ptr->OC_Pin==OC0_disconnected)
	       {
	    	   TCCR1A= (TCCR1A & 0x3F)|((Config_Ptr->OC_Pin)<<6);
	    	   TCCR1A= (TCCR1A & 0x3F)|((Config_Ptr->OC_Pin)<<4);
	       }
	       else
	       {
	    	        TCCR1A= (TCCR1A & 0x3F)|((Config_Ptr->OC_Pin)<<4);     //Choose OC Pin Mode channel B
	    	   		TCCR1A= (TCCR1A & 0x3F)|((Config_Ptr->OC_Pin)<<6);     //Choose OC Pin Mode channel A
	       }
	       }

		/*****************CTC*************************/
break;
default : break;
}}
/******************************Generic Function*********************************************/

void Timer_Start(Timer_Id tim_id)                 //StartTimer
{
	switch(tim_id)
	{
	case Timer0:
	  TCCR0= (TCCR0 & 0xF8) | (persacler_value0) ;
	   break;

	case Timer1:
		TCCR1B = (TCCR1B & 0xF8) | (persacler_value1);
		break;
	default : break;
	}
}
/******************************Generic Function*********************************************/
void Timer_Stop(Timer_Id tim_id)
{

	switch(tim_id)
	{
	case Timer0:
		TCCR0=TCCR0 & 0xF8;
	  break;
	case Timer1:
		TCCR1B=TCCR1B & 0xF8;
		  break;
	default : break;
	}
}
/*********************************************************************************************************/
     /*********************************************************************************************/



              /********************Timer0_Normal Mode ISR****************************************/

ISR(TIMER0_OVF_vect)
 {

	if(g_callBackPtrTimer0 !=NULL_PTR)
		{
			/* Call the Call Back function in the application after the edge is detected */
			(*g_callBackPtrTimer0)(); /* another method to call the function using pointer to function g_callBackPtr(); */
		}
 }

/****************Timer0_CTC MODE ISR*****************/

ISR(TIMER0_COMP_vect)
 {

	if(g_callBackPtrTimer0 !=NULL_PTR)
		{
			/* Call the Call Back function in the application after the edge is detected */
			(*g_callBackPtrTimer0)(); /* another method to call the function using pointer to function g_callBackPtr(); */
		}
 }


/********************************************/

void Timer0_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtrTimer0 = a_ptr;
}

              /**************************Timer 1 ISR**************************************************/

ISR(TIMER1_OVF_vect)
 {

	if(g_callBackPtrTimer1 !=NULL_PTR)
		{
			/* Call the Call Back function in the application after the edge is detected */
			(*g_callBackPtrTimer1)(); /* another method to call the function using pointer to function g_callBackPtr(); */
		}
 }

/*************************************************************/

ISR(TIMER1_COMPA_vect)    // ISR CHANNEL A
 {

	if(g_callBackPtrTimer1 !=NULL_PTR)
		{
			/* Call the Call Back function in the application after the edge is detected */
			(*g_callBackPtrTimer1)(); /* another method to call the function using pointer to function g_callBackPtr(); */
		}
 }


/************************************************************/
ISR(TIMER1_COMPB_vect)    // ISR CHANNEL B
 {

	if(g_callBackPtrTimer1 !=NULL_PTR)
		{
			/* Call the Call Back function in the application after the edge is detected */
			(*g_callBackPtrTimer1)(); /* another method to call the function using pointer to function g_callBackPtr(); */
		}
 }
/************************************************************/
void Timer1_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtrTimer1 = a_ptr;
}



void Timer_Set_OutPut_Compare_value(Timer_Id tim_id,  uint16 Cmp_value)
{
	switch(tim_id)
	  {

	  case Timer0:
		  OCR0=(uint8)Cmp_value;
		  break;
	  case Timer1:
		  OCR1A=Cmp_value;  //ChannelA
		  break;
	  default : break;

	 }

}

void Timer_Set_init_value(Timer_Id tim_id,uint16 init_value)
{
	switch(tim_id)
		  {

		  case Timer0:
			  TCNT0=(uint8)init_value;
			  break;
		  case Timer1:
			  TCNT1=init_value;
			  break;
		  default : break;

		 }
}


void Timer_Enable_Interrupt(Timer_Id tim_id,Timer_Mode mode)
{
	switch(tim_id)
		  {

		  case Timer0:
			  if(mode==Normal)
			  {
				  Enable_Global_Interrupt;
				  TIMSK |= (1<<TOIE0);
			  }
			  else if (mode==CTC)
			  {
				  Enable_Global_Interrupt;
				  TIMSK |= (1<<OCIE0);   // Enable Timer0 Compare Interrupt
			  }
			  break;
		  case Timer1:
		  			  if(mode==Normal)
		  			  {
		  				  Enable_Global_Interrupt;
		  				 TIMSK |= (1<<TOIE1);
		  			  }
		  			  else if (mode==CTC)
		  			  {
		  				  Enable_Global_Interrupt;
		  				 TIMSK|=(1<<OCIE1A);            //Enable Timer1 Compare Interrupt Channel A
		  			  }
		  			  break;
		  default : break;

		 }
}
void Timer1_COMP_Channel(Timer1_Channel ch)
{
	switch(ch)
	{ case ChannelA: DDRD = DDRD | (1<<PD5);
	 break;
	 case ChannelB: DDRD = DDRD | (1<<PD4);
	 break;
	default : break;
	}

}
