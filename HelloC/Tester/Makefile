HelloWorld: HelloWorld.o
	gcc -g -o HelloWorld HelloWorld.o

HelloWorld.o: HelloWorld.c # Has to be in this order...?
	gcc -c -std=c99 -Wall HelloWorld.c

# Run the above by simply typing "make" into the command line!

clean: # Gets rid of all ".o" files and HelloWorld. Run by typing "make clean" into terminal.
	rm *.o HelloWorld
