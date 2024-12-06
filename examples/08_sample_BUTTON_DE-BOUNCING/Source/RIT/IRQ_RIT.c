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

void RIT_IRQHandler (void)
{			
	static int down=0;	
	down++;
	if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){
		static uint8_t position=0;
		reset_RIT();
		switch(down){
			case 1:
				LED_Off(7);
				LED_Off(6);
				LED_Off(5);
				LED_Off(4);
				if( position == 3){
					LED_On(0);
					LED_Off(3);
					position = 0;
				}
				else{
					LED_Off(position);
					LED_On(++position);
				}
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
	
	static int down2=0;	
	down2++;
	if((LPC_GPIO2->FIOPIN & (1<<12)) == 0){
		static uint8_t position=0;
		reset_RIT();
		switch(down2){
			case 1:
				LED_Off(3);
				LED_Off(2);
				LED_Off(1);
				LED_Off(0);
				if( position == 7){
					LED_On(4);
					LED_Off(7);
					position = 4;
				}
				else{
					LED_Off(position);
					LED_On(++position);
				}
				break;
			default:
				break;
		}
	}
	else {	/* button released */
		down2=0;			
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