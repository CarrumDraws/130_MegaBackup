SeperateFiles: SeperateFiles.o Add.o # recreate executable "SeperateFiles" everytime these two are updated
	gcc SeperateFiles.o Add.o -o SeperateFiles

SeperateFiles.o: SeperateFiles.c # recreate "SeperateFiles.o" everytime SeperateFiles.c is updated
	gcc -c SeperateFiles.c

Add.o: Add.c Add.h # recreate "Add.o" everytime either Add.c or Add.h are updated
	gcc -c Add.c

# Run the above by simply typing "make clean" into the command line!

clean: # Gets rid of all ".o" files and SeperateFiles. Run by typing "make clean" into terminal.
	rm *.o SeperateFiles
