#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
int main() {
    int arr[5];
    srand(time(NULL));
    int i;
    for (i = 0; i < 5; i++) {
        arr[i] = rand() % 100;
        printf("Wrote %d in fifo\n", arr[i]);
    }

    int fd = open("sum", O_WRONLY);
    if (fd == -1) {
        printf("The fifo file is not created\n");
        return 1;
    }
    // if (write(fd, &arr[i], sizeof(int)) == -1) {
    //     return 2;
    // }
    // this one writes all the 5 elements in 1 go
    if (write(fd, arr, sizeof(int) * 5) == -1) {
        return 2;
    }
    close(fd);
    return 0;
}
