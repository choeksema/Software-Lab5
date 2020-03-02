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
#include "ADC.h"


int main(void) {
	
	System_Clock_Init();
	GPIOE_Init();
	LCDinit();
	
	// Servo Stuff
	Timer_Init();
	
	// Start up ADC
	ADC_Run();
	
	uint16_t angle, time, ADCReading, MilVolts;
	
	while(1){
		
		// Read ADC (PA1) for voltage level
		ADCReading = triggerADCConv();  				// 16 bit ADC register value
		MilVolts = MilVoltsRead(ADCReading);		// Voltage Conversion
		angle = AngleConversion(ADCReading);		// Angle Conversion
		
		// Move the servo to "angle"
		Servo_Update(angle, &time);
		
		//Print the following Values to the LCD
		LCDprintf("ADC:%d, mV:%d\nAng:%d", ADCReading, MilVolts, angle - 90);
		
		Delay_ms(100);
	}
	
}

