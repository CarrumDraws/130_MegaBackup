all: httpserver testScript testScript_2

httpserver: httpserver.o
	gcc -g -o httpserver httpserver.o

httpserver.o: httpserver.c
	gcc -c -std=c99 -Wall -Wextra -Wpedantic -Wshadow httpserver.c

testScript: testScript.o
	gcc -g -o testScript testScript.o

testScript.o: testScript.c
	gcc -c -std=c99 testScript.c

testScript_2: testScript_2.o
	gcc -g -o testScript_2 testScript_2.o

testScript_2.o: testScript_2.c
	gcc -c -std=c99 testScript_2.c

clean: # Gets rid of all ".o" files and httpserver. Run by typing "make clean" into terminal.
	rm *.o httpserver download_file test0file012345 testScript testScript_2