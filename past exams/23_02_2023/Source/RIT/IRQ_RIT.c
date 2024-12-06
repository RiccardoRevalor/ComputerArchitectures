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
#include <stdio.h>
#include <stdbool.h>

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/


extern unsigned short var;
void RIT_IRQHandler (void)
{			
	static int down=0;	//ogni qual volta premo il bottone o continuo a premerlo down aumenta
	down++;
	if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){
		reset_RIT();
		switch(down){
			case 1:
				break;
			default:
				break;
		}
	}
	else {	/* button released */
		/*
		l'intervallo del RIT è 50 ms
		quindi per down < 6 hai che il KEY 1 è premuto per < 300 ms
		se down è >= 6 viene incrementato di due ogni 300 ms
		*/
		if (down < 6){
			//incrementa var di 1
			++var;
		} else {
			if (down % 6 == 0){
				var=var+2;
			}
		}
	}
		
		
		
		disable_RIT();
		reset_RIT();
		NVIC_EnableIRQ(EINT1_IRQn);							 /* disable Button interrupts			*/
		LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
		
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
