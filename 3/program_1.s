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
     daddui  r3, r0, 3 # division by 3
     daddui r1, r0, 248 # r1 holds the vectors index (i=31 multiplied by 8)
     daddui r2, r0, 31 # r2 holds the index i=31
     daddi r5, r0, -1 #check for loop exit condition
     ld r6, m(r0) #load m into register
     l.d f9, b(r0) #load b into register

cycle:  

     # load vector values at index i
     l.d f1, v1(r1)
     l.d f2, v2(r1)
     l.d f3, v3(r1)

     #computation of i mod 3 in r4
     ddivu r4, r2, r3   
     dmulu r4, r4, r3
     dsubu r4, r2, r4
          
     # check if branch condition and jump accordingly
     beqz r4, multiple3
     j no_multiple3

multiple3:
     dsllv r6, r6, r2 #shift m by i positions
     mtc1 r6, f7 #convert shifted m to a double and store it in f7
     cvt.d.l f7, f7
     div.d f8, f1, f7 #"a" computation
     cvt.l.d f10, f8 
     mfc1 r6, f10 # m = int(a) conversion
     j end

no_multiple3:
     dmulu r6, r6, r2 #computer m*i
     mtc1 r6, f7 #convert m*i to a double and store it in f7
     cvt.d.l f7, f7
     mul.d f8, f1, f7 #"a" computation
     cvt.l.d f10, f8 
     mfc1 r6, f10 # m = int(a) conversion
     j end

# instructions after if condition inside for loop
end:
     #computation of v4[i]
     mul.d f4, f8, f1
     sub.d f4, f4, f2
     s.d f4, v4(r1)
     
     #computation of v5[i]
     div.d f5, f4, f3
     sub.d f5, f5, f9
     s.d f5, v5(r1)

     #computation of v6[i]
     sub.d f6, f4, f1
     mul.d f6, f6, f5
     s.d f6, v6(r1)

     #update of indeces
     daddi r1, r1, -8
     daddi r2, r2, -1

     #check for loop branch condition and jump accordingly
     bne r2, r5, cycle
halt