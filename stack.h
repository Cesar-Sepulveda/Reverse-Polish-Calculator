//
//  stack.h
//  rpn
//
//  Created by William McCarthy on 2/18/19.
//  Copyright © 2019 William McCarthy. All rights reserved.
//

#ifndef stack_h
#define stack_h

#include <stdio.h>

#define MAXVAL 100

typedef struct stack stack;
struct stack {
  int sp;
  double val[MAXVAL];
};

void stack_clear(stack* st);     // clears entire stack

void stack_duplicatetop(stack* st);  // duplicates top of stack

double stack_empty(stack* st);  // checks if stack is empty

void stack_init(stack* st);  // initializes array and stack pointer

double stack_pop(stack* st);  // pops top value off stack and returns it (NOT like the STL)

void stack_push(stack* st, double f);  // pushes a value onto the stack

size_t stack_size(stack* st);  // gets size of stack

void stack_swap(stack* st);    // swaps top two elements of the stack

double stack_top(stack* st);   // returns top stack element without popping it (like the STL)


#endif /* stack_h */
