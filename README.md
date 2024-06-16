# xv6-from-scratch

Here is a simple plan for building xv6-riscv from scratch, which will be continuously refined and supplemented as the project progresses:

- [ ] `Stage-1 Basic Execution Environment`: Isolate applications from hardware. An operating system with this functionality resembles a function library, which can be accessed by applications and uses the library's functions to access hardware.
    - [ ] `mini-SBI`: We need a minimal SBI implementation to boot the OS and provide it with some runtime services.
    - [ ] `printf`: We will output characters through the serial port, so we need to implement the printf function from scratch, which includes a UART driver.
