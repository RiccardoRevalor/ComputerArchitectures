.data
v1: .double 1.0 2.0 3.0 4.0
    .double 5.0 6.0 7.0 8.0
    .double 9.0 10.0 11.0 12.0
    .double 13.0 14.0 15.0 16.0
    .double 17.0 18.0 19.0 20.0
    .double 21.0 22.0 23.0 24.0
    .double 25.0 26.0 27.0 28.0
    .double 29.0 30.0 31.0 32.0

v2: .double 2.0 2.0 3.0 4.0
    .double 5.0 6.0 7.0 8.0
    .double 9.0 10.0 11.0 12.0
    .double 13.0 14.0 15.0 16.0
    .double 17.0 18.0 19.0 20.0
    .double 21.0 22.0 23.0 24.0
    .double 25.0 26.0 27.0 28.0
    .double 29.0 30.0 31.0 32.0

v3: .double 10.0 2.0 3.0 4.0
    .double 5.0 6.0 7.0 8.0
    .double 9.0 10.0 11.0 12.0
    .double 13.0 14.0 15.0 16.0
    .double 17.0 18.0 19.0 20.0
    .double 21.0 22.0 23.0 24.0
    .double 25.0 26.0 27.0 28.0
    .double 29.0 30.0 31.0 32.0
    .double 33.0 34.0 35.0 36.0

v4: .space 256
v5: .space 256
v6: .space 256
m: .word 1


.text
    daddui r1, r0, 8     # r1 holds the index (i)
    daddui r2, r0, 31    # r2 holds the loop counter (i = 31)
    dmul r1, r1, r2      #r1 = 31 * 8
    ld r3, m(r0)         #r3 = m = 1 at the beginning
    daddui r8, r0, 1     #b = 1 (double)
    daddui r15, r0, 1
    #convert r8 to double
    mtc1 r8, f8
    daddui r14, r0, 3
    cvt.d.l f8, f8
    #r8 holds b


cycle_unrolled:
#NOT multiple
#multiple
#NOT multiple

    l.d f2, v2(r1)
    l.d f3, v3(r1)
    l.d f1, v1(r1)


### NOT MULTIPLE 1 ###
not_multiple_1:
    ##daddi r11, r11, 1 ##DEBUG
    #perform: a = v1[i] * ((double) m* i)
    dmul r4, r3, r2     #m*i
    mtc1 r4, f4         #f4 contains m*i in integer form
    cvt.d.l f4, f4      #f4 contains m*i in double form
    mul.d f5, f2, f4    #f5 contains a

    #m = (int)a
    cvt.l.d f6, f5
    mfc1 r3, f6         #in r3 there is m = int(a)#perform: v4[i] = a*v1[i] – v2[i];

    mul.d f6, f5, f1    #a*v1[i]
    sub.d f6, f6, f2    #a*v1[i] - v2[i]
    s.d f6, v4(r1)      #v4[i] = a*v1[i] - v2[i]

#perform: v5[i] =v4[i]/v3[i] – b
    div.d f7, f6, f3    #v4[i]/v3[i]
    sub.d f9, f6, f1    #v4[i]-v1[i]
    sub.d f7, f7, f8    #v4[i]/v3[i] - b
    daddi r2, r2, -1    #r2 = r2 - 1
    s.d f7, v5(r1)      #v5[i] = v4[i]/v3[i] - b

#perform: v6[i] = (v4[i]-v1[i])*v5[i]
    mul.d f9, f9, f7    #(v4[i]-v1[i])*v5[i]
    s.d f9, v6(r1)      #v6[i] = (v4[i]-v1[i])*v5[i]

    daddi r1, r1, -8     #r1 = r1 - 8


### MULTIPLE ###
multiple:
    dsllv r3, r3, r2    #m<<i
    l.d f2, v2(r1)
    l.d f3, v3(r1)
    l.d f1, v1(r1)
    ##daddi r12, r12, 1 ##DEBUG
    #perform: a = v1[i] / ((double)m<< i) /*logic shift */
    mtc1 r3, f4         #f4 contains m<<i in integer form
    cvt.d.l f4, f4      #f4 contains m<<i in double form
    div.d f5, f1, f4    #f5 contains a

    #m = int(a)
    cvt.l.d f6, f5

    #at the end: F5 = a, r3 = m
    mfc1 r3, f6         #in r3 there is m = int(a)

    #perform: v4[i] = a*v1[i] – v2[i];
    mul.d f6, f5, f1    #a*v1[i]
    sub.d f6, f6, f2    #a*v1[i] - v2[i]
    s.d f6, v4(r1)      #v4[i] = a*v1[i] - v2[i]

#perform: v5[i] =v4[i]/v3[i] – b
    div.d f7, f6, f3    #v4[i]/v3[i]
    sub.d f9, f6, f1    #v4[i]-v1[i]
    sub.d f7, f7, f8    #v4[i]/v3[i] - b
    daddi r2, r2, -1    #r2 = r2 - 1
    s.d f7, v5(r1)      #v5[i] = v4[i]/v3[i] - b

#perform: v6[i] = (v4[i]-v1[i])*v5[i]
    mul.d f9, f9, f7    #(v4[i]-v1[i])*v5[i]
    slt r10, r2, r0     #r10 = r2 < 0
    s.d f9, v6(r1)      #v6[i] = (v4[i]-v1[i])*v5[i]


end2:
    #here, if r2 < 0 the program ends
    beq r10, r0, not_multiple_2  #if r2 >= 0, go to cycle
    daddi r1, r1, -8     #r1 = r1 - 8
    halt


### NOT MULTIPLE 2 ###
not_multiple_2:
    dmul r4, r3, r2     #m*i
    l.d f2, v2(r1)
    ##daddi r11, r11, 1 ##DEBUG
    l.d f3, v3(r1)
    l.d f1, v1(r1)
    mtc1 r4, f4         #f4 contains m*i in integer form
    cvt.d.l f4, f4      #f4 contains m*i in double form
    mul.d f5, f2, f4    #f5 contains a

    #m = (int)a
    cvt.l.d f6, f5
    mfc1 r3, f6         #in r3 there is m = int(a)#perform: v4[i] = a*v1[i] – v2[i];

    mul.d f6, f5, f1    #a*v1[i]
    sub.d f6, f6, f2    #a*v1[i] - v2[i]
    s.d f6, v4(r1)      #v4[i] = a*v1[i] - v2[i]

#perform: v5[i] =v4[i]/v3[i] – b
    div.d f7, f6, f3    #v4[i]/v3[i]
    sub.d f9, f6, f1    #v4[i]-v1[i]
    sub.d f7, f7, f8    #v4[i]/v3[i] - b
    daddi r2, r2, -1    #r2 = r2 - 1
    s.d f7, v5(r1)      #v5[i] = v4[i]/v3[i] - b

#perform: v6[i] = (v4[i]-v1[i])*v5[i]
    mul.d f9, f9, f7    #(v4[i]-v1[i])*v5[i]
    s.d f9, v6(r1)      #v6[i] = (v4[i]-v1[i])*v5[i]

    daddi r1, r1, -8     #r1 = r1 - 8

    j cycle_unrolled




