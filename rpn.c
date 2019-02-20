//
//  main.c
//  rpn
//
//  Created by William McCarthy on 2/18/19.
//  Copyright © 2019 William McCarthy. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "stack.h"

#define MAXOP     100

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

#define NUMBER '0'

double atof(char s[]) {	//Exercise 4.2
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


int getch(void) {
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
	if (bufp >= BUFSIZE) {
		printf("ungetch: too many characters\n");
	}
	else {
		buf[bufp++] = c;
	}
}

int getop(char s[]) {
	int i, c;
	while ((s[0] = c = getch()) == ' ' || c == '\t');
	s[1] = '\0';
	if (!isdigit(c) && c != '.') { return c; }
	i = 0;
	if (isdigit(c)) {
		while (isdigit(s[++i] = c = getch()));
	}
	if (c == '.') {
		while (isdigit(s[++i] = c = getch()));
	}
	s[i] = '\0';
	if (c != EOF) { ungetch(c); }
	return NUMBER;
}


int main(int argc, const char * argv[]) {
  int type, intop2;
  double op2;
  char s[MAXOP];
  stack st;
  stack_init(&st);
  
  printf("//------------------ RPN CALCULATOR -----------------\n");
  printf("Enter expression: ");
  
  while ((type = getop(s)) != EOF) {
    switch(type) {
    case NUMBER:
        stack_push(&st, atof(s));
        break;
    case '+':
        stack_push(&st, stack_pop(&st) + stack_pop(&st));
        break;
    case '*':
        stack_push(&st, stack_pop(&st) * stack_pop(&st));
        break;
    case '-':
        op2 = stack_pop(&st);
        stack_push(&st, stack_pop(&st) - op2);
        break;
    case '/':
      op2 = stack_pop(&st);
      if (op2 != 0.0) {
        stack_push(&st, stack_pop(&st) / op2);
      } else {
        printf("error: zero divisor\n");
      }
      break;
//-----------------------------------------------------------------------------
    case '%':		//Exercise 4.3
      intop2 = (int)stack_pop(&st);
      if (intop2 != 0.0) {
        stack_push(&st, (int)stack_pop(&st) % intop2);
      } else {
        printf("error: zero modulus divisor\n");
      }
      break;
//-----------------------------------------------------------------------------   
	case '~':
      stack_push(&st, -1 * stack_pop(&st));
      break;
    case '\n':
        printf("\t%.8g\n", stack_pop(&st));
        break;
    default:
        printf("error: unknown command: %s\n", s);
        break;
    }
  }
  
  return 0;
}
