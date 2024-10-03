.data
v1: .double 1, 2, 3, 4, 5
v2: .double 5, 4, 3, 2, 1
v3: .double 6, 7, 8, 9, 10
v4: .double 10, 9, 8, 7, 6
v5: .space 40
v6: .space 40

.text
daddui r1,r0,0
daddui r2,r0,5
cycle: l.d f1, v1(r1)
l.d f2, v2(r1)
l.d f3, v3(r1)
l.d f4, v4(r1)
mul.d f5, f1, f2
mul.d f6, f3, f4
s.d f5, v5(r1)
s.d f6, v6(r1)
daddui r1,r1,8
daddi r2,r2,-1
bnez r2,cycle
halt
