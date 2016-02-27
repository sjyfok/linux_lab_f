#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main(void)
{
	int p_id;
	if ((p_id = fork()) == 0)
	{
			printf("This is child process\n");
	}
	else if (p_id == -1) 
	{
		printf("fork new process error!\n");
		exit(-1);
	}
	else 
	{
		wait(p_id);
			printf("This is parent process\n");
	}
}
