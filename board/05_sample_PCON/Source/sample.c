/*----------------------------------------------------------------------------
 * Name:    sample.c
 * Purpose: 
 *		to control led through EINT buttons (similarly to project 03_)
 * 		to enter a power-down mode while waiting for interruptions
 * Note(s): this version supports the LANDTIGER Emulator
 * Author: 	Paolo BERNARDI - PoliTO - last modified 07/12/2020
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

/* Led external variables from funct_led */
extern unsigned char led_value;					/* defined in funct_led								*/
#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif
/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
int main (void) {
  	
	SystemInit();				/* System Initialization (i.e., PLL)  */
	LED_init();				/* LED Initialization                 */
	BUTTON_init();				/* BUTTON Initialization              */
	
	
	
	/*
	set the last 2 LSB to 01. I have to use a combination of OR + AND
	Set power down mode. I have to write 01 in the LSB of PCON
	So I am forcing to 1 the LSB
	Then I use a mask with D as final char. D = 1101
	So the effect of the mask is forcing to 0 the second bit
	
	*/
	
	LPC_SC->PCON |= 0x1;			/* power-down mode */
	LPC_SC->PCON &= 0xFFFFFFFFD;	
	SCB->SCR |= 0x4;			//SET SLEEP DEEP BIT because this is required by the manual because I enter in power down mode if sleep deep bit is set
	//BUG: regardless the value of sleep deep bit we always enter in power down mode so you can also not write it 
	/*
	Then I wann set the sleep on exit bit which is bit number 1 from right. So at the end of the interrupt handler we wanna return to power down mode
	*/
	SCB->SCR |= 0x2;			/*set SLEEPONEXIT  */
	
	/*
	I wanna move into SLEEP MODE
	I have to set the 2 LSB to 0 in the PCON rebister
	I can do it with an AND with a  mask which is all F and final C so all ones and two final zeros
	I also have to set the SLEEPDEEP bit to 0 (bit 2 of sys ctrl reg) to 0 because I don't want deep sleep but just sleep.
	In order to do so I use a mask with all 1 except 0 in the third lsb (so bit number 2 from rigth)...in hex that value is all F and the last is B
	*/
	//LPC_SC->PCON |= 0xFFFFFFFC;  //ENABLE SLEEP MODE
	//SCB->SCR &= 0xFFFFFFFB;				//DEEPSLEEP FLAG SET TO 0 BECAUSE I JUST WANT SLEEP AND NOT DEEP SLEEP
		
  	
	__ASM("wfi"); //wait for interrupt
	
	/*
	Avfter this if you click F5 Run you see at the bottom the timer running but the system stays at this instruction !!
	
	*/
	
	/*open Peripherals -> Core and config > To see system ctrl value
	open Perioherals > Clocking and power > Power Ctrl to see the bits of PCON */


}
