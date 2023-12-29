# CHIP-8 Emulator

CHIP-8 Emulator implemented in C language using SDL3 for Graphics and Keyboard inputs.

## History

CHIP-8 was created by RCA engineer Joe Weisbecker in 1977 for the COSMAC VIP microcomputer. It was intended as a simpler way to make small programs and games for the computer. Instead of using machine language for the VIP’s CDP1802 processor, you could type in hexadecimal instructions (with the VIP’s hex keypad) that resembled machine code, but which were more high-level, and interpreted on the fly by a small program (the CHIP-8 emulator/interpreter).

## Architecture

The details of how CHIP-8 works can be found in [this guide](https://tobiasvl.github.io/blog/write-a-chip-8-emulator/#font).

However, the summary of CHIP-8 components is as follows:

    1. Memory - Direct access memory of 4096 (4KB), single word being 8 bit.
    2. Program Counter - PC, pointing at current instruction in memory
    3. Index Register - 16-bit I, pointing at various locations in memory
    4. Stack - 16-bit to call functions and return them
    5. Two 8-bit Timers - Sound and Delay
    6. Sixteen 8-bit General Purpose Registers - Called V0 to VF in Hex, VF used as a flag register

## Running
