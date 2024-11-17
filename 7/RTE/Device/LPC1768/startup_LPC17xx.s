;/**************************************************************************//**
; * @file     startup_LPC17xx.s
; * @brief    CMSIS Cortex-M3 Core Device Startup File for
; *           NXP LPC17xx Device Series
; * @version  V1.10
; * @date     06. April 2011
; *
; * @note
; * Copyright (C) 2009-2011 ARM Limited. All rights reserved.
; *
; * @par
; * ARM Limited (ARM) is supplying this software for use with Cortex-M
; * processor based microcontrollers.  This file can be freely distributed
; * within development tools that are supporting such ARM based processors.
; *
; * @par
; * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
; * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
; * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
; * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
; *
; ******************************************************************************/

; *------- <<< Use Configuration Wizard in Context Menu >>> ------------------

; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000200

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000000

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors

__Vectors       DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     MemManage_Handler         ; MPU Fault Handler
                DCD     BusFault_Handler          ; Bus Fault Handler
                DCD     UsageFault_Handler        ; Usage Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     DebugMon_Handler          ; Debug Monitor Handler
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; External Interrupts
                DCD     WDT_IRQHandler            ; 16: Watchdog Timer
                DCD     TIMER0_IRQHandler         ; 17: Timer0
                DCD     TIMER1_IRQHandler         ; 18: Timer1
                DCD     TIMER2_IRQHandler         ; 19: Timer2
                DCD     TIMER3_IRQHandler         ; 20: Timer3
                DCD     UART0_IRQHandler          ; 21: UART0
                DCD     UART1_IRQHandler          ; 22: UART1
                DCD     UART2_IRQHandler          ; 23: UART2
                DCD     UART3_IRQHandler          ; 24: UART3
                DCD     PWM1_IRQHandler           ; 25: PWM1
                DCD     I2C0_IRQHandler           ; 26: I2C0
                DCD     I2C1_IRQHandler           ; 27: I2C1
                DCD     I2C2_IRQHandler           ; 28: I2C2
                DCD     SPI_IRQHandler            ; 29: SPI
                DCD     SSP0_IRQHandler           ; 30: SSP0
                DCD     SSP1_IRQHandler           ; 31: SSP1
                DCD     PLL0_IRQHandler           ; 32: PLL0 Lock (Main PLL)
                DCD     RTC_IRQHandler            ; 33: Real Time Clock
                DCD     EINT0_IRQHandler          ; 34: External Interrupt 0
                DCD     EINT1_IRQHandler          ; 35: External Interrupt 1
                DCD     EINT2_IRQHandler          ; 36: External Interrupt 2
                DCD     EINT3_IRQHandler          ; 37: External Interrupt 3
                DCD     ADC_IRQHandler            ; 38: A/D Converter
                DCD     BOD_IRQHandler            ; 39: Brown-Out Detect
                DCD     USB_IRQHandler            ; 40: USB
                DCD     CAN_IRQHandler            ; 41: CAN
                DCD     DMA_IRQHandler            ; 42: General Purpose DMA
                DCD     I2S_IRQHandler            ; 43: I2S
                DCD     ENET_IRQHandler           ; 44: Ethernet
                DCD     RIT_IRQHandler            ; 45: Repetitive Interrupt Timer
                DCD     MCPWM_IRQHandler          ; 46: Motor Control PWM
                DCD     QEI_IRQHandler            ; 47: Quadrature Encoder Interface
                DCD     PLL1_IRQHandler           ; 48: PLL1 Lock (USB PLL)
                DCD     USBActivity_IRQHandler    ; 49: USB Activity interrupt to wakeup
                DCD     CANActivity_IRQHandler    ; 50: CAN Activity interrupt to wakeup


                IF      :LNOT::DEF:NO_CRP
                AREA    |.ARM.__at_0x02FC|, CODE, READONLY
CRP_Key         DCD     0xFFFFFFFF
                ENDIF

	
	
				AREA    MyData, DATA, READWRITE
					ALIGN 2
Best_times2 		DCD     0x06, 1300, 0x03, 1700, 0x02, 1200, 0x04, 1900
					DCD     0x05, 1110, 0x01, 1670, 0x07, 1000
	
Failed_runs2       	DCD     0x02, 50, 0x05, 30, 0x06, 100, 0x01, 58
					DCD     0x03, 40, 0x04, 90, 0x07, 25

Best_times_ordered 	DCD     0, 0, 0, 0, 0, 0, 0
Failed_runs_ordered DCD    0, 0, 0, 0, 0, 0, 0

temp_buffer       	DCD     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

					ALIGN 2
					
					
				AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
					
				;use this to jmp to task 2 without exeuting the fist one
				;ldr r9, =prova
				b task_2
				
				ldr r0, =Best_times					;pointer to the Best_times table
				;PRIMA ldr r1, =Failed_runs				;pointer to the Failed_runs table
				mov r2, #1300 		
				;clear r11 and r10
				mov r11, #0
				mov r10, #0
				add r4, r0, #56						;end adx of Best_times table (14 elements * 4 bytes each)
				;PRIMA add r5, r1, #56						;end adx of Failed_runs table

loop
				;load values
				ldr r6, [r0], #4					;load day and increment pointer value
				ldr r7, [r0], #4					;load score for that day and increment pointer value
				
				cmp r7, r2
				blt continue_loop
				
				;search fo failed runs associated to day in register r6
				add r11, r11, #1					; + 1 day with score >= 1300
				;mov r3, #0							; counter for failed runs
				;DOPO
				ldr r1, =Failed_runs				;pointer to the Failed_runs table
				add r5, r1, #56						;end adx of Failed_runs table
				
search_failed_runs
				ldr r12, [r1], #4					;load day
				ldr r7, [r1], #4					;load failed runs for that day
				cmp r6, r12							;test if the 2 days are the same day
				beq add_failed_run
				; check end of failed runs table
				cmp r1, r5
				bne search_failed_runs
				b continue_loop
				
				
add_failed_run
				addeq r10, r10, r7
continue_loop   

				;check end of outer loop
				cmp r0, r5
				bne loop
				
				
				
				
				
				
task_2				
				;TASK 2
				ldr r0, =Best_times         ; R0 -> Base di Best_times
				ldr r1, =Failed_runs        ; R1 -> Base di Failed_runs
				ldr r2, =Best_times_ordered ; R2 -> Output ordinato Best_times_ordered
				ldr r3, =Failed_runs_ordered ; R3 -> Output ordinato Failed_runs_ordered
				mov r4, #7					;N days
				
				;sort best times
				bl sort_best_times
				
				;determine theb worst best time day
				bl worst_best_time
				
				
				;sort failed runs
				bl sort_failed_runs
				
				
				b .

;SUBS TO SORT AND STORE BES TIMES		
sort_best_times	push {r4, lr}
				
				;Store all the value from the read-only vector to the writable buffer
				ldr r5, =temp_buffer
store_in_buffer_1
				ldr r6, [r0], #4		;load day
				str r6, [r5], #4			;store day in buffer
				ldr r6, [r0], #4		;load score
				str r6, [r5], #4		; store score in buffer
				subs r4, r4, #1
				bne store_in_buffer_1
				
				;call the bubble sort algorithm
				mov r4, #6
				ldr r5, =temp_buffer
				bl bubble_sort
				mov r4, #7
				
				
				;after the descending sort, save all the days in the final destination which is the Best_times_ordered
store_best_times
				;goes through the buffer by 8 in 8 to avoid saving also the score
				ldr r6, [r5], #8
				str r6, [r2], #4	;in the Best_times_ordered you just save the days so you jump 4 by 4
				subs r4, r4, #1
				bne store_best_times
				
				;end of function
				pop {r4, pc}
				
				
				
;SUBS TO SORT AND STORE FAILED_RUNS				
				
sort_failed_runs
				push {r4, lr}
				ldr r5, =temp_buffer
				
store_in_buffer_2
				ldr r6, [r1], #4		;load day
				str r6, [r5], #4		;store day in buffer
				ldr r6, [r1], #4		;load score
				str r6, [r5], #4		; store score in buffer
				subs r4, r4, #1
				bne store_in_buffer_2
				
				;call the bubble sort algorithm
				mov r4, #6
				ldr r5, =temp_buffer
				bl bubble_sort
				mov r4, #7
				
store_failed_runs
				;goes through the buffer by 8 in 8 to avoid saving also the score
				ldr r6, [r5], #8
				str r6, [r3], #4	;in the Best_times_ordered you just save the days so you jump 4 by 4
				subs r4, r4, #1
				bne store_failed_runs
				
				;end of function
				pop {r4, pc}



				


;BUBBLE SORT ALGORITHM
				
				
bubble_sort
				push {r4, r5, lr}
				;sort on the temp buffer
				;ldr r5, =temp_buffer
				;add r5, r5, #4
sort_outer		
				ldr r5, =temp_buffer
				add r5, r5, #4
				mov r8, #0			;0 = no swaps, 1 = a swap happened
				mov r9,  r4			;num of items (7 at the beginning)
sort_inner
				ldr r6, [r5, #0]	;first score
				ldr r7, [r5, #8]	;second score
				cmp r6, r7
				bhs no_swap			;no swap if r6 >= r7...otherwise swap
				
				;do the swap of the scores and the days
				;swap scores first
				str r6, [r5, #8]	;first scores goes in the place of second score
				str r7, [r5, #0]	;and viceversa
				
				;load days
				ldr r6, [r5, #-4]	;first day
				ldr r7, [r5, #4]	;second day
				;swap first day with second day
				str r6, [r5, #4]
				str r7, [r5, #-4]
				
				;set the change boolean value to true (1)
				mov r8, #1			;THERE WAS A SWAP

no_swap
				;increment r5 by 8 to analyze the second pair
				add r5, r5, #8
				;decrement the element counter
				subs r9, r9, #1
				bne sort_inner		;if i > 0 continue inner loop
				
				;check if there has been a swap
				cmp r8, #1
				beq sort_outer		;if swap == True continue outer loop
				
				pop {r4, r5, pc}
				
				
worst_best_time
				push {lr}
				;worst best time day is located at the last index of the Best_times_ordered
				ldr r5, =Best_times_ordered
				ldr r11, [r5, #24] ;worst day				
				pop{pc}
				
				
				
				
				
				
				
				
				
				b .
				ltorg
                ENDP
					
				; Data section with alignment and boundary
				ALIGN 2
				SPACE 4096

Days			DCB     0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07

Best_times		DCD     0x06, 1300, 0x03, 1700, 0x02, 1200, 0x04, 1900
				DCD     0x05, 1110, 0x01, 1670, 0x07, 1000

Failed_runs		DCD     0x02, 50, 0x05, 30, 0x06, 100, 0x01, 58
				DCD     0x03, 40, 0x04, 90, 0x07, 25

Num_days		DCB     7

				SPACE 4096
				ALIGN 2


; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler         [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler          [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler        [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler          [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  WDT_IRQHandler            [WEAK]
                EXPORT  TIMER0_IRQHandler         [WEAK]
                EXPORT  TIMER1_IRQHandler         [WEAK]
                EXPORT  TIMER2_IRQHandler         [WEAK]
                EXPORT  TIMER3_IRQHandler         [WEAK]
                EXPORT  UART0_IRQHandler          [WEAK]
                EXPORT  UART1_IRQHandler          [WEAK]
                EXPORT  UART2_IRQHandler          [WEAK]
                EXPORT  UART3_IRQHandler          [WEAK]
                EXPORT  PWM1_IRQHandler           [WEAK]
                EXPORT  I2C0_IRQHandler           [WEAK]
                EXPORT  I2C1_IRQHandler           [WEAK]
                EXPORT  I2C2_IRQHandler           [WEAK]
                EXPORT  SPI_IRQHandler            [WEAK]
                EXPORT  SSP0_IRQHandler           [WEAK]
                EXPORT  SSP1_IRQHandler           [WEAK]
                EXPORT  PLL0_IRQHandler           [WEAK]
                EXPORT  RTC_IRQHandler            [WEAK]
                EXPORT  EINT0_IRQHandler          [WEAK]
                EXPORT  EINT1_IRQHandler          [WEAK]
                EXPORT  EINT2_IRQHandler          [WEAK]
                EXPORT  EINT3_IRQHandler          [WEAK]
                EXPORT  ADC_IRQHandler            [WEAK]
                EXPORT  BOD_IRQHandler            [WEAK]
                EXPORT  USB_IRQHandler            [WEAK]
                EXPORT  CAN_IRQHandler            [WEAK]
                EXPORT  DMA_IRQHandler            [WEAK]
                EXPORT  I2S_IRQHandler            [WEAK]
                EXPORT  ENET_IRQHandler           [WEAK]
                EXPORT  RIT_IRQHandler            [WEAK]
                EXPORT  MCPWM_IRQHandler          [WEAK]
                EXPORT  QEI_IRQHandler            [WEAK]
                EXPORT  PLL1_IRQHandler           [WEAK]
                EXPORT  USBActivity_IRQHandler    [WEAK]
                EXPORT  CANActivity_IRQHandler    [WEAK]

WDT_IRQHandler
TIMER0_IRQHandler
TIMER1_IRQHandler
TIMER2_IRQHandler
TIMER3_IRQHandler
UART0_IRQHandler
UART1_IRQHandler
UART2_IRQHandler
UART3_IRQHandler
PWM1_IRQHandler
I2C0_IRQHandler
I2C1_IRQHandler
I2C2_IRQHandler
SPI_IRQHandler
SSP0_IRQHandler
SSP1_IRQHandler
PLL0_IRQHandler
RTC_IRQHandler
EINT0_IRQHandler
EINT1_IRQHandler
EINT2_IRQHandler
EINT3_IRQHandler
ADC_IRQHandler
BOD_IRQHandler
USB_IRQHandler
CAN_IRQHandler
DMA_IRQHandler
I2S_IRQHandler
ENET_IRQHandler
RIT_IRQHandler
MCPWM_IRQHandler
QEI_IRQHandler
PLL1_IRQHandler
USBActivity_IRQHandler
CANActivity_IRQHandler

                B       .

                ENDP


                ALIGN


; User Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap
__user_initial_stackheap

                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR

                ALIGN

                ENDIF


                END
