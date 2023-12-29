#include "../include/components.h"
#include "../include/display.h"
#include "../include/memory.h"
#include "../include/stack.h"
#include <stdint.h>
#include <stdio.h>

// Fetch -> Decode -> Execute cycle
// Fetch 2 bytes from memory, increment PC by 2 and return the bytes
uint8_t *fetch(uint8_t *out);

// Decode and execute
void decode_execute(uint8_t *instr_arr);

// Instruction set defined below

// 00E0 - Clear Screen
void op_00E0();

// 00EE - Return from Subroutine, pop last address out of stack
void op_00EE();

// 1NNN - Jump
void op_1NNN(uint16_t NNN);

// 2NNN - Add Subroutine to stack
void op_2NNN(uint16_t NNN);

// 3XNN - Skip if VX == NN
void op_3XNN(uint8_t VX, uint8_t NN);

// 4XNN - Skip if VX != NN
void op_4XNN(uint16_t VX, uint8_t NN);

// 5XY0 - Skip if VX == VY
void op_5XY0(uint8_t VX, uint8_t VY);

// 6XNN - Set register VX
void op_6XNN(uint8_t NN, uint8_t X);

// 7XNN - Add value to register VX
void op_7XNN(uint8_t NN, uint8_t X);

// Logical and Arithmetic Instructions
// 8XY0 - Set VX = VY
void op_8XYO(uint8_t VX, uint8_t VY);

// 8XY1 - Set VX = Binary OR of VX and VY
void op_8XY1(uint8_t VX, uint8_t VY);

// 8XY2 - Set in VX = Binary AND of VX and VY
void op_8XY2(uint8_t VX, uint8_t VY);

// 8XY3 - Set VX = Binary XOR of VX and VY
void op_8XY3(uint8_t VX, uint8_t VY);

// 8XY4 - Set VX = VX + VY
void op_8XY4(uint8_t VX, uint8_t VY);

// 8XY5 - Set VX = VX - VY
void op_8XY5(uint8_t VX, uint8_t VY);

// 8XY7 - Set VX = VY - VX

// 9XY0 - Skip if VX != VY
void op_9XY0(uint8_t VX, uint8_t VY);

// ANNN - Set index register I
void op_ANNN(uint16_t NNN);

// DXYN - Draw screen buffer
void op_DXYN(uint8_t X, uint8_t Y, uint8_t N);
