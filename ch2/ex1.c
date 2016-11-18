#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void)
{
	pid_t cpid = 0;

	cpid = fork();
	if (cpid < 0)
	{
		printf("fail to fork\n");
	}
	else if(cpid == 0)
	{
		printf("child is running\n");
		exit(0);
	}
	else
	{
		pid_t pid;
		pid = wait(NULL);
		printf("parent, %d is exit\n", pid);
	}
	return 0;
}
