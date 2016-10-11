#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <klee/klee.h>
#include "C-Sorting-Algorithms/selectionSort.h"

#ifdef DOUBLES
static void check(double* arr, size_t length) {
  for (size_t i = 1; i < length; ++i) {
    klee_assert(arr[i] >= arr[i - 1]);
  }
}

int main(int argc, char** argv) {
	double a, b;
	klee_make_symbolic(&a, sizeof(a), "a");
	klee_make_symbolic(&b, sizeof(b), "b");
	klee_assume(a == a); // we don't want any NaN's, as the code we are testing probably can't deal with them anyway ;)
	klee_assume(b == b);
	double arr[] = {10., a, b, .3, .2, 1., 3., a + b, 1., 8.};

	selectionSortDouble(arr, sizeof(arr) / sizeof(arr[0]));

	check(arr, sizeof(arr) / sizeof(arr[0]));
}
#endif

#ifdef FLOATS
static void check(float* arr, size_t length) {
  for (size_t i = 1; i < length; ++i) {
    klee_assert(arr[i] >= arr[i - 1]);
  }
}

int main(int argc, char** argv) {
	float sym[5];
	klee_make_symbolic(&sym, sizeof(sym), "sym");
	for(size_t i = 0; i < sizeof(sym)/sizeof(*sym); ++i)
		klee_assume(!isnan(sym[i]));
	float arr[] = {sym[1] + sym[2], sym[1], sym[2], .3, .2, 1., 3., sym[3], 1., 8.};

	selectionSortFloat(arr, sizeof(arr) / sizeof(arr[0]));

	check(arr, sizeof(arr) / sizeof(arr[0]));
}
#endif
