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

v3: .double 1.0 2.0 3.0 4.0
    .double 5.0 6.0 7.0 8.0
    .double 9.0 10.0 11.0 12.0
    .double 13.0 14.0 15.0 16.0
    .double 17.0 18.0 19.0 20.0
    .double 21.0 22.0 23.0 24.0
    .double 25.0 26.0 27.0 28.0
    .double 29.0 30.0 31.0 32.0

v4: .space 256
v5: .space 256
v6: .space 256

m:   .double 1
fcs: .double 3.0 2.0

.text
    daddui r1, r0, 31  # i = 31
    daddui r2, r0, 248 # i * 8
    daddui r3, r0, 1   # m
    #f20 <- a
    l.d f21, fcs(r3) #f21 <- b = 2.0

    #r9 <- counter to check for multiples of 3
    daddui r9, r9, 1 # start at 1 to sync it with the counter `i`
    l.d f10, fcs(r0)
cycle:
    l.d f1, v1(r2)
    l.d f2, v2(r2)
    l.d f3, v3(r2)

    # START IF
    # i % 3 == 0
    bne r9, r0, else_not_multiple3
    # START (double) m<< i
    dsllv r15, r15, r1
    mtc1 r3, f15
    cvt.d.l f15, f15
    # END r15 <- (double) m<< i

    # START a = v1[i] / r15
    div.d f20, f1, f15
    # END f15 <- a = v1[i] / r15
    # m = (int) a
    cvt.l.d f16, f20
    mtc1 r16, f16

    daddui r9, r0, 2

    j end_if
else_not_multiple3:
    # START a = v1[i] * ((double)m * i))
    mtc1 r3, f15
    cvt.d.l f15, f15
    mtc1 r1, f16
    cvt.d.l f16, f16    # f16 <- (double)i
    mul.d f15, f15, f16 # f16 <- ((double)m * (double)i))
    mul.d f20, f15, f1  # v1[i] * ((double)m * (double)i))
    # END f20 <- a = v1[i] * ((double)m * i))
    # m = (int) a
    cvt.l.d f16, f20
    mtc1 r16, f16
    daddui r9, r9, -1
    # END IF
end_if:
    # v4[i] = a*v1[i] – v2[i];
    mul.d f4, f20, f1
    sub.d f4, f4, f2
    s.d f4, v4(r2)

    # v5[i] = v4[i]/v3[i] – b;
    div.d f5, f4, f3
    sub.d f5, f5, f21
    s.d f5, v5(r2)

    # v6[i] = (v4[i] - v1[i])*v5[i]
    sub.d f6, f4, f1
    mul.d f6, f6, f5
    s.d f6, v6(r2)

    daddi r2, r2, -8
    daddi r1, r1, -1
    slt r3, r2, r0

    beq r3, r0, cycle

    halt                  # End the program

