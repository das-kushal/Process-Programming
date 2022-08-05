#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define nline printf("\n");

int main(int argc, char *argv[]) {
    int id = fork();
    int n;
    if (id == 0) {
        n = 1;
    } else {
        n = 6;
    }
    if (id != 0) {
        wait(NULL);
    }
    int i;
    for (i = n; i < n + 5; i++) {
        printf("%d ", i);
        fflush(stdout);
    }
    // if it is not the child process then line break
    if (id != 0) {
        nline;
    }
    return 0;
}
