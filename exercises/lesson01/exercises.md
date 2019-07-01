## 1.5: Exercises.

Exercises are optional, though I strongly recommend you to experiment with the source code a little bit. If you were able to complete any of the exercises - please share your source code with others. 

1. Introduce a constant `baud_rate`, calculate necessary Mini UART register values using this constant. Make sure that the program can work using baud rates other than 115200.
    >[answer] see [peripherals/mini_uart.h](./include/peripherals/mini_uart.h)
2. Change the OS code to use UART device instead of Mini UART. Use `BCM2837 ARM Peripherals` manual to figure out how to access UART registers and how to configure GPIO pins.
    >[answer] see [peripherals/uart.h](./include/peripherals/uart.h) [./src/uart.c](./src/uart.c)
3. Try to use all 4 processor cores. The OS should print `Hello, from processor <processor index>` for all of the cores. Don't forget to set up a separate stack for each core and make sure that Mini UART is initialized only once. You can use a combination of global variables and `delay` function for synchronization.
    >[answer] see [src/boot.S](./src/boot.S) [src/kernel.c](./src/kernel.c)
4. Adapt lesson 01 to run on qemu. Check [this](https://github.com/s-matyukevich/raspberry-pi-os/issues/8) issue for reference.
    >[answer] see [CMakeLists.txt](./CMakeLists.txt)  
    qemu-system-aarch64 -m 128 -M raspi3 -cpu cortex-a57 -smp 4 ${qemu_opts} -nographic -kernel kernel8.img  
    but i cannot make "-smp 4" working on ubuntun docker in *Docker for Windows*

### make&run

```shell
cd exercises/lesson01 && mkdir build && cd build
cmake -DCONFIG_UART=1 -DCMAKE_TOOLCHAIN_FILE=../cmake/aarch64-gcc-toolchain.cmake ..
make
make run
```