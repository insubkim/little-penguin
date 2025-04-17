#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    int fd = open("/dev/fortytwo", O_RDONLY);

    printf("open file %d\n", fd);

    char f[1024] = {0,};

    int bytes = read(fd, f, 1023);

    printf("read %d\n", bytes);

    bytes = write(fd, f, 0);

    printf("write %d\n", bytes);

    bytes = close(fd);

    printf("close %d\n", bytes);
    return 0;
}
