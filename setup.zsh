#!/bin/zsh

# this script is entirely untested, but is at least a tight list of what to do
# to get the riscv64 tools built and installed
# this is derived from https://github.com/johnwinans/riscv-toolchain-install-guide

emulate -LR zsh

git clone --depth 1 --shallow-submodules https://github.com/johnwinans/riscv-toolchain-install-guide riscv-tools

pushd riscv-tools || exit

./instaldeps.sh
./setup.sh
./buildall.sh
export PATH=${HOME}/install/rv64i/bin:${PATH}
which qemu-system-riscv64
qemu-system-riscv64 --version
qemu-system-riscv64 -machine help

which riscv64-unknown-elf-as
riscv64-unknown-elf-as --version
riscv64-unknown-elf-gcc --version
riscv64-unknown-elf-gdb --version

popd || exit
cp ~/.gdbinit ~/.gdbinit.bak
cp gdb-dashboard/.gdbinit ~
