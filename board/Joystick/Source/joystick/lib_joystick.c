/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           joystick.h
** Last modified Date:  2018-12-30
** Last Version:        V1.00
** Descriptions:        Atomic joystick init functions
** Correlated files:    lib_joystick.c, funct_joystick.c
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "LPC17xx.h"
#include "joystick.h"

/*----------------------------------------------------------------------------
  Function that initializes joysticks and switch them off
 *----------------------------------------------------------------------------*/

void joystick_init(void) {
	/* joystick up functionality */
	/*
	THIS IS JUST FOR JOYSTICK UP...FOR OTHER DIRECTIONS YOU NEED TO INITIALIZE THEM AS WELL
	UP FUNCTIONALITY: ON PIN 1.29
	PINSEL 3 HAS PINS FROM 31 TO 16 FOR I'LL HAVE TO USE IT FOR ACCESSING THE JOYSTICK UP PIN 1.29
	TO SET GPIO FUNCTIONALITY OF PIN 19 I HAVE TO SET BIT 26 AND 27 TO ZERO
	SO I DO THE END WITH TEH NEGATION OF 3 = 2_110, SHIFT TO 26 POSITIONS TO SET JUST PIN 26, 37 TO 1
	THEN IN THE SECOND LINE I DO THE AND WITH 1 NEGATED TO BIT 29
	*/
  LPC_PINCON->PINSEL3 &= ~(3<<26);	//PIN mode GPIO (00b value per P1.29)
	LPC_GPIO1->FIODIR   &= ~(1<<29);	//P1.25 Input (joysticks on PORT1 defined as Input) 
}
