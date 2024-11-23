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
  //You can look at Peripherals -> Clocking and POwer Ctrl -> Clock generation schematic
	//and clock source selection to see the clock SystemInit() has set for us, among other things
	
	//Now, open the PIN Connect Block (In peripherals)
	LED_init();                           /* LED Initialization                 */
  BUTTON_init();												/* BUTTON Initialization              */
	//If you open the PIN Connect Block you'll see that pin 2.10, 2.11, 2.12 are now set to EINT0, EINT1, EINT2 instead of standard GPIO Mode!
	
	while (1) {};
	/*for checking the direction of pins is correctly set after these inits:
	1) open Peripherals > GPIO Fast Interface > Port 2 (as we've used this port)
	2) After LED_Init(): direction of leds pin to 1 (output)
	In facts, you see from the GPIO Fast Interface that after the led_init()
	we have FIO2DIR: 0x000000FF to use the 8 leds (8 lsb: bits 0 to 7) and the are all CHECKED 
	3) After the execution of the BUTTON_init(), pins 10, 11, 12 are connectd to the buttons.
	You can look at Peripherals -> System Ctrl Block -> External Interrupts
		After the BUTTON_INIT: The Mode for EINT0,1,2 gets updated from 0 to 1!!!!
		To look for edges.
		
		Now open Peripherals -> Core Peripherals -> Nested Vectored Interrupt Controller (NVIC)
		Here you see that External Interrupts 0,1,2 (indexes number 34, 35, 36 in the table) have 1 to the 'E' columns. 'E' stands for enabled.
		
		To force an interrupt by simulating an 'in software' button pressing:
		1) set a breakpoint at the while (1). IN debug mode, click F5 to run the system 
		2) In software, work on the GPIO Fast Interface to control the 3 pins related to the 3 buttons we have set
		pins: 2.10, 2.11, 2.12
		You can check or unchek the bit 9,10,11 in the PINS row (the last row near) to trigger the interrupts
		By triggering interrupts, you will execute them in the IRQ_button.c file
		*/
	
	
	
	
	
	//TOY EXAMPLES WITH LEDS AND COMBINATION OF LEDS
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
