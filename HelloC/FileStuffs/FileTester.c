#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <err.h>
#include <string.h>

#define BUFSIZE 15

int main(){
    // char buf[BUFSIZE];
    // char minibuf[10];
    // char fileName[50] = "myfile.txt";
    // char bufCounter = 0;
    // char num[2];
    
    // /* write to file */
    // int fd = open(fileName, O_CREAT | O_WRONLY, 0600);
    // for (int x = 0; x < BUFSIZE; x++) {
    //     sprintf(num, "%d", x%10); // converts 'x' to string (char buffer num)
    //     write(fd, &num, 1); // writes num buffer to file
    // }
    // close(fd);

    // /* read into buffer with loops*/
    // fd = open("myfile.txt", O_RDONLY);
    // int readBytes = read(fd, &buf[bufCounter], 3);
    // bufCounter += 3;
    // while(readBytes == 3) {
    //     readBytes = read(fd, &buf[bufCounter], 3);
    //     bufCounter += 3;
    // }
    // buf[bufCounter-(readBytes + 3)] = '\0';
    // close(fd);
    // printf("%s\n", buf);

    // /* read into buffer with loops*/
    // int fd = open("myfile.txt", O_RDONLY);
    // int readBytes2 = read(fd, &minibuf, 10);
    // minibuf[readBytes2] = '\0';
    // while(readBytes2 == 10) {
    //     printf("%s", minibuf);
    //     readBytes2 = read(fd, &minibuf, 10);
    //     minibuf[readBytes2] = '\0';
    // }
    // printf("%s\n", minibuf); // How to print [readbytes] amount of chars from buffer?
    // close(fd);

    // // Stacking sprintf's
    // int length = 0;
    // char sprintfTest[20];
    // for(int x = 0; x < 20; x++) {
    //     length += sprintf(sprintfTest + length, "%d", x);
    // }
    // printf("%s\n", sprintfTest);
    // printf("Done");

    // // Chaining sprintf's
    // int length = 0;
    // char sprintfTest[30];
    // char sprintfTest2[30];

    // length += sprintf(sprintfTest + length, "Hello ");
    // length += sprintf(sprintfTest + length, "World! ");
    // length += sprintf(sprintfTest + length, "I'm Ca");
    // length += sprintf(sprintfTest + length, "lum.\n");
    // printf("%s\n", sprintfTest);

    // BELOW FAILS....?
    // int length = 0;
    // char testBuf[5];
    // for(int i = 0; i < 5; i++) { testBuf[i%5] = i; printf("%d ", testBuf[i%5]);}
    // printf("result : %s\n", testBuf);
    // for(int i = 0; i < 5; i++) { sprintf(testBuf, "%d", i); printf("%s ", testBuf);}
    // printf("result : %s\n", testBuf);

    // length += sprintf(sprintfTest2 + length, "%s", testBuf);
    // for(int i = 5; i < 10; i++) { testBuf[i%5] = i; }
    // length += sprintf(sprintfTest2 + length, "%s", testBuf);
    // for(int i = 10; i < 15; i++) { testBuf[i%5] = i; }
    // length += sprintf(sprintfTest2 + length, "%s", testBuf);
    // printf("%s\n", sprintfTest2);

    // sprintf(Buffer,"Hello World");
    // sprintf(Buffer + strlen(Buffer),"Good Morning");
    // sprintf(Buffer + strlen(Buffer),"Good Afternoon");

    // for (int x = 0; x < BUFSIZE; x++) {
    //     printf("Index: %d = %c\n", x, buf[x]);
    // }

    // /* write from buffer to stdout */
    // fd = open("myfile.txt", O_RDONLY);
    // for (int x = 0; x < BUFSIZE; x++) {
    //     write(0, &buf[x], 1);
    // }
    // close(fd);

    // Reading and writing from files
    char fileBuf[100000];
    int fileD = open("y1.txt", O_RDONLY); // Open with O_RDONLY
    int fileSize = read(fileD, fileBuf, 100000);
    printf("FileSize: %d\n", fileSize);
    printf("FileBody: %s\n", fileBuf);
    close(fileD); 

    fileD = open("result.txt", O_CREAT | O_WRONLY | O_TRUNC, 0600); // Write with O_RDONLY
    write(fileD, fileBuf, fileSize);
    close(fileD);
    
    return 0;
}