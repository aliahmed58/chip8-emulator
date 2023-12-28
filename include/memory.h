#pragma once
#include <stdint.h>
#define MEMORY_SIZE 0xFFF

extern uint8_t *memory;

// method to init memory with needed data in the start
void init_memory();

// method to add bytes to memory from start_index to end_index
int nbytes_tm(int start_index, int end_index, int b_size, short *bytes);

// method to load a .ch8 rom
int load_rom(char *filename, uint8_t *buffer);

// print memory for debugging
void print_mem();
