#include "button.h"
#include "lpc17xx.h"

#include "../led/led.h"

/*When we push a button, the system is stopped
The functionality that was executed  (while(1) in the C file after having finished the initialization of buttons)
is stopped
We retrieve the adx of the handler in the IVT
These handlers are like assembly handlers (like SVC Hnalder for ex)
But they are written in C
However, in the assembly startup they are referenced:
At line 91 ate the Vector table
								DCD     EINT0_IRQHandler          ; 34: External Interrupt 0
                DCD     EINT1_IRQHandler          ; 35: External Interrupt 1
                DCD     EINT2_IRQHandler          ; 36: External Interrupt 2
                DCD     EINT3_IRQHandler          ; 37: External Interrupt 3
								
At line 193 they are exported to be visible to the whole project: 
EXPORT  EINT0_IRQHandler          [WEAK]
EXPORT  EINT1_IRQHandler          [WEAK]
EXPORT  EINT2_IRQHandler          [WEAK]
EXPORT  EINT3_IRQHandler          [WEAK]

at line 232 they are declared:
EINT0_IRQHandler          
EINT1_IRQHandler          
EINT2_IRQHandler          
EINT3_IRQHandler  

They are decalred and exported. Then we can implements them in C!


*/


//NEXT STATE FUNCTION IS DONE IN ASSEMBLY
 extern unsigned char next_state(unsigned char current_state, unsigned char taps, int *output_bit);
 
 
void EINT1_IRQHandler (void)	  
{
  LED_On(1);
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
}


