/*****************************************************************************
 * ADC.h
 * Contains function prototypes to use an ADC
 * Caleb Hoeksema, Gregory Huras
 * February 2020
 ****************************************************************************/
 

#ifndef _ADC_H
#define _ADC_H

#include "SysClock.h"
#include "stm32l476xx.h"
#include "utils.h"

// Pins
#define		ADC_PIN			1UL

// Clock
#define		CLK					80000000UL

// (Regular) Channel Trigger Selection
#define		EXT0				0UL
#define		EXT1				ADC_CFGR_EXTSEL_0
#define		EXT2				ADC_CFGR_EXTSEL_1
#define		EXT3				ADC_CFGR_EXTSEL_1 | ADC_CFGR_EXTSEL_0
#define		EXT4				ADC_CFGR_EXTSEL_2
#define		EXT5				ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_0
#define		EXT6				ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_1
#define		EXT7				ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_1 | ADC_CFGR_EXTSEL_0
#define		EXT8				ADC_CFGR_EXTSEL_3
#define		EXT9				ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_0
#define		EXT10				ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_1
#define		EXT11				ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_1 | ADC_CFGR_EXTSEL_0
#define		EXT12				ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_2
#define		EXT13				ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_0
#define		EXT14				ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_1
#define		EXT15				ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_1 | ADC_CFGR_EXTSEL_0

// Trigger Types
#define		TRG_SOFT		0UL
#define		TRG_HRISE		ADC_CFGR_EXTEN_0
#define		TRG_HFALL		ADC_CFGR_EXTEN_1
#define		TRG_HBOTH		ADC_CFGR_EXTEN_1 | ADC_CFGR_EXTEN_0

// ADC macros
#define		MSTR_MODE_SEL(timer, mode)			FORCE_BITS((timer), TIM_CR2_MMS, (mode))
#define		TIM4_MODE(mode)									FORCE_BITS(TIM4->CCMR1, TIM_CCMR1_OC1M, (mode))
#define		SEL_TRGR_CHNL(channel, mode)		FORCE_BITS((channel), ADC_CFGR_EXTSEL, (mode))
#define		SEL_TRGR_EDGE(channel, mode)		FORCE_BITS((channel), ADC_CFGR_EXTEN, (mode))
//#define		

// ADC Fn Prototypes
//void TIM4_Init(void);
void ADC_Run(void);
void ADC_CLK(void);
void ADC_init(void);
void ADC1_Wakeup(void);
void Set_Trigger(void);
uint16_t triggerADCConv(void);
float TimeFromReading(uint16_t reading);
uint16_t MilVoltsRead(uint16_t reading);
uint16_t AngleConversion(uint16_t reading);

#endif
