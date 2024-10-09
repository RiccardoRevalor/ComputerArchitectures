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

.text

    daddui r1, r0, 0     # r1 holds the index (i)
    daddui r2, r0, 31    # r2 holds the loop counter (i = 31)

cycle:
    l.d f1, v1(r1)       
    l.d f2, v2(r1)   
    #l.d f3, v3(r1)   MOSSA SOTTO        

    mul.d f4, f1, f1 
    l.d f3, v3(r1) 
    sub.d f4, f4, f2    
    s.d f4, v4(r1)       

    div.d f5, f4, f3     
    sub.d f5, f5, f2     
    s.d f5, v5(r1)      

    sub.d f6, f4, f1     
    mul.d f6, f6, f5  
    daddi r2, r2, -1  
    slt r3, r2, r0
    s.d f6, v6(r1)      

    daddui r1, r1, 8     
    #daddi r2, r2, -1     MOSSA SOPRA
       
    #slt r3, r2, r0       MOSSA SOPRA
    beq r3, r0, cycle   
    halt                  # End the program
