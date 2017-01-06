#include <assert.h>
#include <stdlib.h>
#include <klee/klee.h>
#include "units.h"

int main(int argc, char** argv) {
  double f;
  klee_make_symbolic(&f, sizeof(f), "meters");
  klee_assume(f >= 0);
  klee_assume(f <= 1000);

#ifdef M2FT
  double ft = m2ft(f);
  assert(ft >= 0 && ft <= f * 3.3); // this is a rough approximation
#endif

#ifdef TOSTR
  char* lat = DecimalLatitudeToLORAN(f);
	assert(lat && "this really should not fail");
  free(lat);
  char* lon = DecimalLongitudeToLORAN(f);
	assert(lon && "this really should not fail");
  free(lon);
#endif
}
