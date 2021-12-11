# read a line and print its length

main:
    la      $a0, str0       # printf("Enter a line of input: ");
    li      $v0, 4
    syscall

    la      $a0, line       # fgets(line, 256, stdin);
    li      $a1, 256
    li      $v0, 8
    syscall
    move    $t0, $a0

    li      $t1, 0          # i = 0;
    add     $t2, $t0, $t1   # line[i] = line + i;
    lb      $t2, ($t2)

loop:
    beq     $t2, 0, end     # if (line[i] == 0) goto end;

    addi    $t1, $t1, 1     # i++;

    add     $t2, $t0, $t1   # line[i] = line + i;
    lb      $t2, ($t2)

    b       loop;           # goto loop;

end:
    la      $a0, str1       # printf("Line length: ");
    li      $v0, 4
    syscall

    move    $a0, $t1        # printf("%d", i);
    li      $v0, 1
    syscall

    li      $a0, '\n'       # printf("\n");
    li      $v0, 11
    syscall

    li      $v0, 0          # return 0;
    jr      $31

.data
str0: .asciiz "Enter a line of input: "
str1: .asciiz "Line length: "
line: .space 256
