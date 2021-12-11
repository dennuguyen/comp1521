# Sieve of Eratosthenes
# https://en.wikipedia.org/wiki/Sieve_of_Eratosthenes

BYTE_SIZE = 4

main:
    la      $t0, prime          # $t0 = &prime;
    li      $t1, 0              # i = 0;

loop1:
    bge     $t1, 1000, end1     # if (i >= 1000) goto end1;

    mul     $t2, $t1, BYTE_SIZE # addr = 4 * i;
    add     $t2, $t2, $t0       # prime[i] = start + addr;
    li      $t3, 1
    sb      $t3, ($t2)          # prime[i] = 1;
    
    addi    $t1, $t1, 1         # i++;
    b       loop1;              # goto loop1;

end1:
    li      $t1, 2              # i = 2;

loop2:
    bge     $t1, 1000, end2     # if (i >= 1000) goto end2;

    mul     $t2, $t1, BYTE_SIZE # addr = 4 * i;
    add     $t2, $t2, $t0       # prime[i] = start + addr;
    lb      $t3, ($t2)          # $t3 = prime[i];

    beq     $t3, 0, skip        # if (prime[i] == 0) goto skip;

    move    $a0, $t1            # printf("%d", i);
    li      $v0, 1
    syscall

    li      $a0, '\n'           # printf("\n");
    li      $v0, 11
    syscall

    mul     $t4, $t1, 2         # j = 2 * i;

loop3:
    bge     $t4, 1000, skip     # if (j >= 1000) goto skip;

    mul     $t2, $t4, BYTE_SIZE # addr = 4 * j;
    add     $t2, $t2, $t0       # prime[j] = start + addr;
    li      $t3, 0
    sb      $t3, ($t2)          # prime[j] = 0;

    add     $t4, $t4, $t1       # j += i;
    b       loop3               # goto loop3;

skip:
    addi    $t1, $t1, 1         # i++;
    b       loop2;              # goto loop2;

end2:
    li      $v0, 0          # return 0;
    jr      $31

.data
prime: .space 1000
