#include "../include/timer.h"
#include <SDL3/SDL_timer.h>

Uint32 get_ticks(Timer *self) {
  Uint32 time = 0;

  if (self->started == SDL_TRUE) {
    if (self->paused == SDL_TRUE) {
      time = self->paused_ticks;
    } else {
      time = SDL_GetTicks() - self->start_ticks;
    }
  }
  return time;
}

void start(Timer *self) {
  self->started = SDL_TRUE;
  self->paused = SDL_FALSE;

  self->start_ticks = SDL_GetTicks();
  self->paused_ticks = 0;
}

void stop(Timer *self) {
  self->started = SDL_FALSE;
  self->paused = SDL_FALSE;
  self->start_ticks = 0;
  self->paused_ticks = 0;
}

void pause(Timer *self) {
  if (self->started == SDL_TRUE && self->paused == SDL_FALSE) {
    self->paused = SDL_TRUE;

    self->paused_ticks = SDL_GetTicks() - self->start_ticks;
    self->start_ticks = 0;
  }
}

void unpause(Timer *self) {
  if (self->started == SDL_TRUE && self->paused == SDL_TRUE) {
    self->paused = SDL_FALSE;

    self->start_ticks = SDL_GetTicks() - self->paused_ticks;
    self->paused_ticks = 0;
  }
}

void init_timer(Timer *self) {
  self->start_ticks = 0;
  self->paused_ticks = 0;
  self->paused = SDL_FALSE;
  self->started = SDL_FALSE;

  self->start = start;
  self->pause = pause;
  self->stop = stop;
  self->unpause = unpause;
  self->get_ticks = get_ticks;
}
