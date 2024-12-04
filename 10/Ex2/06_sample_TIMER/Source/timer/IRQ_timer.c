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

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
extern unsigned char led_value;					/* defined in funct_led								*/
extern unsigned int led_position;
extern unsigned int led_position2;
void TIMER0_IRQHandler (void)
{
	static uint8_t position = 7;
	static uint8_t sw_count = 0;
	sw_count++;	
	if(sw_count == 10){
		LED_Off(position);
		if(position == 7)
			position = 2;
		else
			position++;
		LED_On(position);
		sw_count = 0;
	}
	/* alternatively to LED_On and LED_off try to use LED_Out */
	//LED_Out((1<<position)|(led_value & 0x3));							
	/* LED_Out is CRITICAL due to the shared led_value variable */
	/* LED_Out MUST NOT BE INTERRUPTED */
  LPC_TIM0->IR |= 1;			/* clear interrupt flag */
  return;
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

extern unsigned int circBuffer[7000];
void TIMER1_IRQHandler (void)
{
	
	//campiona timer 0
	static unsigned int index = 0;
	
	//circular buffer
	//insert sampled data in circular buffer at position i % 7000
	
	unsigned int sample = LPC_TIM0->TC; //sample = the value read from counter of timer 0
	
	//insert in buffer
	circBuffer[index % 7000] = sample;
	
	
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}

void TIMER2_IRQHandler (void)
{
	static unsigned int flagBlink = 0;
	
	if( flagBlink%2 == 0){
			//qua è zero,
			LED_Off(led_position);
			flagBlink++;
	} else {
		  LED_On(led_position);
			flagBlink = 0;
	}
	
	
	LPC_TIM2->IR |= 1;			/* clear interrupt flag */
  return;
}

void TIMER3_IRQHandler (void)
{
	static unsigned int flagBlink2 = 0;
	
	if( flagBlink2%2 == 0){
			//qua è zero,
			LED_Off(led_position2);
			flagBlink2++;
	} else {
		  LED_On(led_position2);
			flagBlink2 = 0;
	}
	
	
	LPC_TIM3->IR |= 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
