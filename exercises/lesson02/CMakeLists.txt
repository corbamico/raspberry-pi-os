cmake_minimum_required(VERSION 3.13.4)
project(kernel.elf C ASM)

set(all_src src/printf.c
            src/mini_uart.c
            src/kernel.c
            src/mm.S
            src/boot.S
            src/utils.S
            )


add_executable(kernel8.elf ${all_src})

if(CONFIG_QEMU)
    set(link_opt -T${PROJECT_SOURCE_DIR}/src/linker.qemu.ld)
else(CONFIG_QEMU)
    set(link_opt -T${PROJECT_SOURCE_DIR}/src/linker.ld)
endif(CONFIG_QEMU)


target_include_directories(kernel8.elf PUBLIC include)
target_compile_options(kernel8.elf PUBLIC -MMD -nostdlib -nostartfiles -ffreestanding 
    #-mgeneral-regs-only
    )
target_link_options(kernel8.elf PUBLIC ${link_opt})

add_custom_target(kernel8.img ALL
    COMMAND ${CMAKE_OBJCOPY} kernel8.elf -O binary kernel8.img
    DEPENDS kernel8.elf    
)

add_custom_target(run
    COMMAND qemu-system-aarch64 -machine raspi3 -serial null -serial mon:stdio -nographic -kernel kernel8.img 
)


