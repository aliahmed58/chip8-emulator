#include <SDL3/SDL.h>
#include <stdint.h>
#include <stdlib.h>
#define DISPLAY_WIDTH 64
#define DISPLAY_HEIGHT 32
#define R 255
#define G 255
#define B 255
#define SCALE_X 8
#define SCALE_Y 16

extern uint16_t *display;

// for debug purposes
void print_array();

// Initialize display and allocate memory
void init_display();

// write to display buffer
void wt_d_buffer(uint8_t *memory, uint8_t *VF, int VX, int VY);

// draw on SDL screen using renderer
void draw(SDL_Renderer *renderer);
