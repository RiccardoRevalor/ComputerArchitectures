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
extern int currentCounterBuffer[];

void RIT_IRQHandler (void)
{			
	static int down=0;	
	down++;
	if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){
		reset_RIT();
		int i,k;
		int sum=0;
		long int temp;
		switch(down){
			case 1:
				for(i = 0; i<7000-1; i++) {
					sum += currentCounterBuffer[i];
				 for(k = 0; k<7000-1-i; k++) {
								 if(currentCounterBuffer[k] > currentCounterBuffer[k+1]) {
									temp = currentCounterBuffer[k];
									currentCounterBuffer[k] = currentCounterBuffer[k+1];
									currentCounterBuffer[k+1] = temp;
								 }
				 }
				}
				int average = sum/7000;
				
				for (i = 0; i < 7000 - 1; i++) {
					currentCounterBuffer[i] = 0xCAFECAFE;
				}
				LED_On(7);
				break;
			default:
				break;
		}
	}
	else {	/* button released */
		down=0;			
		disable_RIT();
		reset_RIT();
		NVIC_EnableIRQ(EINT1_IRQn);							 /* disable Button interrupts			*/
		LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
	}
		
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
