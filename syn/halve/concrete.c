#include <assert.h>
#include <stdio.h>
#include <float.h>

#ifdef USE_KLEE
#include <klee/klee.h>
#endif

int main(int argc, char** argv) {
	(void)argc;
	(void)argv;

	{
		puts("\nrunning float test...\n");
		printf("sizeof(float): %zu\n", sizeof(float));
		puts("");

		float f = 4035262704280141824.000000;

		#if defined(USE_KLEE)
		klee_make_symbolic(&f, sizeof(f), "f");
		klee_assume(f == f);
		#endif
		float g = f / 2;
		g *= 2;
		{
			printf("f,g: %f %f\n", (f), (g));
		}
		assert(g < f || f == g && "this should never fail");
		assert(f == g && "this should have an error path when underflow occurs");
	}

#ifdef ENABLE_DOUBLE
	{
		puts("\nrunning double test...");
		printf("sizeof(double): %zu\n", sizeof(double));
		puts("");

		double f = 131, g = 331;
		test(f, g);

		#if defined(USE_KLEE)
		klee_make_symbolic(&f, sizeof(f), "f");
		klee_assume(!isnan(f));
		klee_assume(!isinf(f));
		klee_assume(f > 0);
		klee_make_symbolic(&g, sizeof(g), "g");
		klee_assume(!isnan(g));
		klee_assume(!isinf(g));
		klee_assume(g > 0);
		klee_assume(g > f);
		test(f, g);
		#endif
	}
#endif

#ifdef ENABLE_LONGDOUBLE
	{
		puts("\nrunning long double test...");
		printf("sizeof(long double): %zu\n", sizeof(long double));
		puts("");

		double f = 131, g = 331;
		test(f, g);

		#if defined(USE_KLEE)
		klee_make_symbolic(&f, sizeof(f), "f");
		klee_assume(!isnan(f));
		klee_assume(!isinf(f));
		klee_assume(f > 0);
		klee_make_symbolic(&g, sizeof(g), "g");
		klee_assume(!isnan(g));
		klee_assume(!isinf(g));
		klee_assume(g > 0);
		klee_assume(g > f);
		test(f, g);
		#endif
	}
#endif
}
