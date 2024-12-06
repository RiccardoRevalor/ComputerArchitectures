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
void TIMER0_IRQHandler (void)
{
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
int currentCounterBuffer[7000];
int ccbIndex = 0;

void TIMER1_IRQHandler (void)
{
	currentCounterBuffer[ccbIndex] = LPC_TIM0->TC;		
	ccbIndex = (ccbIndex + 1) % 7000;
	
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}

int isLed0On = 1;

void TIMER2_IRQHandler (void)
{
	if (LPC_TIM2->IR==1){
		LED_Off(4);
		LPC_TIM2->IR |= 1;			/* clear interrupt flag */
	}
	if (LPC_TIM2->IR==2){
		LED_On(4);
		LPC_TIM2->IR |= 2;			/* clear interrupt flag */
	}
	if (LPC_TIM2->IR==3){
		LPC_TIM2->IR |= 3;			/* clear interrupt flag */
	}
  
  return;
}

int isLed7On = 1;
void TIMER3_IRQHandler (void)
{ 
	
	if (LPC_TIM3->IR==1){
		LED_Off(2);
		LPC_TIM3->IR |= 1;			/* clear interrupt flag */
	}
	if (LPC_TIM3->IR==2){
		LED_On(2);
		LPC_TIM3->IR |= 2;			/* clear interrupt flag */
	}
	if (LPC_TIM3->IR==3){
		LPC_TIM3->IR |= 3;			/* clear interrupt flag */
	}
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
