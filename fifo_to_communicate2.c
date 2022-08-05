#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int arr[5];
    int fd = open("sum", O_RDONLY);
    if (fd == -1) {
        printf("The fifo cannot open\n");
        return 1;
    }
    if (read(fd, arr, sizeof(int) * 5)) {
        return 2;
    }
    close(fd);
    uint32_t sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += arr[i];
        printf("The element is %d\n", arr[i]);
    }
    printf("The sum is %d\n", sum);
}