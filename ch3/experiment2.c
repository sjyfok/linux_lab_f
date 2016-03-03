#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void sigint_handler(int sig)
{
	printf("received SIGINT signal sucessed\n");
	return;
}

int main(void)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		printf("child id: %d\n", getpid());
		sleep(2);
		printf("child id: %d sleep 2 second\n", getpid());
		sleep(2);
		printf("child id: %d sleep 2 second again\n", getpid());
		exit(0);
	}
	else
	{
		if (pid > 0)
		{
			signal(SIGINT, sigint_handler);
			pause();
		}
		else 
		{
			if (pid < 0)
			{
				printf("fail to fork\n");
				exit(1);
			}
		}
	}

}
