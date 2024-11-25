
#include "button.h"
#include "lpc17xx.h"

/**
 * @brief  Function that initializes Buttons
 */
void BUTTON_init(void) {
	
	//IN THE SCHEMATIC YOU SEE YOU HAVE TO USE PINS:
	//2.10
	//2.11
	//2.12
	//FOR BUTTONS
	
	//Btn pressed: GND absorbs all the current, value read is 0
	//Btn not pressed: GND not connected to the circuit, value read is 1
	
	//PRESSED -> 0; RELEASED -> 1
	
	
	//HERE WE USE AN INTERRUPT FUNCTIONALITY, NOT NORMAL GPIO
	//SO WE NEED TO FORCE 01 (NOT 00 AS LEDS) TO THE PINS!!!
	
	//SET p2.10
	//BITS 21 SET TO 0, 20 SET TO 1
  LPC_PINCON->PINSEL4    |= (1 << 20);		 /* External interrupt 0 pin selection */
	//for p2.10 -> set bit 21 to 0 and bit 20 to 1 --> APLY A MASK WITH 1 SHIFTED LEFT 20 POSITION
	//then I have to set the verse (input, output)
	//button obviously are only for input
	//we set bits 10, to 0
	//<< shift lofic left
  LPC_GPIO2->FIODIR      &= ~(1 << 10);    /* PORT2.10 defined as input          */
	//~= negation
	//I set everything to 1 except for bit 10 that is set to 0
	
	
	
	
	//SET p2.11
	//BITS: 23 TO 0, 22 TO 1
  LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
	
	//set bit 11 to 0 and leave all the others to 1
  LPC_GPIO2->FIODIR      &= ~(1 << 11);    /* PORT2.11 defined as input          */
	
	
	
	
	//SET p.21
  //BITS: 25 TO 0, 24 TO 1	
  LPC_PINCON->PINSEL4    |= (1 << 24);     /* External interrupt 0 pin selection */
	
	//set bit 12 to 0 and leave all the others to 1
  LPC_GPIO2->FIODIR      &= ~(1 << 12);    /* PORT2.12 defined as input          */
	
	
	//NOW, WE SET THE EXTERNAL INTERRUPT MODE
	//The interrupt can be ither trigged by the EDGE or the LEVEL
	//In case of buttons, we want to trigger the interrupt when they are pressed
	//In this case, the read current is zero (0 is read), so FALLING EDGE is read
	//We want to trigger interrupts at FALLING EDGES
	
	//POLARITY CAN BE RAISING OR FALLING EDGE
	//HERE WE NEED FALLING EDGE

  LPC_SC->EXTMODE = 0x7; //set EXTMODE to BE EDGE SENSITIVE
	//I have to turn the bit number 0, 1, 2 to 1 so 000..00111 = 0x7
	
	
	//NVIC = NESTED VECTORED INTERRUPT CONTROLLER
	//SELECTIVE ENABLE OF EXTERNAL INTERRUPTS IN NVIC
	//Here we enable the 3 interrupts (EINT0, EINT1, EINT2) in NVIC!
  NVIC_EnableIRQ(EINT2_IRQn);              /* enable irq in nvic                 */
  //set priority
	NVIC_SetPriority(EINT2_IRQn, 1);
	NVIC_EnableIRQ(EINT1_IRQn);              /* enable irq in nvic                 */
  NVIC_SetPriority(EINT1_IRQn, 2);
	NVIC_EnableIRQ(EINT0_IRQn);              /* enable irq in nvic                 */
	NVIC_SetPriority(EINT0_IRQn, 3);
	
	/*
	PRIORITY OF INTERRUPTS
	The lower the number the higher the priority.
	If 2 interrupts have the same priority they're executed as they are triggered.
	If one interrupt handler is being executed BUT another interrupt with HIGHER PRIORITY (lower number) is raised
	then this second interrupt is served FIRST! And then the system excutes again the original interrupt handler related to te first interrupt with lower priority.
	*/
}
