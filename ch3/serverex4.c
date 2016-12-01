#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#define	FIFO_SERVER "/tmp/cfifo"
#define	BUFFERSIZE	80

int main(void)
{
	int ret;
	pid_t pid;
	int fdwr, fdrd;
	char *ptr;

	while(((ret=mkfifo(FIFO_SERVER, 0666) < 0)
	{
		printf("fail to mkfifo.\n");
		sleep(5);
		continue;
	}

	printf("success to mkfifo.\n");

	fdrd = open(FIFO_SERVER, O_RDONLY);
	if (fdrd < 0)
	{
		printf("fail to open file.\n");
		return 1;
	}
	else
	{
		bytes = read(fdrd, rdbuf, BUFFERSIZE);
		if (bytes < 0)
		{
			printf("fail to read.\n");
		}
		close(fdrd);
		printf("%s", rdbuf);
//		ptr = malloc(sizeof(char)*bytes);
		
	}
}
