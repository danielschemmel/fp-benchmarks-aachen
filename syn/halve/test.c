#include <assert.h>
#include <stdio.h>
#include <float.h>
#include <math.h>

#ifdef USE_KLEE
#include <klee/klee.h>
#endif

int main(int argc, char** argv) {
	(void)argc;
	(void)argv;

#ifdef ENABLE_FLOAT
	{
		puts("\nrunning float test...\n");
		printf("sizeof(float): %zu\n", sizeof(float));
		puts("");

		float f = 131, g;
		#if defined(USE_KLEE)
		klee_make_symbolic(&f, sizeof(f), "f");
		#endif
		klee_assume(f == f);
		g = f / 2;
		g *= 2;
#ifdef ENABLE_FLOW
		if(fabsf(f) < 2*FLT_MIN) {
			assert(fabsf(g) <= 2*FLT_MIN && "gotta love floating point arithmetic");
			return 0;
		}
#endif
		assert(f == g && "this should have an error path when underflow occurs");
	}
#endif

#ifdef ENABLE_DOUBLE
	{
		puts("\nrunning double test...");
		printf("sizeof(double): %zu\n", sizeof(double));
		puts("");

		double f = 131, g;
		#if defined(USE_KLEE)
		klee_make_symbolic(&f, sizeof(f), "f");
		#endif
		klee_assume(f == f);
		g = f / 2;
		g *= 2;
#ifdef ENABLE_FLOW
		if(fabs(f) < 2*DBL_MIN) {
			assert(fabs(g) <= 2*DBL_MIN && "gotta love floating point arithmetic");
			return 0;
		}
#endif
		assert(f == g && "this should have an error path when underflow occurs");
	}
#endif

#ifdef ENABLE_LONGDOUBLE
	{
		puts("\nrunning long double test...");
		printf("sizeof(long double): %zu\n", sizeof(long double));
		puts("");

		long double f = 131, g;
		#if defined(USE_KLEE)
		klee_make_symbolic(&f, sizeof(f), "f");
		#endif
		klee_assume(f == f);
		g = f / 2;
		g *= 2;
#ifdef ENABLE_FLOW
		if(fabsl(f) < 2*LDBL_MIN) {
			assert(fabsl(g) <= 2*LDBL_MIN && "gotta love floating point arithmetic");
			return 0;
		}
#endif
		assert(f == g && "this should have an error path when underflow occurs");
	}
#endif

	return 0;
}
