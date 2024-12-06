/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "LPC17xx.h"
#include "timer.h"
#include "../led/led.h"
#define N 8

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
extern unsigned char led_value;					/* defined in funct_led								*/
void TIMER0_IRQHandler (void)
	//AFTER EVERY 1 SEC WE GO INTO THE HANDLER FOR TIMER 0
{
	static uint8_t position = 7;
	static uint8_t sw_count = 0;
	sw_count++;	
	if(sw_count == 10){
		LED_Off(position);
		if(position == 7)
			position = 2;
		else
			position++;
		LED_On(position);
		sw_count = 0;
	}
	/* alternatively to LED_On and LED_off try to use LED_Out */
	//LED_Out((1<<position)|(led_value & 0x3));							
	/* LED_Out is CRITICAL due to the shared led_value variable */
	/* LED_Out MUST NOT BE INTERRUPTED */
	
	
	
	
	/*
	I take the Instr reg of timer 0 and make an OR with 1...why???
	The current value of associated Interrupt reg is 1..wjy 1? Because gthe interrupt reg (see slides) has its bit number 0 set to 1 when an interrupt related to MR0 is raised.
	Now, before exiting the interruot handler I don't wanna call it enymore to I have to write 1 to the corresponding Interruopt Reg to reset the Interrupt reg
	So, I do this OR that just changes the LSB and sets it to 1 to reset the LSB of IR.
	*/
  LPC_TIM0->IR |= 1;			/* clear interrupt flag */
  return; //I EXIT FROM THE TIMER HANDLER
}


/******************************************************************************
** Function name:		Timer3_IRQHandler
**
** Descriptions:		Timer/Counter 3 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
extern unsigned int currPos;
extern unsigned short var;					
extern unsigned short vett[N];
extern unsigned int concat_sum(unsigned short int VETT[], unsigned int dim, char* alarm); //FUNZIONE ASM

void cleanVett(unsigned short *v){
	int i;
	for (i = 0; i < N; i++){
		vett[i] = 0;
	}
}
void TIMER3_IRQHandler (void)
{
	
	volatile unsigned int result; //a 32 bit
	char alrm;
	if (currPos >= N){
		//vettore è saturo: chiama la funzione assembly e poi svuotalo
		
		
		//call ass
		result = concat_sum(vett, currPos, &alrm);
		
		cleanVett(vett);
		currPos = 0;
		
		if (alrm == 0){
			LED_On(0);
			LED_Off(1);
		} else {
			LED_On(1);
			LED_Off(0);
		}
		
	} else {
		//copia var nella prima posizione libnera di vett (currPos) e aumenta currPos
		vett[currPos] = var;
		++currPos;
		
		//chiamata ass
		result = concat_sum(vett, currPos, &alrm);
		
		if (alrm == 0){
			LED_On(0);
			LED_Off(1);
		} else {
			LED_On(1);
			LED_Off(0);
		}

		
	}
	
  LPC_TIM3->IR = 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
