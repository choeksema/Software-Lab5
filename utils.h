/*****************************************************************************
 * utils.h
 * Header file containing various useful functions
 * Caleb Hoeksema
 * February 2020
 ****************************************************************************/
 
 
#ifndef _UTILS_H
#define _UTILS_H

#include "stm32l476xx.h"
 
// General Definitions -------------------------------------------------------
#define	LOW_BYTE(arg)		((arg) & 0xFF)

#define	SET_BITS(port, mask)		((port) |= (mask))
#define	CLR_BITS(port, mask)		((port) &= ~(mask))
#define	FLIP_BITS(port, mask)		((port) ^= (mask))

#define	FORCE_BITS(port, mask, value)		(port) = ((port) & ~(mask)) | ((value) & (mask))

#define GPIO_PIN_DRV_TYPE(pin, type)		FORCE_BITS(GPIOE->ODR, 1 << (pin), (type) << (pin))
#define	GPIO_PIN_MODE(pin, mode)				FORCE_BITS(GPIOE->MODER, 3 << ((pin)*2), (mode) << ((pin)*2))

#define	LO_NYBBLE(val)	((val) & 0x0F)
#define	HI_NYBBLE(val)	(((val) >> 4) & 0x0F)

// LCD Definitions -----------------------------------------------------------
//#define LCD_MOVE_CURSOR		(0x80)		// Command to write an address to DDRAM
//#define LCD_NEW_LINE			(0x28)		// 0x28=40d, the start of the new line


// LCD Prototypes ------------------------------------------------------------
//void LCDinit(void);
//static void LCDcmd(uint8_t thisByte);
//static void LCDdata(uint8_t thisByte);
//void LCDputc(unsigned char thisChar);
//void LCDputs(char *thisString);
//void LCDprintf(char *fmt, ...);

////General Prototypes ---------------------------------------------------------
//void Delay_ms(uint32_t delayTime);

#endif

