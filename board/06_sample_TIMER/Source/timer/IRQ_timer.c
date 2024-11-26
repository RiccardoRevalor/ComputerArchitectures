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
	//AFTER EVERY 1 SEC WE GO INTO THE HANDLER FOR TIMER 0
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
	
	
	
	
	/*
	I take the Instr reg of timer 0 and make an OR with 1...why???
	The current value of associated Interrupt reg is 1..wjy 1? Because gthe interrupt reg (see slides) has its bit number 0 set to 1 when an interrupt related to MR0 is raised.
	Now, before exiting the interruot handler I don't wanna call it enymore to I have to write 1 to the corresponding Interruopt Reg to reset the Interrupt reg
	So, I do this OR that just changes the LSB and sets it to 1 to reset the LSB of IR.
	*/
  LPC_TIM0->IR |= 1;			/* clear interrupt flag */
  return; //I EXIT FROM THE TIMER HANDLER
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
void TIMER1_IRQHandler (void)
{
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
