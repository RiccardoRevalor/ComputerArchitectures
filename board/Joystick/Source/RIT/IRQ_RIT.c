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

//DOWN = 0 (VOLATILE -> NOT GONNA BE OPTIMIZED)
volatile int down=0;

void RIT_IRQHandler (void)
{					
	static int up=0;
	static int position=0;	
	
	if((LPC_GPIO1->FIOPIN & (1<<29)) == 0){	
		/* Joytick UP pressed */
		up++;
		switch(up){
			case 1:
				//turn off the led of currrent position and on the led at position 0
				LED_Off(position);
				LED_On(0);
				position = 0;
				break;
			case 60:	//3sec = 3000ms/50ms = 60
				//60: after 3 sec
				/*
			check after 3 seconds: 
			Tpoll = 50 ms (period of polling)
			Tcheck = 3 seconds = 3000 ms
			1 interval takes 50 ms
			2 interval take 100 ms
			4 intervals take 200 ms
			So I have to wait for 3 seconds is simply Tcheck / Tpoll
			So 3000 ms / 50 ms = 60 intervals of 50 ms each!!!
				*/
				LED_Off(position);
				LED_On(7);
				position = 7;
				break;
			default:
				break;
		}
	}
	else{
			up=0;
	}
	
	/* button management */
	if(down>=1){ 
		if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){	/* KEY1 pressed */
			/*
			2 SITUATIONS:
			1) IS BUTTON 2.11 (KEY1) STILL PRESSED?
			IF YES, DOWN >= 1
			IF THE POLLING IS DONE RIGHT AFTER I PRESS THE BUTTON, THE POLLING IS DONE ON THE BOUNCING
			IF IT IS 1 THEN THE USER HAS TO PRESS AGAIN
			IT IT IS ZERO, IT COULD STILL BE BOUNCING
			
			SO I USE DOWN ==2 BECAUSE DOWN ==1 COULD MEAN IT'S JUST BOUNCING
			I HAVE TO WAIT FOR DOWN == 2 SO FOR ANOTHER INTERVAL OF THE TIMER TO BE SURE THE USER ACTUALLY WANTS TO PRESS THE BUTTON!!!
			*/
			switch(down){				
				case 2:				/* pay attention here: please see slides 19_ to understand value 2 */
				if( position == 7){
					LED_On(0);
					LED_Off(7);
					position = 0;
				}
				else{
					LED_Off(position);
					LED_On(++position);
				}
					break;
				default:
					//IF DOWN == 1 DO NOTHING
					//IT COULD BE BOUNCING SO WE HAVE TO WAIT FOR ANOTHER INTERVAL OF THE TIMER!!
					//IF IT'S 1 I CANNOT DISTINGUISH WHETHER IT WAS AN ACTUAL RELEASE OF THE BTN OR JUST BOUNCING
					//SO WAIT FOR ANOTHE INTERVAL TO BE SURE THE BUTTON IS PRESSED AND RELEASED PROPERLY BY THE USER
					break;
			}
			down++;
		}
		else {	/* button released */
			/*
			IF KEY1 NOT PRESSED, I HAVE TO DISCARD THIS PRESSING, SET BACK THE PIN TO INTERRUPT INSTEAD OF GPIO AND SET DOWN = T
			*/
			down=0;			
			NVIC_EnableIRQ(EINT1_IRQn);							 /* enable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
		}
	}
/*	else{
			if(down==1)
				down++;
	} */
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
