#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>

int main(void)
{
	pid_t pid;

	pid = fork();
	if ( pid < 0)
	{
		perror("Fail to fork process:");
		exit(-1);
	}
	else if (pid == 0) 
	{
		int fd;
		char buf[256];

		printf("child process %d\n", getpid());
		fd = open("testfile.txt", O_RDONLY);

		read(fd, buf, 256);
		printf("buf: %s\n", buf);
	}
	else
	{
		//parent
		wait(NULL);
		printf("child  process %d is exit\n", pid); 
	}
	return 0;
}
