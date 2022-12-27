CC=gcc
CFLAGS=-I.
DEPS = utils.h directory_tree.h
OBJ = utils.c directory_tree.o main.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

directory_tree:$(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean :
	rm -rf *.o