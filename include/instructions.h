#include "../include/components.h"
#include "../include/display.h"
#include "../include/memory.h"
#include "../include/stack.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern int instruction_count;

// Fetch -> Decode -> Execute cycle
// Fetch 2 bytes from memory, increment PC by 2 and return the bytes
uint8_t *fetch(uint8_t *out);

// Decode and execute
void decode_execute(uint8_t *instr_arr, uint8_t key_press, uint8_t key_release);

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
void op_8XY7(uint8_t VX, uint8_t VY);

// 8XY6 - Shift 1 bit right VX
void op_8XY6(uint8_t VX, uint8_t VY);

// 8XYE - Shift 1 bit right VX
void op_8XYE(uint8_t VX, uint8_t VY);

// 9XY0 - Skip if VX != VY
void op_9XY0(uint8_t VX, uint8_t VY);

// ANNN - Set index register I
void op_ANNN(uint16_t NNN);

// BNNN - Jump with Offset PC = NNN + V0
void op_BNNN(uint16_t NNN);

// CXNN - VX = Random AND with NN
void op_CXNN(uint8_t NN, uint8_t VX);

// EX9E - Skip if Key
void op_EX9E(uint8_t VX, uint8_t key_press);

// EXA1 - SKip if key
void op_EXA1(uint8_t VX, uint8_t key_press);

// FX0A - Get Key
void op_FX0A(uint8_t VX, uint8_t key_press, uint8_t key_release);

// FX07 - Set VX = delay timer
void op_FX07(uint8_t VX);

// FX15 - Set delay timer = VX
void op_FX15(uint8_t VX);

// FX18 - Set Sound timer = VX
void op_FX18(uint8_t VX);

// FX1E - Add to Index I += VX, VF = 1 if I > 0XFFF
void op_FX1E(uint8_t VX);

// FX29 - Font Character
void op_FX29(uint8_t VX);

// FX33 - BCD conversion
void op_FX33(uint8_t VX);

// FX55 - Store in Memory from V0 to VX
void op_FX55(uint8_t VX);

// FX65 - Load to registers from memory
void op_FX65(uint8_t VX);

// DXYN - Draw screen buffer
void op_DXYN(uint8_t X, uint8_t Y, uint8_t N);
