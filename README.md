A super simple freestanding RV32I app that is suitable for verifying a toolchain & qemu installation.


## Run with one hart like this:

qemu-system-riscv32 -machine virt -m 128M -bios none -device loader,file=./prog -nographic -s


## Note that qemu will set the PC register to the load address of 'prog'.
## To stop qemu: ^A x


# run qemu with -S to make it wait for gdb to attach before it starts running:

qemu-system-riscv32 -machine virt -m 128M -bios none -device loader,file=./prog -nographic -s -S


# Then run gdb like this:

riscv32-unknown-elf-gdb ./prog
target remote :1234


In lieu of already having (remembering) a place to store useful links:
https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf
https://dev.to/donaldsebleung/getting-started-with-osdev-on-risc-v-1fd9
https://www.youtube.com/watch?v=n8g_XKSSqRo
https://osblog.stephenmarz.com/
https://x86.lol/generic/2020/01/01/riscv-intro.html
https://github.com/mikeroyal/RISC-V-Guide
