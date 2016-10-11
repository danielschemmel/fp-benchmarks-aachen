#include <assert.h>
#include <float.h>
#include <stdio.h>
#include <math.h>

#ifdef KLEE
#include <klee/klee.h>
#endif

#include "gmp-6.1.1/gmp.h"

#ifdef NEGATE
int main(int argc, char** argv) {
  double d;
#ifdef KLEE
  klee_make_symbolic(&d, sizeof(d), "d");
  klee_assume(d >=   1.0);
  klee_assume(d <= 100.0);
#else
  d = 42.0;
#endif

  mpf_t mp_d;
  mpf_init_set_d(mp_d, d);
  mpf_neg(mp_d, mp_d);

  double e = mpf_get_d(mp_d);
  printf("Checking e == -d...\n");
  assert(e == -d);
  printf("Checking e <= -1.0...\n");
  assert(e <= -1.0);
  printf("Checking e >= -100.0...\n");
  assert(e >= -100.0);

  mpf_clear(mp_d);
}
#endif


#ifdef MUL
int main(int argc, char** argv) {
  double d1, d2;
  mpf_t mp_d1, mp_d2;
  mpf_t mp_one, mp_four;

#ifdef KLEE
  klee_make_symbolic(&d1, sizeof(d1), "d1");
  klee_make_symbolic(&d2, sizeof(d2), "d2");
  klee_assume(d1 >=   1.0);
  klee_assume(d1 <= 2.0);
  klee_assume(d2 > 1.0);
  klee_assume(d2 < 2.0);
#else
  d1 = 1.0;
  d2 = 1.9;
#endif

  mpf_init_set_d(mp_d1, d1);
  mpf_init_set_d(mp_d2, d2);

  mpf_mul(mp_d2, mp_d1, mp_d2);
  
  printf("Checking if d1 * d2 > 1...\n");
  mpf_init_set_d(mp_one, 1.0);
  assert(mpf_cmp(mp_d2, mp_one) > 0);

  printf("Checking if d1 * d2 < 4...\n");
  mpf_init_set_d(mp_four, 2.0*2.0);
  printf("Ending...\n");
  assert(mpf_cmp(mp_d2, mp_four) < 0);

  mpf_clear(mp_d1);
  mpf_clear(mp_d2);
  mpf_clear(mp_one);
  mpf_clear(mp_four);
}
#endif


#ifdef INVALID_ARGUMENTS
int main(int argc, char** argv) {
  double d;
  mpf_t mp_d;

  klee_make_symbolic(&d, sizeof(d), "d");
  mpf_init(mp_d);

  unsigned choice;
  klee_make_symbolic(&choice, sizeof(choice), "choice");

  switch(choice) {
  case 0:
    klee_assume(d < -1);
    klee_assume(d > -2);
    mpf_set_d(mp_d, d);
    mpf_sqrt(mp_d, mp_d);
    break;
  case 1:
    klee_assume(d != d);
    mpf_set_d(mp_d, d);
    break;
  default:
    return 0;
  }

  assert(0 && "This should never happen!");
}
#endif


#ifdef INTEGER
int main(int argc, char** argv) {
  double d;
  mpf_t mp_d;
  klee_make_symbolic(&d, sizeof(d), "d");
  klee_assume(d < 3);
  klee_assume(d > 1);
  mpf_init_set_d(mp_d, d);

  if (mpf_integer_p(mp_d)) {
    assert(d == 2);
  } else {
    assert(d != 2);
  }
  mpf_clear(mp_d);
}
#endif


#ifdef PRECISION
int main(int argc, char** argv) {
  double d1, d2, avg;
  mpf_t mp_d1, mp_d2, mp_avg, mp_half;
  klee_make_symbolic(&d1, sizeof(d1), "d");
  klee_assume(d1 == d1);
  klee_assume(d1 > 1);
  klee_assume(d1 < 10);
  klee_assume(((*(char*) &d1) & 0x01) == 0);

  d2 = d1;
  *(char*) &d2 |= 0x01;

  // use a mantissa length of 53 bits
  mpf_init2(mp_d1, 53);
  mpf_init2(mp_d2, 53);
  mpf_init2(mp_avg, 53);
  mpf_set_d(mp_d1, d1);
  mpf_set_d(mp_d2, d2);

  printf("Calculating native average...\n");
  avg = (d1 + d2) * 0.5;

  printf("Calculating gmp average...\n");
  mpf_add(mp_avg, mp_d1, mp_d2);
  mpf_init_set_d(mp_half, 0.5);
  mpf_mul(mp_avg, mp_avg, mp_half);

  printf("Verifying that the native calculation had fp errors...\n");
  assert(avg == d1);
  assert(avg != d2);
  printf("Verifying that the calculation in gmp was precise...\n");
  assert(mpf_cmp(mp_d1, mp_avg) < 0);
  assert(mpf_cmp(mp_d2, mp_avg) > 0);


  mpf_clear(mp_d1);
  mpf_clear(mp_d2);
  mpf_clear(mp_avg);
  mpf_clear(mp_half);
}
#endif

#ifdef MPQLOAD
int main(int argc, char** argv) {
  int i;
  klee_make_symbolic(&i, sizeof(i), "i");
	double d = i;

	mpq_t moo;
	mpq_init(moo);
	mpq_set_d(moo, d);
	double e = mpq_get_d(moo);
	assert(e == d);
}
#endif
