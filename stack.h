#ifndef stack_h
#define stack_h

#include <stdio.h>

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

void push(double f);

double pop(void);

void print_top();

void clear();

void swap_stack();

void duplicate_top()

#endif 
