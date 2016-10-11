#include <stdio.h>
#include <klee/klee.h>
#include <assert.h>

typedef struct struc {
	int a;
	double b;
} struc;

void f(struc*, int, double);

int main(int argc, char** argv) {
	int i;
	klee_make_symbolic(&i, sizeof(i), "i");
	double d;
	klee_make_symbolic(&d, sizeof(d), "d");
	klee_assume(d == d);

	struc x = {.a = i, .b = d};
	f(&x, i, d);
}

void f(struc* s, int i, double d) {
	assert(s->a == i);
	assert(s->b == d);
}
