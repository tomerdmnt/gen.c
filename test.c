#include <stdio.h>
#include <stdlib.h>
#include "gen.h"

void generator(gen_t *gen, void *omitch) {
	int c;

	while ((c = getchar()) != EOF) {
		if (c != *((char *)omitch)) {
			printf("getting char %c\n", c);
			int *c_p = malloc(sizeof(char));
			*c_p = c;
			gen_yield(gen, c_p);
		}
	}
}

int main(void) {
	int *ch_p;
	int omitch;
	gen_t *gen;

	gen = gen_create(generator, &omitch);
	omitch = 'z';

	while ((ch_p = gen_resume(gen)) != NULL) {
		printf("putting char %c\n", *ch_p);
		putchar(*ch_p);
	}
	
	gen_free(gen);

	return 0;
}
