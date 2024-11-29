/*----------------------------------------------------------------------------
 * Name:    sample.c
 * Purpose: to control led through EINT buttons 
 *        	- key1 switches on LED10 
 *				  - key2 switches off all LEDs 
 *			    - int0 switches on LED 11
 * Note(s): this version supports the LANDTIGER Emulator
 * Author: 	Paolo BERNARDI - PoliTO - last modified 07/12/2020
 *----------------------------------------------------------------------------
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2017 Politecnico di Torino. All rights reserved.
 *----------------------------------------------------------------------------*/
                  
#include <stdio.h>
#include "LPC17xx.H"                    /* LPC17xx definitions                */
#include "led/led.h"
#include "button_EXINT/button.h"

/* Led external variables from funct_led */
extern unsigned char led_value;					/* defined in funct_led								*/
#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif

unsigned char currentState = 0xAA; //0b101010
unsigned char taps = 0x2E; //0b00011101
/*examples of taps tested:
1) 0b00011101 = 0x1D 		taps: 0, 2, 3, 4
2) 0b00001101 = 0xD  		taps: 0, 2, 3
3) 0b00101100 = 0x2C		taps: 2, 3, 5
4) 0b00101110 = 0x2E		taps: 1, 2, 3, 5

*/
//for point b:
unsigned char startState = 0xAA; //when the program is loaded, startState = currentState

/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
int main (void) {
 
  SystemInit();  												/* System Initialization (i.e., PLL)  */
  LED_init();                           /* LED Initialization                 */
  BUTTON_init();												/* BUTTON Initialization              */
	
	LED_Out(currentState); //ti "accende" i led con sequenza binaria
	
  while (1) {                           /* Loop forever                       */	
  }

}
