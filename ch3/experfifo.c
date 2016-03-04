#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char *clientfifo = "/tmp/cfifo";
	int ret;
	pid_t pid;
	int fd_w;

	while(1)
	{
		ret = mkfifo(clientfifo, 0600);
		if (ret == -1)
		{
			printf("Fail to mkfifo\n");
			exit(1);
		}
		pid = fork();
		if (pid == 0)
		{
			fd_w = open(
		}
	}
}
