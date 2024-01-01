#include "../include/stack.h"
#include <stdio.h>
#include <string.h>

Stack stack_reg;

void show(Stack *s) {
  for (int i = 0; i < 16; i++) {
    printf("%d ", s->stack_arr[i]);
  }
  printf("\n");
}

int push(Stack *self, short data) {
  self->stack_arr[self->top] = data;
  self->top++;
  return 1;
}

short pop(Stack *self) {

  short data = self->stack_arr[self->top];
  self->top--;
  return data;
}

void init_stack(Stack *s) {
  printf("stack initalized\n");
  memset(s->stack_arr, 0, sizeof(s->stack_arr));
  s->top = 0;
  s->push = push;
  s->pop = pop;
}
