#include "csfifo.h"

int main(void)
{
	int ret;
	pid_t pid;
	int fdwr, fdrd;
	char *ptr, *cf = "/tmp/cfifo", *tmp;
	int bytes, i;
	char rdbuf[BUFSIZ];
	char s_msg[BUFSIZ];
	int r_num;

	while(((ret=mkfifo(CSFIFO, 0666)) < 0) && errno != EEXIST)
	{
		printf("fail to mkfifo.\n");
		sleep(5);
		continue;
	}

	printf("success to mkfifo.\n");

	fdrd = open(CSFIFO, O_RDONLY);
	if (fdrd < 0)
	{
		printf("fail to open file.\n");
		return 1;
	}
	else
	{
		bytes = read(fdrd, rdbuf, BUFSIZ);
		if (bytes < 0)
		{
			printf("fail to read.\n");
		}
		close(fdrd);
		printf("%s\n", rdbuf);
		ptr = malloc(sizeof(char)*bytes);
		i = 0;
		while(rdbuf[i] != '#')
		{
			ptr[i] = rdbuf[i];
			i ++;
		}
		ptr[i] = '\0';
		tmp = malloc(strlen(cf)+i+1);
		strcpy(tmp, cf);
		strcat(tmp, ptr);
		fdwr = open(tmp, O_WRONLY);
		if (fdwr < 0)
		{
			printf("fail to open client fifo\n");
			return 1;
		}
		s_msg[0] = '\0';
		strcpy(s_msg, "Hello client ");
		strcat(s_msg, ptr);
		write(fdwr, s_msg, strlen(s_msg));
		close(fdwr);
		return 0;
	}
}
