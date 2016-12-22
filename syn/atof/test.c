#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <klee/klee.h>

int main(int argc, char** argv) 
{
	char input[8];
	klee_make_symbolic(input, sizeof(input), "input");
	input[0] = '0';
	input[1] = '.';
	input[sizeof(input) - 1] = 0;
	bool has_e = false;
	for(size_t i = 2; i < sizeof(input) - 1; ++i) {
		if(input[i] == 'e' || input[i] == 'E') has_e = true;
	}
	double out = atof(input);
	assert(out >= 0);
	assert(has_e || out < 1);
}
