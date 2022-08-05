/**
 * @file com_bw_processes_with_signal.c
 * @author Kushal Das (kushaldas30102002@gmail.com)
 * @brief communicate between the parent and child process
 * @version 0.1
 * @date 2022-08-05
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <fcntl.h>
#include <math.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

void handle_sigusr1(int sig) {
    printf("\nHINT:: multip[lication is repeated addition\n");
}
int main(int argc, char* argv[]) {
    pid_t pid = fork();
    if (pid == -1) return 1;
    if (pid == 0) {
        sleep(5);
        kill(getppid(), SIGUSR1);
    } else {
        // now handle the signal
        struct sigaction sa = {0};  // initialise the struct to 0
        sa.sa_flags = SA_RESTART;
        sa.sa_handler = &handle_sigusr1;
        sigaction(SIGUSR1, &sa, NULL);
        // parent process
        int x;
        printf("What is the value of 3x5 ? : ");
        scanf("%d", &x);
        if (x == 15) {
            printf("Right!!\n");
        } else {
            printf("Wrong!!\n");
        }
        wait(NULL);
    }
    return 0;
}
