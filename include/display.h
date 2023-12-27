#include <stdint.h>
#include <stdlib.h>
#define DISPLAY_WIDTH 64
#define DISPLAY_HEIGHT 32

extern uint16_t *display;

void init_display();
void draw();
