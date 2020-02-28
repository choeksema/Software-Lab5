/*****************************************************************************
 * main.c
 * Mainline function to run an LCD
 * Caleb Hoeksema
 * February 2020
 ****************************************************************************/


#include "stm32l476xx.h"
#include "SysClock.h"
#include "GPIO.h"
#include "lcd.h"
#include "Servo.h"


int
main(void) {
	
	System_Clock_Init();
	GPIOE_Init();
	LCDinit();
	Timer_Init();
	
	uint32_t count = 0;
	
	int brightness = 1;
	int angle = 1;
	
	while(1) {
		
		// Read ADC (PA1) for voltage level
		// Code stuff returning a value for angle
		
		// Move the servo to "angle"
		Servo_Update(angle);
		
//		if ((brightness >= TIM1->ARR) || (brightness <= 0))
//			angle = -angle;
//		
//		brightness += angle*20;
//		
//		TIM1->CCR1 = brightness;
		
		LCDprintf("Greg, Caleb\n%d, duty:%d%%", count++, (((TIM1->CCR1)*100)/(TIM1->ARR)));
		Delay_ms(100);
	}
	
}
