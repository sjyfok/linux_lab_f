#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <wait.h>
#include <stdlib.h>

void sigchld_handler(int sig)
{
	pid_t pid;
	int status;

	for (; (pid= waitpid(-1, &status, WNOHANG)) >0;)
	{
		printf("child %d died:%d\n", pid, WEXITSTATUS(status));
		printf("hi,parent process received SIGHLD signal sucessfully\n");
	}
	return ;
}	


int main(void)
{
	int pid;

	pid = fork();
	if (pid == 0)
	{
		printf("child:%d\n", getpid());
		sleep(2);
		exit(0);
	}
	else if (pid > 0) 
	{
		signal(SIGCHLD, sigchld_handler);
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
