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
unsigned int led_avoid_flickr; //LED0
unsigned int led_show_flickr;	//LED1

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
	//init_timer(0,0x00006148);							/* TIMER0 Initialization              */
																				/* K = T*Fr = [s]*[Hz] = [s]*[1/s]	  */
																				/* T = K / Fr = 0x017D7840 / 25MHz    */
																				/* T = K / Fr = 25000000 / 25MHz      */
																				/* T = 1s	(one second)   							*/
	
																				/* T = 1ms - Fr = 25MHz								*/
																				/* K = T * F = 1*10^-3 * 25*10^6			*/																
	
	//set LED0 and LED1 for first point
	led_avoid_flickr = 0;
	led_show_flickr = 1;
	LED_On(led_avoid_flickr);
	LED_On(led_show_flickr);
	
	/*
	RAGIONAMENTO PER NON FARE PERCEPIRE IL FLICKERING ALL'OCCHIO UMANO
	Io ho pensato in questo modo:
metto 75 hz come freq di lampeggiamento perchè non si veda il flickering (media tra 60 e 90, magari poi adatto), essendo il duty di 50 ho TempoOn = TempoOff = 1 / 75 Hz * 1/2.
La frequenza PCLK base è 25 Mhz quindi faccio:
K_off = TempoOff×PCLK=0.00666×25,000,000=166,666.67 -> (int)166667
K_on = K_off + TempoOn×PCLK=2*166666.67 = 333,333.33 -> (int)333333
	*/
	init_timer(2, 0x28B0B, 0x51615);
	
	//start timer2
	enable_timer(2);
	
	
	//do the same for timer 3
	/*
	RAGIONAMENTO PERE FARE PERCEPIRE IL FLICKERING ALL'OCCHIO UMANO
	Metto 10 hz come frequenza di lampeggiamento per fare vedere il flickering
	duty = 50
	PCLK = 25 Mhz
	TempoOn = TempoOff = 1 / 10 Hz * 1/2
	K_Off = TempoOff * PCLK = 0.05 * 25,000,000 = 1,250,00 (già int)
	K_On = 2 * K_off = 2,500,000 (già int)
	*/
	init_timer(3, 0x1312D0, 0x2625A0);
	
	enable_timer(3);
	
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
