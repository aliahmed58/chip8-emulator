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

// 1NNN - Jump
void op_1NNN(uint16_t NNN);

// 6XNN - Set register VX
void op_6XNN(uint8_t NN, uint8_t X);

// 7XNN - Add value to register VX
void op_7XNN(uint8_t NN, uint8_t X);

// ANNN - Set index register I
void op_ANNN(uint16_t NNN);

// DXYN - Draw screen buffer
void op_DXYN(uint8_t X, uint8_t Y, uint8_t N);
