# Dynamically load instructions

main:
    la      $a0, prompt         # printf("Enter mips instructions as integers, -1 to finish: ");
    li      $v0, 4
    syscall


    la      $a0, start          # printf("Starting executing instructions\n");
    li      $v0, 4
    syscall



    la      $a0, finish          # printf("Finished executing instructions\n");
    li      $v0, 4
    syscall

    jr		$ra					# return

.data
    prompt: .asciiz "Enter mips instructions as integers, -1 to finish: "
    start:  .asciiz "Starting executing instructions\n"
    finish: .asciiz "Finished executing instructions\n"
    txt: .asciiz  "print10.instructions"
