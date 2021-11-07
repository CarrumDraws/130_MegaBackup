MultiThread: MultiThread.o
	gcc -g -pthread -o MultiThread MultiThread.o

MultiThread.o: MultiThread.c # Has to be in this order...?
	gcc -c -std=c99 -Wall -Wextra -Wpedantic -Wshadow  MultiThread.c

# Run the above by simply typing "make" into the command line!

clean: # Gets rid of all ".o" files and MultiThread. Run by typing "make clean" into terminal.
	rm *.o MultiThread
