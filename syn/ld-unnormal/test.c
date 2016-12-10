#include <assert.h>
#include <math.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <stdio.h>

void dump_long_double(char* name, long double ld) {
  uint64_t data[2] = {0, 0};
  memcpy(data, &ld, 10);
  printf("%s: 0x%.4" PRIx16 " %.16" PRIx64 "\n", name, (uint16_t)data[1], data[0]);
}

int main(int argc, char **argv) {
  long double l = -5.0l;

  uint64_t *l_bits = (void *)&l;

  l_bits[0] &= 0x7FFFFFFFFFFFFFFF;
  // l: 0xc001 2000000000000000
  //
  // Sign    Exponent        Significand
  //                      Integer  Fraction
  // [1] [100000000000001]  [0]    [010...0]
  //
  // This is part of the  "Negative Floating Point Unnormals"
  // class as defined in 8.2.2 "Unsupported Double Extended-Precision
  // Floating-Point Encodings and Pseduo-Denormals" in the Intel(R)
  // 64 and IA-32 Architectures Software Developer's Manual.
  //
  // This is an invalid operand.
  dump_long_double("l", l);

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
