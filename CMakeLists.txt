# some of this can probably be replaced with CMake's cross-compiling mechanism?
# riscv.cmake?
# https://github.com/five-embeddev/riscv-scratchpad/blob/master/cmake/cmake/riscv.cmake
# not sure where this is stored locally, or how to access it correctly..

PROJECT(FishBowl)
CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

SET(CMAKE_TOOLCHAIN_FILE "riscv.cmake")

SET(QEMU_PATH "${CMAKE_CURRENT_LIST_DIR}/install/rv64i/bin/qemu-system-riscv64")

# SET(CMAKE_SYSTEM_NAME Generic)
# SET(CMAKE_SYSTEM_PROCESSOR rv64g)

SET(LINKER_SCRIPT "riscv64-virt.ld")

ADD_EXECUTABLE(${PROJECT_NAME} main.cc crt0.S)

# it seems this particular piece prevents ninja from working :(
# not sure what that's about
# ADD_CUSTOM_COMMAND(TARGET ${PROJECT_NAME}
#                    PRE_LINK
#                    COMMAND "riscv64-unknown-elf-ld --verbose > ${LINKER_SCRIPT}"
#                    USES_TERMINAL)

# if this is the same as the pre_link custom command, then maybe one could be removed
#  removing one might let ninja work again?
# idc right now until this works...
# set_target_properties(${PROJECT_NAME} PROPERTIES LINK_DEPENDS "${LINKER_SCRIPT}")
target_include_directories(${PROJECT_NAME} PRIVATE ../include/ )

# Linker control
#SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -nostartfiles -nostdlib -fno-exceptions -Xlinker --defsym=__stack_size=${STACK_SIZE} -T ${LINKER_SCRIPT} -Wl,-Map=${TARGET}.map")
CONFIGURE_FILE(${LINKER_SCRIPT} ${LINKER_SCRIPT})
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -nostartfiles -nostdlib -fno-exceptions -Xlinker -T ${LINKER_SCRIPT} -Wl,-Map=${TARGET}.map")

# need to find the correct run command
ADD_CUSTOM_TARGET("run_${PROJECT_NAME}"
                  COMMAND "${QEMU_PATH} "
                  DEPENDS "${PROJECT_NAME}"
                  USES_TERMINAL
                 )

SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES
                      CXX_STANDARD 20
                      CXX_STANDARD_REQUIRED YES
                      CXX_EXTENSIONS NO)
TARGET_COMPILE_FEATURES(${PROJECT_NAME} PUBLIC cxx_std_20)

TARGET_COMPILE_OPTIONS(${PROJECT_NAME} INTERFACE
                       $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
                           -Wall -Wextra -pedantic>
                       $<$<CXX_COMPILER_ID:MSVC>:
                           /W4>)

# auxiliary assists
ADD_CUSTOM_TARGET("device_tree_${PROJECT_NAME}"
                  COMMAND "${QEMU_PATH} -machine virt,dumpdtb=riscv64-virt.dtb && dtc riscv64-virt.dtb > riscv64-virt.dts"
                  DEPENDS "${PROJECT_NAME}"
                  USES_TERMINAL
                 )

