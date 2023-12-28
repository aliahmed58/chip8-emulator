#include "../include/components.h"
#include "../include/display.h"
#include "../include/memory.h"
#include "../include/stack.h"
#include <stdint.h>
#include <string.h>

uint16_t pc_reg;
uint16_t i_reg;
uint8_t gp_regs[16];

// initalize all components needed
void init_chip8_components() {
  init_memory();
  init_display();
  init_stack(&stack_reg);
  uint16_t pc_reg = 0;
  uint16_t i_reg = 0;
  uint8_t gp_regs[16];
  memset(&gp_regs, 0, 16);
}

// free allocated memory for memory and display buffers
void free_mem() {
  free(memory);
  free(display);
}
