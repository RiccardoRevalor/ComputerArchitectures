.data
v1: .double  43, 23, 57, 34, 79, 6, 30, 44, 82, 18
v2: .double  37, 12, 94, 59, 31, 77, 58, 21, 62, 1
v3: .double  44, 94, 56, 67, 23, 78, 37, 14, 9, 52 
v4: .space 80

.text
daddui r1,r0,0
daddui r2,r0,10
cyc: l.d f1,v1(r1)
l.d f2,v2(r1)
l.d f3,v3(r1)
add.d f5,f1,f1
mul.d f6,f1,f2
add.d f5,f5,f2
div.d f7,f5,f6
s.d f7,v4(r1)
daddui r1,r1,8
daddi r2,r2,-1
bnez r2, cyc
halt