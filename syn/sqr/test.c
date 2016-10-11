#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <float.h>
#include <klee/klee.h>

int main(int argc, char** argv) {
	(void)argc;
	(void)argv;

#if defined(ENABLE_FLOAT)
	{
		puts("\nrunning float test...\n");
		printf("sizeof(float): %zu\n", sizeof(float));
		puts("");

		float f;
		klee_make_symbolic(&f, sizeof(f), "f");
		klee_assume(f == f);
		float a = fabsf(f);
		float b = sqrtf(f*f);
#if defined(ENABLE_FLOW)
		assert(b == INFINITY || b == 0 || (a * 0.99 <= b && a >= b * 0.99) && "this should pass...");
#else
		assert(a * 0.99 <= b && a >= b * 0.99 && "this should have an error path...");
#endif
		assert(a == b && "this should have an error path");
	}
#endif

#if defined(ENABLE_DOUBLE)
	{
		puts("\nrunning double test...");
		printf("sizeof(double): %zu\n", sizeof(double));
		puts("");

		double f;
		klee_make_symbolic(&f, sizeof(f), "f");
		klee_assume(f == f);
		double a = fabs(f);
		double b = sqrt(f*f);
#if defined(ENABLE_INFINITY)
		assert(b == INFINITY || (a * 0.99 <= b && a >= b * 0.99) && "this should pass...");
#else
		assert(a * 0.99 <= b && a >= b * 0.99 && "this should have an error path...");
#endif
		assert(a == b && "this should have an error path");
	}
#endif

#if defined(ENABLE_LONGDOUBLE)
	{
		puts("\nrunning long double test...");
		printf("sizeof(long double): %zu\n", sizeof(long double));
		puts("");

		long double f;
		klee_make_symbolic(&f, sizeof(f), "f");
		klee_assume(f == f);
		long double a = fabsl(f);
		long double b = sqrtl(f*f);
#if defined(ENABLE_INFINITY)
		assert(b == INFINITY || (a * 0.99 <= b && a >= b * 0.99) && "this should pass...");
#else
		assert(a * 0.99 <= b && a >= b * 0.99 && "this should have an error path...");
#endif
		assert(a == b && "this should have an error path");
	}
#endif
}
