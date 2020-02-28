/*****************************************************************************
 * main.c
 * Mainline function to run an LCD
 * Caleb Hoeksema
 * February 2020
 ****************************************************************************/


#include "stm32l476xx.h"
#include "SysClock.h"
#include "GPIO.h"
#include "Servo.h"

float TimeFromReading(uint16_t reading){
	return reading * 0.00044 + 0.6;
}

uint16_t MilVoltsRead(uint16_t reading){
	
	return (uint16_t)(3300 / 0xFFF * reading);
}

int16_t Angle(uint16_t reading){
	return(int16_t)(180/0xfff * reading -90);
}
int
main(void) {
	
	System_Clock_Init();
	GPIO_CLOCK_ENABLE();
	GPIO_Init();
	TIMER_CLOCK_ENABLE();
	Timer_Init();
	
	int i;
	int brightness = 500;
	int stepSize = 1;
	
	while(1) {
		
		if ((brightness >= 1999) || (brightness <= 0))
			stepSize = -stepSize;
		
		brightness = stepSize*5;
		
		TIM1->CCR1 = brightness;
		
		for(i = 0; i < 1000; i++);
	}
	
	// uint32_t count = 0;
		
}
