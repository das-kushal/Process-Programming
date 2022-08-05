#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, char* argv[]) {
    if (mkfifo("myfifo1", 0777) == -1) {
        if (errno == EEXIST) {
            printf("Could not create fifo file\n");
            return 1;
        }
    }
    printf("Opening...");
    int fd = open("myfifo1", O_WRONLY);
    // int fd2=open("myfifo1",O_RDONLY); -> for read only
    printf("Opened...");
    int x = 100;  // prints d ASCII of 100 ( 97 is 'a' )
    if (write(fd, &x, sizeof(x)) == -1) {
        return 2;
    }
    close(fd);
    printf("Closed...");
    return 0;
}