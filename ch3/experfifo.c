#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

#define FIFO_SERVER "/tmp/fifoserver"
#define	BUFFERSIZE	80

int main(void)
{
	int ret;
	pid_t pid;
	int fd_w, fd_r;
	char buf[BUFFERSIZE];

	ret = mkfifo(FIFO_SERVER, 0600);
	if (ret == -1)
	{
		printf("Fail to mkfifo\n");
		exit(1);
	}
	printf("mkfifo successful\n");
	pid = fork();
	if (pid == 0)
	{
		fd_w = open(FIFO_SERVER, O_WRONLY);
		if (fd_w == -1)
		{
			printf("fail to open fifo\n");
			exit(1);
		}
		strcpy(buf, "this is test for fifo\n");
		ret = write(fd_w, buf, strlen(buf));
		if (ret == -1)
		{
			printf("Fail to write to fifo\n");
			exit(1);
		}
		printf("write to fifo is success\n");
		close(fd_w);
	}
	else
	{
		if (pid > 0)
		{
			strcpy(buf, "this is old text\n");
			printf("old:%s", buf);
			fd_r = open(FIFO_SERVER, O_RDONLY);
			ret = read(fd_r, buf, BUFFERSIZE);
			printf("new:%s\n", buf);
			close(fd_r);
		}
		else
		{
			printf("fail to fork\n");
			exit(1);
		}
	}
}
