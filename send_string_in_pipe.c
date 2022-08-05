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

int32_t main(int argc, char* argv[]) {
    int fd[2];
    if (pipe(fd) == -1) {
        return 1;
    }
    pid_t pid = fork();
    if (pid == -1) {
        return 2;
    }
    if (pid == 0) {
        // child process
        close(fd[0]);
        char str[200];
        printf("Input String : ");
        fgets(str, 200, stdin);
        str[strlen(str) - 1] = '\0';

        int n = strlen(str) + 1;
        if (write(fd[1], &n, sizeof(int)) == -1) {
            return 4;
        }

        if (write(fd[1], str, sizeof(char) * (n)) == -1) {
            return 3;
        }
        printf("The string sent is %s and its length is %d\n", str, n);

        close(fd[1]);
    } else {
        // parent process
        close(fd[1]);
        char str[200];
        int n;
        if (read(fd[0], &n, sizeof(int)) == -1) {
            return 5;
        }
        if (read(fd[0], str, sizeof(char) * n) == -1) {
            return 6;
        }

        printf("The string received is %s and its length is %d\n", str, n);
        close(fd[0]);
        wait(NULL);
    }
    return 0;
}
