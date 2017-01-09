
c generator using jmpbuf

# Overview

Write a generator function:

```c
void generator(gen_t *gen, void *in) {
	...
	yield(gen, x);
	yield(gen, y);
	...
}
```

Create a generator and run it:

```c
	...
	gen_t *gen = gen_create(generator, &in);
	while ((val = gen_resume(gen)) != NULL) {
		// val will hold the yielded value
		...
	}
	...
	gen_free(gen);
```

Stack size for each generator is set in gen.h (#define GEN_STACK_SIZE)

