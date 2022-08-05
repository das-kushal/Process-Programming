#include <fcntl.h>
#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

void handle_sigtstp(int sig) {
    printf("Stop not allowed\n");
}

void handle_sigcont(int sig) {
    printf("Input number: ");
    fflush(stdout);
}
int main(int argc, char* argv[]) {
    // for handling the stop signal
    struct sigaction sa;
    // sa.sa_handler = &handle_sigtstp;
    // sa.sa_flags = SA_RESTART;
    // sigaction(SIGTSTP, &sa, NULL);

    // for handling the continue signal
    // struct sigaction sa;
    sa.sa_handler = &handle_sigcont;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGCONT, &sa, NULL);

    int x;
    printf("Input number : ");
    scanf("%d", &x);
    printf("Result %d * 5 = %d\n", x, x * 5);
    return 0;
}
