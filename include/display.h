#include <SDL3/SDL.h>
#include <stdint.h>
#include <stdlib.h>
#define SDL_WIDTH 1024
#define SDL_HEIGHT 512
#define DISPLAY_WIDTH 64
#define DISPLAY_HEIGHT 32
#define R 251
#define G 234
#define B 235
#define SCALE_X (SDL_WIDTH / DISPLAY_WIDTH)
#define SCALE_Y (SDL_HEIGHT / DISPLAY_HEIGHT)

extern uint16_t *display;

// for debug purposes
void print_array();

// Initialize display and allocate memory
void init_display();

// write to display buffer
void wt_d_buffer(uint8_t *memory, uint8_t *vf, int vx, int vy, uint8_t N,
                 uint16_t I);

// draw on SDL screen using renderer
void draw(SDL_Renderer *renderer);
