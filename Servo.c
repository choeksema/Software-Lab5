/*****************************************************************************
 * Servo.c
 * Contains code to initialize a Servo PWM timer
 * Caleb Hoeksema
 * February 2020
 ****************************************************************************/

#include "utils.h"


void TIMER_CLOCK_ENABLE(void) {
	
	// Set timer 1 clock
	SET_BITS(RCC->APB2ENR, RCC_APB2ENR_TIM1EN);
	
}

void Timer_Init(void) {
	
	// Count up: 0, count down: 1
	CLR_BITS(TIM1->CR1, TIM_CR1_DIR);
	
	// Clock Prescale (16 bits - up to 65 535)
	TIM1->PSC = 39;
	
	// Auto-reload (also 16b)
	TIM1->ARR = 2000-1;
	
	//Clear ouptut compare mode bits for channel 1
	FORCE_BITS(TIM1->CCMR1, TIM_CCMR1_OC1M, (TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2));
	
	// Output 1 preload enable
	SET_BITS(TIM1->CCMR1, TIM_CCMR1_OC1PE);
	
	// Output polarity: active high = 0, active low = 1
	CLR_BITS(TIM1->CCER, TIM_CCER_CC1NP);	
	
	// Enable channel 1 complementary output
	SET_BITS(TIM1->CR1, TIM_CR1_CEN);
	
	// Main O/P enable: 0 = off, 1 = en
	SET_BITS(TIM1->BDTR, TIM_BDTR_MOE);
	
	// Any value from 0:(ARR-1)
	TIM1->CCR1 = 500;
	
	// Enable timer 1
	SET_BITS(TIM1->CR1, TIM_CR1_CEN);
	
}
