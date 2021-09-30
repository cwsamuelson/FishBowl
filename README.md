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