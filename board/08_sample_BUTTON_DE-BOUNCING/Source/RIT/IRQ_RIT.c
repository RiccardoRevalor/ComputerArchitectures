/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "LPC17xx.h"
#include "RIT.h"
#include "../led/led.h"
#include <stdio.h>
#include <stdbool.h>

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/


extern unsigned int circBuffer[7000];
void swap(unsigned int* xp, unsigned int* yp){
    unsigned int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// Implement Bubble Sort
void bubbleSort(unsigned int *arr, int n){
    int i, j;
    bool swapped;
    for (i = 0; i < n - 1; i++) {
        swapped = false;
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(&arr[j], &arr[j + 1]);
                swapped = true;
            }
        }

        // If no two elements were swapped by inner loop,
        // then break
        if (swapped == false)
            break;
    }
		
		return;
}

float calculateAvg(unsigned int *arr, int n){
	unsigned int i;
	unsigned int sum = 0;
	for (i = 0; i < n; i++){
		sum = sum + arr[i];
	}
	
	return (float) sum / (float)n;
}


void clean(unsigned int *arr, int n) {
	
	unsigned int i;
	for (i = 0; i < n; i++){
		arr[i] = 0xCAFECAFE;
	}
	
	return;
}
void RIT_IRQHandler (void)
{			
	static int down=0;	
	down++;
	if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){
		reset_RIT();
		switch(down){
			case 1:
				break;
			default:
				break;
		}
	}
	else {	/* button released */
		down=0;			
		int N = 7000;
		volatile float avg;
		bubbleSort(circBuffer,N);
		avg = calculateAvg(circBuffer,N);
		clean(circBuffer,N);
		disable_RIT();
		reset_RIT();
		NVIC_EnableIRQ(EINT1_IRQn);							 /* disable Button interrupts			*/
		LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
	}
		
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
