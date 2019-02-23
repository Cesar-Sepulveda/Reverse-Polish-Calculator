#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "stack.h"

#define MAXOP 100
#define NUMBER '0'

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

#define FUNC 'n'
//Exercise 4.2
//----------------------------------------------------
double atof_(char s[]) {
	double val, power, sci;
	int i, sign;
	for (i = 0; isspace(s[i]); i++);
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-') { i++; }
	for (val = 0.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
	}
	if (s[i] == '.') { i++; }
	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10;
	}
	if (s[i] == 'e' || s[i] == 'E') { ++i; }
	for (sci = 1.0; isdigit(s[i]); ++i) {
		val = 10.0 * val + (s[i] - '0');
		sci *= 10;
	}

	return sign * val / power * sci;
}
//------------------------------------------------------


void operation(char s[]) {
	double op;
	if (strcmp(s, "sin") == 0) {
		push(sin(pop()));
	}
	else if (strcmp(s, "cos") == 0) {
		push(cos(pop()));
	}
	else if (strcmp(s, "tan") == 0) {
		push(tan(pop()));
	}
	else if (strcmp(s, "exp") == 0) {
		push(exp(pop()));
	}
	else if (strcmp(s, "pow") == 0) {
		op = pop();
		push(pow(pop(), op));
	}
	else {
		printf("error: invalid operation\n");
	}
}
