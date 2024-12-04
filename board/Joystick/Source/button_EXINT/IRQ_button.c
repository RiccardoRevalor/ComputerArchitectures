#include "button.h"
#include "LPC17xx.h"

extern int down;

void EINT0_IRQHandler (void)	  	/* INT0														 */
{		
	
	LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
}


void EINT1_IRQHandler (void)	  	/* KEY1														 */
{
	/*
	RIT TIMER IS COUNTING
	AS SOON I PRESS THIS BTN THE INTERRUPT IS DISABLED, DOWN = 1 DOWN IS EXTERN VARIABLE
	*/
	
	//DISable future interrupts of this button
	NVIC_DisableIRQ(EINT1_IRQn);		/* disable Button interrupts			 */
	//I have to set the button temporarily to gpio
	LPC_PINCON->PINSEL4    &= ~(1 << 22);     /* GPIO pin selection */
	down=1;
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)	  	/* KEY2														 */
{
	
  LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */    
}


