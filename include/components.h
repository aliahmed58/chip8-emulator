#include "timer.h"
#include <stdint.h>

extern uint16_t pc_reg;
extern uint16_t i_reg;
extern uint8_t d_timer;
extern uint8_t s_timer;
extern uint8_t gp_regs[16];
extern uint8_t delay_timer;
extern uint8_t sound_timer;

void init_chip8_components();

void free_mem();
