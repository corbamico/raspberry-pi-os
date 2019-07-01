# raspberry-pi-os
exercises for study github.com/s-matyukevich/raspberry-pi-os

## How to make

```shell
cd exercises/lesson01 && mkdir build && cd build
cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/aarch64-gcc-toolchain.cmake ..
make
make run
```
