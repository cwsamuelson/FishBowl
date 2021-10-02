
print:
  .cfi_startproc

  li      x5,0x10000000       // x5 = @ XS16550 transmitter holding register
2:
  la      x6,x10            // x6 = @ of null-terminated string to print

  // check if nothing to print
  lb      x7,0(x6)            // x7 = next byte to print from the string
  beq     x0,x7,2f            // if the character is \0 then we are done...

  // have something to print
1:
  sb      x7,0(x5)            // ...else write it to the THR 
  addi    x6,x6,1             // advance string pointer to the next character to print
  lb      x7,0(x6)            // x7 = next byte to print from the string
  bne     x0,x7,1b            // if the character is NOT \0 then keep going

2:
  jalr ra

  .cfi_endproc
