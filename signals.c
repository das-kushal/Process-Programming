#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
int main() {
    pid_t pid = fork();
    if (pid == -1) {
        return 1;
    }
    if (pid == 0) {
        while (1) {
            printf("Some text\n");
            usleep(50000);
        }
    } else {
        sleep(1);
        kill(pid, SIGKILL);  // sending a signal
        wait(NULL);
    }
    return 0;
}
