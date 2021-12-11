# print the integers between x and y except 13
main:
    li      $v0, 5          # scanf("%d", &x);
    syscall
    move    $t0, $v0

    li      $v0, 5          # scanf("%d", &y);
    syscall
    move    $t1, $v0

    add     $t3, $t0, 1     # i = x + 1;

loop:
    bge     $t3, $t1, end   # if (i >= y) goto end;

    beq     $t3, 13, skip   # if (i == 13) goto skip;

    move    $a0, $t3        # printf("%d", i);
    li      $v0, 1
    syscall

    li      $a0, '\n'       # printf("\n");
    li      $v0, 11
    syscall

skip:
    addi    $t3, $t3, 1     # i++;
    b       loop;

end:
    li      $v0, 0          # return 0
    jr      $31
