#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <klee/klee.h>

int main(int argc, char** argv)
{
        long double l = -5.0l;

        uint64_t* l_bits = (void*) &l;

        l_bits[0] &= 0x7FFFFFFFFFFFFFFF;

	klee_print_expr("l", l);
        klee_assert(!isnan(l));
        klee_assert(isfinite(l));
        klee_assert(!isinf(l));

        klee_assert(fpclassify(l) == FP_NORMAL);

	if (l != l)
		klee_print_expr("l", l);
	else
		klee_print_expr("l", l);
        klee_assert(l!=l);
        klee_assert(!(l==l));
        klee_assert(!(l<l));
        klee_assert(!(l<=l));
        klee_assert(!(l>l));
        klee_assert(!(l>=l));

        long double d = 4.0l;

        klee_assert(isnan(l+d));
        klee_assert(isnan(l-d));
        klee_assert(isnan(l/d));
        klee_assert(isnan(l*d));

        klee_assert(!isnan(fabsl(l)));
        klee_assert(isnan(fabsl(l)+d));
        klee_assert(isnan(sqrtl(l)));
        klee_assert(isnan(nearbyintl(l)));

        klee_assert(isnan((float)l));
        klee_assert(isnan((double)l));

        klee_assert((uint8_t)l == 0);
        klee_assert((int8_t)l == 0);
        klee_assert((uint16_t)l == 0);
        klee_assert((int16_t)l == 0);
        klee_assert((uint32_t)l == 0);
        klee_assert((int32_t)l == -2147483648);
        klee_assert((uint64_t)l == 0);
        klee_assert((int64_t)l == INT64_MIN);
}

