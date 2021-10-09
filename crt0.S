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

// machine information
    /*csrr a0,mvendorid   // 0x00000000
    csrr a0,marchid     // 0x00000000
    csrr a0,mimpid      // 0x00000000
    csrr a0,mhartid     // 0x00000000

// machine trap setup
    csrr a0,mstatus     // 0x00000000
    csrr a0,misa        // 0x4014112d
    csrr a0,medeleg     // 0x00000000
    csrr a0,mideleg     // 0x00000000
    csrr a0,mie         // 0x00000000
    csrr a0,mtvec       // 0x00000000
    csrr a0,mcounteren  // 0x00000000

// change privelege?
    //csrw mstatus,x0

// supervisor trap setup
    csrr a0,sstatus     // 0x00000000
    //csrr a0,sedeleg
    //csrr a0,sideleg
    csrr a0,sie         // 0x00000000
    csrr a0,stvec       // 0x00000000
    csrr a0,scounteren  // 0x00000000

// supervisor trap handling
    csrr a0,satp        // 0x00000000


// user trap setup
    //csrr a0,ustatus
    //csrr a0,uie
    //csrr a0,utvec

// user FP CSRs
    csrr a0,fflags
    csrr a0,frm
    csrr a0,fcsr

// user counter/timers
    csrr a0,cycle       // 0x92550a44
    csrr a0,time        // 0x0000735e
    csrr a0,instret     // 0xc1a68b00
    csrr a0,hpmcounter3 // 0x00000000
    csrr a0,hpmcounter4 // 0x00000000
    csrr a0,hpmcounter5 // 0x00000000
    csrr a0,hpmcounter6 // 0x00000000
    csrr a0,hpmcounter7 // 0x00000000
*/

    add s0, sp, zero
    jal ra, main
    .cfi_endproc

    csrw mie,x0
1:
    wfi
    j 1b
.end
