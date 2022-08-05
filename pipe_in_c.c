#include <fcntl.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int fd[2];
    if (pipe(fd) == -1) {
        return 1;
    }
    pid_t pid1 = fork();
    if (pid1 < 0) {
        return 2;
    }
    if (pid1 == 0) {
        // child process 1 (ping)
        dup2(fd[1], STDOUT_FILENO);  // ping is on the write end of the pipe so fd[1]
        close(fd[0]);
        close(fd[1]);
        execlp("ping", "ping", "-c", "5", "google.com", NULL);
    }
    pid_t pid2 = fork();
    if (pid2 == -1) {
        return 3;
    }
    if (pid2 == 0) {
        // child process 2 (grep)
        dup2(fd[0], STDIN_FILENO);  // grep is on the reading end of the pipe so fd[0]
        close(fd[0]);
        close(fd[1]);
        execlp("grep", "grep", "round-trip", NULL);
    }
    // close both ends of the pipe in the main process as well so that the grep stops reading and continues
    close(fd[0]);
    close(fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    return 0;
}
