#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int id = fork();
    if (id == 0) sleep(1);
    /*
    getpid -> gives the process id of the current process
    getppid -> gives the process id of the parent process
    */
    printf("Current ID %d and parent id %d\n", getpid(), getppid());
    // if (id != 0) wait(NULL);

    if (wait(NULL) == -1) printf("No child process\n");
    return 0;
}
