/*****************************************************************************
 * Servo.c
 * Contains code to initialize a Servo PWM timer
 * Caleb Hoeksema
 * February 2020
 ****************************************************************************/

#include "utils.h"


void TIMER_CLOCK_ENABLE(void) {
	
	// Set timer 1 clock
	//SET_BITS(RCC->APB2ENR, RCC_APB2ENR_TIM1EN);
	
}


void ADC1_Wakeup(void){
	int wait_time;
	
	if((ADC1->CR & ADC_CR_DEEPPWD) == ADC_CR_DEEPPWD) {
		
		ADC1->CR &= ~ADC_CR_DEEPPWD;
	}
	
	ADC1->CR |= ADC_CR_ADVREGEN;
	
	wait_time = 20 * (80000000 / 1000000);
	
	while(wait_time != 0){
		wait_time--;
	}
}

void Timer_Init(void) {
	
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	
	// Count up: 0, count down: 1
	//CLR_BITS(TIM1->CR1, TIM_CR1_DIR);
	TIM1->CR1 &= ~TIM_CR1_DIR;
	
	// Clock Prescale (16 bits - up to 65 535)
	TIM1->PSC = 39;
	
	// Auto-reload (also 16b)
	TIM1->ARR = 2000-1;
	
	//Clear ouptut compare mode bits for channel 1
	//FORCE_BITS(TIM1->CCMR1, TIM_CCMR1_OC1M, (TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2));
	TIM1->CCMR1 &= ~TIM_CCMR1_OC1M;
	
	// Output 1 preload enable
	//SET_BITS(TIM1->CCMR1, TIM_CCMR1_OC1PE);
	TIM1->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;
	
	// Output polarity: active high = 0, active low = 1
	//CLR_BITS(TIM1->CCER, TIM_CCER_CC1NP);	
	TIM1->CCMR1 |= TIM_CCMR1_OC1PE;
	
	// Enable channel 1 complementary output
	//SET_BITS(TIM1->CR1, TIM_CR1_CEN);
	TIM1->CCER &= ~TIM_CCER_CC1NP;
	
	// Main O/P enable: 0 = off, 1 = en
	//SET_BITS(TIM1->BDTR, TIM_BDTR_MOE);
	TIM1->CCER |= TIM_CCER_CC1NE;
	
	TIM1->BDTR |= TIM_BDTR_MOE;
	
	
	// Any value from 0:(ARR-1)
	TIM1->CCR1 = 500;
	
	// Enable timer 1
	//SET_BITS(TIM1->CR1, TIM_CR1_CEN);
	TIM1->CR1 |= TIM_CR1_CEN;
}

// Function to set the on time position waveform to a value between 600 us to 2400 us


uint16_t triggerADCConv(){	// This will convert the ADC value on the ADC port
	
	uint16_t ADCVal;
	ADC1->CR |= ADC_CR_ADSTART;
	
	while((ADC123_COMMON->CSR &= ADC_CSR_EOC_MST) == 0){}
	
	ADCVal = ADC1->DR;
	
	return ADCVal;
	// The value returned will be between 0 - 0xFFF - this is the reading used in the calculations. 
	
}


void PA1_AnalogConfig(void){
	
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	
	GPIOA->MODER |= 3U<<2;
	
	GPIOA->PUPDR &= ~(3U<<2);
	
	GPIOA->ASCR |= 1U<<1;
	
}


void ADC_CLK(void){
	
	RCC->CR |= RCC_CR_HSION;
	
	while((RCC->CR &= RCC_CR_HSIRDY) == 0){}
}



void ADC_init(void){
	
	//enable ADC clock
	RCC->AHB2ENR |= RCC_AHB2ENR_ADCEN;
	
	//Disable ADC1 - clear bits
	ADC1->CR &= ~ ADC_CR_ADEN;
	
	//Enable I/O analog switches 
	ADC123_COMMON->CCR |= SYSCFG_CFGR1_BOOSTEN;
	
	//Set bits
	ADC123_COMMON ->CCR|= ADC_CCR_VREFEN;
	
	//configure ADC presacaler
	ADC123_COMMON->CCR = ADC_CCR_PRESC;
	
	// Configure synchronous clock mode 
	ADC123_COMMON ->CCR |=ADC_CCR_CKMODE; //tHIS MAY BE WRONG
	
	//Configure all ADC as independant
	ADC123_COMMON -> CCR &= ~ADC_CCR_DUAL;
	
	//Wake up ADC 
	ADC1_Wakeup();
	// Do ADC wak up function - example 20.4
	
	//configure RES bits 
	ADC1->CFGR &= ~ADC_CFGR_RES;
	
	
	ADC1->CFGR &= ~ADC_CFGR_ALIGN;
	
	//Selest 1 conversation in the regular channel conversion sequence
	ADC1->SQR1 &= ~ADC_SQR1_L;
	
	//Specify the the channel number 6 as the 1st conversion in regular sequence 
	ADC1->SQR1 |= (ADC_SQR1_SQ1_1 | ADC_SQR1_SQ1_2);
	
	//configure teh channel 6 as the single ended
	ADC1->DIFSEL &= ~ADC_DIFSEL_DIFSEL_6;
	
	//Select ADC sample time
	ADC1->SMPR1 |= (ADC_SMPR1_SMP6_0 | ADC_SMPR1_SMP6_2);
	
	//select ADC as discontinuous mode 
	ADC1->CFGR &= ~ADC_CFGR_CONT;
	
	//Clear Bits to select software tirgger
	ADC1->CFGR &= ~ADC_CFGR_EXTEN;
	
	//Enable ADC 
	ADC1->CR |= ADC_CR_ADEN;
	
	while((ADC1->ISR &= ADC_ISR_ADRDY) == 0){}
	
}


