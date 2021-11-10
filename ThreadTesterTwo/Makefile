MultiThreadTwo: MultiThreadTwo.o
	gcc -g -pthread -o MultiThreadTwo MultiThreadTwo.o

MultiThreadTwo.o: MultiThreadTwo.c # Has to be in this order...?
	gcc -c -std=c99 -Wall -Wextra -Wpedantic -Wshadow  MultiThreadTwo.c

clean: # Gets rid of all ".o" files and MultiThreadTwo. Run by typing "make clean" into terminal.
	rm *.o MultiThreadTwo
