## 3.5: Exercises

1. Use local timer instead of the system timer to generate processor interrupts. See [this](https://github.com/s-matyukevich/raspberry-pi-os/issues/70) issue for details.
    >[answer]local timer is not supported in qemu, so we try to generic timer to do this. see [timer.c](src/timer.c) [generic_timer.S](src/generic_timer.S)   
1. Handle MiniUART interrupts. Replace the final loop in the `kernel_main` function with a loop that does nothing. Setup MiniUART device to generate an interrupt as soon as the user types a new character. Implement an interrupt handler that will be responsible for printing each newly arrived character on the screen.
    >[answer]see <code>void handle_irq_peripheral(void)</code>  [irq.c](src/irq.c)  
1. Adapt lesson 03 to run on qemu. Check [this](https://github.com/s-matyukevich/raspberry-pi-os/issues/8) issue for reference.
    >[answer]qemu boot from 0x80000, change it in [linker.qemu.ld](./src/linker.qemu.ld), and check CMakeLists.txt  
    >cmake -DCONFIG_QEMU=1 -DCMAKE_TOOLCHAIN_FILE=../cmake/aarch64-gcc-toolchain.cmake ..
    >qemu-system-aarch64 -machine raspi3 -serial null -serial mon:stdio -nographic -kernel kernel8.img 

