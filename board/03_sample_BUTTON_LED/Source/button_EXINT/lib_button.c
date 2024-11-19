
#include "button.h"
#include "lpc17xx.h"

/**
 * @brief  Function that initializes Buttons
 */
void BUTTON_init(void) {
	
	
	//SET p2.10

  LPC_PINCON->PINSEL4    |= (1 << 20);		 /* External interrupt 0 pin selection */
	//for p2.10 -> set bit 21 to 0 and bit 21 to 1 --> APLY A MASK WITH 1 SHIFTED LEFT 20 POSITION
	//then I have to set the verse (input, output)
	//button obviously are onyl for input
	//we set bits 10, to 0
	//<< shift lofic left
  LPC_GPIO2->FIODIR      &= ~(1 << 10);    /* PORT2.10 defined as input          */
	//~= negation
	//I set everything to 1 except for bit 10 that is set to 0
	
	
	
	
	//SET p2.11
	

  LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
	
	//set bit 11 to 0 and leave all the others to 1
  LPC_GPIO2->FIODIR      &= ~(1 << 11);    /* PORT2.11 defined as input          */
	
	
	
	
	//SET p.21
  
  LPC_PINCON->PINSEL4    |= (1 << 24);     /* External interrupt 0 pin selection */
	
	//set bit 12 to 0 and leave all the others to 1
  LPC_GPIO2->FIODIR      &= ~(1 << 12);    /* PORT2.12 defined as input          */
	
	
	

  LPC_SC->EXTMODE = 0x7;

  NVIC_EnableIRQ(EINT2_IRQn);              /* enable irq in nvic                 */
  NVIC_EnableIRQ(EINT1_IRQn);              /* enable irq in nvic                 */
  NVIC_EnableIRQ(EINT0_IRQn);              /* enable irq in nvic                 */
}
