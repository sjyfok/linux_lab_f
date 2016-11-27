#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#define	FIFO_SERVER "/tmp/fifoserver"
#define	BUFFERSIZE	80

int main(void)
{
	int ret;
	pid_t pid;
	int fdwr, fdrd;

	ret = mkfifo(FIFO_SERVER, 0666);
	if (ret < 0)
	{
		printf("fail to mkfifo.\n");
		exit(1);
	}
	printf("success to mkfifo.\n");

	pid = fork();
	if (pid == 0)
	{
		int bytes;
		char buf[BUFFERSIZE] = "hello\n";
		fdwr = open(FIFO_SERVER, O_WRONLY);
		if (fdwr < 0)
		{
			printf("fail to open\n");
			exit(2);
		}
		bytes = write(fdwr, buf, strlen(buf));
		if (bytes < 0)
		{
			printf("fail to write.\n");
			exit(3);
		}
		printf("sucess wirte to fifo\n");
		close(fdwr);
	}
	else if (pid > 0)
	{
		char rdbuf[BUFFERSIZE] = "test buf";
		int bytes;

		fdrd = open(FIFO_SERVER, O_RDONLY);
		if (fdrd < 0)
		{
			printf("fail to open for rd\n");
			exit(4);
		}
		printf("%s\n", rdbuf);
		bytes = read(fdrd, rdbuf, BUFFERSIZE);
		if (bytes < 0)
		{
			printf("fail to read form fifo\n");
			exit(5);
		}
		rdbuf[bytes] = '\0';
		printf("fifo: %s\n", rdbuf);
		close(fdrd);
	}
	else
	{
		printf("fail to fork()\n");
		exit(6);
	}
}
