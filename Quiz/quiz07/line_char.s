#  read a line from stdin and and then an integer n
#  Print the character in the nth-position

main:
    la      $a0, str0       # printf("Enter a line of input: ");
    li      $v0, 4
    syscall

    la      $a0, line       # fgets(line, 256, stdin);
    li      $a1, 256
    li      $v0, 8
    syscall
    move    $t0, $a0

    la      $a0, str1       # printf("Enter a position: ");
    li      $v0, 4
    syscall

    li      $v0, 5          # scanf("%d", position);
    syscall
    move    $t1, $v0

    la      $a0, str2       # printf("Character is: ");
    li      $v0, 4
    syscall

    add     $t1, $t0, $t1   # line[position] = line + position;
    lb      $t1, ($t1)

    move    $a0, $t1        # printf("%c", line[position]);
    li      $v0, 11
    syscall

    li      $a0, '\n'       # printf("%c", '\n');
    li      $v0, 11
    syscall

    li      $v0, 0          # return 0;
    jr      $31

.data
str0: .asciiz "Enter a line of input: "
str1: .asciiz "Enter a position: "
str2: .asciiz "Character is: "
line: .space 256
