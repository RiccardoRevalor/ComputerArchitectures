				
				
				AREA asm_functions, CODE, READONLY				
                EXPORT  checkCoordinates
				EXPORT my_division
				IMPORT __aeabi_fdiv ;Import the function to perform fp division
				; __aeabi_fdiv accepts float a, float b as paremeters (already declared float in C) and returns a/b
					
					
checkCoordinates	FUNCTION
					;R0 = x
					;r0, r1, r2 -> scratch registers, don't have to save them in the stack
					;R1 = y
					;R2 = RADIUS
					;save the LR in the stack 
					push {lr}
					
					;I cannot use the LSL because x, y don't necessarily have to be power of 2
					mul r0, r0, r0	;x^2
					mul r1, r1, r1	;y^2
					mul	r2, r2, r2	;RADIUS ^2
					add r1, r0, r1	;x^2 + y^2
					
					;check whether x^2 + y^2 <= RADIUS ^2
					cmp r1, r2
					ite le 
					movle r0, #1
					movgt r0, #0
					
					pop {pc}
					
					ENDFUNC
	
	
my_division			FUNCTION
					;R0 = pointer to Area
					;R1 = pointer to RADIUS ^2
					
					;save registers into R4,R5,R6,R7,LR,PC into stack
					push {r4-r7, lr}
					push {r1-r3}
					
					;I have passed the POINTERS to Area and den
					;NOT THE VALUES THEMSELVES!
					;SO, I HAVE TO LOAD THE VALUES FROM THE POINTERS (POINTERS = ADX IN MEMORY)
					ldr r4, [r0]	;It's like doing; Area_val = *Area in C
					ldr r5, [r1]
					
					;Then , I have to pass them as parameters to __aeabi_fdiv
					mov r0, r4	;Pass the Area value IN R0
					mov r1, r5	;Pass the den value IN R1
					
					;call __aeabi_fdiv
					bl __aeabi_fdiv
					
					;result returned in r0
					
					
					pop{r1-r3}
					pop{r4-r7, pc}
	
					ENDFUNC
					
					END