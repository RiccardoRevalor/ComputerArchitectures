
#include "button.h"
#include "lpc17xx.h"

/**
 * @brief  Function that initializes Buttons
 */
void BUTTON_init(void) {
	
	//i HAVE TO SETUP BUTTON KEY 1 SO THE BTN RELATED TO PIN 2.11 ONLY
	
	//Btn pressed: GND absorbs all the current, value read is 0
	//Btn not pressed: GND not connected to the circuit, value read is 1
	
	//PRESSED -> 0; RELEASED -> 1
	
	
	//HERE WE USE AN INTERRUPT FUNCTIONALITY, NOT NORMAL GPIO
	//SO WE NEED TO FORCE 01 (NOT 00 AS LEDS) TO THE PINS!!!
	
	
	
	
	//SET p2.11
	//BITS: 23 TO 0, 22 TO 1
  LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
	
	//set bit 11 to 0 and leave all the others to 1
  LPC_GPIO2->FIODIR      &= ~(1 << 11);    /* PORT2.11 defined as input          */

	
	
	//NOW, WE SET THE EXTERNAL INTERRUPT MODE
	//The interrupt can be ither trigged by the EDGE or the LEVEL
	//In case of buttons, we want to trigger the interrupt when they are pressed
	//In this case, the read current is zero (0 is read), so FALLING EDGE is read
	//We want to trigger interrupts at FALLING EDGES
	
	//POLARITY CAN BE RAISING OR FALLING EDGE
	//HERE WE NEED FALLING EDGE

  LPC_SC->EXTMODE = 0x7; //set EXTMODE to BE EDGE SENSITIVE
	//I have to turn the bit number 0, 1, 2 to 1 so 000..00111 = 0x7
	
	
	//NOW I ENABLE EINT1 FOR pin 2.11 with the lowest priority
	NVIC_EnableIRQ(EINT1_IRQn);              /* enable irq in nvic                 */
  NVIC_SetPriority(EINT1_IRQn, 1);
	
	/*
	PRIORITY OF INTERRUPTS
	The lower the number the higher the priority.
	If 2 interrupts have the same priority they're executed as they are triggered.
	If one interrupt handler is being executed BUT another interrupt with HIGHER PRIORITY (lower number) is raised
	then this second interrupt is served FIRST! And then the system excutes again the original interrupt handler related to te first interrupt with lower priority.
	*/
}
