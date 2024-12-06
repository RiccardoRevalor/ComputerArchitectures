		AREA MyCode, CODE, READONLY
		EXPORT concat_sum
		
		;unsigned int concat_sum(unsigned short int VETT[], unsigned int dim, char* alarm);
concat_sum	PROC
		; R0 -> VETT[]
		; R1 -> N
		; R2 -> ADX TO ALARM VARIABLE (FOR OVERFLOW)
		
		push {r4-r7, lr}
		
		mov r3, #0	;somma totale su 32 bit 
		mov r4, #0	;flag di overflow
		
		mov r5, #0	;contatore elementi del vettore
		
loop
		cmp r5, r1
		beq endLoop
		
		;carica primo short
		ldrh r6, [r0, r5, lsl #1] ;fai lsl siccome r5 è il contatore però per caricare devi spostarti di due 2 bytes in 2 bytes quindi moltiplicare ogni valore il valore di r5 per due
		add r5, r5, #1				;incrementa contatore
		
		;ora se r5 è = r2 significa N dispari
		cmp r5, r1
		bge odd
		
		;non dispari -> estrai il secondo short a 16 bit
		ldrh r7, [r0, r5, lsl #1]
		add r5, r5, #1
		
		;ora contatena i due short
		;16bit + 16 bit
		;devi però prima shiftare di 16 bit uno dei due short e metterlo nei 16 MSB della variabile a 32 bit
		lsl r6, r6, #16
		;poi fai un orr 
		orr r6, r6, r6	;r6 ora contiene la concatenazione ed è a 32 bit
		
		;ora aggiorna il risultato globale
		;devi fare il check per vedere se hai overflow!
		;quindi usa adds, che in caso setta la flag 
		;VS per overflow
		adds r3, r3, r6
		bvs overflow
		
		b loop
		
odd
		;assumi ultimo elemento sia 0
		;metti i 16 lsb a zero
		;cioè ti basta shifater il primo short di 16 e metterlo nei primi 16 MSB
		lsl r6, r6, #16
		;no orr non serve
		;aggiungi al risultato
		adds r3, r3, r6
		bvs overflow
		
		b endLoop ; per forza essendo all'ultimo elemento (N dispari mi dice ciò)
		
overflow
		;scrivi in adx char* alarm
		mov r4, #-1
		str r4, [r2]
		;se c'è overflow esci 
		b endLoop
		
endLoop
		mov r4, #0
		str r4, [r2]
		mov r0, r3
		pop {r4-r7, pc}
		
		ENDP
		