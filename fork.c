#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#define nline printf("\n");

int main() {
    /*this creates 4 processes*/
    // fork();
    // fork();
    // printf("Hello world\n");

    /*but if we want 3*/
    int id = fork();
    if (id != 0) fork();
    printf("Hello world\n");
    return 0;
}
