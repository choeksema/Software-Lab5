/*****************************************************************************
 * GPIO.c
 * Contains code to initialize a GPIO port
 * Caleb Hoeksema, Gregory Huras
 * February 2020
 ****************************************************************************/

#include "utils.h"
#include "GPIO.h"


void GPIO_CLOCK_ENABLE(){
	
	// Enable GPIO port E clock
	SET_BITS(RCC->AHB2ENR, RCC_AHB2ENR_GPIOEEN);
}


void GPIO_Init(void){
	
	// 00 = Input, 01 = Output, 10 = Alt Fn, 11 = Analogue
	FORCE_BITS(GPIOE->MODER, 0x3 << (2*8), 0x2 << (2*8));	// Set alternate function
	FORCE_BITS(GPIOE->AFR[1], 0xF, 0x1);			// Set to alternate function 1 (TIM_CH1N)
	
	// 00 = Low speed, 01 = Medium, 10 = Fast, 11 = Reserved
	//FORCE_BITS(GPIOE->OSPEEDR, (0x3 << (2*8)), 0x0);		// Clear bits for low speed
	
	// 00 = no PUPD, 01 = PU, 10 = PD, 11 = Reserved
	FORCE_BITS(GPIOE->PUPDR, (0x3 << (2*8)), 0x0);
	
}
