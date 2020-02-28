/*****************************************************************************
 * GPIO.h
 * Contains function prototypes to initialize a GPIO port
 * Caleb Hoeksema
 * February 2020
 ****************************************************************************/
 

#ifndef _GPIO_H
#define _GPIO_H

#include "SysClock.h"
#include "stm32l476xx.h"
#include "utils.h"

// Pin modes
#define		MODER_IN		0x0UL
#define		MODER_OUT		0x1UL
#define		MODER_AF		0x2UL
#define		MODER_AL		0x3UL

// Drain mode
#define 	PUSH_PULL		0x0UL
#define 	OPEN_DR			0x1UL

// Pin speed
#define		LOW_SPEED		0x0UL
#define		MED_SPEED		0x1UL
#define		FAST_SPEED	0x2UL
#define		HI_SPEED		0x3UL

// Pin pull up/down
#define		PULL_NONE		0x0UL
#define		PULL_UP			0x1UL
#define		PULL_DOWN		0x2UL
#define		PULL_RES		0x3UL

// GPIO macros
#define 	GPIO_PIN_DRV_TYPE(pin, type)		FORCE_BITS(GPIOE->ODR, 1 << (pin), (type) << (pin))
#define		GPIOE_PIN_MODE(pin, mode)				FORCE_BITS(GPIOE->MODER, 3UL << ((pin)*2UL), (mode) << ((pin)*2UL))
#define		GPIOE_OP_TYPE(pin, mode)				FORCE_BITS(GPIOE->OTYPER, 1UL << (pin), (mode) << (pin))
//#define		GPIOE_AF_SET(pin, mode)					FORCE_BITS(GPIOE->AFR[, 
#define		GPIOE_PIN_SPEED(pin, speed)			FORCE_BITS(GPIOE->OSPEEDR, 3UL << (2*(pin)), (speed) << (2*(pin)))
#define		GPIOE_PIN_PULL(pin, pull)				FORCE_BITS(GPIOE->PUPDR, 3UL << (2*(pin)), (pull) << (2*(pin)))

// GPIO function prototypes
void GPIOE_Init(void);
void GPIO_CLOCK_ENABLE(void);

#endif


