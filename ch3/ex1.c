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
	for(;(pid=waitpid(-1, &status, WNOHANG))>0;)
	{
		printf("child %d died:%d\n", pid, WEXITSTATUS(status));
		printf("hi, parent process received SIGCHLD signal successfully!\n");
	}
	return ;
}


int main(void)
{
	pid_t pid;
	pid = fork();
	if (pid == 0)
	{
		printf("child pid = %d\n", getpid());
		sleep(5);
		exit(1);
	} 
	else if (pid > 0)
	{
		signal(SIGCHLD, sigchld_handler);
		pause();
	}
	else
	{
		printf("fail to fork()\n");
		exit(1);
	}
}

