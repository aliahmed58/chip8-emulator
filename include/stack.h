#pragma once
// struct to store the stack of program
#include <string.h>
typedef struct stack {
  short stack_arr[16];
  short top;
  int (*push)(struct stack *self, short data);
  short (*pop)(struct stack *self);
} stack;

extern stack prg_stack;

// constructor for the stack
void init_stack(stack *s);

// push data into stack
// returns 0 if success else 1
int push(stack *self, short data);

// pop data from stack
// returns -1 if stack empty
short pop(stack *self);
