# read 10 numbers into an array
# swap any pairs of of number which are out of order
# then print the 10 numbers

# i in register $t0,
# registers $t1 - $t3 used to hold temporary results

main:

    li $t0, 0           # i = 0
loop0:
    bge $t0, 10, end0   # while (i < 10) {

    li $v0, 5           #   scanf("%d", &numbers[i]);
    syscall             #

    mul $t1, $t0, 4     #   calculate &numbers[i]
    la $t2, numbers     #
    add $t3, $t1, $t2   #
    sw $v0, ($t3)       #   store entered number in array

    add $t0, $t0, 1     #   i++;
    b loop0             # }
end0:

###
    li      $t0, 1                  # i = 1;
    la      $t2, numbers

loop2:
    bge     $t0, 10, end2           # if (i >= 10) goto end2;

    mul     $t1, $t0, 4             # size = 4 * i;
    add     $t3, $t1, $t2           # address = start + curr;
    lw      $t4, ($t3)              # x = numbers[i];
    lw      $t5, -4($t3)            # y = numbers[i - 1];

    bge     $t4, $t5, next          # if (x >= y) goto next;

    sw      $t4, -4($t3)            # x = y;
    sw      $t5, ($t3)              # y = x;

next:
    add     $t0, $t0, 1             # i++;
    b       loop2;                  # goto loop2;

end2:
###

    li $t0, 0           # i = 0
loop1:
    bge $t0, 10, end1   # while (i < 10) {

    mul $t1, $t0, 4     #   calculate &numbers[i]
    la $t2, numbers     #
    add $t3, $t1, $t2   #
    lw $a0, ($t3)       #   load numbers[i] into $a0
    li $v0, 1           #   printf("%d", numbers[i])
    syscall

    li   $a0, '\n'      #   printf("%c", '\n');
    li   $v0, 11
    syscall

    add $t0, $t0, 1     #   i++
    b loop1             # }
end1:

    jr $31              # return

.data

numbers:
    .word 0 0 0 0 0 0 0 0 0 0  # int numbers[10] = {0};

