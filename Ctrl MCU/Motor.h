/*
 * Motor.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Ikhlas Amgad
 */

#ifndef MOTOR_H_
#define MOTOR_H_
#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"
#include"Timer.h"

void Motor(void);
void Timer_intit_for_motor(void);
void Motor_Ctrl(void);
#endif /* MOTOR_H_ */
