# this code reads 1 integer and prints it
# add code so that prints 1 iff
# the least significant (bottom) byte of the number read
# is equal to the 2nd least significant byte
# and it prints 0 otherwise

main:
    li   $v0, 5 # scanf int
    syscall

    move    $t1, $v0  # LSB
    move    $t2, $v0      # 2nd LSB

    and     $t1, $t1, 0xFF

    srl     $t2, $t2, 8 # shift right 8 bits
    and     $t2, $t2, 0xFF

    li      $a0, 0
    bne     $t1, $t2, print    
    li      $a0, 1
    
print:
    li      $v0, 1
    syscall

    li   $a0, '\n'
    li   $v0, 11
    syscall

    li   $v0, 0
    jr   $ra
