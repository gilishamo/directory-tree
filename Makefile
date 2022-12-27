CC=gcc
CFLAGS=-I.
DEPS = directory_tree.h
OBJ = directory_tree.o main.o

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS)

directory_tree:$(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean :
	rm -rf *.o