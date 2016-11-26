#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

void sigint_handler(int sig)
{
	printf("received SIGINT signal successed!\n");
	return ;
}

int main(void)
{
	pid_t pid;
//	signal(SIGINT, sigint_handler);
	pid = fork();
	if (pid == 0)
	{
		printf("child pid = %d\n", getpid());
		sleep(5);
		printf("child pid = %d\n", getpid());
		sleep(5);
		printf("child pid = %d\n", getpid());
		exit(1);
	}
	else if (pid > 0)
	{
	signal(SIGINT, sigint_handler);
		pause();
	}
	else
	{
		printf("fail to fork()\n");
		exit(1);
	}
}
