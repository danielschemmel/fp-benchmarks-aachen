#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <float.h>

#ifdef USE_KLEE
#include <klee/klee.h>
#endif

static void ftest(float f, float g) {
	assert(fmodf(f, g) == f);
}

static void dtest(double f, double g) {
	assert(fmod(f, g) == f);
}

static void ltest(long double f, long double g) {
	assert(fmodl(f, g) == f);
}

#define test(f, g) _Generic((f), \
	float: ftest, \
	double: dtest, \
	long double: ltest \
	)(f, g)

int main(int argc, char** argv) {
	(void)argc;
	(void)argv;

#ifdef ENABLE_FLOAT
	{
		puts("\nrunning float test...\n");
		printf("sizeof(float): %zu\n", sizeof(float));
		puts("");

		float f = 131, g = 331;
		ftest(f, g);

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
