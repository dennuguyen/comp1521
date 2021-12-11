# this code reads 1 integer and prints it
# change it to read integers until their sum is >= 42
# and then print their sum

main:
    li $t0, 0 # sum = 0;

loop:
    bge $t0, 42, end

    li   $v0, 5        #   scanf("%d", &x);
    syscall            #

    add $t0, $t0, $v0

    b loop
end:
    move $a0, $t0      #   printf("%d\n", x);
    li   $v0, 1
    syscall

    li   $a0, '\n'     #   printf("%c", '\n');
    li   $v0, 11
    syscall

    li   $v0, 0        # return 0
    jr   $ra
