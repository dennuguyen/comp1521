# Read a number and print positive multiples of 7 or 11 < n

main:
    la      $a0, prompt             # printf("Enter a number: ");
    li      $v0, 4
    syscall

    li      $v0, 5                  # scanf("%d", num);
    syscall
    move    $t0, $v0

    li      $t1, 1                  # i = 1;

loop:
    bge     $t1, $t0, end           # if (i >= num) goto end;

    div		$t2, $t1, 7			    # div1 = i / 7
    mfhi	$t3					    # mod1 = i % 7

    div     $t4, $t1, 11            # div2 = i / 11
    mfhi	$t5					    # mod2 = i % 11

    beq		$t3, 0, print	        # if mod1 == 0 goto print;
    bne		$t5, 0, next	        # if mod2 != 0 goto next;

print:
    move    $a0, $t1                # printf("%d", i);
    li      $v0, 1
    syscall

    li      $a0, '\n'               # printf("%c", '\n');
    li      $v0, 11
    syscall

next:
    addi 	$t1, $t1, 1		        # i++;
    b       loop                    # goto loop;

end:
    jr      $ra                     # return

.data
    prompt: .asciiz "Enter a number: "
