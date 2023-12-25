#include "../include/memory.h"
#include "../include/renderer.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {

  init_memory();

  // test values
  uint16_t VX = 0;
  uint16_t VY = 40;

  uint16_t display[64 * 32];
  int index = VX + 64 * VY;

  memset(display, 0, sizeof(display));
  for (int i = 0x50; i < 0x55; i++) {
    short byte = memory[i];
    short bit;
    for (int b = 7; b >= 0; b--) {
      bit = (byte >> b) & 1;
      if (bit == 1) {
        display[index] = 1;
      } else {
        display[index] = 0;
      }
      VX++;
      index = VX * 64 + VY;
    }
    VY++;
  }

  for (int i = 0; i < 64 * 32; i++) {
    // printf("%d ", display[i]);
    if (i % 10 == 0) {
      // printf("\n");
    }
  }

  struct SDL_struct sdl_struct;
  sdl_struct.sdl_init = sdl_init;
  sdl_struct.sdl_init(&sdl_struct, 500, 500, "something");

  while (1) {
    int finished = 0;
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        finished = 1;
        break;
      }
    }
    if (finished) {
      break;
    }

    // Clear screen
    SDL_SetRenderDrawColor(sdl_struct.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(sdl_struct.renderer);

    for (int x = 0; x < 64; x++) {
      for (int y = 0; y < 32; y++) {
        int index = x + 64 * y;
        if (display[index] == 1) {
          const SDL_FRect rect = {x, y, 10, 10};
          SDL_SetRenderDrawColor(sdl_struct.renderer, 255, 0, 0, 255);
          SDL_RenderFillRect(sdl_struct.renderer, &rect);
        }
      }
    }
    SDL_RenderPresent(sdl_struct.renderer);
  }

  SDL_DestroyRenderer(sdl_struct.renderer);
  SDL_DestroyWindow(sdl_struct.window);

  SDL_Quit();
}
