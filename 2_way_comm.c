#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int p1[2];  // child to parent
    int p2[2];  // parent to child
    if (pipe(p1) == -1) {
        return 1;
    }
    if (pipe(p2) == -1) {
        return 1;
    }
    pid_t pid = fork();
    if (pid == -1) {
        return 2;
    }
    if (pid == 0) {
        // child process
        close(p1[0]);
        close(p2[1]);
        int x;
        if (read(p2[0], &x, sizeof(x)) == -1) {
            return 3;
        }
        printf("Received %d from the parent process\n", x);
        x *= 4;
        if (write(p1[1], &x, sizeof(int)) == -1) {
            return 4;
        }
        printf("Wrote back to parent process from the child process %d\n", x);
        close(p1[1]);
        close(p2[0]);
    } else {
        // parent process
        close(p1[1]);
        close(p2[0]);
        srand(time(NULL));
        int num = rand() % 10;
        if (write(p2[1], &num, sizeof(int)) == -1) {
            return 5;
        }
        printf("Wrote %d from parent\n", num);
        sleep(1);
        if (read(p1[0], &num, sizeof(num)) == -1) return 6;
        printf("Read %d from the child process\n", num);
        close(p1[0]);
        close(p2[1]);
        wait(NULL);
    }
    return 0;
}
