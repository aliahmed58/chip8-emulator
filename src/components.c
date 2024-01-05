#include "../include/components.h"
#include "../include/display.h"
#include "../include/memory.h"
#include "../include/stack.h"
#include <stdint.h>
#include <string.h>

uint16_t pc_reg;
uint16_t i_reg;
uint8_t gp_regs[16];
uint8_t delay_timer;
uint8_t sound_timer;

// initalize all components needed
void init_chip8_components() {
  init_memory();
  init_display();
  init_stack(&stack_reg);
  pc_reg = 0x200;
  i_reg = 0;
  delay_timer = 0;
  sound_timer = 0;
  memset(&gp_regs, 0, 16);
}

// free allocated memory for memory and display buffers
void free_mem() {
  free(memory);
  free(display);
}
