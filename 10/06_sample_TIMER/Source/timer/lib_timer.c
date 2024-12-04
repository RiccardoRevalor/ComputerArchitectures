/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           lib_timer.h
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        atomic functions to be used by higher sw levels
** Correlated files:    lib_timer.c, funct_timer.c, IRQ_timer.c
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "LPC17xx.h"
#include "timer.h"

/******************************************************************************
** Function name:		enable_timer
**
** Descriptions:		Enable timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
**
******************************************************************************/
void enable_timer( uint8_t timer_num )
	
/*
We set 1 to the lowest bit of TCR (Timer Ctrl Reg) to enable counting 
Then the timer starts counting
*/
{
  if ( timer_num == 2 )
  {
	LPC_TIM2->TCR = 1;
  }
  else
  {
	LPC_TIM3->TCR = 1;
  }
  return; //NOW TCR IS 1 SO NOW TIMER COUNTER STARTS COUNTING
}

/******************************************************************************
** Function name:		disable_timer
**
** Descriptions:		Disable timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
**
******************************************************************************/
void disable_timer( uint8_t timer_num )
{
  if ( timer_num == 2 )
  {
	LPC_TIM2->TCR = 0;
  }
  else
  {
	LPC_TIM3->TCR = 0;
  }
  return;
}

/******************************************************************************
** Function name:		reset_timer
**
** Descriptions:		Reset timer
**
** parameters:			timer number: 0 or 1
** Returned value:		None
**
******************************************************************************/
void reset_timer( uint8_t timer_num )
{
  uint32_t regVal;

  if ( timer_num == 2 )
  {
	regVal = LPC_TIM2->TCR;
	regVal |= 0x02;
	LPC_TIM2->TCR = regVal;
  }
  else
  {
	regVal = LPC_TIM3->TCR;
	regVal |= 0x02;
	LPC_TIM3->TCR = regVal;
  }
  return;
}

uint32_t init_timer (uint8_t timer_num, uint32_t TimerInterval_MR0, uint32_t TimerInterval_MR1  ) {
	
	if (timer_num == 2) {
		/*FUNTION TO SET TIMER 2 SPECIFICALLY
		set MR0 t0 TimerInterval_MR0
		set MR1 to TimerInterval_MR1
		when timer reaches MR0 it has to continue counting after the interrupt, without resetting
		when timer reaches MR1 it ha to reset the counting to 0 after the interrupt and start again
		*/
		
		LPC_TIM2->MR0 = TimerInterval_MR0;
		LPC_TIM2->MR1 = TimerInterval_MR1;
		
		//configure bits on Match Control Register for Timer 2
		//interrupt on MR0 -> set bit 0 to 1
		//interrupt on MR1 -> set bit 3 to 1
		//reset timer after raising interrupt on MR1 -> set bit 4 to 1
		LPC_TIM2->MCR = (1 << 0) | (1 << 3) | (1 << 4);
		
		//enable interrupts for timer2 in NVIC
		NVIC_EnableIRQ(TIMER2_IRQn);
		NVIC_SetPriority(TIMER2_IRQn, 0); //max priority
		
		return 1;
	}
	
	if (timer_num == 3) {
		/*FUNTION TO SET TIMER 3 SPECIFICALLY
		set MR0 t0 TimerInterval_MR0
		set MR1 to TimerInterval_MR1
		when timer reaches MR0 it has to continue counting after the interrupt, without resetting
		when timer reaches MR1 it ha to reset the counting to 0 after the interrupt and start again
		*/
		
		LPC_TIM3->MR0 = TimerInterval_MR0;
		LPC_TIM3->MR1 = TimerInterval_MR1;
		
		//configure bits on Match Control Register for Timer 2
		//interrupt on MR0 -> set bit 0 to 1
		//interrupt on MR1 -> set bit 3 to 1
		//reset timer after raising interrupt on MR1 -> set bit 4 to 1
		LPC_TIM3->MCR = (1 << 0) | (1 << 3) | (1 << 4);
		
		//enable interrupts for timer2 in NVIC
		NVIC_EnableIRQ(TIMER3_IRQn);
		NVIC_SetPriority(TIMER3_IRQn, 0); //max priority
		
		return 1;
	}
	
	return 0;
}



uint32_t init_timer_old ( uint8_t timer_num, uint32_t TimerInterval )
{
	/* 
	for simplicity we just put the if statement to handle and init timer 0
	First I set Match Reg 0 with the value TimerInterval that is the CC
	So when the timer counter reaches TimerInterval something happens
	*/
  if ( timer_num == 0 )
  {
	LPC_TIM0->MR0 = TimerInterval;

// <<< Use Configuration Wizard in Context Menu >>>
// <h> timer0 MCR
//   <e.0> MR0I
//	 <i> 1 Interrupt on MR0: an interrupt is generated when MR0 matches the value in the TC. 0
//	 <i> 0 This interrupt is disabled
//   </e>
//   <e.1> MR0R
//	 <i> 1 Reset on MR0: the TC will be reset if MR0 matches it.
//	 <i> 0 Feature disabled.
//   </e>
//   <e.2> MR0S
//	 <i> 1 Stop on MR0: the TC and PC will be stopped and TCR[0] will be set to 0 if MR0 matches the TC
//	 <i> 0 Feature disabled.
//   </e>
//   <e.3> MR1I
//	 <i> 1 Interrupt on MR1: an interrupt is generated when MR0 matches the value in the TC. 0
//	 <i> 0 This interrupt is disabled
//   </e>
//   <e.4> MR1R
//	 <i> 1 Reset on MR1: the TC will be reset if MR0 matches it.
//	 <i> 0 Feature disabled.
//   </e>
//   <e.5> MR1S
//	 <i> 1 Stop on MR1: the TC and PC will be stopped and TCR[1] will be set to 0 if MR1 matches the TC
//	 <i> 0 Feature disabled.
//   </e>
//   <e.6> MR2I
//	 <i> 1 Interrupt on MR2: an interrupt is generated when MR2 matches the value in the TC.
//	 <i> 0 This interrupt is disabled
//   </e>
//   <e.7> MR2R
//	 <i> 1 Reset on MR2: the TC will be reset if MR2 matches it.
//	 <i> 0 Feature disabled.
//   </e>
//   <e.8> MR2S
//	 <i> 1 Stop on MR2: the TC and PC will be stopped and TCR[2] will be set to 0 if MR2 matches the TC
//	 <i> 0 Feature disabled.
//   </e>
//   <e.9> MR3I
//	 <i> 1 Interrupt on MR3: an interrupt is generated when MR3 matches the value in the TC.
//	 <i> 0 This interrupt is disabled
//   </e>
//   <e.10> MR3R
//	 <i> 1 Reset on MR3: the TC will be reset if MR3 matches it.
//	 <i> 0 Feature disabled.
//   </e>
//   <e.11> MR3S
//	 <i> 1 Stop on MR3: the TC and PC will be stopped and TCR[3] will be set to 0 if MR3 matches the TC
//	 <i> 0 Feature disabled.
//   </e>


	/*
	VALUE 3 TO MCR MEANS:
	e = 011 in binary
	bit 0 = 1 -> we generate an INTERRUPT on MR 0
	bit 1 = 1 -> we eant to reset the counter after the count has finished
	bit 2 = 0 -> we don't want to stop the counter after raising the interruopt so it starts counting AGAIN FROM 0
	!!!! This means we eill generate an interrupt EVERY SECOND because the counter always restarts after raising the interrupt !!!!
	
	*/
	
	/*
	FOR LAB10:
	just set bit 0 to 1, to generated interrupt
	*/
	LPC_TIM0->MCR = 3;  //We give a value to the MCR to decide the outcome after the TimerIntervak is reached by the counter
	
	
// </h>
// <<< end of configuration section >>>

	NVIC_EnableIRQ(TIMER0_IRQn);
	/*NVIC_SetPriority(TIMER0_IRQn, 4);*/		/* less priority than buttons */
	NVIC_SetPriority(TIMER0_IRQn, 0);		/* more priority than buttons */
	return (1);
  }
  else if ( timer_num == 1 )
  {
	LPC_TIM1->MR0 = TimerInterval;
	LPC_TIM1->MCR = 3;				

	NVIC_EnableIRQ(TIMER1_IRQn);
	NVIC_SetPriority(TIMER1_IRQn, 5);	/* less priority than buttons and timer0*/
	return (1);
  }
  return (0);
}

/******************************************************************************
**                            End Of File
******************************************************************************/
