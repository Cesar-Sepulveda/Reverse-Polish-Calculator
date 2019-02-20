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
	if (islower(c)) {
		while (islower(s[++i] = c = getch()));
		if (c != EOF) {
			ungetch(c);
		}
		s[i] = '\0';
		if (strlen(s) > 1) {
			return FUNC;
		}
		else {
			return c;
		}
	}
	s[i] = '\0';
	if (c != EOF) { ungetch(c); }
	return NUMBER;
}





int main() {
	int type;
	double op2;
	char s[MAXOP];
	printf("RNP Calculator:\n");
	double var_array[26];
	while ((type = getop(s)) != EOF) {
		switch (type) {
		case NUMBER:
			push(atof(s));
			break;
		//Exercise 4.5
		//-------------------------------------------------------------
		case FUNC:
			operation(s);
			break;
		//-------------------------------------------------------------
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
			//Exercise 4.3
			//-------------------------------------------------------------
		case '%':	
			op2 = pop();
			if (op2 != 0.0) {
				push(fmod(pop(), op2));
			}
			else {
				printf("error: zero modulus\n");
			}
			break;
			//-------------------------------------------------------------
		case '\n':
			printf("\t%.8g\n", pop());
			break;
		default:
			//Exercise 4.6
			//-------------------------------------------------------------
			if (type <= 'Z' && type >= 'A') {
				push(var_array[type - 'A']);
			}
			//-------------------------------------------------------------
			else {
				printf("error: unknown command %s\n", s);
			}
			break;
		}
	}
	return 0;
}
