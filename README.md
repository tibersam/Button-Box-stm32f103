# General
This Project is a simple box, that has 5 Buttons connected to it, that can light up. The task of the microcontroller is to collect push state of 4 buttons, the white one is directly connected to the lightcontroller, but not the light. It communicates over UART with lightcontroller and send updates of state to it. Receives instructions if Button LEDs should be put on. You can see here how to setup a project for stm32f1 series and how to program it, however it does not use many hardware features. Mainly i had it lying  around. 


# Setup
You need:
 - cmake
 - arm-none-eabi-gcc
 - arm-none-eabi-gdb
 - st-link (https://github.com/stlink-org/stlink)
 - libopencm3 (is a submodule, use git submodule init && git submodule update)

See startcmake to how to initialise the build system. Will create a build system.

# Build target
in the build directory use make to build project
make flash will build and flash firmware to microcontroller using st-link
make debug-server uses st-link to setup a remote gdb interface. in second terminal execute make debug to open gdb

