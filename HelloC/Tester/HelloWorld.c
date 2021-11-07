#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <err.h>
#include <string.h>

#define BUFSIZE 9

int main(){
    char str[] = "hello my na;me is calum";
    char str2[] = "hello my name is calum";
    char body[10];
    char w1[30];
    char w2[30];
    char *delim = " ";

    // String concatination - WARNING: STRCAT IS DANGEROUS- IT CAN OVERWRITE MEMORY
    char test[] = "howdy ""howdy";
    strcat(test, " ho");
    if(strcmp(test, "howdy howdy ho") == 0) printf("Equiv\n");

    // // Match Fail
    // int temp = sscanf(str, "%s /%s HTTP/1.1", w1, w2); 
    // printf("Matches Found: %d : %s-----%s\n", temp, w1, w2);

    // // Match Success
    // temp = sscanf(str, "%[a-zA-Z ];%[a-zA-Z ]", w1, w2);
    // printf("Matches Found: %d : %s-----%s\n", temp, w1, w2);
    // if(strncmp(w1, "hello my na", 12) == 0) printf("Fixed-size array equals string!\n");
    
    // strtok : destructive string breaker
    // printf("Before strtok: %s\n", str2);
    // char *buf = strtok(str2, delim);
    // while (buf != NULL) {
    //     printf("%s\n", buf);
    //     buf = strtok(NULL, delim);
    // }
    // printf("After strtok: %s\n", str2);

    // strrchr : Last token finder
    // char *s = "some---very---big---contentscontentscontents";
    // char *last = strrchr(s, "---");
    // if (last != NULL) {
    //     last += 1;
    //     printf("Last token: '%s'\n", last);
    //     strcpy(body, last);
    // }
    // printf("Body: '%s'\n", body);

    char w3[30];
    w3[0] = '\0';
    strcat(w3, "Hello");
    strcat(w3, " World!");
    char nums[10];
    sprintf(nums, "%d", 12345);
    strcat(w3, nums);
    printf("%s\n", w3);

    // char *test = "User-Agent: curl/7.58.0";
    // int temp = sscanf(test, "%[^:]:%[^:]", w1, w2);
    // printf("Matches Found: %d : %s-----%s\n", temp, w1, w2);
    // if(strncmp(w1, "hello my na", 12) == 0) printf("Fixed-size array equals string!\n");

    // Checking if a substring exists with strstr(), non-destructive!
    // char str3[] = "hello my name is calum";
    // char str4[] = "named";
    // char *val = strstr(str3, str4); // NULL if none found
    // printf("Match Found: %s\n", val);
    // printf("After strstr: %s\n", str3);
    // printf("After strstr: %s\n", str4);
    return 0;
}