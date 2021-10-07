    .section .text,"ax"
    .global _start
    .type   _start, @function
    .align 2

/*
Currently, the CPU initializes at 0x1000, which contains:
0x00001000  ? auipc    t0,0x0
0x00001004  ? addi    a2,t0,40
0x00001008  ? csrr    a0,mhartid
0x0000100c  ? lw    a1,32(t0)
0x00001010  ? lw    t0,24(t0)
0x00001014  ? jr    t0
0x00001018  ? unimp

this is not something I have written, but is useful reference
ultimately, I would like control of this code as well
 */

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
