CC=clang
CFLAGS=-Wall -Wextra -g -o 

all:clean mycalc
	./mycalc.out source && $(CC) -o assem.out assem.s

mycalc:mycalc.c
	$(CC) $(CFLAGS) mycalc.out mycalc.c


clean:
	rm -rf assem* *.out

.PHONY: clean
