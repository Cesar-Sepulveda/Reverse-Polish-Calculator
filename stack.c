//
//  stack.c
//  rpn
//
//  Created by William McCarthy on 2/18/19.
//  Copyright © 2019 William McCarthy. All rights reserved.
//

#include <stdlib.h>
#include <string.h>

#include "stack.h"


int stack_check_underflow(stack* st) {
  return st->sp < 0 ? 1 : 0;
}

int stack_check_overflow(stack* st) {
  return st->sp >= MAXVAL ? 1 : 0;
}

void stack_clear(stack* st) {
  while (!stack_empty(st)) {
    stack_pop(st);
  }
}

void stack_duplicatetop(stack* st) {  // duplicates top of stack
  double top = stack_pop(st);
  stack_push(st, top);
  stack_push(st, top);
}

double stack_empty(stack* st) { return stack_size(st) == 0; }

void stack_init(stack* st) {
  st->sp = 0;
  memset(st->val, 0, MAXVAL * sizeof(double));
}

double stack_pop(stack* st) {
  if (stack_check_underflow(st)) {
    fprintf(stderr, "error: stack empty\n");
    return 0.0;
  }
  return st->val[--st->sp];
}

void stack_push(stack* st, double f) {
  if (stack_check_overflow(st)) {
    fprintf(stderr, "error: stack full, can\'t push %g\n", f);
    return;
  }
  st->val[st->sp++] = f;
}

size_t stack_size(stack* st) { return st->sp; }

void stack_swap(stack* st) {          // swaps top two elements
  double top = stack_pop(st);
  double second = stack_pop(st);
  stack_push(st, top);
  stack_push(st, second);
}

double stack_top(stack* st) {
  if (stack_empty(st)) {
    printf("error: stack empty\n");
    return 0.0;
  }
  return st->val[st->sp - 1];
}


