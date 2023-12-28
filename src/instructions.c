#include "../include/instructions.h"
#include <stdint.h>

uint16_t fetch() {
  // check if pc_reg is in range of memory
  uint8_t byte_1 = memory[pc_reg];
  pc_reg++;
  uint8_t byte_2 = memory[pc_reg];
  pc_reg++;

  uint16_t complete = (uint16_t)byte_1;
  complete = (complete << 8) | byte_2;
  return complete;
}
