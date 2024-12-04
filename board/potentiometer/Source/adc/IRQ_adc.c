/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_adc.c
** Last modified Date:  20184-12-30
** Last Version:        V1.00
** Descriptions:        functions to manage A/D interrupts
** Correlated files:    adc.h
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "LPC17xx.h"
#include "adc.h"
#include "../led/led.h"

/*----------------------------------------------------------------------------
  A/D IRQ: Executed when A/D Conversion is ready (signal from ADC peripheral)
 *----------------------------------------------------------------------------*/

unsigned short AD_current;   
unsigned short AD_last = 0xFF;     /* Last converted value               */

void ADC_IRQHandler(void) {
	
	/*
	BITS 15 TO 4 STORE TEH RESULT
	FIRST I SHIFT BY 5 TO TEH LEFT AND THEN I DO THE AND
	I AM ONLY INTERESTED IN THE BITS OF RESULT, THAT'S WHY I PERFORM ALSO THE AND TO SET TO ZERO ALL THE OTHER BITS
	*/
	
	/*
	min value of potentiom,eter: i wanna to switch OFF the rightmost led
	max value: switch on the leftmost led
	scaling is applied
	So when I have maximum I have 1, when I haVE MIN on potentiometer I have 0
	And I multiply by 7 because leds are from 0 to 1
	So when I have the max value on potentiomegter I have MAX * 7 / 0xFFF = led 7
	*/
  	
  AD_current = ((LPC_ADC->ADGDR>>4) & 0xFFF);/* Read Conversion Result             */
  if(AD_current != AD_last){
		LED_Off(AD_last*7/0xFFF);	  // ad_last : AD_max = x : 7 		LED_Off((AD_last*7/0xFFF));	
		LED_On(AD_current*7/0xFFF);	// ad_current : AD_max = x : 7 		LED_On((AD_current*7/0xFFF));	
		
		AD_last = AD_current;
  }	
}
