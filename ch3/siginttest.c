#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void my_func(int sigo_num)
{
	printf("If you want to quit, please try 'ctrl+\\'.\n");
}

int main(void)
{
	sigset_t set;

	struct sigaction action1, action2;
	if (sigemptyset(&set)<0) 
	{
		perror("sigemptyset");
		exit(1);
	}
	if (sigaddset(&set, SIGQUIT)<0)
	{
		perror("sigaddset SIGQUIT");
		exit(1);
	}
	if (sigaddset(&set, SIGINT)<0)
	{
		perror("sigaddset SIGINT");
		exit(1);
	}
	if (sigprocmask(SIG_BLOCK, &set, NULL) < 0) 
	{
		perror("sigprocmask SIG_BLOCK");
		exit(1);
	}
	else 
	{
		printf("Blocked and sleep for 5s ...\n");
		sleep(5);
	}
	if (sigprocmask(SIG_UNBLOCK, &set, NULL) < 0)
	{
		perror("sigprocmask SIG_UNBLCOK");
		exit(1);
	}
	else 
	{
		printf("unblock\n");
		sleep(2);
		printf("If you want to quit this program, please try 'ctrl+\\'...\n");
	}
	while(1)
	{
		if (sigismember(&set, SIGINT))
		{
			sigemptyset(&action1.sa_mask);
			action1.sa_handler = my_func;
			sigaction(SIGINT, &action1, NULL);
		}
		else
			if (sigismember(&set, SIGQUIT))
			{
				sigemptyset(&action2.sa_mask);
				action2.sa_handler = SIG_DFL;
				sigaction(SIGTERM, &action2, NULL);
			}	
	}
	return 0;
}
