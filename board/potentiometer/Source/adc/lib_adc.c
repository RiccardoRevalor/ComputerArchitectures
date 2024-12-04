#include "LPC17xx.h"
#include "adc.h"

/*----------------------------------------------------------------------------
  Function that initializes ADC
 *----------------------------------------------------------------------------*/
void ADC_init (void) {
	
	//setup pin function to ADC
  LPC_PINCON->PINSEL3 |=  (3UL<<30);      /* P1.31 is AD0.5                     */
	
	//BIT 12 IN PCONP IS THE ADC 
  LPC_SC->PCONP       |=  (1<<12);      /* Enable power to ADC block          */
	
	
	/*
	IN MANUAL, POINT 29.5.1 A/D Control Register
	1) Set bit number 5 of ADCR equal to 1. The first 8 bits havw a seleciton functionalities and corresponds to the used channel of the ADC7
	So I am using the sitxh channel
	
	2) Set bit 8 to 1
	I WANNA WRITE THE VALUE 4 ON A BLOCK OF BITS THAT STARTS AT BIT 8
	SO I JUST SHIFT THIS BLOCK OF BITS BY 8 POSITIONS
	
	
	3) set bit 21 to 1 to enable comnverter
	*/

  LPC_ADC->ADCR        =  (1<< 5) |     /* select AD0.5 pin                   */
                          (4<< 8) |     /* ADC clock is 25MHz/5    -> it is due to reach the maximum limitation for freq for the board           */
                          (1<<21);      /* enable ADC                         */ 

	/*
	enable interrupt on channel of index 5 (channel sixth starting from zero)
	
	*/
  LPC_ADC->ADINTEN     =  (1<< 8);      /* global enable interrupt            */

  NVIC_EnableIRQ(ADC_IRQn);             /* enable ADC Interrupt               */
}

void ADC_start_conversion (void) {
	/*
	to start conversion I have to act on ADCR register
	ADCR Register 
	set bit 24 to 1. If I set 24 to 1 it means I wann start the conversion NOW
	*/
	LPC_ADC->ADCR |=  (1<<24);            /* Start A/D Conversion 				*/
}				 
