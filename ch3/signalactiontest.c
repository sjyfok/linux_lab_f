#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#define PROMPT "do you want to end the program?"

char *prompt = PROMPT;

void ctrl_c_op(int signo)
{
	write(STDERR_FILENO, prompt, strlen(prompt));
}

int main(void)
{
	struct sigaction act;
	act.sa_handler = ctrl_c_op;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	if (sigaction(SIGINT, &act, NULL) < 0) 
	{
		fprintf(stderr, "Install signal action error:%s\n\a", strerror(errno));
		exit(1);
	}
	while(1);
}
