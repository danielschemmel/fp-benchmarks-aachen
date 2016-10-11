#include <assert.h>
#include <klee/klee.h>

int main(int argc, char** argv) {
	long double a, b;
	klee_make_symbolic(&a, sizeof(a), "a");
	klee_make_symbolic(&b, sizeof(b), "b");
	// the following ensures that no truly annoying cases remain (inf, nan, etc)
	klee_assume(a <= 1000000);
	klee_assume(a >= -1000000);
	klee_assume(b <= 1000000);
	klee_assume(b >= -1000000);

	long double ldsum = a + b;
	double dsum = (double)a + (double)b;
	assert(ldsum == dsum && "this assertion will fail due to floating point arithmetic");
}
