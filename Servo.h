/*****************************************************************************
 * Servo.c
 * Contains function prototypes to initialize a servo
 * Caleb Hoeksema, Gregory Huras
 * February 2020
 ****************************************************************************/
 

#ifndef _SERVO_H
#define _SERVO_H

#include "SysClock.h"
#include "stm32l476xx.h"
#include "utils.h"

// Counting direction
#define 	COUNT_UP		0x00UL
#define 	COUNT_DN		0x10UL

// Timer modes
#define		MODE_PWM		(uint32_t)0x00000060

// Preload mode
#define		PRELOAD_OF	0x0UL
#define		PRELOAD_ON	TIM_CCMR1_OC1PE

// O/P polarity
#define		ACT_HI			0x0UL
#define		ACT_LO			TIM_CCER_CC1NP

// Main O/P mode
#define		OP_OF				0x0UL
#define		OP_ON				TIM_BDTR_MOE

// Pins
#define		SERVO_PIN		8UL

// Timer macros
#define		COUNT_DIR(timer, dir)			FORCE_BITS((timer), 0x10UL, (dir))
#define		TIM1_MODE(mode)						FORCE_BITS(TIM1->CCMR1, TIM_CCMR1_OC1M, (mode))
#define		TIM1_PRELOAD(mode)				FORCE_BITS(TIM1->CCMR1, TIM_CCMR1_OC1PE, (mode))
#define		TIM1_POLAR(mode)					FORCE_BITS(TIM1->CCER, TIM_CCER_CC1NP, (mode))
#define		OP_ENABLE(mode)						FORCE_BITS(TIM1->BDTR, TIM_BDTR_MOE, (mode))

// Timer function prototypes
void TIMER_CLOCK_ENABLE(void);
void Timer_Init(void);
void Servo_Update(uint16_t angle, uint16_t *time);



#endif

