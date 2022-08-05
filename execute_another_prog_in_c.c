#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    pid_t pid = fork();
    execlp("ping", "ping", "-c", "3", "google.com", NULL);
    // but
    // ping google.com | grep "round trip" does not work in c
    // done in pipe_in_c program using fork 2 times

    return 0;
}
