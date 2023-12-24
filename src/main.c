#include <SDL2/SDL.h>
#include "../include/renderer.h"

int main(int argc, char *argv[])
{
    struct SDL_struct sdl_struct;
    sdl_struct.sdl_init = sdl_init;
    sdl_struct.sdl_init(&sdl_struct, 500, 500, "something");

    while (1)
    {
        int finished = 0;
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                finished = 1;
                break;
            }
        }
        if (finished)
        {
            break;
        }

        SDL_SetRenderDrawColor(sdl_struct.renderer, 255, 255, 255, 255);
        SDL_RenderClear(sdl_struct.renderer);
        SDL_RenderPresent(sdl_struct.renderer);
    }

    SDL_DestroyRenderer(sdl_struct.renderer);
    SDL_DestroyWindow(sdl_struct.window);

    SDL_Quit();
}
