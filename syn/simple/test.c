#include <stdio.h>
#include <assert.h>
#include <klee/klee.h>

int main(int argc, char** argv) {
	int i;
	int j;
	klee_make_symbolic(&i, sizeof(i), "i");
	klee_make_symbolic(&j, sizeof(j), "j");
	klee_assume(j >= 10);
	
	i = i + j;

	double d = (double) i;

	if(i == 0 && j == 11 && d != 0.3) {
		assert(0 && "this assertion should definitely trigger");
	} else {
		printf("Done");
	}
}
