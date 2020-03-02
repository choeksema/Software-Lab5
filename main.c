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

float TimeFromReading(uint16_t reading){
	
	return reading * 0.00044 + 0.6;
}

uint16_t MilVoltsRead(uint16_t reading){
	
	return (uint16_t)(3300 * reading / 0xFFF);
}

// 180/OxFFF - This will 
uint16_t AngleConversion(uint16_t reading){
	
	return(int16_t)(180 * reading / 0xFFF);
}

int main(void) {



	
	System_Clock_Init();
	// Initalize the GPIO
	GPIO_CLOCK_ENABLE();
	GPIOE_Init();
	
	// LCD Init
	LCDinit();
	
	// Intialize the Timer
	TIMER_CLOCK_ENABLE();
	Timer_Init();
	
	// Initalize the ADC
	ADC_CLK();
	ADC_init();
	
	
	
	
	/*
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
	*/
	
	
	uint16_t ADCReading, MilVolts, Angle;
	while(1){
		
		//ADCvalue is the 16 bit value outputed from the ADC register
		ADCReading = triggerADCConv();
		
		
		// Convertes the ADC value (0 - 0xFFF) to a voltage
		MilVolts = MilVoltsRead(ADCReading);
		
		// Converts the ADC Value into an Angle
		Angle = AngleConversion(ADCReading);
		
		//Print the following Values to the LCD
		LCDprintf("ADC:%d, V:%d, A:%d",ADCReading, MilVolts, Angle);
		Delay_ms(100);
	}
		
}
