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
	//EINT1
	static int downE1=0;	
	downE1++;
	if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){
		reset_RIT();
		switch(downE1){
			case 1:
				currState = next_state(currState, taps, &outputBit);
				ledsFromState(currState);
				break;
			default:
				break;
		}
	}
	else {	
		downE1=0;			
		disable_RIT();
		reset_RIT();
		NVIC_EnableIRQ(EINT1_IRQn);							 
		LPC_PINCON->PINSEL4    |= (1 << 22);     
	}
		
	//EINT2
	static int downE2=0;	
	downE2++;
	if((LPC_GPIO2->FIOPIN & (1<<12)) == 0){
		reset_RIT();
	  unsigned char initialState = currState;
		int length = 0;
		switch(downE2){
			case 1:
				do{
					length++;
					currState = next_state(currState, taps, &outputBit);
				} while(currState != initialState);
				
				//Show length on leds
				ledsFromState((unsigned char)length);
				break;
			default:
				break;
		}
	}
	else {	/* button released */
		downE2=0;			
		disable_RIT();
		reset_RIT();
		NVIC_EnableIRQ(EINT2_IRQn);							 /* disable Button interrupts			*/
		LPC_PINCON->PINSEL4    |= (1 << 24);     /* External interrupt 0 pin selection */
	}
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
