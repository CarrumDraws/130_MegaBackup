all: shoulders extremeTest unitTest testScript

shoulders: shoulders.o
	gcc -g -o shoulders shoulders.o

shoulders.o: shoulders.c
	gcc -c -std=c99 -Wall shoulders.c

testScript: testScript.o
	gcc -g -o testScript testScript.o

testScript.o: testScript.c
	gcc -c -std=c99 -Wall testScript.c

unitTest: unitTest.o
	gcc -g -o unitTest unitTest.o

unitTest.o: unitTest.c
	gcc -c -std=c99 -Wall unitTest.c

extremeTest: extremeTest.o
	gcc -g -o extremeTest extremeTest.o

extremeTest.o: extremeTest.c
	gcc -c -std=c99 -Wall extremeTest.c

# Run the above by simply typing "make" into the command line!

clean: # Gets rid of all ".o" files and shoulders. Run by typing "make clean" into terminal.
	rm *.o shoulders extremeTest unitTest testScript
