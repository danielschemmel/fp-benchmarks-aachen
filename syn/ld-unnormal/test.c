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

  // Clearly `l` is not a NaN but GCC and Clang (using glibc 2.24) differ on
  // their behaviour here. GCC 6.2.1 (both at `-O0` and `-O2`) fail this
  // assertion (`isnan(l)` is true). Clang 3.9 (both at `-O0` and `-O2`) pass
  // this assertion (`isnan(l)` is false).
  // TODO: Report to Clang devs
  // TODO: Report to GCC devs
  // assert(!isnan(l));

  // Clearly `l` is not finite but GCC and Clang (using glibc 2.24) differ on
  // their behaviour here. GCC 6.2.1 (both at `-O0` and `-O2`) fail this
  // assertion (`isfinite(l)` is false). Clang 3.9 (both at `-O0` and `-O2`) pass
  // this assertion (`isfinite(l)` is true).
  // TODO: Report to Clang devs
  // TODO: Report to GCC devs
  // assert(isfinite(l));

  assert(!isinf(l));

  // Clearly `l` is not a normal floating point number but GCC and Clang (using
  // glibc 2.24) differ on their behaviour here. GCC 6.2.1 (both at `-O0` and
  // `-O2`) fail this assertion. Clang 3.9 (both at `-O0` and `-O2`) pass this
  // assertion.
  // TODO: Report to Clang devs
  // TODO: Report to GCC devs
  // assert(fpclassify(l) == FP_NORMAL);

  // Note these assertions should all be true but some are mis-compiled by
  // Clang 3.9 at -O2 and constant folded to be false.
  // Reported to Clang devs: https://llvm.org/bugs/show_bug.cgi?id=31294
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

  // Performing an `fabsl(l)` should give a NaN but GCC and Clang
  // (using glibc 2.24) differ on their behaviour here. GCC 6.2.1
  // (both at `-O0` and `-O2`) fail this assertion (`isnan(fabsl(l))` is true).
  // Clang 3.9 (both at `-O0` and `-O2`) pass this assertion
  // (`isnan(fabs(l))` is false).
  // TODO: Report to Clang devs
  // TODO: Report to GCC devs
  // assert(!isnan(fabsl(l)));

  assert(isnan(fabsl(l) + d));
  assert(isnan(sqrtl(l)));
  assert(isnan(nearbyintl(l)));

  assert(isnan((float)l));
  assert(isnan((double)l));

  // Unnormal numbers are not part of C11's model of floating point so I think
  // the behaviour below is undefined.
  //
  // Here is the relevant section from the C11 Committee Draft
  // ```
  // F4. Floating to integer conversion
  //
  // If the integer type is _Bool, 6.3.1.2 applies and no floating-point
  // exceptions are raised (even for NaN). Otherwise, if the floating value is
  // infinite or NaN or if the integral part of the floating value exceeds
  // the range of the integer type, then the "invalid" floating-point exception
  // is raised and the resulting value is unspecified. Otherwise, the resulting
  // value is determined by 6.3.1.4. Conversion of an integral floating value
  // that does not exceed the range of the integer type raises no
  // floating-point exceptions; whether conversion of a non-integral floating
  // value raises the "inexact" floating-point exception is
  // unspecified.
  // ```
  assert((uint8_t)l == 0);
  assert((int8_t)l == 0);
  assert((uint16_t)l == 0);

  // GCC and Clangs behaviour differ here. GCC 6.2.1 (both at `-O0` and `-O2`)
  // fail this assertion with the casted value being `-32768`. Clang passes
  // this assertion.
  // TODO: Report to Clang devs
  // TODO: Report to GCC devs
  // assert((int16_t)l == 0);

  assert((uint32_t)l == 0);
  assert((int32_t)l == -2147483648);
  assert((uint64_t)l == 0);
  assert((int64_t)l == INT64_MIN);
}
