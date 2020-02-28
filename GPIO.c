/*****************************************************************************
 * GPIO.c
 * Contains code to initialize a GPIO port
 * Caleb Hoeksema
 * February 2020
 ****************************************************************************/

#include "lcd.h"
#include "utils.h"
#include "GPIO.h"
#include "Servo.h"

void GPIO_CLOCK_ENABLE(){
	
	// Enable GPIO port B clock
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;
}

void GPIOE_Init(void){
	
	GPIO_CLOCK_ENABLE();
	
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
