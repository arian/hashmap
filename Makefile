

CC=gcc
CFLAGS=-Wall -ansi -pedantic

test: clean
	$(CC) $(CFLAGS) hashmap.c test.c -o test

clean:
	rm -f *.o test
