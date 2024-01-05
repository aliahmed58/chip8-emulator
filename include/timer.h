#pragma once
#include <SDL3/SDL.h>
#include <stdint.h>
typedef struct Timer {
  // time of start and time of pause
  uint8_t start_ticks;
  uint8_t paused_ticks;
  uint8_t interval;
  Uint32 seen;

  // timer status
  SDL_bool paused;
  SDL_bool started;

  // actions of timer
  void (*start)(struct Timer *self);
  void (*stop)(struct Timer *self);
  void (*pause)(struct Timer *self);
  void (*unpause)(struct Timer *self);

  // get current time ticks
  uint8_t (*get_ticks)(struct Timer *self);

} Timer;

void init_timer(Timer *timer);

void start(Timer *self);
void stop(Timer *self);
void pause(Timer *self);
void unpause(Timer *self);
uint8_t get_ticks(Timer *self);
