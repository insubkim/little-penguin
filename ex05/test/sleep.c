#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

int main()
{
    int fd = open("/dev/fortytwo", O_RDONLY);

    printf("open file %d\n", fd);

    char f[1024] = {0,};

    int bytes = read(fd, f, 1023);

    printf("read %d\n", bytes);
    printf("read str :[%s]\n", f);
	
//    bytes = write(fd, f, 0);

//    printf("write %d\n", bytes);
	time_t t;
	time(&t);
	while (1)
	{
		time_t t2;
		time(&t2);
	printf("[%d] [%d] [%d]\n", t, t2, t2 - t);
		if (t2 - t > 10)
			break;
		sleep(1);
	}

    bytes = close(fd);

    printf("close %d\n", bytes);
    return 0;
}
