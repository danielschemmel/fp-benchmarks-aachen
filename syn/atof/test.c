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
	double out = atof(input);
	assert(out >= 0);
	assert(out < 1);
}
