TOP=.
include $(TOP)/Make.rules

#LDLIBS=-lc -lgcc
LDLIBS=
CFLAGS+=-O2

#LDFLAGS+=-Wl,--no-relax
LDFLAGS+=-Wl,-T,riscv32-virt.ld

PROGS=prog prog.lst

all:: $(PROGS)

prog: crt0.o main.o
	$(LINK.c) -o $@ $^ $(LDLIBS)
	$(SIZE) -A -x $@

# device tree
device:
	qemu-system-riscv32 -machine virt,dumpdtb=qemu-riscv32-virt.dtb
	dtc qemu-riscv32-virt.dtb > qemu-riscv32-virt.dts

script:
	riscv32-unknown-elf-ld --verbose > riscv32-virt.ld

clean::
	rm -f $(PROGS) *.o *.s *.lst *.dtb *.dts

