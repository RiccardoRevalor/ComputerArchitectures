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
#include "RIT.h"

/* Led external variables from funct_led */
extern unsigned char led_value;					/* defined in lib_led								*/
volatile unsigned int led_position = 0;
volatile unsigned int led_position2 = 1;

//ex2
//cirular buffer of 7000 elements -> it's an array
volatile unsigned int circBuffer[7000];

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif
/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
int main (void) {
  
	//unsigned int ledPosition = 7;
	
	SystemInit();  												/* System Initialization (i.e., PLL)  */
  LED_init();                           /* LED Initialization                 */
  BUTTON_init();												/* BUTTON Initialization              */
	init_timer(2,0x3D090);							 //0.01 s 100Hz
	init_timer(3,0x1AB3F0);               //0.07s
	
	/* TIMER0 Initialization              */
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
	LED_On(led_position);
	LED_On(led_position2);
	enable_timer(2);
	enable_timer(3);
	
	
	
	
	
	//EX 2
	//set and start timer 0 ad a runnign timer
	init_timer(0, 0xC350);
	enable_timer(0);
	
	//set timer 1 to a frequency 100x than timer2 frequency
	//0x9C4
	init_timer(1, 0x9C4);
	enable_timer(1);


	//initialize RIT timer to 50 ms
	init_RIT(0x004C4B40);
	
	
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= 0xFFFFFFFFD;						
		
  while (1) {                           /* Loop forever                       */	
		__ASM("wfi");
  }

}
