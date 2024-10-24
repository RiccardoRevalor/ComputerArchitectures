.data
     
     a: .space 8
     b: .double 7.5
     m: .word 1
     v1: .double 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0
          .double 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0
          .double 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3.0, 3.1, 3.2
     v2: .double 0.2, 0.4, 0.6, 0.8, 1.0, 1.2, 1.4, 1.6, 1.8, 2.0
          .double 2.2, 2.4, 2.6, 2.8, 3.0, 3.2, 3.4, 3.6, 3.8
          .double 4.0, 4.2, 4.4, 4.6, 4.8, 5.0, 5.2, 5.4, 5.6
          .double 5.8, 6.0, 6.2, 6.4
     v3: .double 3.1, 3.2, 3.3, 3.4, 3.5, 3.6, 3.7, 3.8, 3.9, 4.0, 4.1
          .double 4.2, 4.3, 4.4, 4.5, 4.6, 4.7, 4.8, 4.9, 5.0, 5.1, 5.2
          .double 5.3, 5.4, 5.5, 5.6, 5.7, 5.8, 5.9, 6.0, 6.1, 6.2
     v4: .space 256
     v5: .space 256
     v6: .space 256

.text
     daddui r1, r0, 248 # r1 holds the vectors index (i=31 multiplied by 8)
     daddui r2, r0, 240 # r2 holds the vectors index (i=30 multiplied by 8)
     daddui r3, r0, 232 # r3 holds the vectors index (i=29 multiplied by 8)
     daddui r4, r0, 31 # r4 holds the index i=31
     ld r6, m(r0) #load m into register
     daddi r5, r0, -2 #check for loop exit condition
     l.d f9, b(r0) #load b into register

cycle:  

#CYCLE 1: 

     dmulu r6, r6, r2 #computer m*i

     # load vector values at index i
     l.d f1, v1(r1)
     l.d f2, v2(r1)
     l.d f3, v3(r1)

#CYCLE 2:
     # load vector values at index i
     l.d f11, v1(r2)

#CYCLE 1:      
     #convert m*i to a double and store it in f7
     mtc1 r6, f7 
     cvt.d.l f7, f7

     mul.d f8, f1, f7 #"a" computation

#CYCLE 2:
     l.d f12, v2(r2)
     l.d f13, v3(r2)

#CYCLE 1: 
     #computation of v4[i]
     mul.d f4, f8, f1

     # m = int(a) conversion
     cvt.l.d f10, f8 
     mfc1 r6, f10 
     
     sub.d f4, f4, f2
     
     #computation of v5[i]
     div.d f5, f4, f3

#CYCLE 2:
     dsllv r6, r6, r2 #shift m by i positions

     #convert shifted m to a double and store it in f7
     mtc1 r6, f7 
     cvt.d.l f7, f7

     div.d f8, f11, f7 #"a" computation

#CYCLE 1:
     sub.d f6, f4, f1
     sub.d f5, f5, f9

     #computation of v6[i]
     mul.d f6, f6, f5
     s.d f4, v4(r1)
     s.d f5, v5(r1)

#CYCLE 2:

    # m = int(a) conversion
     cvt.l.d f10, f8 
     mfc1 r6, f10

     #computation of v4[i]
     mul.d f4, f8, f11

#CYCLE 3:
     dmulu r6, r6, r2 #compute m*i

#CYCLE 1:
     s.d f6, v6(r1)

     #update r1
     daddi r1, r1, -24
     
#CYCLE 2:
     sub.d f4, f4, f12
     
     #computation of v5[i]
     div.d f5, f4, f13

#CYCLE 3:
     mtc1 r6, f7 #convert m*i to a double and store it in f7
     cvt.d.l f7, f7
     mul.d f8, f1, f7 #"a" computation

     # load vector values at index i
     l.d f1, v1(r3)
     l.d f2, v2(r3)
     l.d f3, v3(r3)

     cvt.l.d f10, f8 
     mfc1 r6, f10 # m = int(a) conversion

     #computation of v4[i]
     mul.d f14, f8, f1
     sub.d f14, f14, f2
     #s.d f4, v4(r1)
     
     #computation of v5[i]
     div.d f15, f14, f3

#CYCLE 2:
     sub.d f6, f4, f11
     sub.d f5, f5, f9

     #computation of v6[i]
     mul.d f6, f6, f5
     s.d f4, v4(r2)
     s.d f5, v5(r2)
     s.d f6, v6(r2)

     #update r1
     daddi r2, r2, -24

#CYCLE 3:
     sub.d f6, f14, f1
     sub.d f15, f15, f9

     #computation of v6[i]
     mul.d f6, f6, f15
     s.d f14, v4(r3)
     s.d f15, v5(r3)
     s.d f6, v6(r3)

     #update of indeces
     daddi r4, r4, -3


     #check for loop branch condition and jump accordingly
     bne r4, r5, cycle
     daddi r3, r3, -24
halt
