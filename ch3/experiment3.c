#include <wait.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define	MAX_LINE	80

int main(void)
{
	int fd[2];
	int ret;
	pid_t pid1, pid2;
	
	char buf[MAX_LINE];

	ret = pipe(fd);
	if (ret == 0)
	{
		pid1 = fork();
		if (pid1 == 0)
		{
			close(fd[1]);
			sleep(2);
			read(fd[0], buf, MAX_LINE);
			printf("chile read pipe: %s\n", buf);
			exit(0);
		}
		else
		{
			if (pid1 > 0)
			{
				pid2 = fork();
				if (pid2 == 0)
				{
					close(fd[0]);
					strcpy(buf, "this is test for pipe\n");
					write(fd[1], buf, sizeof(buf));
					printf("brather write pipe %s\n", buf);
					close(fd[1]);
					printf("brather close wirte pipe\n");
					sleep(5);
				}
				else 
				{
					close(fd[0]);
					close(fd[1]);
					while (wait(NULL) != -1);

				}
			}
		}
	}
	return 0;
}
