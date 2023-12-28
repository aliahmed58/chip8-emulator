#include "../include/stack.h"
#include "../include/memory.h"
#include "../include/components.h"
#include "../include/display.h"
#include <stdio.h>

// Fetch -> Decode -> Execute cycle
// Fetch 2 bytes from memory, increment PC by 2 and return the bytes
uint16_t fetch();

// Decode and execute
void decode_execute(uint16_t instruction);

// Instruction set defined below

// 00E0 - Clear Screen
void op_00E0();

// 1NNN - Jump
void op_1NNN(uint16_t NNN);

// 6XNN - Set register VX
void op_6XNN(uint16_t NN);

// 7XNN - Add value to register VX
void op_7XNN(uint8_t NN);

// ANNN - Set index register I
void op_ANNN(uint16_t NNN);

// DXYN - Draw screen buffer
void op_DXYN();
