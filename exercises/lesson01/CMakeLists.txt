cmake_minimum_required(VERSION 3.13.4)
project(kernel.elf C ASM)

if(${CONFIG_UART})
    set(uart_src src/uart.c)
    set(qemu_opts -serial mon:stdio -serial null)    
else()
    set(uart_src src/mini_uart.c)
    set(qemu_opts -serial null -serial mon:stdio)
endif()  

if(CONFIG_QEMU)
    set(link_opt -T${PROJECT_SOURCE_DIR}/src/linker.qemu.ld)
else(CONFIG_QEMU)
    set(link_opt -T${PROJECT_SOURCE_DIR}/src/linker.ld)
endif(CONFIG_QEMU)

set(all_src src/boot.S
            src/mm.S
            src/utils.S
            ${uart_src}            
            src/kernel.c)


add_executable(kernel8.elf ${all_src})

target_include_directories(kernel8.elf PUBLIC include)
target_compile_options(kernel8.elf PUBLIC -MMD -nostdlib -nostartfiles -ffreestanding -mgeneral-regs-only)
target_link_options(kernel8.elf PUBLIC ${link_opt})

add_custom_target(kernel8.img ALL
    COMMAND ${CMAKE_OBJCOPY} kernel8.elf -O binary kernel8.img
    DEPENDS kernel8.elf    
)

add_custom_target(run
    COMMAND qemu-system-aarch64 -m 128 -M raspi3 -cpu cortex-a57 -smp 4 ${qemu_opts} -nographic -kernel kernel8.img     
)


