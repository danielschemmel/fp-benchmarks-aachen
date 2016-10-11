#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <float.h>

#ifdef USE_KLEE
#include <klee.h>
#endif

int main(int argc, char** argv) {
	(void)argc;
	(void)argv;

	{
		puts("\nrunning float test...\n");
		printf("sizeof(float): %zu\n", sizeof(float));
		puts("");

		char input[20];
		klee_make_symbolic(input, sizeof(input), "input");
		input[sizeof(input) - 1] = 0;
		float f = strtoll(input, NULL, 10);
		f = f*f*f;
		assert(!isnan(f) && "nan (should not happen)");
		assert(!isinf(f) && "inf");
		assert(!(f == 0) && "f == 0");
		assert(!(f > 1000) && "f > 0");
		assert(!(f > 0) && "f > 0");
		assert(!(f < -1000) && "f < 0");
		assert(!(f < 0) && "f < 0");
		assert(0 && "i missed something?");
	}

	{
		puts("\nrunning double test...");
		printf("sizeof(double): %zu\n", sizeof(double));
		puts("");

		#if defined(USE_KLEE)
		#endif
	}

	assert(0 && "unreachable");
}
