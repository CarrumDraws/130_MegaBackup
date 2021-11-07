#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main() {
    int r;
    // system("./shoulders 2 a.txt > so.txt");
    // system("head -qn 2 a.txt > ho.txt");
    // r = system("diff so.txt ho.txt");
    // if (r == 0){
    //     printf("test 1 passed: No diff found\n");
    // } else if(r == 1) {
    //     printf("test 1 FAIL\n");
    // } else if (r > 1) {
    //     printf("test 1: Found a difference\n");
    // }

    // system("./shoulders 2 a.txt b.txt > so.txt");
    // system("head -qn 2 a.txt b.txt > ho.txt");
    // r = system("diff so.txt ho.txt");
    // if (r == 0){
    //     printf("test 2 passed: No diff found\n");
    // } else if(r == 1) {
    //     printf("test 2 FAIL\n");
    // } else if (r > 1) {
    //     printf("test 2: Found a difference\n");
    // }

    // system("./shoulders 10 a.txt b.txt > so.txt");
    // system("head -qn 10 a.txt b.txt > ho.txt");
    // r = system("diff so.txt ho.txt");
    // if (r == 0){
    //     printf("test 3 passed: No diff found\n");
    // } else if(r == 1) {
    //     printf("test 3 FAIL\n");
    // } else if (r > 1) {
    //     printf("test 3: Found a difference\n");
    // }

    // system("./shoulders 11 a.txt b.txt > so.txt");
    // system("head -qn 11 a.txt b.txt > ho.txt");
    // r = system("diff so.txt ho.txt");
    // if (r == 0){
    //     printf("test 4 passed: No diff found\n");
    // } else if(r == 1) {
    //     printf("test 4 FAIL\n");
    // } else if (r > 1) {
    //     printf("test 4: Found a difference\n");
    // }

    // system("./shoulders 15 a.txt b.txt > so.txt");
    // system("head -qn 15 a.txt b.txt > ho.txt");
    // r = system("diff so.txt ho.txt");
    // if (r == 0){
    //     printf("test 5 passed: No diff found\n");
    // } else if(r == 1) {
    //     printf("test 5 FAIL\n");
    // } else if (r > 1) {
    //     printf("test 5: Found a difference\n");
    // }

    // system("./shoulders 7 a.txt b.txt > so.txt");
    // system("head -qn 7 a.txt b.txt > ho.txt");
    // r = system("diff so.txt ho.txt");
    // if (r == 0){
    //     printf("test 6 passed: No diff found\n");
    // } else if(r == 1) {
    //     printf("test 6 FAIL\n");
    // } else if (r > 1) {
    //     printf("test 6: Found a difference\n");
    // }

    // system("./shoulders 8 a.txt b.txt > so.txt");
    // system("head -qn 8 a.txt b.txt > ho.txt");
    // r = system("diff so.txt ho.txt");
    // if (r == 0){
    //     printf("test 7 passed: No diff found\n");
    // } else if(r == 1) {
    //     printf("test 7 FAIL\n");
    // } else if (r > 1) {
    //     printf("test 7: Found a difference\n");
    // }

    // system("./shoulders 9 a.txt b.txt > so.txt");
    // system("head -qn 9 a.txt b.txt > ho.txt");
    // r = system("diff so.txt ho.txt");
    // if (r == 0){
    //     printf("test 8 passed: No diff found\n");
    // } else if(r == 1) {
    //     printf("test 8 FAIL\n");
    // } else if (r > 1) {
    //     printf("test 8: Found a difference\n");
    // }

    // system("./shoulders 2 b.txt a.txt > so.txt");
    // system("head -qn 2 b.txt a.txt > ho.txt");
    // r = system("diff so.txt ho.txt");
    // if (r == 0){
    //     printf("test 9 passed: No diff found\n");
    // } else if(r == 1) {
    //     printf("test 9 FAIL\n");
    // } else if (r > 1) {
    //     printf("test 9: Found a difference\n");
    // }

    // system("./shoulders 10 b.txt a.txt > so.txt");
    // system("head -qn 10 b.txt a.txt > ho.txt");
    // r = system("diff so.txt ho.txt");
    // if (r == 0){
    //     printf("test 10 passed: No diff found\n");
    // } else if(r == 1) {
    //     printf("test 10 FAIL\n");
    // } else if (r > 1) {
    //     printf("test 10: Found a difference\n");
    // }

    // system("./shoulders 11 b.txt a.txt > so.txt");
    // system("head -qn 11 b.txt a.txt > ho.txt");
    // r = system("diff so.txt ho.txt");
    // if (r == 0){
    //     printf("test 11 passed: No diff found\n");
    // } else if(r == 1) {
    //     printf("test 11 FAIL\n");
    // } else if (r > 1) {
    //     printf("test 11: Found a difference\n");
    // }

    // system("./shoulders 12 b.txt a.txt > so.txt");
    // system("head -qn 12 b.txt a.txt > ho.txt");
    // r = system("diff so.txt ho.txt");
    // if (r == 0){
    //     printf("test 12 passed: No diff found\n");
    // } else if(r == 1) {
    //     printf("test 12 FAIL\n");
    // } else if (r > 1) {
    //     printf("test 12: Found a difference\n");
    // }

    // system("./shoulders 13 b.txt a.txt > so.txt");
    // system("head -qn 13 b.txt a.txt > ho.txt");
    // r = system("diff so.txt ho.txt");
    // if (r == 0){
    //     printf("test 13 passed: No diff found\n");
    // } else if(r == 1) {
    //     printf("test 13 FAIL\n");
    // } else if (r > 1) {
    //     printf("test 13: Found a difference\n");
    // }

    // system("./shoulders 8 b.txt a.txt > so.txt");
    // system("head -qn 8 b.txt a.txt > ho.txt");
    // r = system("diff so.txt ho.txt");
    // if (r == 0){
    //     printf("test 14 passed: No diff found\n");
    // } else if(r == 1) {
    //     printf("test 14 FAIL\n");
    // } else if (r > 1) {
    //     printf("test 14: Found a difference\n");
    // }

    // system("./shoulders 9 b.txt a.txt > so.txt");
    // system("head -qn 9 b.txt a.txt > ho.txt");
    // r = system("diff so.txt ho.txt");
    // if (r == 0){
    //     printf("test 15 passed: No diff found\n");
    // } else if(r == 1) {
    //     printf("test 15 FAIL\n");
    // } else if (r > 1) {
    //     printf("test 15: Found a difference\n");
    // }

    // system("./shoulders 80 a.txt b.txt b.txt b.txt a.txt > so.txt");
    // system("head -qn 80 a.txt b.txt b.txt b.txt a.txt > ho.txt");
    // r = system("diff so.txt ho.txt");
    // if (r == 0){
    //     printf("test 16 passed: No diff found\n");
    // } else if(r == 1) {
    //     printf("test 16 FAIL\n");
    // } else if (r > 1) {
    //     printf("test 16: Found a difference\n");
    // }

    // system("./shoulders 2 error a.txt > so.txt");
    // system("head -qn 2 error a.txt > ho.txt");
    // r = system("diff so.txt ho.txt");
    // if (r == 0){
    //     printf("test 17 passed: No diff found\n");
    // } else if(r == 1) {
    //     printf("test 17 FAIL\n");
    // } else if (r > 1) {
    //     printf("test 17: Found a difference\n");
    // }

    system("./shoulders 4f error a.txt > so.txt");
    system("head -qn 4f error a.txt > ho.txt");
    r = system("diff so.txt ho.txt");
    if (r == 0){
        printf("test 18 passed: No diff found\n");
    } else if(r == 1) {
        printf("test 18 FAIL\n");
    } else if (r > 1) {
        printf("test 18: Found a difference\n");
    }

    // system("./shoulders 4 bad b.txt wrong > so.txt");
    // system("head -qn 4 bad b.txt wrong > ho.txt");
    // r = system("diff so.txt ho.txt");
    // if (r == 0){
    //     printf("test 19 passed: No diff found\n");
    // } else if(r == 1) {
    //     printf("test 19 FAIL\n");
    // } else if (r > 1) {
    //     printf("test 19: Found a difference\n");
    // }

    // system("./shoulders 40 a.txt b.txt > so.txt");
    // system("head -qn 40 a.txt b.txt > ho.txt");
    // r = system("diff so.txt ho.txt");
    // if (r == 0){
    //     printf("test 20 passed: No diff found\n");
    // } else if(r == 1) {
    //     printf("test 20 FAIL\n");
    // } else if (r > 1) {
    //     printf("test 20: Found a difference\n");
    // }

    // system("./shoulders 60 b.txt a.txt > so.txt");
    // system("head -qn 60 b.txt a.txt > ho.txt");
    // r = system("diff so.txt ho.txt");
    // if (r == 0){
    //     printf("test 21 passed: No diff found\n");
    // } else if(r == 1) {
    //     printf("test 21 FAIL\n");
    // } else if (r > 1) {
    //     printf("test 21: Found a difference\n");
    // }

    // system("./shoulders 50 DESIGN.pdf > so.txt");
    // system("head -qn 50 DESIGN.pdf > ho.txt");
    // r = system("diff so.txt ho.txt");
    // if (r == 0){
    //     printf("test 22 passed: No diff found\n");
    // } else if(r == 1) {
    //     printf("test 22 FAIL\n");
    // } else if (r > 1) {
    //     printf("test 22: Found a difference\n");
    // }

    // system("./shoulders 40 DESIGN.pdf a.txt > so.txt");
    // system("head -qn 40 DESIGN.pdf a.txt > ho.txt");
    // r = system("diff so.txt ho.txt");
    // if (r == 0){
    //     printf("test 23 passed: No diff found\n");
    // } else if(r == 1) {
    //     printf("test 23 FAIL\n");
    // } else if (r > 1) {
    //     printf("test 23: Found a difference\n");
    // }

    // system("./shoulders 70 DESIGN.pdf a.txt b.txt WRITEUP.pdf Makefile shoulders > so.txt");
    // system("head -qn 70 DESIGN.pdf a.txt b.txt WRITEUP.pdf Makefile shoulders > ho.txt");
    // r = system("diff so.txt ho.txt");
    // if (r == 0){
    //     printf("test 24 passed: No diff found\n");
    // } else if(r == 1) {
    //     printf("test 24 FAIL\n");
    // } else if (r > 1) {
    //     printf("test 24: Found a difference\n");
    // }

    // system("./shoulders 60 error a.txt - < r.txt > so.txt");
    // system("head -qn 60 error a.txt - < r.txt > ho.txt");
    // r = system("diff so.txt ho.txt");
    // if (r == 0){
    //     printf("test 25 passed: No diff found\n");
    // } else if(r == 1) {
    //     printf("test 25 FAIL\n");
    // } else if (r > 1) {
    //     printf("test 25: Found a difference\n");
    // }

    // system("./shoulders 5 a.txt - b.txt < r.txt > so.txt");
    // system("head -qn 5 a.txt - b.txt < r.txt > ho.txt");
    // r = system("diff so.txt ho.txt");
    // if (r == 0){
    //     printf("test 26 passed: No diff found\n");
    // } else if(r == 1) {
    //     printf("test 26 FAIL\n");
    // } else if (r > 1) {
    //     printf("test 26: Found a difference\n");
    // }

    // system("./shoulders 12 - < r.txt > so.txt");
    // system("head -qn 12 - < r.txt > ho.txt");
    // r = system("diff so.txt ho.txt");
    // if (r == 0){
    //     printf("test 27 passed: No diff found\n");
    // } else if(r == 1) {
    //     printf("test 27 FAIL\n");
    // } else if (r > 1) {
    //     printf("test 27: Found a difference\n");
    // }

    // system("./shoulders 25 - DESIGN.pdf < r.txt > so.txt");
    // system("head -qn 25 - DESIGN.pdf < r.txt > ho.txt");
    // r = system("diff so.txt ho.txt");
    // if (r == 0){
    //     printf("test 28 passed: No diff found\n");
    // } else if(r == 1) {
    //     printf("test 28 FAIL\n");
    // } else if (r > 1) {
    //     printf("test 28: Found a difference\n");
    // }

    system("./shoulders 20 WRITEUP.pdf - DESIGN.pdf < r.txt > so.txt");
    system("head -qn 20 WRITEUP.pdf - DESIGN.pdf < r.txt > ho.txt");
    r = system("diff so.txt ho.txt");
    if (r == 0){
        printf("test 29 passed: No diff found\n");
    } else if(r == 1) {
        printf("test 29 FAIL\n");
    } else if (r > 1) {
        printf("test 29: Found a difference\n");
    }

    // system("./shoulders 50 < r.txt > so.txt");
    // system("head -qn 50 < r.txt > ho.txt");
    // r = system("diff so.txt ho.txt");
    // if (r == 0){
    //     printf("test 30 passed: No diff found\n");
    // } else if(r == 1) {
    //     printf("test 30 FAIL\n");
    // } else if (r > 1) {
    //     printf("test 30: Found a difference\n");
    // }

    // system("./shoulders 10000 < r.txt > so.txt");
    // system("head -qn 10000 < r.txt > ho.txt");
    // r = system("diff so.txt ho.txt");
    // if (r == 0){
    //     printf("test 31 passed: No diff found\n");
    // } else if(r == 1) {
    //     printf("test 31 FAIL\n");
    // } else if (r > 1) {
    //     printf("test 31: Found a difference\n");
    // }

    // system("./shoulders 10000 - < r.txt > so.txt");
    // system("head -qn 10000 - < r.txt > ho.txt");
    // r = system("diff so.txt ho.txt");
    // if (r == 0) {
    //     printf("test 32 passed: No diff found\n");
    // } else if(r == 1) {
    //     printf("test 32 FAIL\n");
    // } else if (r > 1) {
    //     printf("test 32: Found a difference\n");
    // }

    // system("./shoulders 905 - a.txt - < r.txt > so.txt");
    // system("head -qn 905 - a.txt - < r.txt > ho.txt");
    // r = system("diff so.txt ho.txt");
    // if (r == 0) {
    //     printf("test 32 passed: No diff found\n");
    // } else if(r == 1) {
    //     printf("test 32 FAIL\n");
    // } else if (r > 1) {
    //     printf("test 32: Found a difference\n");
    // }

    // system("./shoulders 500 a.txt > so.txt");
    // system("head -qn 500 a.txt > ho.txt");
    // r = system("diff so.txt ho.txt");
    // if (r == 0){
    //     printf("test 33 PASSED: No diff found\n");
    // } else if(r == 1) {
    //     printf("test 33 FAILED\n");
    // } else if (r > 1) {
    //     printf("test 33: Found a difference\n");
    // }

    // system("./shoulders 10000 a.txt > so.txt");
    // system("head -qn 10000 a.txt > ho.txt");
    // r = system("diff so.txt ho.txt");
    // if (r == 0){
    //     printf("test 34 PASSED: No diff found\n");
    // } else if(r == 1) {
    //     printf("test 34 FAILED\n");
    // } else if (r > 1) {
    //     printf("test 34: Found a difference\n");
    // }
    // return 0;
}
