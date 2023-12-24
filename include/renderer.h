#pragma once
#include <SDL3/SDL.h>

typedef struct SDL_struct {
    SDL_Renderer* renderer;
    SDL_Window* window;

    void (*sdl_init)(struct SDL_struct* sdl_struct, int screen_width, int screen_height, char* title);
} SDL_struct;

void sdl_init(struct SDL_struct* sdl_struct, int screen_width, int screen_height, char* title);