/*****************************************************************************
 * GPIO.c
 * Contains code to initialize a GPIO port
 * Caleb Hoeksema, Gregory Huras
 * February 2020
 ****************************************************************************/

#include "lcd.h"
#include "utils.h"
#include "GPIO.h"
#include "Servo.h"
#include "ADC.h"

// Initalize the GPIO Clocks
void GPIO_CLOCK_ENABLE(volatile uint32_t port){
	
	// Enable GPIO port clock
	RCC->AHB2ENR |= port;
}

// Initalize PE8
void GPIOE_Init(void){
	
	GPIO_CLOCK_ENABLE(PORT_E);
	
	// Set pin I/O mode (LCD)
	GPIOE_PIN_MODE(LCD_D4, MODER_OUT);
	GPIOE_PIN_MODE(LCD_D5, MODER_OUT);
	GPIOE_PIN_MODE(LCD_D6, MODER_OUT);
	GPIOE_PIN_MODE(LCD_D7, MODER_OUT);
	
	GPIOE_PIN_MODE(LCD_E, MODER_OUT);
	GPIOE_PIN_MODE(LCD_RS, MODER_OUT);
	
	//Set output type (LCD)
	GPIOE_OP_TYPE(LCD_D4, PUSH_PULL);
	GPIOE_OP_TYPE(LCD_D5, PUSH_PULL);
	GPIOE_OP_TYPE(LCD_D6, PUSH_PULL);
	GPIOE_OP_TYPE(LCD_D7, PUSH_PULL);
	
	GPIOE_OP_TYPE(LCD_E, PUSH_PULL);
	GPIOE_OP_TYPE(LCD_RS, PUSH_PULL);
	
	
	// Set pin I/O mode (Servo)
	GPIOE_PIN_MODE(SERVO_PIN, MODER_AF);
	
	GPIOE->AFR[1] &= ~(0xFUL);
	GPIOE->AFR[1] |= 1UL;
	
	GPIOE_PIN_SPEED(SERVO_PIN, LOW_SPEED);
	GPIOE_PIN_PULL(SERVO_PIN, PULL_NONE);	
	
}

// Initalize Gpio A
void GPIOA_Init(void) {
	
	GPIO_CLOCK_ENABLE(PORT_A);
	
	// Set pin I/O settings (ADC)
	GPIOA_PIN_MODE(ADC_PIN, MODER_AL);
	GPIOA_PIN_PULL(ADC_PIN, PULL_NONE);
	
	GPIOA->ASCR |= 1U<<1;			// Pin 1 (close analog switch)

}
