			AREA myAsmFunctions, CODE, READONLY
			EXPORT call_svc
	
call_svc	PROC
			
			mov r0, sp ;copy the sp adx into r0 and pass it as argument to the svc Handler
			svc #0x15
			
			;AFTER THE SVC HAS BEEN CALLED AND FINISHED THE RESULT IS SAVED THE TOP OF THE PSP STACK
			;THE RESULT NEEDS TO BE RETURNED IN R0 PER AAPCS STANDARDS
			ldr r0, [sp, #-32]
			BX LR
			
			ENDP
			END
			