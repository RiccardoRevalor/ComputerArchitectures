/*----------------------------------------------------------------------------
 * Name:    sample.c
 * Purpose: 
 *		to control led11 and led 10 through EINT buttons (similarly to project 03_)
 *		to control leds9 to led4 by the timer handler (1 second - circular cycling)
 * Note(s): this version supports the LANDTIGER Emulator
 * Author: 	Paolo BERNARDI - PoliTO - last modified 15/12/2020
 *----------------------------------------------------------------------------
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2017 Politecnico di Torino. All rights reserved.
 *----------------------------------------------------------------------------*/

                  
#include <stdio.h>
#include "LPC17xx.h"                    /* LPC17xx definitions                */
#include "led/led.h"
#include "button_EXINT/button.h"
#include "timer/timer.h"

/* Led external variables from funct_led */
extern unsigned char led_value;					/* defined in lib_led								*/
#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif
/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
	int main (void) {
  	
	SystemInit();  												/* System Initialization (i.e., PLL)  */
  LED_init();                           /* LED Initialization                 */
  BUTTON_init();												/* BUTTON Initialization              */
	/*
	to init_timer i Pass two params:
	- 0 param: I wanna configure TIMER 0 
	- hex param: this will be copied into the first Match Register
	The clk of timer goes at 15 MHZ, if I wanna wait for 1 sec I have to do: 25 * 10 ^6 * 1 sec = 25 * 10 ^ 6 Clock Cycles
	So in Hex this value corresponds to 0x017D7840
	*/
	//0x017D78407
	//THE CALCULATIONS ARE RELATED TO 0x017D78407 WHICH IS THE ORIGINAL VALUE USED IN THIS EXAMPLE TEMPLATE
	//BUT TO INIT THE TIMER I PUT 0x00006148 TO SPEED UP THE PROCESS OF SWITCHING LEDS IF COUNT = 10 AT THE TIMER INTERRUPT
	init_timer(0,0x00006148);							/* TIMER0 Initialization              */
																				/* K = T*Fr = [s]*[Hz] = [s]*[1/s]	  */
																				/* T = K / Fr = 0x017D7840 / 25MHz    */
																				/* T = K / Fr = 25000000 / 25MHz      */
																				/* T = 1s	(one second)   							*/
	
																				/* T = 1ms - Fr = 25MHz								*/
																				/* K = T * F = 1*10^-3 * 25*10^6			*/																
//	init_timer(0,0x000061A8);
	
//	init_timer(0,0xFFFFFFFF);							// 5min 43sec
	//init_timer(0,0x00B41780);							// 1min 0x2CB41780
//	init_timer(0,0x0EE6B280);								// 10 sec
	LED_On(7);
	
	
	/*
	we enabled timer 0 passing the index of timer 0
	Then the timer starts counting

	*/
	//NOTE THAT TCR IS STILL 0 IN PERIPHERALS > TIMER > TIMER0
	enable_timer(0);
	
	/*
	The we move to power down mode
	REMEMBER: THIS MODE DOESN'T STOP THE TIMERS CLOCKS!!
	
	So: we set timer to wait for 1 sec, then power down mode
	After 1 sec the timer raises an interrupt
	so we go inside the handler of the timer interrupt
	At the end of it the system comes back to power down mode because we set the sleep-on-exit bit so it sleeps for another sec
	After another sec the timer raises another interrupt because we set bit 2 = 0 in MCR (see lib_timer.c init_timer)
	*/
	LPC_SC->PCON |= 0x1;			/* power-down mode */
	//TC DID PASS FROM 2 TO 4 BECAUSE MAYBE THIS INST CORRESPON DS TO 2 CLOCKS
	LPC_SC->PCON &= 0xFFFFFFFFD;						
	SCB->SCR |= 0x2;			/*set SLEEPONEXIT  */	
  	
	__ASM("wfi");

	//SEE PERIPHERALS > TIMER > TIMER0 TO CONTROL THE VALUE OF MCR, MR0 and the flags !!

}
