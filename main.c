#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

#define MAXOP 100
#define NUMBER '0'

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int strindex(const char * s, const char* t) {
	char * u = strstr(s, t);
	return u == NULL ? -1 : u - s;
}

int strrindex(const char * s, const char* t) { //Exercise 4.1
	char* prev = NULL;
	char * u = s;
	while ((u = strstr(u, t)) != NULL) {
		prev = u;
		++u;
	}
	return prev == NULL ? -1 : prev - s;
}

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
		return 0.0; } 
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





int main() {
	int type;       
	double op2;       
	char s[MAXOP];
	while ((type = getop(s)) != EOF) {
		switch (type) { 
		case NUMBER:               
			push(atof(s));               
			break;           
		case '+':               
			push(pop() + pop());               
			break;           
		case '*':               
			push(pop() * pop());               
			break;           
		case '-':               
			op2 = pop();               
			push(pop() - op2);               
			break;           
		case '/':               
			op2 = pop();               
			if (op2 != 0.0) {
				push(pop() / op2);
			}
			else {
				printf("error: zero divisor\n");
			}
			break;           
		case '\n':               
			printf("\t%.8g\n", pop());               
			break;           
		default:               
			printf("error: unknown command %s\n", s);               
			break;
		}
	}       
	return 0;
}
