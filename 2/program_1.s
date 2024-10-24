.data
     v1: .double 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 10.10
          .double 11.11, 12.12, 13.13, 14.14, 15.15, 16.16, 17.17, 18.18
          .double 19.19, 20.20, 21.21, 22.22, 23.23, 24.24, 25.25, 26.26
          .double 27.27, 28.28, 29.29, 30.30, 31.31, 32.32
     v2: .double 2.0, 4.0, 6.0, 8.0, 10.0, 12.0, 14.0, 16.0, 18.0, 20.0
          .double 22.0, 24.0, 26.0, 28.0, 30.0, 32.0, 34.0, 36.0, 38.0
          .double 40.0, 42.0, 44.0, 46.0, 48.0, 50.0, 52.0, 54.0, 56.0
          .double 58.0, 60.0, 62.0, 64.0
     v3: .double 3.1, 3.2, 3.3, 3.4, 3.5, 3.6, 3.7, 3.8, 3.9, 4.0, 4.1
          .double 4.2, 4.3, 4.4, 4.5, 4.6, 4.7, 4.8, 4.9, 5.0, 5.1, 5.2
          .double 5.3, 5.4, 5.5, 5.6, 5.7, 5.8, 5.9, 6.0, 6.1, 6.2
     v4: .space 256
     v5: .space 256
     v6: .space 256

.text
     daddui r1, r0, 248 # r1 holds the index i=31 (multiplied by 8)
     daddi r2, r0, -8 # r2 holds the value to evaluate the loop condition 
                         # (>= 0 corresponds to > -1, in my case -8 since its multiplied by 8)
cycle:  l.d f1, v1(r1)
     l.d f2, v2(r1)
     #l.d f3, v3(r1) MOVED BELOW
     mul.d f4, f1, f1
     l.d f3, v3(r1)
     sub.d f4, f4, f2
     #s.d f4, v4(r1) MOVED BELOW
     div.d f5, f4, f3
     sub.d f6, f4, f1
     sub.d f5, f5, f2
     #s.d f5, v5(r1) MOVED BELOW
     #sub.d f6, f4, f1 MOVED ABOVE
     mul.d f6, f6, f5
     s.d f4, v4(r1)
     s.d f5, v5(r1)
     s.d f6, v6(r1)
     daddi r1, r1, -8
     bne r1, r2, cycle

halt