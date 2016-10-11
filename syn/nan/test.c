#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <float.h>

static void fnantest(float f) {
	//printf("%f (expected nan)\n", f);
	assert(f != f);
	assert(!(f == f));
	assert(!(f < f));
	assert(!(f <= f));
	assert(!(f > f));
	assert(!(f >= f));
}

static void dnantest(double f) {
	//printf("%lf (expected nan)\n", f);
	assert(f != f);
	assert(!(f == f));
	assert(!(f < f));
	assert(!(f <= f));
	assert(!(f > f));
	assert(!(f >= f));
}

static void lnantest(long double f) {
	//printf("%Lf (expected nan)\n", f);
	assert(f != f);
	assert(!(f == f));
	assert(!(f < f));
	assert(!(f <= f));
	assert(!(f > f));
	assert(!(f >= f));
}

#define nantest(f) _Generic((f), \
	float: fnantest, \
	double: dnantest, \
	long double: lnantest \
	)(f)

#ifdef USE_KLEE
#include <klee/klee.h>
#endif

static void ftest(float f) {
	nantest(f);

	f = f + 1;
	nantest(f);

	f -= f;
	nantest(f);

	f *= 0;
	nantest(f);

	f /= 0;
	nantest(f);

	f = 0;
	f /= 0;
	nantest(f);

	f = INFINITY;
	f -= INFINITY;
	nantest(f);
}

static void dtest(double f) {
	nantest(f);

	f = f + 1;
	nantest(f);

	f -= f;
	nantest(f);

	f *= 0;
	nantest(f);

	f /= 0;
	nantest(f);

	f = 0;
	f /= 0;
	nantest(f);

	f = INFINITY;
	f -= INFINITY;
	nantest(f);
}

static void ltest(long double f) {
	nantest(f);

	f = f + 1;
	nantest(f);

	f -= f;
	nantest(f);

	f *= 0;
	nantest(f);

	f /= 0;
	nantest(f);

	f = 0;
	f /= 0;
	nantest(f);

	f = INFINITY;
	f -= INFINITY;
	nantest(f);
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

		float f = NAN;
		test(f);

		#if defined(USE_KLEE)
		klee_make_symbolic(&f, sizeof(f), "f");
		klee_assume(f != f);
		test(f);

		klee_make_symbolic(&f, sizeof(f), "f");
		klee_assume(f < 0);
		f = sqrtf(f);
		#endif
	}
#endif

#ifdef ENABLE_DOUBLE
	{
		puts("\nrunning double test...");
		printf("sizeof(double): %zu\n", sizeof(double));
		puts("");

		double f = NAN;
		test(f);

		#if defined(USE_KLEE)
		klee_make_symbolic(&f, sizeof(f), "f");
		klee_assume(f != f);
		test(f);

		klee_make_symbolic(&f, sizeof(f), "f");
		klee_assume(f < 0);
		f = sqrt(f);
		test(f);
		#endif
	}
#endif

#ifdef ENABLE_LONGDOUBLE
	{
		puts("\nrunning long double test...");
		printf("sizeof(long double): %zu\n", sizeof(long double));
		puts("");

		long double f = NAN;
		test(f);

		#if defined(USE_KLEE)
		klee_make_symbolic(&f, sizeof(f), "f");
		klee_assume(isnan(f));
		test(f);

		klee_make_symbolic(&f, sizeof(f), "f");
		klee_assume(f < 0);
		f = sqrtl(f);
		test(f);
		#endif
	}
#endif
}
