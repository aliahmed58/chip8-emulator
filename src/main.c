#include "../include/components.h"
#include "../include/instructions.h"
#include "../include/renderer.h"
#include "../include/timer.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// conver char to literal hex instead of normal conversion
uint8_t char_to_hex(char key);

int main(int argc, char *argv[]) {

  struct SDL_struct sdl_struct;
  sdl_struct.sdl_init = sdl_init;
  sdl_struct.sdl_init(&sdl_struct, SDL_WIDTH, SDL_HEIGHT, "something");

  init_chip8_components();
  load_rom("../res/quirks.ch8", memory + 0x200);
  uint8_t key_press = 0xAB;
  uint8_t key_release = 0xAB;

  while (1) {
    int finished = 0;
    SDL_Event event;
    printf("pc_reg: %d\n", pc_reg);

    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        finished = 1;
        break;
      } else if (event.type == SDL_EVENT_KEY_DOWN) {
        char input = (char)event.key.keysym.sym;
        printf("%c\n", input);
        key_press = char_to_hex(input);

      } else if (event.type == SDL_EVENT_KEY_UP) {
        key_press = 0xAB;
        char input = (char)event.key.keysym.sym;
        printf("%c\n", input);
        key_release = char_to_hex(input);
      }
    }

    if (finished == 1) {
      break;
    }

    // fetch decode execute
    uint8_t out[2] = {0};

    fetch(out);
    decode_execute(out, key_press, key_release);
    // reset key_released to invalid key state so it changes
    key_release = 0xAB;

    // Clear screen
    SDL_SetRenderDrawColor(sdl_struct.renderer, 47, 60, 126, 0xFF);
    SDL_RenderClear(sdl_struct.renderer);

    draw(sdl_struct.renderer);
    SDL_RenderPresent(sdl_struct.renderer);
  }

  SDL_DestroyRenderer(sdl_struct.renderer);
  SDL_DestroyWindow(sdl_struct.window);
  SDL_Quit();
  free_mem();
}

uint8_t char_to_hex(char key) {
  // 0 - 9 in char = 48 - 57
  // key - 48 gives the value
  if (key >= 48 && key <= 57) {
    return (uint8_t)key - 48;
  }
  // a - f in char = 97 - 102
  // key - 87 gives the corresponding value
  else if (key >= 97 && key <= 102) {
    return (uint8_t)key - 87;
  } else
    return 0xAB;
}
