#include "../include/memory.h"
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint8_t *memory;
// method initalizes memory with font and needed initial stuff
void init_memory() {
  memory = (uint8_t *)malloc(MEMORY_SIZE * sizeof(uint8_t));
  // the only usable memory starts after address 0x200 according to old
  // conventions
  int memory_size = MEMORY_SIZE * sizeof(uint8_t);
  memset(memory, 0, memory_size);
  // set font in memory
  short font_hex[80] = {
      0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
      0x20, 0x60, 0x20, 0x20, 0x70, // 1
      0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
      0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
      0x90, 0x90, 0xF0, 0x10, 0x10, // 4
      0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
      0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
      0xF0, 0x10, 0x20, 0x40, 0x40, // 7
      0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
      0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
      0xF0, 0x90, 0xF0, 0x90, 0x90, // A
      0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
      0xF0, 0x80, 0x80, 0x80, 0xF0, // C
      0xE0, 0x90, 0x90, 0x90, 0xE0, // D
      0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
      0xF0, 0x80, 0xF0, 0x80, 0x80  // F
  };
  int font_array_size = sizeof(font_hex);
  nbytes_tm(0x50, 0x9F, font_array_size, font_hex);
}

int load_rom(char *f_name, uint8_t *buffer) {
  FILE *file;
  int file_size;

  // open file stream in binary read-only mode
  file = fopen(f_name, "rb");
  if (file == NULL) {
    printf("File not found. error number: %s\n", strerror(errno));
    exit(-1);
    return -1;
  } else {
    // find file size and load program
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    printf("ROM size: %d\n", file_size);
    rewind(file);

    fread(buffer, 1, file_size, file);
    return 0;
  }
}

int nbytes_tm(int start_index, int end_index, int b_size, short *bytes) {

  int b_counter = 0;
  for (int i = start_index; i < end_index; i++) {
    if (b_counter >= b_size) {
      break;
    }
    memory[i] = bytes[b_counter];
    b_counter++;
  }
  return 0;
}

void print_mem() {

  for (int i = 0; i < MEMORY_SIZE * sizeof(uint8_t); i++) {
    printf("%x ", memory[i]);
    if (i % 5 == 0)
      printf("\n");
  }
}
