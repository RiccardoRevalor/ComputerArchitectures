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

/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
int main (void) {
  
  SystemInit();  												/* System Initialization (i.e., PLL)  */
  LED_init();                           /* LED Initialization                 */
  BUTTON_init();												/* BUTTON Initialization              */
	LED_On(0);
	
	
	//LED MANAGEMENT EXAMPLES
	//The custom defined functions LED_on and LED_Off already do this, you just havw to passs them the mask to determine which leds to switch on/off
	
	LPC_GPIO2->FIOPIN |= 0b00000001; // with this I set just the last 1 bits to 1
	//0b = binary number
	//If I set the last bit to 1 I switch on the most right led on the board
	
	LPC_GPIO2->FIOPIN |= 0b100000001; //with this I set the most left led and the most right led on on the board
	
	
	LPC_GPIO2->FIOSET = 1; //here I don't use a mask, I just the set the first bit to 1
	//FIOSET sets the bit(s) you select to 1
	LPC_GPIO2->FIOSET = 0b01010101; //with this I set to 1 the even bits, I just switch on the even leds
	
	LPC_GPIO2->FIOSET = 0xFF; //with this i switch all the leds on
	
	
	//switch off 
	LPC_GPIO2->FIOCLR = 1; //switch the first led off
	LPC_GPIO2->FIOCLR = 0xFF; //switch all the buttons off

  while (1) {                           /* Loop forever                       */	
  }

}
