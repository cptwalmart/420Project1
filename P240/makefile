CFLAGS=-std=c99
LIBS=-lm
CC=mpicc
all:Proj240

Proj240: 240.o
	$(CC) -o $@ $(CFLAGS) $^ $(LIBS)

.PHONY: clean

clean:
	rm -f *.o Proj240