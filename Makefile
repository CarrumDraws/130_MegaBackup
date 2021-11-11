all: httpserver testScript

httpserver: httpserver.o
	gcc -g -pthread -o httpserver httpserver.o

httpserver.o: httpserver.c
	gcc -c -std=c99 -Wall -Wextra -Wpedantic -Wshadow httpserver.c

testScript: testScript.o
	gcc -g -o testScript testScript.o

testScript.o: testScript.c
	gcc -c -std=c99 testScript.c

clean: # Gets rid of all ".o" files and httpserver. Run by typing "make clean" into terminal.
	rm *.o httpserver testScript