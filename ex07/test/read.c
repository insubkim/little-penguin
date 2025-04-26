#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

int main()
{
	int fd = open("/sys/kernel/debug/fortytwo/foo", O_RDWR);

	printf("open file %d\n", fd);

	char f[100000] = {0,};

	int write_bytes = read(fd, f, 100000);
	//printf("[%d] :%s\n", write_bytes, f);
	printf("%s",  f);

	int bytes = close(fd);

	return 0;
}
