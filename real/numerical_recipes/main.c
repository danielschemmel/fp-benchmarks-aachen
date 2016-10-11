#include <assert.h>
#include <math.h>
#include <stdio.h>
#ifdef KLEE
#include <klee/klee.h>
#endif
#ifdef GAUSSJ
#include "numerical_recipes/gaussj.h"
#endif
#ifdef QRDCMP
#include "numerical_recipes/qrdcmp.h"
#endif

void assert_nan_or_inf(float f) {
  int kind = fpclassify(f);
  assert(kind != FP_NAN);
  assert(kind != FP_INFINITE);
}

#ifdef GAUSSJ
int main(int argc, char** argv){
  float sym_f;
#ifdef KLEE
  klee_make_symbolic(&sym_f, sizeof(sym_f), "sym_f");
  klee_assume(sym_f > 1.0f);
  klee_assume(sym_f < 100.0f);
#else
  sym_f = 3.14;
#endif

  float a1[] = {-0.0f, 1.0f, 0.0f, -1.0f};
  float a2[] = {-0.0f, 2.0f, 1.0f,  4.0f};
  float a3[] = {-0.0f, 0.0f, 3.3f, sym_f};

  float b33 = 4.2f;
  float b1[] = {0.0f,  2.0f};
  float b2[] = {0.0f, -1.2f};
  float b3[] = {0.0f,  b33};
  float* a[] = {NULL, a1, a2, a3};
  float* b[] = {NULL, b1, b2, b3};

  gaussj(a, 3, b, 1);

  printf("Checking if NAN or INF...\n");
  assert_nan_or_inf(b33);

#ifdef PEDANTIC
    printf("Checking if above lower bound...\n");
    assert(a3[2] * b2[1] +  a3[3] * b3[1] >= b33 - 0.1f);
    printf("Checking if below upper bound...\n");
    assert(a3[2] * b2[1] +  a3[3] * b3[1] <= b33 + 0.1f);
#endif
}
#endif

#ifdef QRDCMP
int main(int argc, char** argv) {
  float sym_f;
#ifdef KLEE
  klee_make_symbolic(&sym_f, sizeof(sym_f), "sym_f");
  klee_assume(sym_f >= 1.0f);
  klee_assume(sym_f <= 20.0f);
#else
  sym_f = 3.14;
#endif

  float a1[] = {-0.0f, 12.0f, -51.0f,   4.0f};
  float a2[] = {-0.0f,  6.0f,  62.0f, -32.0f};
  float a3[] = {-0.0f, -3.0f, -31.0f,  sym_f};

  float* a[] = {NULL, a1, a2, a3};

  float c[3];
  float d[4];
  int sing;
  qrdcmp(a, 3, c, d, &sing);

  for (int i = 0; i < 3; ++i) {
    assert_nan_or_inf(c[i]);
  }

  for (int i = 0; i < 4; ++i) {
    assert_nan_or_inf(d[i]);
  }

  if(sym_f == 16.0f) {
    assert(sing == 1);
  } else {
    assert(sing == 0);
  }
}
#endif
