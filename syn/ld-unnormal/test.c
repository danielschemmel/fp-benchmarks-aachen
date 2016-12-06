#include <assert.h>
#include <math.h>
#include <stdint.h>

int main(int argc, char **argv) {
  long double l = -5.0l;

  uint64_t *l_bits = (void *)&l;

  l_bits[0] &= 0x7FFFFFFFFFFFFFFF;

  assert(!isnan(l));
  assert(isfinite(l));
  assert(!isinf(l));

  assert(fpclassify(l) == FP_NORMAL);

  assert(l != l);
  assert(!(l == l));
  assert(!(l < l));
  assert(!(l <= l));
  assert(!(l > l));
  assert(!(l >= l));

  long double d = 4.0l;

  assert(isnan(l + d));
  assert(isnan(l - d));
  assert(isnan(l / d));
  assert(isnan(l * d));

  assert(!isnan(fabsl(l)));
  assert(isnan(fabsl(l) + d));
  assert(isnan(sqrtl(l)));
  assert(isnan(nearbyintl(l)));

  assert(isnan((float)l));
  assert(isnan((double)l));

  assert((uint8_t)l == 0);
  assert((int8_t)l == 0);
  assert((uint16_t)l == 0);
  assert((int16_t)l == 0);
  assert((uint32_t)l == 0);
  assert((int32_t)l == -2147483648);
  assert((uint64_t)l == 0);
  assert((int64_t)l == INT64_MIN);
}
