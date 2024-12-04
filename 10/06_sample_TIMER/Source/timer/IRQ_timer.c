/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "LPC17xx.h"
#include "timer.h"
#include "../led/led.h"
extern unsigned int led_avoid_flickr; //LED0
extern unsigned int led_show_flickr;	//LED1

void TIMER2_IRQHandler (void)
{
	//handler for timer2 interrupts
	//check timer2 Interrupt Register to see whether the source of Interrupt was either MR0 or MR1 (manual page 493)
	//MR0 -> check if bit 0 is high
	//MR1 -> check if bit 1 is high
	if (LPC_TIM2->IR & (1 << 0)) {
		//MR0 REACHED
		//turn off led
		LED_Off(led_avoid_flickr);
	} 
	
	if (LPC_TIM2->IR & (1 << 1)) {
		//MR1 REACHED
		//turn on led
		LED_On(led_avoid_flickr);
	}
	
	
	//Write 1 to timer2 Interrupot Register to clear the Interrupt
  LPC_TIM2->IR = 1;			/* clear interrupt flag */
  return;
}


void TIMER3_IRQHandler (void)
{
	//handler for timer3 interrupts
	//check timer2 Interrupt Register to see whether the source of Interrupt was either MR0 or MR1 (manual page 493)
	//MR0 -> check if bit 0 is high
	//MR1 -> check if bit 1 is high
	if (LPC_TIM3->IR & (1 << 0)) {
		//MR0 REACHED
		//turn off led
		LED_Off(led_show_flickr);
	} 
	
	if (LPC_TIM3->IR & (1 << 1)) {
		//MR1 REACHED
		//turn on led
		LED_On(led_show_flickr);
	}
	
	
	//Write 1 to timer2 Interrupot Register to clear the Interrupt
  LPC_TIM3->IR = 1;			/* clear interrupt flag */
  return;
}
/******************************************************************************
**                            End Of File
******************************************************************************/
