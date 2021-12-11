# print the minimum of two integers
main:
    li      $v0, 5          # scanf("%d", &x);
    syscall
    move    $t0, $v0

    li      $v0, 5          # scanf("%d", &y);
    syscall
    move    $t1, $v0

    move    $a0, $t0        # min = x;
    blt     $t0, $t1, print # if (x < y) goto print;
    move    $a0, $t1        # min = y;

print:
    li      $v0, 1          # printf("%d\n", min);
    syscall

    li      $a0, '\n'       # printf("\n");
    li      $v0, 11
    syscall

end:
    li      $v0, 0          # return 0
    jr      $31
