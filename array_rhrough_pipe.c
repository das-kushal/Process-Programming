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
        return 2;
    }
    int pid = fork();
    if (pid == -1) {
        return 1;
    }
    if (pid == 0) {
        close(fd[0]);
        int n;
        int arr[100];
        srand(time(NULL));
        n = rand() % 10 + 1;
        for (int i = 0; i < n; i++) {
            arr[i] = rand() % 10 + 1;
        }
        if (write(fd[1], &n, sizeof(int)) == -1) {
            return 4;
        }
        if (write(fd[1], arr, sizeof(int) * n) == -1) {
            return 3;
        }
        close(fd[1]);
    } else {
        // parent process
        close(fd[1]);
        int arr[100];
        int n, sum = 0;
        if (read(fd[0], &n, sizeof(int)) == -1) {
            return 5;
        }
        if (read(fd[0], arr, sizeof(int) * n) == -1) {
            return 6;
        }
        close(fd[0]);
        printf("The value of n is %d\n", n);
        printf("The array is : [ ");
        for (int i = 0; i < n; i++) printf("%d ", arr[i]);
        printf("]\n");
        for (int i = 0; i < n; i++) sum += arr[i];
        printf("The sum is %d\n", sum);
        wait(NULL);
    }

    return 0;
}
