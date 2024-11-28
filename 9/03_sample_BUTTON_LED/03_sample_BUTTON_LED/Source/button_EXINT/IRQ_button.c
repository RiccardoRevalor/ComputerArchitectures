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


void EINT2_IRQHandler (void)	{
	extern unsigned char currentState;
	extern unsigned char taps;
	int output_bit;
	volatile unsigned char nextState;
	unsigned int count = 0;
	extern unsigned char startState;
	
	//starting from an initial state, that is defined as the state of the leds before pressing button key2, I use a brute-force algorithm to count the iterations to go back into that state
	
	//set startState as the currentState, which is the state reached before executing the count 
	startState = currentState;
	
	do {
		//at each iteration I call the function to move to the next state
		nextState = next_state(currentState, taps, &output_bit);
		currentState = nextState;
		++count;
		
	} while(currentState!=startState);
	
	//at the end, display the count on the leds
	LED_Out(count);
	
	
	LPC_SC->EXTINT &= (1 << 2);     // clear pending interrupt
	
}
