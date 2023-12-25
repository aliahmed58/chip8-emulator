#include <SDL3/SDL.h>
typedef struct Timer {
  // time of start and time of pause
  Uint32 start_ticks;
  Uint32 paused_ticks;

  // timer status
  SDL_bool paused;
  SDL_bool started;

  // actions of timer
  void (*start)(struct Timer *self);
  void (*stop)(struct Timer *self);
  void (*pause)(struct Timer *self);
  void (*unpause)(struct Timer *self);

  // get current time ticks
  Uint32 (*get_ticks)(struct Timer *self);

} Timer;

void init_timer(Timer *timer);

void start(Timer *self);
void stop(Timer *self);
void pause(Timer *self);
void unpause(Timer *self);
Uint32 get_ticks(Timer *self);
