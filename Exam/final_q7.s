# this code reads 1 integer and prints it
# change it to read integers until their sum is >= 42
# and then print theintgers read in reverse order

main:
    li      $t0, 0          # i = 0;
    li      $t1, 0          # sum = 0;
    la      $t2, numbers

L1:
    bge     $t1, 42, E1     # if (sum >= 42) goto E1;

    li      $v0, 5          # scanf("%d", &x);
    syscall

    mul     $t3, $t0, 4     # curr = 4 * i;
    add     $t3, $t2, $t3   # curr = numbers + curr;
    sw      $v0, ($t3)      # numbers[i] = x;

    addi    $t0, $t0, 1     # i++;
    add     $t1, $t1, $v0   # sum += x;

    b       L1              # goto L1;
E1:
    
L2:
    ble     $t0, 0, E2      # if (i <= 0) goto E2;

    addi    $t0, $t0, -1    # i--;

    mul     $t3, $t0, 4     # curr = 4 * i;
    add     $t3, $t2, $t3   # curr = numbers + curr;
    lw      $t3, ($t3)      # x = numbers[i];

    move    $a0, $t3        # printf("%d\n", x);
    li      $v0, 1
    syscall

    li      $a0, '\n'       # printf("%c", '\n');
    li      $v0, 11
    syscall

    b       L2              # goto L2;
E2:
    li   $v0, 0        # return 0
    jr   $ra

.data
    numbers: .space 1000
