#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#define nline printf("\n");
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
void print(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d\t", arr[i]);
    nline
}
int main() {
    int arr[] = {1, 2, 3, 4, 1, 2};
    int start, end = 0;
    int fd[2];
    int n = sizeof(arr) / sizeof(int);
    if (pipe(fd) == -1) {
        return 1;
    }
    pid_t id = fork();
    if (id == -1) {
        return 2;
    }
    if (id == 0) {
        start = 0;
        end = n / 2;
    } else {
        start = n / 2;
        end = n;
    }
    int sum = 0;

    for (int i = start; i < end; i++) {
        sum += arr[i];
    }
    printf("the partial sum is %d from process %u\n", sum, getpid());
    if (id == 0) {
        close(fd[0]);
        write(fd[1], &sum, sizeof(int));
        close(fd[1]);
    } else {
        int sumFromChild;
        close(fd[1]);
        read(fd[0], &sumFromChild, sizeof(int));
        close(fd[0]);

        int totSum = sum + sumFromChild;
        printf("Total sum is %d\n", totSum);
        wait(NULL);
    }
    return 0;
}
