/*****************************************************************************
 * ADC.c
 * Contains function definitions to use an ADC
 * Caleb Hoeksema, Gregory Huras
 * February 2020
 ****************************************************************************/


#include "stm32l476xx.h"
#include "ADC.h"
#include "Servo.h"
#include "GPIO.h"


void ADC_Run(void) {
	
	// Turn on HSI
	ADC_CLK();
	
	// Initialize the GPIO
	GPIOA_Init();
	
	// Initalize the ADC
	ADC_init();
	
}


void ADC_CLK(void) {
	
	// Turn on internal high speed oscilator 
	RCC->CR |= RCC_CR_HSION;
	
	// Wait until HSI is ready
	while((RCC->CR & RCC_CR_HSIRDY) == 0){}
			
}

// Initalize ADC files, Source for this came from textbook/econestoga
void ADC_init(void) {
	
	//enable ADC clock
	RCC->AHB2ENR |= RCC_AHB2ENR_ADCEN;
	
	//Disable ADC1 - clear bits
	ADC1->CR &= ~ADC_CR_ADEN;
	
	//Enable I/O analog switches 
	ADC123_COMMON->CCR |= SYSCFG_CFGR1_BOOSTEN;
	
	//Set bits
	ADC123_COMMON->CCR |= ADC_CCR_VREFEN;
	
	//configure ADC prescaler 
	ADC123_COMMON->CCR = ADC_CCR_PRESC;
	
	// Configure synchronous clock mode (anything but 0)
	ADC123_COMMON->CCR |= ADC_CCR_CKMODE_1;
	
	// Configure all ADC as independant
	ADC123_COMMON->CCR &= ~ADC_CCR_DUAL;
	
	// Wake up ADC 
	ADC1_Wakeup();
	
	// Configure RES bits: BIT 00 = 12 Bit, 01 = 10 Bit, 10 = 8 Bit, 11 = 6 Bit
	ADC1->CFGR &= ~ADC_CFGR_RES;	// Resolution is set as 12 Bit
	ADC1->CFGR &= ~ADC_CFGR_ALIGN;	
	
	// Select 1 conversion in the regular channel conversion sequence
	ADC1->SQR1 &= ~ADC_SQR1_L;
	
	// Specify the channel number 6 as the 1st conversion in regular sequence 
	ADC1->SQR1 |= (ADC_SQR1_SQ1_1 | ADC_SQR1_SQ1_2);
	
	// Configure channel 6 as the single ended
	ADC1->DIFSEL &= ~ADC_DIFSEL_DIFSEL_6;
	
	// Select ADC sample time
	ADC1->SMPR1 |= (ADC_SMPR1_SMP6_0 | ADC_SMPR1_SMP6_2);
	
	// Select ADC as discontinuous mode 
	ADC1->CFGR &= ~ADC_CFGR_CONT;
	
	// Set the trigger mode
	ADC1->CFGR &= ~ADC_CFGR_EXTEN;
	
	//Enable ADC 
	ADC1->CR |= ADC_CR_ADEN;
	
	// Wait until ADC1 hardware is ready
	while((ADC1->ISR & ADC_ISR_ADRDY) == 0){}
	
}

// ADC is in sleep mode to save power, have to wake it up for it to run
void ADC1_Wakeup(void) {
	
	uint32_t wait_time;
	
	// Bring from deep power down
	if ((ADC1->CR & ADC_CR_DEEPPWD) == ADC_CR_DEEPPWD) {
		//SET_BITS(ADC1->CR, ADC_CR_DEEPPWD);
		ADC1->CR &= ~ADC_CR_DEEPPWD;
	}
	
	// Turn on internal voltage regulator
	//SET_BITS(ADC1->CR, ADC_CR_ADVREGEN);
	ADC1->CR |= ADC_CR_ADVREGEN;
	
	// Wait for the startup time
	wait_time = 20 * (CLK / 1000000);
	while (wait_time)
		wait_time--;
	
}

// This function reads the value on the ADC, Returnes the reading from 0 - 0xFFF. (0 - 4095)
uint16_t triggerADCConv(){	// This will convert the ADC value on the ADC port
	
	uint16_t ADCVal;
	
	// Start ADC conversion
	SET_BITS(ADC1->CR, ADC_CR_ADSTART);
	
	// Wait for ADC conversion to complete
	while((ADC123_COMMON->CSR & ADC_CSR_EOC_MST) == 0){}
	
	ADCVal = ADC1->DR;
	
	return ADCVal;
	// The value returned will be between 0 - 0xFFF - this is the reading used in the calculations. 
	
}

// Returns a time value from 600us to 2400us
float TimeFromReading(uint16_t reading){
	
	return reading * 0.00044 + 0.6;
	// Returns a time from 600us to 2400us
	
}

// Returns a voltage value from 0 - 3300
uint16_t MilVoltsRead(uint16_t reading){
	
	return (uint16_t)(3300 * reading / 0xFFF);
	//Returns a voltage from 0 - 3300
}

// This function returns an Angle from 0 - 180
uint16_t AngleConversion(uint16_t reading){
	
	return(int16_t)(180 * reading / 0xFFF);
}
