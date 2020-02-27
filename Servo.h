/*****************************************************************************
 * Servo.c
 * Contains code to initialize a Servo PWM timer
 * Caleb Hoeksema
 * February 2020
 ****************************************************************************/
 

#ifndef _SERVO_H
#define _SERVO_H

#include "SysClock.h"
#include "stm32l476xx.h"

void TIMER_CLOCK_ENABLE(void);
void Timer_Init(void);


#endif
