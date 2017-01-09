#ifndef GEN_H
#define GEN_H

#define yield gen_yield
#define resume gen_resume

#define GEN_STACK_SIZE 1024

typedef struct gen_t gen_t;
typedef void (*gen_func_t)(gen_t *, void *);

gen_t *gen_create(gen_func_t func, void *in);
void gen_free(gen_t *gen);
void gen_yield(gen_t *gen, void *data);
void *gen_resume(gen_t *gen);

#endif
