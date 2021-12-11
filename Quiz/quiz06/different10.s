# $t0 = x
# $t1 = i
# $t2 = n_seen
# $t3 = &numbers
main:
    li      $t2, 0              # n_seen = 0;
    la      $t3, numbers        # $t3 = &numbers;

loop0:
    bge     $t2, 10, end0       # if (n_seen >= 10) goto end0;

    la      $a0, string0        # printf("Enter a number: ");
    li      $v0, 4
    syscall

    li      $v0, 5              # scanf("%d", &x);
    syscall
    move    $t0, $v0

    li      $t1, 0              # i = 0;

loop1:
    bge     $t1, $t2, end1      # if (i >= n_seen) goto end1;

    mul     $t4, $t1, 4         # size = i * sizeof(byte);
    add     $t4, $t3, $t4       # curr = start + size;
    lw      $t4, ($t4)          # numbers[n_seen] = x

    beq     $t0, $t4, end1      # if (x == numbers[i]) goto end1;

    addi    $t1, $t1, 1         # i++;
    b       loop1               # goto loop1;

end1:
    bne     $t1, $t2, loop0     # if (i != n_seen) goto loop0;

    mul     $t4, $t2, 4         # size = n_seen * sizeof(byte);
    add     $t4, $t3, $t4       # curr = start + size;
    sw      $t0, ($t4)          # numbers[n_seen] = x

    addi    $t2, $t2, 1         # n_seen++;
    b       loop0               # goto loop0;

end0:
    la      $a0, string1        # printf("10th different number was: ");
    li      $v0, 4
    syscall

    move    $a0, $t0            # printf("%d", x)
    li      $v0, 1
    syscall

    la      $a0, newline        # printf("\n");
    li      $v0, 4
    syscall

    li      $v0, 0              # return 0;
    jr      $31

.data
numbers: .space 40              # int numbers[10];
string0: .asciiz "Enter a number: "
string1: .asciiz "10th different number was: "
newline: .asciiz "\n"
