#include <errno.h>
#include <error.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

char command[256];

int main(void)
{
	int rtn;
	while(1)
	{
		printf(">");
		fgets(command, 256, stdin);
		command[strlen(command)-1] = 0;
		if (fork() == 0)
		{
			execlp(command, command);
			perror(command);
			exit(-1);
		}
		else 
		{
			wait(&rtn);
			printf("child process return %d\n", rtn);
		}
	}
}

