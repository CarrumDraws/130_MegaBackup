#include <err.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>

#define LARGE 10000
#define SMALL 1000

/**
   String to int conversion- return 0 if fails
 */
uint16_t strtouint16(char number[]) {
  char *lastCarriage;
  long num = strtol(number, &lastCarriage, 10);
  if (num <= 0 || num > UINT16_MAX || *lastCarriage != '\0') {
    return 0;
  }
  return num;
}

/**
   Creates a socket for listening for connections.
   Closes the program and prints an error message on error.
 */
int create_listen_socket(uint16_t port) {
  struct sockaddr_in addr;
  int listenfd = socket(AF_INET, SOCK_STREAM, 0);
  if (listenfd < 0) {
    err(EXIT_FAILURE, "socket error");
  }

  memset(&addr, 0, sizeof addr);
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = htons(INADDR_ANY);
  addr.sin_port = htons(port);
  if (bind(listenfd, (struct sockaddr*)&addr, sizeof addr) < 0) {
    err(EXIT_FAILURE, "bind error");
  }
  if (listen(listenfd, 500) < 0) {
    err(EXIT_FAILURE, "listen error");
  }

  return listenfd;
}

void parse(int connfd, char request[], char type[], char fileName[], char hostVal[], int *contLenVal, int *failCode) {

  char *currLine = strtok(request, "\r\n");
  if(currLine == NULL) {
    send(connfd, "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 22\r\n\r\nInternal Server Error\n", 80, 0);
    return;
  }
  
  while(currLine != NULL) {
    if(strstr(currLine, "HTTP/1.1")) {
      if(sscanf(currLine, "%s /%[a-zA-Z0-9._] HTTP/1.1", type, fileName) > 4) *failCode = 400;
      // How to check for length 19?
      printf("Operation is: %s, Filename is: %s\n", type, fileName);
    } else if (strstr(currLine, "Host: ")) {
      sscanf(currLine, "Host: %s", hostVal);
      printf("Host is: %s\n", hostVal);
    } else if (strstr(currLine, "Content-Length: ")) {
      char * ContLenBuf = calloc(100, sizeof(char));
      if(ContLenBuf == NULL) {
        send(connfd, "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 22\r\n\r\nInternal Server Error\n", 80, 0);
        return;
      }
      sscanf(currLine, "Content-Length: %s", ContLenBuf);
      sscanf(ContLenBuf, "%d", contLenVal);
      printf("Content-Length is: %d\n", *contLenVal);
      free(ContLenBuf);
    }
    currLine = strtok(NULL, "\r\n");
  }
}

void process(char type[], char fileName[], int contLenVal, int connfd) {
  printf("Processing Type: %s\n", type);
  
  if(strcmp(type, "GET") == 0) { // Return a file to client
    // Check for file, respond 404 if not found
    // If found, respond 200 OK\r\n. Find length of file by reading the whole file into a temporary request first.
    // Should anything fail, clear response, respond 400 Bad Request
    int fileD = open(fileName, O_RDONLY);
    
    if(fileD == -1){
      send(connfd, "HTTP/1.1 404 File Not Found\r\nContent-Length: 15\r\n\r\nFile Not Found\n", 66, 0); // Send error
    } else {
      struct stat buf;
      fstat(fileD, &buf);
      off_t fileSize = buf.st_size; // Get fileSize of file
      printf("Size: %ld\n", fileSize);

      char * fileBuf = calloc(SMALL, sizeof(char)); // Allocate memory for fileBuf
      if(fileBuf == NULL) {
        send(connfd, "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 22\r\n\r\nInternal Server Error\n", 80, 0);
        free(fileBuf);
        close(fileD); 
        return;
      }
      int bytes = read(fileD, fileBuf, SMALL); // Read the first 1000 byte 'chunk' from the file
      int totalBytesRead = bytes;
      if(bytes == -1) {
        send(connfd, "HTTP/1.1 400 Bad Request\r\nContent-Length: 12\r\n\r\nBad Request\n", 60, 0); // Send error if read fails
      } else {
        char * header = calloc(SMALL, sizeof(char));
        if(header == NULL) {
          send(connfd, "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 22\r\n\r\nInternal Server Error\n", 80, 0);
          free(fileBuf);
          close(fileD); 
          return;
        }
        int headerLen = sprintf(header, "HTTP/1.1 200 OK\r\nContent-Length: %ld\r\n\r\n", fileSize);
        if(headerLen < 0) {
          send(connfd, "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 22\r\n\r\nInternal Server Error\n", 80, 0);
          free(header);
          free(fileBuf);
          close(fileD); 
          return;
        }
        send(connfd, header, headerLen, 0); // Send header to response
        free(header);
        send(connfd, fileBuf, bytes, 0); // Send current 'chunk' to response
        while(totalBytesRead < fileSize) {
          bytes = read(fileD, fileBuf, SMALL); // Read the next 1000 byte chunk
          if(bytes == -1) {
            send(connfd, "HTTP/1.1 400 Bad Request\r\nContent-Length: 12\r\n\r\nBad Request\n", 60, 0); // Send error if read fails
            free(fileBuf);
            close(fileD); 
            return;
          }
          totalBytesRead += bytes;
          send(connfd, fileBuf, bytes, 0); // Send the 'chunk' to response
        }
        send(connfd, "\n", 1, 0);
      }
      free(fileBuf);
      close(fileD); 
    }
    return;
  }

  if(strcmp(type, "PUT") == 0) { // Store file contents to server. Can create and alter files.
    // If contLenVal is NULL, 400 Bad Request
    // Check for fileName
    // If fileName found, respond 200
    // If fileName not found, respond 201, make new file
    // Write from body to fileName, replacing all content
    // Client tells us content length, we can loop throguh this (Move to process)
    if (!contLenVal) {
      send(connfd, "HTTP/1.1 400 Bad Request\r\nContent-Length: 12\r\n\r\nBad Request\n", 60, 0); // Send error
    } else {
      int exists;
      if( access( fileName, F_OK ) == 0 ) exists = 1;

      int fileD = open(fileName, O_CREAT|O_WRONLY|O_TRUNC,  00777);
      if(fileD == -1){
        send(connfd, "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 22\r\n\r\nInternal Server Error\n", 80, 0);
      } else {
        char * body = calloc(SMALL, sizeof(char)); // Allocate memory for body
        if(body == NULL) {
          send(connfd, "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 22\r\n\r\nInternal Server Error\n", 80, 0);
          free(body);
          close(fileD); 
          return;
        }
        int bytes = recv(connfd, body, SMALL, 0);
        int totalBytesRead = bytes;
        if(bytes == -1) {
          send(connfd, "HTTP/1.1 400 Bad Request\r\nContent-Length: 12\r\n\r\nBad Request\n", 60, 0); // Send error if recv fails
        } else {
          if(write(fileD, body, bytes) == -1) {
            send(connfd, "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 22\r\n\r\nInternal Server Error\n", 80, 0);
            free(body);
            close(fileD); 
            return;
          }
          while(totalBytesRead < contLenVal) {
            bytes = recv(connfd, body, SMALL, 0); //recv X bytes
            if(bytes == -1) {
              send(connfd, "HTTP/1.1 400 Bad Request\r\nContent-Length: 12\r\n\r\nBad Request\n", 60, 0); // Send error if read fails
              free(body);
              close(fileD); 
              return;
            }
            totalBytesRead += bytes;
            if(write(fileD, body, bytes) == -1) {
              send(connfd, "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 22\r\n\r\nInternal Server Error\n", 80, 0);
              free(body);
              close(fileD); 
              return;
            }
          }
          if(exists == 1){
            send(connfd, "HTTP/1.1 200 OK\r\nContent-Length: 8\r\n\r\nCreated\n", 46, 0); // Otherwise, I send this response
          } else {
            send(connfd, "HTTP/1.1 201 Created\r\nContent-Length: 8\r\n\r\nCreated\n", 51, 0); // And send a response.
          }          
        }
        free(body);
        close(fileD);
      }
    }
    return;
  }

  if(strncmp(type, "HEAD", 5) == 0) { // Send file info without file (GET - file)
    // Should any of these fail, clear response, respond 400 Bad Request
    // Check for file, respond 404 if not found
    // If found, respond 200 OK\r\n. Find length of file by reading the whole file into a temporary request first.
    // Should anything fail, clear response, respond 400 Bad Request
    int fileD = open(fileName, O_RDONLY);
    
    if(fileD == -1){
      send(connfd, "HTTP/1.1 404 File Not Found\r\nContent-Length: 15\r\n\r\nFile Not Found\n", 66, 0); // Send error
    } else {
      struct stat buf;
      fstat(fileD, &buf);
      off_t fileSize = buf.st_size; // Get fileSize of file
      printf("Size: %ld\n", fileSize);

      char * fileBuf = calloc(SMALL, sizeof(char)); // Allocate memory for fileBuf
      if(fileBuf == NULL) {
        send(connfd, "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 22\r\n\r\nInternal Server Error\n", 80, 0);
        free(fileBuf);
        close(fileD); 
        return;
      }
      int bytes = read(fileD, fileBuf, SMALL); // Read the first 1000 byte 'chunk' from the file
      if(bytes == -1) {
        send(connfd, "HTTP/1.1 400 Bad Request\r\nContent-Length: 12\r\n\r\nBad Request\n", 60, 0); // Send error if read fails
      } else {
        char * header = calloc(SMALL, sizeof(char));
        if(header == NULL) {
          send(connfd, "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 22\r\n\r\nInternal Server Error\n", 80, 0);
          free(fileBuf);
          close(fileD); 
          return;
        }
        int headerLen = sprintf(header, "HTTP/1.1 200 OK\r\nContent-Length: %ld\r\n\r\n", fileSize);
        if(headerLen < 0) {
          send(connfd, "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 22\r\n\r\nInternal Server Error\n", 80, 0);
          free(header);
          free(fileBuf);
          close(fileD); 
          return;
        }
        send(connfd, header, headerLen, 0); // Send header to response
        free(header);
      }
      free(fileBuf);
      close(fileD); 
    }
    return;
  }
  send(connfd, "HTTP/1.1 501 Not Implemented\r\nContent-Length: 16\r\n\r\nNot Implemented\n", 68, 0); // Send error
  return;
}

void handle_connection(int connfd) {
  char * request = calloc(LARGE, sizeof(char));
  if(request == NULL) {
    send(connfd, "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 22\r\n\r\nInternal Server Error\n", 80, 0);
    free(request);
    close(connfd);
    printf("-- End of Request --\n");
    return;
  }
  if(recv(connfd, request, LARGE, 0) == -1) {
    send(connfd, "HTTP/1.1 400 Bad Request\r\nContent-Length: 12\r\n\r\nBad Request\n", 60, 0);
    free(request);
    close(connfd);
    printf("-- End of Request --\n");
    return;
  }

  char type[20]; // Get/Put/Post
  char fileName[20] = {0};
  char hostVal[100] = {0};
  int contLenVal;
  int failCode = 0;

  parse(connfd, request, type, fileName, hostVal, &contLenVal, &failCode);

  // Fail if hostVal or fileName is invalid
  if(hostVal == 0 || fileName == 0 || failCode == 400) {
    send(connfd, "HTTP/1.1 400 Bad Request\r\nContent-Length: 12\r\n\r\nBad Request\n", 60, 0);
    free(request);
    close(connfd);
    printf("-- End of Request --\n");
    return;
  }

  process(type, fileName, contLenVal, connfd);

  free(request);
  close(connfd);
  printf("-- End of Request --\n");
}

int main(int argc, char *argv[]) {
  int listenfd;
  uint16_t port;

  int option;
  int numThreads = 0;
  char logFile[50];
  while ((option = getopt(argc, argv, "l:N:")) != -1) {
    switch (option) {
      case 'l' : // LogFile Name
        strcpy(logFile, optarg);
        printf("logFile : %s\n", logFile);
        break;
      case 'N' : // Number of Threads
        numThreads = strtouint16(optarg);
        printf("numThreads : %d\n", numThreads);
        break;
      default : // Default
        break;
    }
  }
  // if (argc != 2) {
  //   errx(EXIT_FAILURE, "wrong arguments: %s port_num", argv[0]);
  // }
  port = strtouint16(argv[1]);
  if (port == 0) {
    errx(EXIT_FAILURE, "invalid port number: %s", argv[1]);
  }
  listenfd = create_listen_socket(port);

  // Code here

  while(1) {
    int connfd = accept(listenfd, NULL, NULL); // Accept function? What is connfd, is it an HTTP request 0.0
    if (connfd < 0) {
      warn("accept error");
      continue;
    }
    handle_connection(connfd);
  }
  return EXIT_SUCCESS;
}
