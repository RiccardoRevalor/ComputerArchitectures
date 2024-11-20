			AREA myAsmFunctions, CODE, READONLY
	
call_svc	PROC
			
			EXPORT call_svc
			svc #0x15
			
			BX LR
			
			ENDP
			END
			