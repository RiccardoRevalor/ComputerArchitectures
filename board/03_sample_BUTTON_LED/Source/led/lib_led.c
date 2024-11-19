/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           timer.h
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        Atomic led init functions
** Correlated files:    lib_timer.c, funct_timer.c, IRQ_timer.c
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "lpc17xx.h"
#include "led.h"

/*----------------------------------------------------------------------------
  Function that initializes LEDs and switch them off
 *----------------------------------------------------------------------------*/

unsigned char led_value;

void LED_init(void) {

  LPC_PINCON->PINSEL4 &= 0xFFFF0000;	//PIN mode GPIO (00b value per P2.0 to P2.7)
	//&= PINSEL4 AND mask
	//WE set 16 bits on PINSEL4 in order to use pin 2.0 uo to 2.7 (see manual page 110)
	
	//I want LPC_GPIO2 
	//in LPC17xx.h we see LPC_GPIO_BASE, so I add this to an ogffset to have GPIO2. It's all already done in the header
	
	//SEE PAGE 123 OF MANUAL TO SET FIODIR
	LPC_GPIO2->FIODIR   |= 0x000000FF;  //P2.0...P2.7 Output (LEDs on PORT2 defined as Output)
	//|= IS AN OR
	//I just want to set the bits I am interested in and force them to 1
	//I set the last 8 lsb to 1
	
  /* LPC_GPIO2->FIOSET    = 0x000000FF;	//all LEDs on */
	LPC_GPIO2->FIOCLR    = 0x000000FF;  //all LEDs off
	
	led_value = 0;
}

void LED_deinit(void) {

  LPC_GPIO2->FIODIR &= 0xFFFFFF00;  //P2.0...P2.7 Output LEDs on PORT2 defined as Output
}
