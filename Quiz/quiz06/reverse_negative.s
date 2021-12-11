# Read numbers into an array until a negative number is entered
# then print the numbers in reverse order
main:
    li      $t0, 0              # i = 0;
    la      $t1, numbers        # start = numbers;

loop0:
    bge     $t0, 1000, end0     # if (i >= 1000) goto end0;

    li      $v0, 5              # scanf("%d", &x);
    syscall

    blt     $v0, 0, end0        # if (x < 0) goto end0;

    mul     $t2, $t0, 4         # size = 4 * i;
    add     $t2, $t1, $t2       # numbers[i] = start + size;
    sw      $v0, ($t2)          # numbers[i] = x;

    addi    $t0, $t0, 1         # i++;
    b       loop0               # goto loop0;

end0:

loop1:
    ble     $t0, 0, end1        # if (i <= 0) goto end1;

    addi    $t0, $t0, -1        # i--;

    mul     $t2, $t0, 4         # size = 4 * i;
    add     $t2, $t1, $t2       # numbers[i] = start + size;
    lw      $a0, ($t2)          # x = numbers[i];

    li      $v0, 1              # printf("%d", x);
    syscall

    la      $a0, newline        # printf("\n");
    li      $v0, 4
    syscall

    b       loop1               # goto loop1;

end1:
    li      $v0, 0              # return 0;
    jr      $31

.data
numbers: .space 4000
newline: .asciiz "\n"
