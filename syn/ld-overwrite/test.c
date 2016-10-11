#include <assert.h>
#ifdef USE_KLEE
#include <klee/klee.h>
#endif

int main(int argc, char** argv)
{
	long double sym, conc;
#ifdef USE_KLEE
	klee_make_symbolic(&sym, sizeof(sym), "sym");
#else
	sym = 2.0L;
#endif
	char* bits = (char*)&conc;

	for (int i = 15; i >= 0; --i)
	{
		bits[i] = 0xCF;
	}

	conc = sym;

	for (int i = 15; i >= 10; --i)
	{
#ifdef USE_KLEE
		klee_assert(bits[i] == (char)0xCF);
#else
		assert(bits[i] == (char)0xCF);
#endif
	}

#ifdef USE_KLEE
	klee_assert(!(sym == sym) || sym == conc);
#else
	assert(!(sym == sym) || sym == conc);
#endif
}
