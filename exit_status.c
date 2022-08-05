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
        int err = execlp("ping", "ping", "-c", "3", "google.con", NULL);
        if (err == -1) {
            printf("Could not find program to execute\n");
            return 2;
        }
        printf("After the ping...\n");
    } else {
        // parent process
        int waitStatus;
        wait(&waitStatus);
        if (WIFEXITED(waitStatus)) {
            int statusCode = WEXITSTATUS(waitStatus);
            if (statusCode == 0) {
                printf("Success**\n");
            } else {
                printf("Failed with status code %d **\n", statusCode);
            }
        }
    }
    return 0;
}