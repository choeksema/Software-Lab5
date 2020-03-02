/*****************************************************************************
 * ADC.c
 * Contains function definitions to use an ADC
 * Caleb Hoeksema
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
	
	ADC_init();
	
}


void ADC_CLK(void) {
	
	RCC->CR |= RCC_CR_HSION;
	while((RCC->CR & RCC_CR_HSIRDY) == 0){}
			
}


void ADC_init(void) {
	
	//enable ADC clock
	RCC->AHB2ENR |= RCC_AHB2ENR_ADCEN;
	
	//Disable ADC1 - clear bits
	ADC1->CR &= ~ADC_CR_ADEN;
	//CLR_BITS(ADC1->CR, ADC_CR_ADEN);
	
	//Enable I/O analog switches 
	//SET_BITS(SYSCFG->CFGR1, SYSCFG_CFGR1_BOOSTEN);
	//SYSCFG->CFGR1 |= SYSCFG_CFGR1_BOOSTEN;
	ADC123_COMMON->CCR |= SYSCFG_CFGR1_BOOSTEN;
	
	//Set bits
	//SET_BITS(ADC123_COMMON->CCR, ADC_CCR_VREFEN);
	ADC123_COMMON->CCR |= ADC_CCR_VREFEN;
	
	//configure ADC prescaler
	ADC123_COMMON->CCR = ADC_CCR_PRESC;
	
	// Configure synchronous clock mode (anything but 0)
	ADC123_COMMON->CCR |= ADC_CCR_CKMODE_1;
	
	// Configure all ADC as independant
	ADC123_COMMON->CCR &= ~ADC_CCR_DUAL;
	
	// Wake up ADC 
	ADC1_Wakeup();
	
	// Configure RES bits 
	ADC1->CFGR &= ~ADC_CFGR_RES;
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
	//Set_Trigger();
	ADC1->CFGR &= ~ADC_CFGR_EXTEN;
	
	//Enable ADC 
	ADC1->CR |= ADC_CR_ADEN;
	
	while((ADC1->ISR & ADC_ISR_ADRDY) == 0){}
	
}


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


void Set_Trigger(void) {
 
	// Select trigger event and rising edge
	SEL_TRGR_CHNL(ADC1->CFGR, EXT12);
	SEL_TRGR_EDGE(ADC1->CFGR, TRG_HRISE);

	// Start when software begins
	SET_BITS(ADC1->CR, ADC_CR_ADSTART);
 
}


uint16_t triggerADCConv(){	// This will convert the ADC value on the ADC port
	
	uint16_t ADCVal;
	
	SET_BITS(ADC1->CR, ADC_CR_ADSTART);
	
	while((ADC123_COMMON->CSR & ADC_CSR_EOC_MST) == 0){}
	
	ADCVal = ADC1->DR;
	
	return ADCVal;
	// The value returned will be between 0 - 0xFFF - this is the reading used in the calculations. 
	
}


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


/*
void TIM4_Init(void) {

	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM4EN;

	// Clear edge-aligned mode bits
	TIM4->CR1 &= ~TIM_CR1_CMS;

	// Count direction
	COUNT_DIR(TIM4->CR1, COUNT_UP);

	// Select master mode
	MSTR_MODE_SEL(TIM4->CR2, TIM_CR2_MMS_2);

	// O/P Compare 1 Mode
	TIM4_MODE(MODE_PWM);

	// Timer setup
	TIM4->PSC = 7;				// Divide 80MHz to 10MHz
	TIM4->ARR = 999;			// Get PWM frequency of 10kHz
	TIM4->CCR1 = 500;		// 50% duty

	// Select channel
	TIM4->CCER |= TIM_CCER_CC1E;

	// Enable timer
	SET_BITS(TIM4->CR1, TIM_CR1_CEN);

}
 
 */
