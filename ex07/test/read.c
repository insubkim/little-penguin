#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

int main()
{
    int fd = open("/sys/kernel/debug/fortytwo/foo", O_RDWR);

    printf("open file %d\n", fd);

    char f[5000] = {0,};

    int write_bytes = read(fd, f, 5000);
    printf("%s\n", f);

    int bytes = close(fd);

    return 0;
}
