#include "../include/components.h"
#include "../include/instructions.h"
#include "../include/renderer.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {

  struct SDL_struct sdl_struct;
  sdl_struct.sdl_init = sdl_init;
  sdl_struct.sdl_init(&sdl_struct, 512, 512, "something");

  init_chip8_components();
  print_mem();

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

    draw(sdl_struct.renderer);
    SDL_RenderPresent(sdl_struct.renderer);
  }

  free_mem();
  SDL_DestroyRenderer(sdl_struct.renderer);
  SDL_DestroyWindow(sdl_struct.window);

  SDL_Quit();
}
