#include "../include/instructions.h"
#include <stdint.h>
#include <stdio.h>

int instruction_count = 0;

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

void decode_execute(uint8_t *instr_arr, uint8_t key_press,
                    uint8_t key_release) {
  instruction_count++;
  // reset instruction count every 700 instructions
  if (instruction_count == 700) {
    instruction_count = 0;
  }

  // for every 100 instructions decrement the timer once
  // to give it an effect wihout using computer time
  // used as an abstraction
  if (instruction_count % 100 == 0) {
    if (delay_timer > 0) {
      delay_timer--;
    }
    if (sound_timer > 0) {
      sound_timer--;
    }
  }
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
    switch (NN) {
    case 0xEE:
      op_00EE();
      break;
    case 0xE0:
      op_00E0();
      break;
    }
    break;
  case 0x1:
    // Jump PC to NNN
    op_1NNN(NNN);
    break;
  case 0x2:
    op_2NNN(NNN);
    break;
  case 0x3:
    op_3XNN(X, NN);
    break;
  case 0x4:
    op_4XNN(X, NN);
    break;
  case 0x5:
    op_5XY0(X, Y);
    break;
  case 0x6:
    // Set register VX to value NN
    op_6XNN(NN, X);
    break;
  case 0x7:
    // Add value NN to register VX
    op_7XNN(NN, X);
    break;
  case 0x8:
    switch (N) {
    case 0x0:
      op_8XYO(X, Y);
      break;
    case 0x1:
      op_8XY1(X, Y);
      break;
    case 0x2:
      op_8XY2(X, Y);
      break;
    case 0x3:
      op_8XY3(X, Y);
      break;
    case 0x4:
      op_8XY4(X, Y);
      break;
    case 0x5:
      op_8XY5(X, Y);
      break;
    case 0x6:
      op_8XY6(X, Y);
      break;
    case 0x7:
      op_8XY7(X, Y);
      break;
    case 0xE:
      op_8XYE(X, Y);
      break;
    }
    break;
  case 0x9:
    op_9XY0(X, Y);
    break;
  case 0xA:
    // Set index reigster I to value NNN
    op_ANNN(NNN);
    break;
  case 0xB:
    op_BNNN(NNN);
    break;
  case 0xC:
    op_CXNN(NN, X);
    break;
  case 0xD:
    // draw screen buffer on screen
    op_DXYN(X, Y, N);
    break;
  case 0xE:
    switch (NN) {
    case 0x9E:
      op_EX9E(X, key_press);
      break;
    case 0xA1:
      op_EXA1(X, key_press);
      break;
    }
    break;
  case 0xF:
    switch (NN) {
    case 0x07:
      op_FX07(X);
      break;
    case 0x0A:
      op_FX0A(X, key_press, key_release);
      break;
    case 0x15:
      op_FX15(X);
      break;
    case 0x18:
      op_FX18(X);
      break;
    case 0x29:
      op_FX29(X);
      break;
    case 0x1E:
      op_FX1E(X);
      break;
    case 0x55:
      op_FX55(X);
      break;
    case 0X33:
      op_FX33(X);
      break;
    case 0x65:
      op_FX65(X);
      break;
    }
    break;
  }
}

void op_00E0() { clear_buffer(); }

void op_00EE() { pc_reg = stack_reg.pop(&stack_reg); }

void op_1NNN(uint16_t NNN) { pc_reg = NNN; }

void op_2NNN(uint16_t NNN) {
  stack_reg.push(&stack_reg, pc_reg);
  pc_reg = NNN;
}

void op_3XNN(uint8_t VX, uint8_t NN) {
  if (gp_regs[VX] == NN) {
    pc_reg += 2;
  }
}

void op_4XNN(uint16_t VX, uint8_t NN) {
  if (gp_regs[VX] != NN) {
    pc_reg += 2;
  }
}

void op_5XY0(uint8_t VX, uint8_t VY) {
  if (gp_regs[VX] == gp_regs[VY]) {
    pc_reg += 2;
  }
}

void op_6XNN(uint8_t NN, uint8_t X) { gp_regs[X] = NN; }

void op_9XY0(uint8_t VX, uint8_t VY) {
  if (gp_regs[VX] != gp_regs[VY]) {
    pc_reg += 2;
  }
}
void op_7XNN(uint8_t NN, uint8_t X) { gp_regs[X] += NN; }

void op_8XYO(uint8_t VX, uint8_t VY) { gp_regs[VX] = gp_regs[VY]; }

void op_8XY1(uint8_t VX, uint8_t VY) { gp_regs[VX] |= gp_regs[VY]; }

void op_8XY2(uint8_t VX, uint8_t VY) { gp_regs[VX] &= gp_regs[VY]; }

void op_8XY3(uint8_t VX, uint8_t VY) { gp_regs[VX] ^= gp_regs[VY]; }

void op_8XY4(uint8_t VX, uint8_t VY) {
  uint8_t overflow_bit = (UINT8_MAX - gp_regs[VX] < gp_regs[VY]);
  uint8_t copy_x = gp_regs[VX];
  gp_regs[VX] += gp_regs[VY];
  gp_regs[0xF] = overflow_bit;
}

void op_8XY5(uint8_t VX, uint8_t VY) {
  uint8_t carry = (gp_regs[VX] >= gp_regs[VY]);
  gp_regs[VX] = gp_regs[VX] - gp_regs[VY];
  gp_regs[0xF] = carry;
}

void op_8XY7(uint8_t VX, uint8_t VY) {
  uint8_t carry = (gp_regs[VY] >= gp_regs[VX]);
  gp_regs[VX] = gp_regs[VY] - gp_regs[VX];
  gp_regs[0xF] = carry;
}

void op_8XY6(uint8_t VX, uint8_t VY) {
  uint8_t lsb = gp_regs[VX] & 1;
  gp_regs[VX] = gp_regs[VX] >> 1;
  gp_regs[0xF] = lsb;
}

void op_8XYE(uint8_t VX, uint8_t VY) {
  uint8_t msb = (gp_regs[VX] >> 7) & 1;
  gp_regs[VX] = gp_regs[VX] << 1;
  gp_regs[0xF] = msb;
}

void op_ANNN(uint16_t NNN) { i_reg = NNN; }

void op_BNNN(uint16_t NNN) { pc_reg = NNN + gp_regs[0x0]; }

void op_CXNN(uint8_t NN, uint8_t VX) {
  srand(time(NULL));
  int r = rand();
  uint8_t result = r & NN;
  gp_regs[VX] = result;
}

void op_EX9E(uint8_t VX, uint8_t key_press) {
  if (gp_regs[VX] == key_press) {
    pc_reg += 2;
  }
}

void op_EXA1(uint8_t VX, uint8_t key_press) {
  if (gp_regs[VX] != key_press) {
    pc_reg += 2;
  }
}

void op_FX0A(uint8_t VX, uint8_t key_press, uint8_t key_release) {
  if (key_release > 0xF) {
    pc_reg -= 2;
  } else {
    gp_regs[VX] = key_release;
  }
}

void op_FX07(uint8_t VX) { gp_regs[VX] = delay_timer; }

void op_FX15(uint8_t VX) { delay_timer = gp_regs[VX]; }

void op_FX18(uint8_t VX) { sound_timer = gp_regs[VX]; }

void op_FX1E(uint8_t VX) {
  if ((i_reg + gp_regs[VX]) > 0x0FFF) {
    gp_regs[0xF] = 1;
  }
  i_reg += gp_regs[VX];
}

void op_FX29(uint8_t VX) {
  int memory_index = 0x50 + gp_regs[VX] * 0x5;
  i_reg = memory[memory_index];
}

void op_FX33(uint8_t VX) {
  int i = 2;
  uint8_t copy = gp_regs[VX];
  while (copy != 0) {
    int bcd = copy % 10;
    memory[i_reg + i] = bcd;
    i--;
    copy /= 10;
  }
}

void op_FX55(uint8_t VX) {
  int offset = 0;
  for (int i = 0x0; i <= VX; i++) {
    memory[i_reg + offset] = gp_regs[i];
    offset++;
  }
}

void op_FX65(uint8_t VX) {
  int offset = 0;
  for (int i = 0x0; i <= VX; i++) {
    gp_regs[i] = memory[i_reg + offset];
    offset++;
  }
}

void op_DXYN(uint8_t X, uint8_t Y, uint8_t N) {
  uint8_t vx = gp_regs[X];
  uint8_t vy = gp_regs[Y];
  uint8_t *vf = &gp_regs[0xF];
  // call displays draw function here
  wt_d_buffer(memory, vf, vx, vy, N, i_reg);
}
