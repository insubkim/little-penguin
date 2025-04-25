#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

int main()
{
    int fd = open("/sys/kernel/debug/fortytwo/foo", O_RDWR);
    int fd2 = open("/sys/kernel/debug/fortytwo/foo", O_RDWR);

    printf("open file %d\n", fd);
    printf("open file2 %d\n", fd2);

    char f[1024] = {0,};

    int write_bytes = write(fd, "inskim", 6);
    printf("write bytes :%d\n", write_bytes);

    int bytes = read(fd2, f, 1);

    printf("read bytes :%d\n", bytes);
    printf("read str :[%s]\n", f);
	

	time_t t;
	time(&t);
	while (1)
	{
		time_t t2;
		time(&t2);
		if (t2 - t > 1)
			break;
		sleep(1);
	}


    bytes = read(fd2, f, 1023);
    printf("read bytes :%d\n", bytes);
    printf("read str :[%s]\n", f);

    bytes = close(fd);
    int bytes2 = close(fd2);

    printf("close %d\n", bytes);
    printf("close %d\n", bytes2);
    return 0;
}
