#include <assert.h>
#include <stdio.h>
#include <klee/klee.h>

int main(int argc, char** argv) {
	double d;
	klee_make_symbolic(&d, sizeof(d), "d");
	klee_assume(d == d);

	// division by 2 is exact
	if(d == 0.5) {
		assert(d == 0.5);
		assert(d / 2 == 0.25);
	} else {
		assert(d != 0.5);
		assert(d / 2 != 0.25);
	}
}
