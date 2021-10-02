TOP=.
include $(TOP)/Make.rules

LDLIBS=-lc -lgcc
CFLAGS+=-O2

#LDFLAGS+=-Wl,--no-relax
LDFLAGS+=-Wl,-T,riscv32-virt.ld

PROGS=prog prog.lst

all:: $(PROGS)

prog: crt0.o crt1.o main.o
	$(LINK.c) -o $@ $^ $(LDLIBS)
	$(SIZE) -A -x $@

clean::
	rm -f $(PROGS) *.o *.s *.lst
