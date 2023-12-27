#include "../include/display.h"
#include "../include/memory.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

uint16_t *display;

void init_display() {
  // allocate memory for display and set it to 0 initially
  display =
      (uint16_t *)malloc(DISPLAY_WIDTH * DISPLAY_HEIGHT * sizeof(uint16_t));
  int size = DISPLAY_WIDTH * DISPLAY_HEIGHT * sizeof(uint16_t);
  memset(display, 0, size);
}

void print_array()  {
  for (int i = 0; i < 64; i ++) {
    for (int j = 0; j < 32; j ++ ) {
      printf("%d ", display[64 * j + i]);
    }
    printf("\n");
  }
}
void draw() {
  // test values
  int vx = 3, vy = 3;
  for (int i = 0x50; i < 0x55; i++) {
    short byte = memory[i];
    int bit, index;
    for (int bits = 7; bits >= 0; bits --) {
      bit = (byte >> bits) & 1;
      if (bit == 1) {
        index = 64 * vy + vx; 
        display[index] = 1;
      }

      vx ++;
    }
    vx = 3;
    vy ++;
  }
  print_array();
  
}
/*

int main() {
  init_display();
  init_memory();

  draw();

  for (int i = 0; i < 20; i ++) {
    for (int j = 0; j < 20; j ++) {
      printf("%d ", display[i]);
    }
    printf("\n");
  }

  free(memory);

  free(display);
}
*/
