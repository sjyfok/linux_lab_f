#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	pid_t pc, pr;
	pc = fork();
	if (pc < 0)
	{
		printf("error ocurred!\n");
	}
	else if (pc == 0)
	{
		printf("This is child process with pid of %d\n", getpid());
		sleep(10);
	}
	else 
	{
		pr = wait(NULL);
		printf("I catched a child process with pid of %d\n", pr);
	}
	exit(0);
}
