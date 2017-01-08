#include "gen.h"
#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>

struct gen_t {
	gen_func_t func;
	volatile int running;
	jmp_buf caller;
	jmp_buf callee;
	void *in;
	void *out;
	void *sp;
};

gen_t *gen_create(gen_func_t func, void *in) {
	gen_t *gen = malloc(sizeof(gen_t));
	gen->func = func;
	gen->in = in;
	gen->running = 0;
	return gen;
}

void gen_free(gen_t *gen) {
	free(gen);
}

#define gen_start(gen) do { \
	gen->sp = (void *)((char *)malloc(GEN_STACK_SIZE) + GEN_STACK_SIZE); \
	int anchor[1]; \
	anchor[0] = 1; \
	char buf[(char *)&anchor - (char *)(gen->sp) - sizeof(int)]; \
	buf[0] = 1; \
	gen->func(gen, gen->in); \
} while(0)

void gen_yield(gen_t *gen, void *data) {
	gen->out = data;
	printf("setting gen->out to %c\n", *(char *)data);
	if (!setjmp(gen->callee))
		longjmp(gen->caller, 1);
}

void *gen_resume(gen_t *gen) {
	if (!setjmp(gen->caller)) {
		if (!gen->running) {
			gen->running = 1;
			gen_start(gen);
			gen->running = 0;
			gen->out = NULL;
		} else
			longjmp(gen->callee, 1);
	}
	return gen->out;
}
