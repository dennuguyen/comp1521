# this code reads a line of input and prints 42
# change it to evaluate the arithmetic expression

MAX = 10000
BYTE = 1

main:
    la      $a0, line           # fgets(buffer, MAX, stdin);
    la      $a1, MAX
    li      $v0, 8
    syscall

    li      $s0, 0              # s = line; incrementer for line
    la      $s1, line
    lb      $s2, ($s1)

    jal     expression
    move    $a0, $v0            # printf("%d", expression());
    li      $v0, 1
    syscall

    li      $a0, '\n'           # printf("%c", '\n');
    li      $v0, 11
    syscall

    li      $v0, 0
    jr      $31                 # return 0;

#############################
expression:
    jal     term
    move    $t0, $v0            # left = term();

    mul     $t8, $s0, BYTE
    add     $t8, $t8, $s1
    lb      $s2, ($t8)

    bne     $s2, '+', end_exp   # if (s != '+') goto end_exp;
    move    $v0, $t0
    jr      $ra                 # return left;

end_exp:
    addi    $s0, $s0, 1         # s++;

    mul     $t8, $s0, BYTE
    add     $t8, $t8, $s1
    lb      $s2, ($t8)

    jal     expression
    move    $t1, $v0            # right = expression();
    add     $v0, $t1, $t2       # left + right;
    jr      $ra                 # return left + right;

#############################
term:
    jal     number
    move    $t0, $v0            # left = number();

    mul     $t8, $s0, BYTE
    add     $t8, $t8, $s1
    lb      $s2, ($t8)

    bne     $s2, '*', end_term  # if (s != '*') goto end_term;
    move    $v0, $t0
    jr      $ra                 # return left;

end_term:
    addi    $s0, $s0, 1         # s++;
    jal     term
    move    $t1, $v0            # right = term();
    mul     $v0, $t1, $t2       # left * right;
    jr      $ra                 # return left * right;

#############################
number:
    li      $t0, 0              # n = 0;

    mul     $t8, $s0, BYTE
    add     $t8, $t8, $s1
    lb      $s2, ($t8)

    bne     $s2, '0', end_number  # if (s < 0) goto end_number;
    bne     $s2, '1', end_number  # if (s < 0) goto end_number;
    bne     $s2, '2', end_number  # if (s < 0) goto end_number;
    bne     $s2, '3', end_number  # if (s < 0) goto end_number;
    bne     $s2, '4', end_number  # if (s < 0) goto end_number;
    bne     $s2, '5', end_number  # if (s < 0) goto end_number;
    bne     $s2, '6', end_number  # if (s < 0) goto end_number;
    bne     $s2, '7', end_number  # if (s < 0) goto end_number;
    bne     $s2, '8', end_number  # if (s < 0) goto end_number;
    bne     $s2, '9', end_number  # if (s > 9) goto end_number;

    mul     $t0, $t0, 10        # n *= 10;
    add     $t0, $t0, $s0       # n += s;
    addi    $s0, $s0, 1         # s++;

end_number:
    move    $v0, $t0
    jr      $ra                 # return n;

.data
    line: .space MAX
