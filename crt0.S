// boot.S
// bootloader for 'QOS'(?)
// Chris Samuelson
// 10 Oct 21

.section .text,"ax"
.global _start
.type   _start, @function
.align 2

_start:     // This has to match the entry address in the ld script!!
    .cfi_startproc
    .cfi_undefined ra

    .option push
    .option norelax

    la gp,__global_pointer$
    .option pop
    la sp,__stack_top

    add s0, sp, zero
    jal ra, main
    .cfi_endproc

    csrw mie,x0
1:
    wfi
    j 1b
.end
