#include "../include/display.h"
#include <SDL3/SDL_render.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// declare display array pointer
uint16_t *display;

void init_display() {
  // allocate memory for display and set it to 0 initially
  int size = DISPLAY_WIDTH * DISPLAY_HEIGHT * sizeof(uint16_t);
  display = (uint16_t *)malloc(size);
  // check if memory is allocated correctly
  if (display == NULL) {
    printf("Display buffer allocation failed");
    exit(-1);
  }
  // set array to 0 initally - blank screen
  memset(display, 0, size);
}

// TODO: Get memory address start and end of byte from I,
// Change VF and do XOR operation between pixel bit and sprite bit.
void wt_d_buffer(uint8_t *memory, uint8_t *VF, int VX, int VY) {
  int x = VX;
  int y = VY;

  for (int i = 0x50; i < 0x55; i++) {
    short byte = memory[i];
    int bit, index;
    for (int bits = 7; bits >= 0; bits--) {
      bit = (byte >> bits) & 1;
      if (bit == 1) {
        index = 64 * y + x;
        display[index] = 1;
      }

      x++;
    }
    x = VX;
    y++;
  }
}

void draw(SDL_Renderer *renderer) {
  for (int x = 0; x < 64; x++) {
    for (int y = 0; y < 32; y++) {
      if (display[DISPLAY_WIDTH * y + x] == 1) {
        SDL_SetRenderDrawColor(renderer, R, G, B, 255);
        const SDL_FRect rect = {x * SCALE_X, y * SCALE_Y, SCALE_X, SCALE_Y};
        SDL_RenderFillRect(renderer, &rect);
      }
    }
  }
}

// print array
void print_array() {
  for (int x = 0; x < DISPLAY_WIDTH; x++) {
    for (int y = 0; y < DISPLAY_HEIGHT; y++) {
      printf("%d ", display[64 * y + x]);
    }
    printf("\n");
  }
}
