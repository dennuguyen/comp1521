# Read a number n and print the first n tetrahedral numbers
# https://en.wikipedia.org/wiki/Tetrahedral_number

main:
    la      $a0, prompt             # printf("Enter how many: ");
    li      $v0, 4
    syscall

    li      $v0, 5                  # scanf("%d", num);
    syscall
    move    $t0, $v0

    li      $t1, 1                  # n = 1;

L1:
    bgt     $t1, $t0, end           # if (n > num) goto E1;
    li      $t4, 0                  # total = 0;
    li      $t2, 1                  # j = 1;

L2:
    bgt     $t2, $t1, E1            # if (j > n) goto E2;
    li      $t3, 1                  # i = 1;

L3:
    bgt     $t3, $t2, E2            # if (i > j) goto E;
    add		$t4, $t4, $t3		    # total = total + 1;
    addi 	$t3, $t3, 1		        # i++;
    b       L3                      # goto loop;

E2:
    addi 	$t2, $t2, 1		        # j++;
    b       L2                      # goto loop;

E1:
    move    $a0, $t4                # printf("%d", total);
    li      $v0, 1
    syscall

    li      $a0, '\n'               # printf("%c", '\n');
    li      $v0, 11
    syscall

    addi 	$t1, $t1, 1		        # n++;
    b       L1                      # goto loop;

end:
    jr      $ra                     # return

.data
    prompt: .asciiz "Enter how many: "
