.data
v1: .double 1.0 2.0 3.0 4.0
    .double 5.0 6.0 7.0 8.0
    .double 9.0 10.0 11.0 12.0
    .double 13.0 14.0 15.0 16.0
    .double 17.0 18.0 19.0 20.0
    .double 21.0 22.0 23.0 24.0
    .double 25.0 26.0 27.0 28.0
    .double 29.0 30.0 31.0 32.0

v2: .double 1.0 2.0 3.0 4.0
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
.globl main

li $t0, 31

for: 
sll $t1, $t0, 3 # double precision, muliply by 8
ld $f0, v1($t1)        
ld $f2, v2($t1)        
ld $f4, v3($t1)

mul.d $f6, $f0, $f0
sub.d $f6, $f6, $f2
sd $f6, v4($t1)

div.d $f8, $f6, $f4
sub.d $f8, $f8, $f2
sd $f8, v5($t1)

sub.d $f10, $f8, $f0
mul.d $f10, $f10, $f8
sd $f10, v6($t1)

subi $t0, $t0, 1
bgez $t0, for

li $v0, 10
syscall


