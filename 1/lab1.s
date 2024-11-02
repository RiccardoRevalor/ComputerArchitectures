.data
v1: .byte 1,2,3,4,5
v2: .byte 1,2,3,4,5
v3: .space 5
v4: .space 5
.text
	daddui r5,r0,0
daddui r6,r0,5
cycle: lb r1,v1(r5)
	lb r2,v2(r5)
	daddu r3,r1,r2
	dsub r4,r1,r2
	sb r3,v3(r5)
	sb r4,v4(r5)
	daddui r5,r5,1
	daddi r6,r6,-1
	bnez r6, cycle
halt
