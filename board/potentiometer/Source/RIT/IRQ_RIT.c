/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "LPC17xx.h"
#include "RIT.h"
#include "../led/led.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

int down=0;

void RIT_IRQHandler (void)
{					
	
	/*
	If I start the conversion omnce it just converts one.
	To keep converting every tot time I have to use a RIT timer
	I set it to 15 ms
	1 / 15 ms would be the Sampling Frequency !
	At every interval of 15 ms I trigger the timer handler and convert, and so on...
	
	*/
			
	/* ADC management */
	ADC_start_conversion();		
			
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
}

/******************************************************************************
**                            End Of File
******************************************************************************/
