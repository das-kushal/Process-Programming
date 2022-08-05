#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    pid_t pid = fork();
    if (pid == -1) return 1;
    if (pid == 0) {
        // child process
        printf("Going to ping...\n");
        execlp("ping", "ping", "-c", "3", "google.com", NULL);
        printf("After the ping...\n");
    } else {
        // parent process
        wait(NULL);
        printf("Success**\n");
    }
    return 0;
}