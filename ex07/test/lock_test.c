#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

int main()
{
	int fd = open("/sys/kernel/debug/fortytwo/foo", O_RDWR);

	printf("open file %d\n", fd);

	char f[1000] = {0,};
	for (int i = 0; i < 1000; i++)
	{
		f[i] = "0123456789"[i % 10];
	}
	int write_bytes = write(fd, f, 1000);
	printf("write bytes :%d\n", write_bytes);
	int bytes = close(fd);

	return 0;
}
