# read a mark and print the corresponding UNSW grade

main:
    la      $a0, prompt     # printf("Enter a mark: ");
    li      $v0, 4
    syscall

    li      $v0, 5          # scanf("%d", mark);
    syscall

    la      $a0, fl
    blt     $v0, 50, end    # if (mark < 50) goto end;

    la      $a0, ps
    blt     $v0, 65, end    # if (mark < 65) goto end;

    la      $a0, cr
    blt     $v0, 75, end    # if (mark < 75) goto end;
    
    la      $a0, dn
    blt     $v0, 85, end    # if (mark < 85) goto end;

    la      $a0, hd

end:
    li      $v0, 4          # printf("%s", mark);
    syscall
    jr      $ra             # return

.data
    prompt: .asciiz "Enter a mark: "
    fl:     .asciiz "FL\n"
    ps:     .asciiz "PS\n"
    cr:     .asciiz "CR\n"
    dn:     .asciiz "DN\n"
    hd:     .asciiz "HD\n"
