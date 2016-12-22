#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

char hint[256];

void setpath(char *newpath);

void init(void)
{
	char *pTmp;

	pTmp = (char *)malloc(128*sizeof(char));
	sprintf(hint, "%s", getlogin());
	strcat(hint, "@");
	gethostname(pTmp, 32);
	strcat(hint, pTmp);
	strcat(hint, ":");
	getcwd(pTmp, 128);
	strcat(hint, pTmp);
//	printf("%s\n", hint);
	strcat(hint, "$ ");
	free(pTmp);
	setpath("/bin:/usr/bin");	
}

void setpath(char *newpath)
{
	
}

int getcmd(char *buf, int nbuf)
{
	printf("%s", hint);
	memset(buf, 0,  nbuf);
	fgets(buf, nbuf, stdin);
	printf("%s", buf);
	if (buf[0] == 0)
	{
		return -1;
	}
	return 0;
}

int main(int argc, char *argv[])
{
	static char buf[100];
	int fd, r;

	init();
	while(getcmd(buf, sizeof(buf)) >= 0)
	{
		if (fork1() == 0)
		{
			runcmd(parsecmd(buf));
		}
		wait(&r);
	}
	return 0;
}
