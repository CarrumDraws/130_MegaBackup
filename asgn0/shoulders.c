#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <err.h>
#include <string.h>

#define BUFSIZE 5000000

void readWrite(long int *numLines, char buf[], int *bufIndex, int fd);

int main(int argc, char *argv[]){
    long int numLines;
    char *invalidChars;
    int fileD;
    char buf[BUFSIZE];
    int bufIndex = 0;

    if(argc == 1) { // Checks for no input
        warn("option requires an argument");
        exit(-1);
    }

    numLines = strtol(argv[1], &invalidChars, 10); // Converts string argv[1] to int, invalid chars moved to invalidChars buffer

    if((invalidChars == NULL) || (invalidChars[0] != '\0')) { // Checks if invalidChars contains anything
        fprintf(stderr, "shoulders: invalid number of lines : '%s'\n", argv[1]);
        exit(-1);
    }

    if(argc == 2) { // Checks for no files, prints stdin to stdout, exits
        readWrite(&numLines, buf, &bufIndex, 0);
        return 0;
    }

    for(int x = 2; x < argc; x++) {
        if(strcmp(argv[x], "-") == 0) { // Checks for '-', prints stdin to stdout
            readWrite(&numLines, buf, &bufIndex, 0);
        }
        else {
            fileD = open(argv[x], O_RDONLY);

            if(fileD == -1){
                warn("cannot open '%s' for reading", argv[x]);
            } else {  // prints file contents to stdout
                readWrite(&numLines, buf, &bufIndex, fileD);
            }            
        }
        memset(buf, 0, sizeof buf); // Clear buffer
        bufIndex = 0;
        close(fileD);
    }
    return 0;
}

void readWrite(long int *numLines, char buf[], int *bufIndex, int fd) {
    int byteSize = read(fd, buf, BUFSIZE);
    for(int x = 0; x < *numLines; x++) {
        while(buf[*bufIndex] != 10 && *bufIndex < byteSize) {
            *bufIndex = *bufIndex + 1;
        }
        if(*bufIndex < byteSize) *bufIndex = *bufIndex + 1;
    }
    write(1, buf, *bufIndex);
}