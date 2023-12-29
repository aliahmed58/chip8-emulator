#include "../include/display.h"
#include <SDL3/SDL_render.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// declare display array pointer
uint8_t *display;

void init_display() {
  // allocate memory for display and set it to 0 initially
  int size = DISPLAY_WIDTH * DISPLAY_HEIGHT * sizeof(uint8_t);
  display = (uint8_t *)malloc(size);
  // check if memory is allocated correctly
  if (display == NULL) {
    printf("Display buffer allocation failed");
    exit(-1);
  }
  // set array to 0 initally - blank screen
  memset(display, 0, size);
}

void wt_d_buffer(uint8_t *memory, uint8_t *VF, int VX, int VY, uint8_t N,
                 uint16_t I) {
  int x = VX % 64;
  int y = VY % 32;
  *VF = 0;

  for (int i = I; i < N + I; i++) {
    uint8_t byte = memory[i];
    int bit, index;
    for (int bits = 7; bits >= 0; bits--) {
      // get individual bits from the byte
      bit = (byte >> bits) & 1;

      // calculate index for the display buffer
      index = 64 * y + x;
      if (display[index] == 1 && bit == 1) {
        *VF = 1;
      }

      // xor the operation to find out new pixel
      display[index] ^= bit;

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

void clear_buffer() {
  memset(display, 0, DISPLAY_HEIGHT * DISPLAY_WIDTH * sizeof(uint8_t));
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
