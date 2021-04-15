CC=clang
CFLAGS=-Wall -Wextra -o

all:mycalc
	./mycalc source && $(CC) -o assem assem.s

mycalc:mycalc.c
	$(CC) $(CFLAGS) mycalc mycalc.c


clean:
	rm -rf assem* mycalc 

.PHONY: clean
