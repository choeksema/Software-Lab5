/*****************************************************************************
 * Servo.c
 * Contains code to initialize a Servo PWM timer
 * Caleb Hoeksema
 * February 2020
 ****************************************************************************/

#include "utils.h"
#include "Servo.h"


void TIMER_CLOCK_ENABLE(void) {
	
	// Set timer 1 clock
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	
}

void Timer_Init(void) {
	
	TIMER_CLOCK_ENABLE();
	
	// Count direction
	COUNT_DIR(TIM1->CR1, COUNT_UP);
	
	// Clock Prescale (16 bits - up to 65 535)
	TIM1->PSC = 39;		//4MHz clock --> clock/(PSC+1) = 100kHz, a convenient #
	
	// Auto-reload (also 16b)
	TIM1->ARR = 2000-1;		//100kHz clock (see above), PWM period = 20ms --> ARR = clock*PWM - 1
	
	// Set PWM mode
	TIM1_MODE(MODE_PWM);
	
	// Output 1 preload enable
	TIM1_PRELOAD(PRELOAD_ON);
	
	// Output polarity
	TIM1_POLAR(ACT_HI);
	
	// Enable channel 1 complementary output (1 = on, 0 = off)
	TIM1->CCER |= TIM_CCER_CC1NE;
	
	// Main O/P enable: 0 = off, 1 = en
	OP_ENABLE(OP_ON);
	
	// Any value from 0:(ARR-1)
	//TIM1->CCR1 = 500;		// CCR1/ARR = duty cycle
	
	// Enable timer 1
	SET_BITS(TIM1->CR1, TIM_CR1_CEN);
	
}


void Servo_Update(uint16_t angle, uint16_t* test, uint16_t *time) {
	
	// 0deg = 600 us
	// 90deg = 1500 us (centre position)
	// 180deg = 2400 us
	// slope of angle/10, offset of 600
	
	uint16_t pulse_min = 600;
	uint16_t pulse_max = 2400;
	uint16_t range = pulse_max - pulse_min;
	uint16_t pulse;
	
	pulse = (angle * 10) + pulse_min;				// Based on linear equation calculations
	*time = pulse;
	
	*test= ((TIM1->ARR * pulse) - (666 * range)) / range;		// Based on linear equation calculations (666 from linear eqn)
	
	TIM1->CCR1 = *test;
	
}

