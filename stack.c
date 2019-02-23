#include <stdlib.h>
#include <string.h>

#include "stack.h"

void push(double f) {
	if (sp < MAXVAL) {
		val[sp++] = f;
	}
	else {
		printf("error: stack full, can't push %g\n", f);
	}
}

double pop(void) {
	if (sp > 0) {
		return val[--sp];
	}
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

//Exercise 4.4
//-----------------------------------------------------------
void print_top(){
	double print = val[sp];
	printf("%g", print);
}

void clear() {
	sp = 0;
}

void swap_stack() {
	double val1, val2;
	val1 = pop();
	val2 = pop();
	push(val1);
	push(val2);
}

void duplicate_top() {
	double top = pop();
	push(top);
	push(top);
}
//-----------------------------------------------------------
