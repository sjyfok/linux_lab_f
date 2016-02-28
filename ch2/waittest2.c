#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
	int status;
	pid_t pc, pr;

	pc = fork();
	if (pc < 0)
	{
		printf("error ocurred!\n");
	}
	else if (pc == 0)
	{
		printf("This is child process with pid of %d.\n", getpid());
		exit(3);
	}
	else
	{
		pr = wait(&status);
		if (WIFEXITED(status))
		{
			printf("The  child process %d exit normally.\n", pr);
			printf("The return code is %d.\n", WEXITSTATUS(status));
		}
		else
		{
			printf("The child process %d exit abnormally.\n", pr);
		}
	}
}
