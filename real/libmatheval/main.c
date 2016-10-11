#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <float.h>
#include "libmatheval-1.1.11/lib/matheval.h"

#ifdef KLEE
#include <klee/klee.h>
#endif

int yywrap() {return 1;}


#ifdef SYM_X
int main (int argc, char **argv) {
  double x;
#ifdef KLEE
  klee_make_symbolic(&x, sizeof(x), "x");
#else
  x = 5.2;
#endif

  char buffer[] = "3.1*(x^2)";
  void *f;

  f = evaluator_create (buffer);

  double f_x = evaluator_evaluate_x(f, x);
  printf("Checking for f(x) >= 0...\n");
  assert(isnan(x) || f_x >= 0);
  printf("Checking for nan...\n");
  assert(isnan(x) ? isnan(f_x) : !isnan(f_x));
  printf("Checking for inf...\n");
  if (isinf(x) || fabs(x) > sqrt(DBL_MAX / 3.1)) {
    assert(isinf(f_x));
  } else {
    assert(!isinf(f_x));
  }

  evaluator_destroy(f);
}
#endif

#ifdef SYM_F
int main (int argc, char **argv) {
  char d;
#ifdef KLEE
  klee_make_symbolic(&d, sizeof(d), "d");
  klee_assume(d >= 0);
  klee_assume(d <= 9);
#else
  d = 1;
#endif
  char buffer[] = "d*x";
  buffer[0] = d + '0';
  void *f, *f_deriv;

  printf("Evaluating buffer...\n");
  f = evaluator_create(buffer);
  printf("Getting derivative...\n");
  f_deriv = evaluator_derivative_x(f);
  printf("Calculating f'(4.2)...\n");
  double slope = evaluator_evaluate_x(f_deriv, 4.2);
  printf("Checking if slope is correct...\n");
  assert((int) slope == (int) d);

  evaluator_destroy(f);
  evaluator_destroy(f_deriv);
}
#endif

#ifdef SQRT
int main (int argc, char **argv) {
  double x, y;
#ifdef KLEE
  klee_make_symbolic(&x, sizeof(x), "x");
  klee_make_symbolic(&y, sizeof(y), "y");
  klee_assume(x >= 0);
  klee_assume(y >= 0);
#else
  x = 5.2;
  y = 9.9;
#endif

  char buffer[] = "sqrt(x-y)";
  void *f;

  f = evaluator_create(buffer);

  printf("Evaluating f(x, y)...\n");
  double f_x_y = evaluator_evaluate_x_y(f, x, y);
  printf("Verifying that f(x, y) is correct...\n");
  if (x >= y && x == x && y == y) {
    if (isinf(x) || isinf(y)) {
      assert(x == y ? f_x_y != f_x_y : isinf(f_x_y));
    } else {
      assert(f_x_y == f_x_y);
    }
  } else {
    assert(f_x_y != f_x_y);
  }

  evaluator_destroy(f);
}
#endif
