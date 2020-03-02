/*****************************************************************************
 * GPIO.h
 * Contains function prototypes to initialize a GPIO port
 * Caleb Hoeksema, Gregory Huras
 * February 2020
 ****************************************************************************/
 

#ifndef _GPIO_H
#define _GPIO_H

#include "SysClock.h"
#include "stm32l476xx.h"

void GPIO_Init(void);
void GPIO_CLOCK_ENABLE(void);

#endif


