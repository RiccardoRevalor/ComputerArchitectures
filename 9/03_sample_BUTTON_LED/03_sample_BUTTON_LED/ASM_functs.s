				
				
				AREA asm_functions, CODE, READONLY				
                EXPORT  next_state
next_state 
				;In C I have: extern unsigned char next_state(unsigned char currentState, unsigned char taps, int *output_bit); //parameters are currentState, position of taps, addres of outputBits that passed by rerefence
				stmfd sp!, {r4-r11, lr}
				
				;R0 = currentState
				;R1 = taps
				;R2 = pointer (adx) to output variable
				
				
				;Calculate uotput bit
				and r4, r0, #1
				str r4, [r2]	;save outputbit to the pointer
				
				;result:
				mov r5, 0
				
				mov r6, r0	;currentState
				mov r7, r1	;taps
				
				mov r8, #0	;8 bits so 8 iterations of the loop
				;r8 also stores the index number of the extracted bit.
				;if the extracted bit is a tap bit, you have to shift according to this index number !
				
				mov r9, #0	;r9 stores the INPUT BIT
				
				
				
loop			;test the bit in position i of taps ans see if it's either 1 or 0
				mov r11, #1
				lsl r11, r11, r8
				tst r7, r11
				;tst sets the Z flag. If the flag == 1 the i bit is 1
				beq not_tap
				;andne r9, r6, #1 ;CURRENT STATE AND 1
				;is tap
				;shift accorfing to its index number
				lsr r10, r6, r8	;perform shift logic right with respect to the index of the tap bit
				;then EXOR with currentState
				and r10, r10, #1 ; take the first bit of the shifted vector
				;perform the exor with the accumuled result
				eor r9, r9, r10		
				
not_tap
				;go to the folllwing bit
				add r8, r8, #1
				;shift right the taps by 1 bit to analyze the next bit
				;lsr r7, r7, #1
				
				;if r8 == 8 then I finished all the bits and I can exit from the loop
				cmp r8, #8
				blt loop
				
				;last part: 
				;now I have to extract the input bit from r9
				and r9, r9, #1
				
				;Now I have the input but
				;I just have to compute: new_state = (current_state>> 1) | (input_bit << 7);
				;shift the ORIGINAL currentState
				lsr r6, r6, #1
				;shift the new input bit and put it at the beginning of the new currentState to calculate the nextState
				lsl r9, r9, #7
				
				;perform the OR to put it at the beginning of the state
				orr r0, r6, r9
				
				
				;perform the pop on the stack
				ldmfd sp!, {r4-r11, pc}
				
				
				
				
				
				END 