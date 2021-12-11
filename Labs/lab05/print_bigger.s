# Read 10 numbers into an array
# then print the numbers which are
# larger than the last number read.

# i in register $t0
# registers $t1, $t2 & $t3 used to hold temporary results

main:
    la      $t2, numbers
    li      $t0, 0                      # i = 0;

loop0:
    bge     $t0, 10, end0               # if (i >= 10) goto end0;

    li      $v0, 5                      # scanf("%d", num);
    syscall

    mul     $t1, $t0, 4                 # curr = 4 * i;
    add     $t3, $t1, $t2               # t3 = curr + start;

    sw      $v0, ($t3)                  # start + curr = num;

    addi    $t0, $t0, 1                 # i++;
    b       loop0                       # goto loop0;

end0:
    move 	$t4, $v0                    # last_number = start + curr;
    li      $t0, 0                      # i = 0;

loop1:
    bge     $t0, 10, end1               # if (i >= 10) goto end1;

    mul     $t1, $t0, 4                 # curr = 4 * i;
    add     $t5, $t1, $t2               # t3 = curr + start;
    lw      $t3, ($t5)

    blt     $t3, $t4, next              # if (curr + start < last_number) goto next;

    move    $a0, $t3                    # a0 = start + curr;
    li      $v0, 1                      # printf("%d", start + curr);
    syscall

    li      $a0, '\n'                   # printf("\n");
    li      $v0, 11
    syscall

next:
    addi    $t0, $t0, 1                 # i++;
    b       loop1                       # goto loop1;

end1:
    jr      $ra                         # return;

.data
    numbers: .word 0 0 0 0 0 0 0 0 0 0  # int numbers[10] = {0};
