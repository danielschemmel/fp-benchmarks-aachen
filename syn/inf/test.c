#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <float.h>

static void finftest(float f) {
	//printf("%f (expected inf)\n", f);
	assert(f == f);
	assert(f > 0);
	assert(f > FLT_MAX);
	assert(f == INFINITY);
	assert(f - f != f - f);
}

static void dinftest(double f) {
	//printf("%lf (expected inf)\n", f);
	assert(f == f);
	assert(f > 0);
	assert(f > DBL_MAX);
	assert(f == INFINITY);
	assert(f - f != f - f);
}

static void linftest(long double f) {
	//printf("%Lf (expected inf)\n", f);
	assert(f == f);
	assert(f > 0);
	assert(f > LDBL_MAX);
	assert(f == INFINITY);
	assert(f - f != f - f);
}

#define inftest(f) _Generic((f), \
	float: finftest, \
	double: dinftest, \
	long double: linftest \
	)(f)

static void finftest_n(float f) {
	//printf("%f (expected inf)\n", f);
	assert(f == f);
	assert(f < 0);
	assert(f < -FLT_MAX);
	assert(f == -INFINITY);
	assert(f - f != f - f);
}

static void dinftest_n(double f) {
	//printf("%lf (expected inf)\n", f);
	assert(f == f);
	assert(f < 0);
	assert(f < -DBL_MAX);
	assert(f == -INFINITY);
	assert(f - f != f - f);
}

static void linftest_n(long double f) {
	//printf("%Lf (expected inf)\n", f);
	assert(f == f);
	assert(f < 0);
	assert(f < -LDBL_MAX);
	assert(f == -INFINITY);
	assert(f - f != f - f);
}

#define inftest_n(f) _Generic((f), \
	float: finftest_n, \
	double: dinftest_n, \
	long double: linftest_n \
	)(f)

#ifdef USE_KLEE
#include <klee/klee.h>
#endif

static void ftest(float f) {
	inftest(f);
	inftest_n(-f);

	f = f + 1;
	inftest(f);

	f -= FLT_MAX;
	inftest(f);
}

static void dtest(double f) {
	inftest(f);
	inftest_n(-f);

	f = f + 1;
	inftest(f);

	f -= DBL_MAX;
	inftest(f);
}

static void ltest(long double f) {
	inftest(f);
	inftest_n(-f);

	f = f + 1;
	inftest(f);

	f -= LDBL_MAX;
	inftest(f);
}

#define test(f) _Generic((f), \
	float: ftest, \
	double: dtest, \
	long double: ltest \
	)(f)

int main(int argc, char** argv) {
	(void)argc;
	(void)argv;

#ifdef ENABLE_FLOAT
	{
		puts("\nrunning float test...\n");
		printf("sizeof(float): %zu\n", sizeof(float));
		puts("");

		float f = INFINITY;
		test(f);

		#if defined(USE_KLEE)
		klee_make_symbolic(&f, sizeof(f), "f");
		klee_assume(isinf(f));
		test(fabsf(f));

		klee_make_symbolic(&f, sizeof(f), "f");
		klee_assume(!isnan(f));
		f = fabsf(f) + 3.1415926535e10;
		for(unsigned i = 0; i < 2; ++i) {
			f = f*f;
		}
		test(f);
		#endif
	}
#endif

#ifdef ENABLE_DOUBLE
	{
		puts("\nrunning double test...");
		printf("sizeof(double): %zu\n", sizeof(double));
		puts("");

		double f = INFINITY;
		test(f);

		#if defined(USE_KLEE)
		klee_make_symbolic(&f, sizeof(f), "f");
		klee_assume(isinf(f));
		test(fabs(f));

		klee_make_symbolic(&f, sizeof(f), "f");
		klee_assume(!isnan(f));
		f = fabs(f) + 3.1415926535e78;
		for(unsigned i = 0; i < 2; ++i) {
			f = f*f;
		}
		test(f);
		#endif
	}
#endif

#ifdef ENABLE_LONGDOUBLE
	{
		puts("\nrunning long double test...");
		printf("sizeof(long double): %zu\n", sizeof(long double));
		puts("");

		long double ld = INFINITY;
		test(ld);

		#if defined(USE_KLEE)
		klee_make_symbolic(&ld, sizeof(ld), "ld");
		klee_assume(isinf(ld));
		test(fabsl(ld));
		#endif
	}
#endif
}
