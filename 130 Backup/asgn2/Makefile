all: httpserver

httpserver: httpserver.o
	gcc -g -o httpserver httpserver.o

httpserver.o: httpserver.c
	gcc -c -std=c99 -Wall -Wextra -Wpedantic -Wshadow httpserver.c

clean: # Gets rid of all ".o" files and httpserver. Run by typing "make clean" into terminal.
	rm *.o httpserver