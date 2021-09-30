#!/bin/zsh

# this script is entirely untested, but is at least a tight list of what to do
# to get the riscv32 tools built and installed
# this is derived from https://github.com/johnwinans/riscv-toolchain-install-guide

emulate -LR zsh

git clone --depth 1 --shallow-submodules https://github.com/johnwinans/riscv-toolchain-install-guide riscv-tools

pushd riscv-tools

./instaldeps.sh
./setup.sh
./buildall.sh
export PATH=${HOME}/install/rv32i/bin:${PATH}
which qemu-system-riscv32
qemu-system-riscv32 --version
qemu-system-riscv32 -machine help

which riscv32-unknown-elf-as
riscv32-unknown-elf-as --version
riscv32-unknown-elf-gcc --version

popd
cp ~/.gdbinit ~/.gdbinit.bak
cp gdb-dashboard/.gdbinit ~

