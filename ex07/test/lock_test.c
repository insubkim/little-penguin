#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

int main()
{
    int fd = open("/sys/kernel/debug/fortytwo/foo", O_RDWR);

    printf("open file %d\n", fd);

    char f[1024] = {0,};

    int write_bytes = write(fd, "inskim", 6);
    printf("write bytes :%d\n", write_bytes);

    int bytes = close(fd);

    return 0;
}
