# Read 10 numbers into an array
# print 0 if they are in non-decreasing order
# print 1 otherwise

# i in register $t0

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
    li      $a0, 1                  # unordered = 1;
    la      $t2, numbers

loop1:
    bge     $t0, 10, end1           # if (i >= 10) goto end1;

    mul     $t1, $t0, 4             # size = 4 * i;
    add     $t3, $t1, $t2           # address = start + curr;
    lw      $t4, ($t3)              # x = numbers[i];
    lw      $t5, -4($t3)            # y = numbers[i - 1];

    slt     $a0, $t4, $t5           # i = x < y ? 1 : 0;
    beq     $a0, 1, end1            # if (ordered == 1) goto end1;

    add     $t0, $t0, 1             # i++;
    b       loop1                   # goto loop0;

end1:
###


    li $v0, 1           #
    syscall

    li   $a0, '\n'      # printf("%c", '\n');
    li   $v0, 11
    syscall

    jr $31

.data

numbers:
    .word 0 0 0 0 0 0 0 0 0 0  # int numbers[10] = {0};
