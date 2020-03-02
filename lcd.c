/*****************************************************************************
 * lcd.c
 * Contains code to use an LCD
 * Caleb Hoeksema, Gregory Huras
 * February 2020
 ****************************************************************************/

#include "lcd.h"
#include "utils.h"
#include <stdio.h>
#include <stdarg.h>

void 
LCDinit(void) {

	Delay_ms(5);
	// run through sync sequence from datasheet to start 4-bit interface
	
	LCD_E_HI;
	LCD_BUS( 0x03 );      // wake up display & sync
	LCD_E_LO;

	Delay_ms( 5 );

	LCD_E_HI;
	LCD_BUS( 0x03 );      // wake up display & sync
	LCD_E_LO;

	Delay_ms( 1 );  

	LCD_E_HI;
	LCD_BUS( 0x03 );      // wake up display & sync
	LCD_E_LO;

	LCD_E_HI;
	LCD_BUS( 0x02 );      // wake up display & sync - go to 4-bit mode
	LCD_E_LO;

	Delay_ms( 2 );

	// now that we're sync'd and in 4-bit mode, issue commands to configure the display
	LCDcmd( LCD_CMD_FUNCTION | LCD_FUNCTION_4BIT | LCD_FUNCTION_2LINES | LCD_FUNCTION_5X8FONT );
	LCDcmd( LCD_CMD_DISPLAY | LCD_DISPLAY_OFF );
	LCDclear();
	LCDcmd( LCD_CMD_ENTRY | LCD_ENTRY_MOVE_CURSOR | LCD_ENTRY_INC );
	LCDcmd( LCD_CMD_DISPLAY | LCD_DISPLAY_ON | LCD_DISPLAY_NOCURSOR | LCD_DISPLAY_NOBLINK );

}


void 
LCDprintf(char *fmt, ...) {
	
	LCDclear();
	
	va_list args;
	char buffer[MAX_LCD_BUFSIZ];
	
	va_start(args, fmt);
	vsnprintf(buffer, MAX_LCD_BUFSIZ, fmt, args);
	va_end(args);
	
	LCDputs(buffer);
}


void
LCDputs(char *thisString) {
	
	while(*thisString)
		LCDputc(*thisString++);
	
}


void
LCDputc(unsigned char thisChar) {
	
	// Check for newlines and similar
	switch (thisChar) {
		case '\n':
			LCDcmd(LCD_MOVE_CURSOR | LCD_NEW_LINE);
			break;
		case '\r':
			LCDcmd(LCD_MOVE_CURSOR | LCD_NEW_LINE);
			break;
		default:
			LCDdata((uint8_t)thisChar);
	}
}


void
LCDclear(void) {
	
	LCDcmd(0x01);	// Command to reset cursor and clear screen
	
}

static void 
LCDdata(uint8_t thisByte) {
	
	Delay_ms(2);
	LCD_E_LO;
	LCD_RS_DR;
	
	LCD_E_HI;
	LCD_BUS(HI_NYBBLE(thisByte));
	LCD_E_LO;
	
	LCD_E_HI;
	LCD_BUS(LO_NYBBLE(thisByte));
	LCD_E_LO;
	Delay_ms(2);
	
}


static void
LCDcmd(uint8_t thisByte) {
	
	Delay_ms(2);
	LCD_E_LO;
	LCD_RS_IR;
	
	LCD_E_HI;
	LCD_BUS(HI_NYBBLE(thisByte));
	LCD_E_LO;
	
	LCD_E_HI;
	LCD_BUS(LO_NYBBLE(thisByte));
	LCD_E_LO;
	Delay_ms(2);
	
}


void 
Delay_ms(uint32_t delayTime) {

	SysTick->CTRL = 0;            // Disable SysTick
  SysTick->LOAD = (80000000UL / 1000UL) * delayTime;    // Set reload register
	SysTick->VAL = 0;             // Reset the SysTick counter value
	
	// Select processor clock: 1 = processor clock; 0 = external clock
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
  
	// Disable SysTick interrupt, 1 = Enable, 0 = Disable
	SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
	
	// Enable SysTick
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	
	// Wait for timeout
	while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
	
	// Disable SysTick until next time
	SysTick->CTRL = 0; 
	
}
