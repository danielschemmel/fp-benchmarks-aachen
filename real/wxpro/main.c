#include <assert.h>
#include <stdlib.h>
#include <klee/klee.h>
#include "wxpro/units.h"

int main(int argc, char** argv) {
  double m;
  klee_make_symbolic(&m, sizeof(m), "meters");
  klee_assume(m >= 0);
  klee_assume(m <= 1000);

  double ft = m2ft(m);
  assert(ft >= 0 && ft <= m * 3.3); // this is a rough approximation

  char* lat = DecimalLatitudeToLORAN(0.9);
  free(lat);
  char* lon = DecimalLongitudeToLORAN(0.9);
  free(lon);
}
