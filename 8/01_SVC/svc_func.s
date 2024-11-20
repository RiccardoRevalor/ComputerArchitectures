			AREA myAsmFunctions, CODE, READONLY
	
call_svc	PROC
			
			EXPORT call_svc
			svc #10
			
			ENDP
			END
			