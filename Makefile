SRC=gen.c
OBJ=gen.o
CFLAGS=-g -o0

test:
	$(CC) $(CFLAGS) gen.c test.c -o test
