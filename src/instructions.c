#include "../include/instructions.h"
#include <stdint.h>

uint8_t *fetch(uint8_t *out) {
  // check if pc_reg is in range of memory
  uint8_t byte_1 = memory[pc_reg];
  pc_reg++;
  uint8_t byte_2 = memory[pc_reg];
  pc_reg++;

  out[0] = byte_1;
  out[1] = byte_2;

  return out;
}

void decode_execute(uint8_t *instr_arr) {
  uint8_t byte1 = instr_arr[0];
  uint8_t byte2 = instr_arr[1];
  uint16_t complete = (byte1 << 8) | byte2;
  uint8_t first_nibble = byte1 >> 4;

  // Decode X, Y, N, NN, NNN from these two bytes
  // X - second nibble from 16 bit number
  uint8_t X = byte1 & 0x0F;
  // Y - third nibble from 16 bit number
  uint8_t Y = byte2 >> 4;
  // N - fourth nibble from 16 bit number
  uint8_t N = byte2 & 0x0F;
  // NN - second byte from 16 bit number
  uint8_t NN = byte2;
  // NNN - second third and fourth nibble from 16 bit number
  uint16_t NNN = (X << 8) | byte2;

  switch (first_nibble) {
  // Instructions starting with 0
  case 0x0:
    // Clear screen - 0x00E0
    if (NNN == 0x0E0) {
      // clear display
      op_00E0();
    }
    break;
  case 0x1:
    // Jump PC to NNN
    op_1NNN(NNN);
    break;
  case 0x6:
    // Set register VX to value NN
    op_6XNN(NN, X);
    break;
  case 0x7:
    // Add value NN to register VX
    op_7XNN(NN, X);
    break;
  case 0xA:
    // Set index reigster I to value NNN
    op_ANNN(NNN);
    break;
  case 0xD:
    // draw screen buffer on screen
    op_DXYN(X, Y, N);
    break;
  default:
    break;
  }
}

void op_00E0() { clear_buffer(); }

void op_00EE() { pc_reg = stack_reg.pop(&stack_reg); }

void op_1NNN(uint16_t NNN) { pc_reg = NNN; }

void op_2NNN(uint16_t NNN) {
  pc_reg = NNN;
  stack_reg.push(&stack_reg, pc_reg);
}

void op_6XNN(uint8_t NN, uint8_t X) { gp_regs[X] = NN; }

void op_7XNN(uint8_t NN, uint8_t X) { gp_regs[X] += NN; }

void op_ANNN(uint16_t NNN) { i_reg = NNN; }

void op_DXYN(uint8_t X, uint8_t Y, uint8_t N) {
  uint8_t vx = gp_regs[X];
  uint8_t vy = gp_regs[Y];
  uint8_t *vf = &gp_regs[0xF];
  // call displays draw function here
  wt_d_buffer(memory, vf, vx, vy, N, i_reg);
}
