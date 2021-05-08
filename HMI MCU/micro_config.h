 /******************************************************************************
 *
 * Module: Micro - Configuration
 *
 * File Name: Micro_Config.h
 *
 * Description: File include all Microcontroller libraries
 *
 * Author: Mohamed Tarek
 *
 *******************************************************************************/

#ifndef MICRO_CONFIG_H_
#define MICRO_CONFIG_H_

#ifndef F_CPU
#define F_CPU 8000000UL //MHz Clock frequency
#endif  

#define Enable_Global_Interrupt (SREG  |= (1<<7))
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


#endif /* MICRO_CONFIG_H_ */
