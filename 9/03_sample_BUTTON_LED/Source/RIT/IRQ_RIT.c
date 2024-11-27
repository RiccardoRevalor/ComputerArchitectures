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

extern unsigned char currState;  // Declare variables defined in main.c
extern unsigned char taps;
extern int outputBit;

void RIT_IRQHandler (void)
{			
	if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){ // if button 1 still pressed
		reset_RIT();
		
		currState = next_state(currState, taps, &outputBit);
		ledsFromState(currState);
	} else if ((LPC_GPIO2->FIOPIN & (1<<12)) == 0){
		unsigned char initialState = currState;
		int length = 0;
		do{
			length++;
			currState = next_state(currState, taps, &outputBit);
		} while(currState != initialState);
		
		//Show length on leds
		ledsFromState((unsigned char)length);
	}
	else {	/* button released */
		disable_RIT();
		reset_RIT();
		NVIC_EnableIRQ(EINT1_IRQn);							 /* enable Button interrupts */
		NVIC_EnableIRQ(EINT2_IRQn);							 /* enable Button interrupts */
		LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
		LPC_PINCON->PINSEL4    |= (1 << 24);     /* External interrupt 1 pin selection */
	}
		
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
		
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
