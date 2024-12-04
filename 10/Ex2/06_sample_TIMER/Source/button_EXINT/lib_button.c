
#include "button.h"
#include "LPC17xx.h"

/**
 * @brief  Function that initializes Buttons
 */
void BUTTON_init(void) {
	
	
	//key1 btn: pin 2.11

  LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
  LPC_GPIO2->FIODIR      &= ~(1 << 11);    /* PORT2.11 defined as input          */

  LPC_SC->EXTMODE = 0x7;
	
  NVIC_EnableIRQ(EINT1_IRQn);              /* enable irq in nvic                 */
	NVIC_SetPriority(EINT1_IRQn, 0);				 
}
