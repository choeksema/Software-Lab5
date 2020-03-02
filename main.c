/*****************************************************************************
 * main.c
 * Mainline function to run an LCD
 * Caleb Hoeksema, Gregory Huras
 * February 2020
 ****************************************************************************/


#include "stm32l476xx.h"
#include "SysClock.h"
#include "GPIO.h"
#include "lcd.h"
#include "Servo.h"
#include "ADC.h"

// initalize the Various clocks and system hardware, perform a while loop that reads teh ADC port constantly and does various conversions
// to write to values to drive and move the RC Servo. 
int main(void) {
	
	// Initalize teh System Clock
	System_Clock_Init();
	// Initalize GPIOE
	GPIOE_Init();
	// Initalize the LCD
	LCDinit();
	
	// Initalize the Timer for the servo
	Timer_Init();
	
	// Initalize and setup the ADC
	ADC_Run();
	
	//Declare values used in teh WHile loop
	uint16_t angle, time, ADCReading, MilVolts;
	
	// Loop Forever
	while(1){
		
		// Read ADC (PA1) for voltage level
		ADCReading = triggerADCConv();  		// 16 bit ADC register value
		MilVolts = MilVoltsRead(ADCReading);		// Voltage Conversion
		angle = AngleConversion(ADCReading);		// Angle Conversion
		
		// Move the servo to "angle"
		Servo_Update(angle, &time);
		
		//Print the following Values to the LCD
		LCDprintf("ADC:%d, mV:%d\nAng:%d", ADCReading, MilVolts, angle - 90);
		
		Delay_ms(100);
	}
}

