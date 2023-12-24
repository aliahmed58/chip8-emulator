#include "../include/renderer.h"

void sdl_init(struct SDL_struct* sdl_struct, int screen_width, int screen_height, char* title)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        SDL_Log("SDL_Init failed (%s)", SDL_GetError());
        return;
    }

    if (SDL_CreateWindowAndRenderer(screen_width, screen_height, 0, &sdl_struct->window, &sdl_struct->renderer) < 0)
    {
        SDL_Log("SDL_CreateWindowAndRenderer failed (%s)", SDL_GetError());
        SDL_Quit();
        return;
    }
    SDL_SetWindowTitle(sdl_struct->window, "SDL issue");
};

