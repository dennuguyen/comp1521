# read a line and print whether it is a palindrom

main:
    la      $a0, str0           # printf("Enter a line of input: ");
    li      $v0, 4
    syscall

    la      $a0, line           # fgets(line, 256, stdin);
    la      $a1, 256
    li      $v0, 8
    syscall
    move    $t0, $a0

    li      $t1, 0              # i = 0;

    add     $t2, $t0, $t1       # line[i] = line + i;
    lb      $t2, ($t2)

loop0:
    beq     $t2, 0, end0        # if (line[i] == 0) goto end0;

    addi    $t1, $t1, 1         # i++;

    add     $t2, $t0, $t1       # line[i] = line + i;
    lb      $t2, ($t2)

    b       loop0               # goto loop0;

end0:
    li      $t3, 0              # j = 0;
    addi    $t1, $t1, -2        # k = i -= 2;

    add     $t4, $t0, $t3       # line[j] = line + j;
    lb      $t4, ($t4)

    add     $t2, $t0, $t1       # line[k] = line + k;
    lb      $t2, ($t2)

loop1:
    bge     $t3, $t1, end1      # if (j >= k) goto end1;
    bne     $t2, $t4, end2      # if (line[j] != line[k]) goto end2;

    addi    $t3, $t3, 1         # j++;
    addi    $t1, $t1, -1        # k--;

    add     $t4, $t0, $t3       # line[j] = line + j;
    lb      $t4, ($t4)

    add     $t2, $t0, $t1       # line[k] = line + k;
    lb      $t2, ($t2)

    b       loop1               # goto loop1;

end1:
    la      $a0, palindrome     # printf("palindrome\n");
    li      $v0, 4
    syscall

    li      $v0, 0              # return 0;
    jr      $31

end2:
    la      $a0, not_palindrome # printf("not palindrome\n");
    li      $v0, 4
    syscall

    li      $v0, 0              # return 0;
    jr      $31

.data
str0:           .asciiz "Enter a line of input: "
palindrome:     .asciiz "palindrome\n"
not_palindrome: .asciiz "not palindrome\n"
line:           .space 256
