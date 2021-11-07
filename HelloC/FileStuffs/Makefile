all: FileTester

FileTester: FileTester.o
	gcc -g -o FileTester FileTester.o

FileTester.o: FileTester.c
	gcc -c -std=c99 FileTester.c

clean: # Gets rid of all ".o" files and FileTester. Run by typing "make clean" into terminal.
	rm *.o *.txt FileTester 