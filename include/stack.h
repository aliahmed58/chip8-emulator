#pragma once
#include <stdio.h>
#include <string.h>
// struct to store the stack of program
typedef struct Stack {
  short stack_arr[16];
  short top;
  int (*push)(struct Stack *self, short data);
  short (*pop)(struct Stack *self);
} Stack;

extern Stack prg_stack;

// constructor for the stack
void init_stack(Stack *s);

// push data into stack
// returns 0 if success else 1
int push(Stack *self, short data);

// pop data from stack
// returns -1 if stack empty
short pop(Stack *self);
