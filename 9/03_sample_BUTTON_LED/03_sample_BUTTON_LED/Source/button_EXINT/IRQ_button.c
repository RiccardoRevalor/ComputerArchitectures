#include "button.h"
#include "lpc17xx.h"
#include "../led/led.h"

extern unsigned char next_state(unsigned char currentState, unsigned char taps, int *output_bit); //parameters are currentState, position of taps, addres of outputBits that passed by rerefence

void EINT1_IRQHandler (void)	  
{
	extern unsigned char currentState;
	extern unsigned char taps;
	int output_bit;
	volatile unsigned char nextState;
	
	//calculate nextState
  nextState = next_state(currentState, taps, &output_bit); 
	
	
	//switch on/off the leds
	LED_Out(nextState);
	
	
	currentState = nextState;
	
	
	//clear interrupt
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
}

