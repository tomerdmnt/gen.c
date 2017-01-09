#include <stdio.h>
#include <stdlib.h>
#include "gen.h"

void generator(gen_t *gen, void *omitch) {
	int c;

	while ((c = getchar()) != EOF) {
		if (c != *((char *)omitch)) {
			gen_yield(gen, &c);
		}
	}
}

int main(void) {
	int *ch_p;
	int omitch;
	gen_t *gen;

	gen = gen_create(generator, &omitch);
	omitch = 'z';

	while ((ch_p = gen_resume(gen)) != NULL)
		putchar(*ch_p);
	
	gen_free(gen);

	return 0;
}
