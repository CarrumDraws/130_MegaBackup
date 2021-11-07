#include <stdio.h>
#include <stdlib.h>

/* 

This only tests for GET and PUT

Files Needed: a.txt, b.txt, c.txt, d.txt, e.txt, f.txt

Make sure to be in same directory for both terminals

HOW TO RUN testScript:
1.) Terminal 1, run "make" and then "./httpserver 8080"
2.) Terminal 2, run "gcc testScript.c" and then "./a.out"

*/

int main() {
    int x;

    system("rm -f x*.txt");

    // GET TESTS  =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    system("echo GET tests  =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");

    system("curl -s http://localhost:8080/a.txt -o d.txt");
    x = system("diff d.txt a.txt");
    if(x == 0) {
        printf("Test 1 PASSED\n");
    } else {
        printf("Test 1 failed\n");
    }

    system("curl -s http://localhost:8080/b.txt -o d.txt");
    x = system("diff d.txt b.txt");
    if(x == 0) {
        printf("Test 2 PASSED\n");
    } else {
        printf("Test 2 failed\n");
    }

    system("curl -s http://localhost:8080/c.txt -o d.txt");
    x = system("diff d.txt c.txt");
    if(x == 0) {
        printf("Test 3 PASSED\n");
    } else {
        printf("Test 3 failed\n");
    }

    system("curl -s http://localhost:8080/e.txt -o d.txt");
    x = system("diff d.txt e.txt");
    if(x == 0) {
        printf("Test 4 PASSED\n");
    } else {
        printf("Test 4 failed\n");
    }

    system("curl -s http://localhost:8080/Makefile -o d.txt");
    x = system("diff d.txt Makefile");
    if(x == 0) {
        printf("Test 5 PASSED\n");
    } else {
        printf("Test 5 failed\n");
    }

    system("curl -s http://localhost:8080/httpserver -o d.txt");
    x = system("diff d.txt httpserver");
    if(x == 0) {
        printf("Test 6 PASSED\n");
    } else {
        printf("Test 6 failed\n");
    }

    system("curl -s http://localhost:8080/httpserver.c -o d.txt");
    x = system("diff d.txt httpserver.c");
    if(x == 0) {
        printf("Test 7 PASSED\n");
    } else {
        printf("Test 7 failed\n");
    }

    system("curl -s http://localhost:8080/f.txt -o d.txt");
    x = system("diff d.txt f.txt");
    if(x == 0) {
        printf("Test 8 PASSED\n");
    } else {
        printf("Test 8 failed\n");
    }

    system("curl -s http://localhost:8080/WRITEUP.pdf -o d.txt");
    x = system("diff d.txt WRITEUP.pdf");
    if(x == 0) {
        printf("Test 9 PASSED\n");
    } else {
        printf("Test 9 failed\n");
    }

    system("curl -s http://localhost:8080/DESIGN.pdf -o d.txt");
    x = system("diff d.txt DESIGN.pdf");
    if(x == 0) {
        printf("Test 10 PASSED\n");
    } else {
        printf("Test 10 failed\n");
    }

    // PUT TESTS  =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    system("echo PUT tests =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");

    system("curl -T Makefile http://localhost:8080/d.txt");
    x = system("diff Makefile d.txt");
    if(x == 0) {
        printf("Test 1 PASSED\n");
    } else {
        printf("Test 1 failed\n");
    }

    system("curl -T a.txt http://localhost:8080/d.txt");
    x = system("diff a.txt d.txt");
    if(x == 0) {
        printf("Test 2 PASSED\n");
    } else {
        printf("Test 2 failed\n");
    }

    system("curl -T b.txt http://localhost:8080/d.txt");
    x = system("diff b.txt d.txt");
    if(x == 0) {
        printf("Test 3 PASSED\n");
    } else {
        printf("Test 3 failed\n");
    }

    system("curl -T c.txt http://localhost:8080/d.txt");
    x = system("diff c.txt d.txt");
    if(x == 0) {
        printf("Test 4 PASSED\n");
    } else {
        printf("Test 4 failed\n");
    }

    system("curl -T e.txt http://localhost:8080/d.txt");
    x = system("diff e.txt d.txt");
    if(x == 0) {
        printf("Test 5 PASSED\n");
    } else {
        printf("Test 5 failed\n");
    }

    system("curl -T a.txt http://localhost:8080/x1.txt");
    x = system("diff a.txt x1.txt");
    if(x == 0) {
        printf("Test 6 PASSED\n");
    } else {
        printf("Test 6 failed\n");
    }

    system("curl -T b.txt http://localhost:8080/x2.txt");
    x = system("diff b.txt x2.txt");
    if(x == 0) {
        printf("Test 7 PASSED\n");
    } else {
        printf("Test 7 failed\n");
    }

    system("curl -T c.txt http://localhost:8080/x3.txt");
    x = system("diff c.txt x3.txt");
    if(x == 0) {
        printf("Test 8 PASSED\n");
    } else {
        printf("Test 8 failed\n");
    }

    system("curl -T e.txt http://localhost:8080/x4.txt");
    x = system("diff e.txt x4.txt");
    if(x == 0) {
        printf("Test 9 PASSED\n");
    } else {
        printf("Test 9 failed\n");
    }

    system("curl -T httpserver http://localhost:8080/x5.txt");
    x = system("diff httpserver x5.txt");
    if(x == 0) {
        printf("Test 10 PASSED\n");
    } else {
        printf("Test 10 failed\n");
    }

    system("curl -T httpserver.c http://localhost:8080/x6.txt");
    x = system("diff httpserver.c x6.txt");
    if(x == 0) {
        printf("Test 11 PASSED\n");
    } else {
        printf("Test 11 failed\n");
    }

    system("curl -T a.txt http://localhost:8080/x4.txt");
    x = system("diff a.txt x4.txt");
    if(x == 0) {
        printf("Test 12 PASSED\n");
    } else {
        printf("Test 12 failed\n");
    }

    system("curl -T b.txt http://localhost:8080/x1.txt");
    x = system("diff b.txt x1.txt");
    if(x == 0) {
        printf("Test 13 PASSED\n");
    } else {
        printf("Test 13 failed\n");
    }

    // PUT tests with large binary files =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    system("echo PUT tests with large binary files similar to test 8 on GitLab =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");

    system("curl -T e.txt http://localhost:8080/x7.txt");
    x = system("diff e.txt x7.txt");
    if(x == 0) {
        printf("Test 1 PASSED\n");
    } else {
        printf("Test 1 failed\n");
    }

    system("curl -T f.txt http://localhost:8080/x8.txt");
    x = system("diff f.txt x8.txt");
    if(x == 0) {
        printf("Test 2 PASSED\n");
    } else {
        printf("Test 2 failed\n");
    }

    system("curl -T e.txt http://localhost:8080/x8.txt");
    x = system("diff e.txt x8.txt");
    if(x == 0) {
        printf("Test 3 PASSED\n");
    } else {
        printf("Test 3 failed\n");
    }

    system("curl -T f.txt http://localhost:8080/x7.txt");
    x = system("diff f.txt x7.txt");
    if(x == 0) {
        printf("Test 4 PASSED\n");
    } else {
        printf("Test 4 failed\n");
    }

    return 0;
}