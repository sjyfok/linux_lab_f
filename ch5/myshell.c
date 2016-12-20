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
	free(pTmp);
	setpath("/bin:/usr/bin");	
}

void setpath(char *newpath)
{
	
}

int main(int argc, char *argv[])
{
	init();
	return 0;
}
