	AREA custom_functions_area, CODE, READONLY
	EXPORT next_state
		
next_state
		STMFD SP!, {R4-R11, LR}
		; r0 contains CurrState, r1 contains taps
		AND r4, r0, r1 ; r4 contains values of bits relevant for taps
		MOV r5, #0 ; nextState
		MOV r6, #8 ; loop index
		
loop	TST R4, #1 
		BNE not_eq
		EOR r5, r5, #0
		B end_l
not_eq  EOR r5, r5, #1
		
end_l   LSR r4, #1
	
		SUBS r6, r6, #1
		BNE loop
	
		MOV r7, r0 ; copy r0 to r7
		AND r7, #1 
		; return nextState
		MOV r0, r0, LSR #1
		LSL r5, #7
		ORR r0, r0, r5
		STR r7, [r3] ; store output bit
		
		LDMFD SP!, {R4-R11, LR}
		BX LR
	
	END