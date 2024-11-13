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


                AREA    |.text|, CODE, READONLY


; Reset Handler


Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
					
				;raise usage faullt
				ldr r1, =0xE000ED24 ;SystemHandlerControlStateReg
				ldr r2, [r1]
				;BIT 18: ENABLED USAGE FAULT
				;orr r2, r2, #0x40000	; usage fault enabled
				;BIT 17
				;orr r2, r2, #0x20000	; bus fault enabled
				;BIT 16
				;orr r2, r2, #0x10000 	; mem  management fault enabled
				
				; or I can usa just one instruction with 1 mask for all of the three faults
				orr r2, r2, #0x70000	; enable usage fault, bus fault, mem management fault all together
				
				
				
				;check they are enabled at: pheripherals -> core -> nested vector icnterrupt controller
				str r2, [r1]
				
				;USAGE FAULT EXAMPLES
				
				;1) coprocessor instruction USAGE FAULT
				; UNCOMMENT THE INSTRUCTION TO ACTIVATE IT
				;ldc p1, c0, [r1]
				;assembler don't recognize error when compiling this instru
				;AT RUNTIME HOWEVER THE ASSEMBLER CANNOT EXECUTE IT BECAUSE COPROCESSO P1 IS MISSING!!! ---> USAGE FAULT GENERATED AGAIN
				
				
				;3) UNDEFINED INSTRUCTION USAFE FAULT
				; Arm cortex m3 doesn0t have a FP unit in the ALU
				; SO FLOAT ISTRUCTION WILL GENERATE  a USAGE FAULT
				; idea: proceed as before: in the usage fault handler 
				dcd 0xe7f0def0
				; I am expecting the usage fault BUT THE EMULATOR SKIPS THE INSTRUCTION WITHOUT GENERATING IT
				; THIS IS A BEHAVIOR DIFFERENT FROM THE EXPECTED ONE
				; BUT IF YOU UPLOAD THIS CODE TO THE BOARD THE USAGE FAULT WILL BE RAISED BY THE BOARD!!!!!!
				; ALWAYS TEST ALSO ON THE BOARD!!!!
				; THE BOARD RAISES AN USAGE FAULT !!!!
				; in the real board registers are not initialized to zero when you upload the code
				
				
				
				;4) DIVISION BY ZERO USAGE FAULT
				;mov r8, #16 ;dummy initialization of r8
				;mov r6, #1
				;mov r7, #0
				;udiv r8, r6, r7 ; this saves zero in r8
				; result is undefined so storing zero is not right
				; but this doesn't raise usage fault either
				
				;IN ORDER TO DETECT IT:
				; we have to manually enabled the div by zero exception
				; we need to set the config control register
				; config control reg: 0xE000ED14
				;first I enable faults due to div by zero
				; .load config control reg
				ldr r5, =0xE000ED14
				ldr r8, [r5]
				; set the bit number 4 of config control reg TO 1
				orr r8, r8, #0x10
				;store new new val in r5
				str r8, [r5]
				;execute again the vid by zero:
				mov r6, #1
				mov r7, #0
				udiv r8, r6, r7
				
				
				
				
				;3) SWITCH TO ARM STATE -> USAGE FAULT INSTRUCTION
				;if I only write these 2 lines an hard fault is generated
				; If I write also the lines at the top I enable the usages fault
				adrl r0, label
				bx r0
				; after this we have T = 0 in xPSR so tye assembler is expecting an ARM instruction
				; this generates a hard fault
				; then it goaes into hard fault handler
				; CHECK FAULT REPORT in Peripherals > Core > Fault Report
label			mov r2, #1
                b .
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
				ldr r0, =0xE000ED2C ;read from hard fault status reg
				ldr r1, [r0]
				; check if 2 bit (bit number 30) starting from the left is set to 1
				tst r1, #0x40000000
				
				;if the result of the test is zero, it means bit 30 is zero
				;if the result of the test is not zero, it means bit 30 is 1
				
				;if zero flag = 1 I wanna jump to the label
				bne Usage_Fault_not_enabled
				
                B       .
				
Usage_Fault_not_enabled	mov r2, #2
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler         [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler          [WEAK]
		
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler        [WEAK]
				
				;r0, r1 don't need to be put in stack as they are scratch registers. If I used other registers like r5,r6 ecc 
				;I'd have to stack them!!
				; I need to distinguish amomng all the different kinds of usage fault
				; read usage fault register
				
				;load usage fault status reg in r0
				ldr r0, =0xE000ED2A
				; the size of the register is an half word!
				ldrh r1,[r0]
				
				;test the MSB (BIT 1)
				;If the result is zero -> bit 1 was 1 -> i am using a bne
				; if not zero -> ot means bit 1 was zero
				
				;bit 1 == 0 means Branch target address to PC with LSB equals 0 (slide 26 pacchetto 10)
				tst r1, #0x2
				
				bne LSB_OF_PC_is_zero
				
				;otherwise: read the other bits..
				
				;TEST FOR THE USAGE FAULT GENERATED BY INVOCATIMNG COPROCESSOR P1 THAT DOESN'T EXIST.
				tst r1, #0x08
				bne coprocessor_instruction
				
				;TEST THE USAGE FAULT GENERATED BY UNDEFINED INSTRUCTION 
				;BEWARE: THIS DOEN'T WORK WITH THE EMULATOR AS IT DOESN'T RAISE THE EXCEPTION BUT IT SHOULD BE RAISED
				tst r1, #0x00000001
				bne undefined_intruction ; not implemeneted
				
				
				;TEST THE DIVISION BY ZERO USAGE FAULT
				; not implemented by prof
                B       .
				
			

undefined_intruction
						b . ; not implemented by prof
LSB_OF_PC_is_zero	
					;bx LR ;return to the offending code 
					;	IN THIS CASE LR CONTAINS A VALUE THAT'S NOT AN ADX BUT ONE OF THE VALUES OF EXC_RETURN!

					;i CAN HANDLE THIS USAGE FAULT BY CHANGING THE T BIT TO 1 IN xPSR
					;I need to use the stack. IN thread mode we can uses the main stack and the process stack, which one do I use?
					;we know it by looking at the link register, it tells me if the normal program was using the MSP or the PSP
					;I have to check the 2 bit of LR
					;TEST BIT 2 OF LR ;bit 2: 0100 comnta da dx a sx
					tst lr, #0x4
					ite eq
					;if equal to 1 I use the MSP
					mrseq r0, MSP
					;if equal to 0 I use PSP
					mrsne r0, PSP
					;I use it toi retrieve the content of xPSR
					;xPSR is stack pointer + 28 in the stack
					ldr r1, [r0, #28] ; now r1 is equal to xPSR
					;NOW: look at the thumb (T) bit
					;T bit is in position 24 in the xPSR
					orr r1, r1, #0x1000000
					str r1, [r0, #28]
					;Now the I can do the bx af before
					bx lr 
					;after this; I return to reset_handler and I reach the end of the subroutine by staying the b . loop
					;the important thing to note is that I DON'T GENERATE A USAGE FAULT ANYMORE!!!!!! 

coprocessor_instruction
					; HANDLE THE EXECRPTION GENERATED BY THE COPROCESSOR INSTRUCTION
					; idea : recognize the instruction and then use a solution to simulate the register that doesn't exist
					; I could use a register to simulate register c0
					; so the idea is similar to the LSB_OF_PC_is_zero
					; but here i wanna retrieve the PC 
					; I can retrieve the value of the line that raised the exception
					; with that value I can access the memory, read that 4 bits and decode them in order to understand the kind of instruction and re-implement it
					; It's a complex example because I have to do many things 
					; so the code will be written for a different exception, but you have to understand the idea
					
					;idea summarized
					
					
					;1) retrieve what stack was used
					mrseq r0, MSP
					;if equal to 0 I use PSP
					mrsne r0, PSP
					;I use it toi retrieve the content of xPSR
					;xPSR is stack pointer + 28 in the stack
					
					;2) retrieve PC from stack
					ldr r1, [r0, #24] ; now r1 is equal to PC 
					; decrease the PC first because it stores the adx of the instruction AFTER the coprocessor instruction but I Wanna retrieve the corpocessor instruction
					ldr r2, [r1, #-4] ; r2 is the operating code of the coprocessor instruction
					
					;3) do something to emulate the coprocessor instruction
					bx lr
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