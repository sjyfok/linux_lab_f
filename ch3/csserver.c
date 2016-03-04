#include "csfifo.h"

int main(int argc, char *argv[])
{
	char *clientfifo = "/tmp/cfifo";
	int ret = 0;
	int fd_r, fd_w;
	char buf[BUFFERSIZE];
	char *ptrTmp = NULL;
	while(1)
	{	
		ret = mkfifo(clientfifo, 0600);
		if (ret == -1)
		{
			printf("client is not created\n");
			sleep(2);
			continue;
		}
		fd_r = open(clientfifo, O_RDONLY);
		if (fd_r == -1)
		{
			printf("Fail to open fifo\n");
		}
		ret = read(fd_r, buf, BUFFERSIZE);
		if (ret == -1)
		{
			printf("Fail to read from fifo\n");
			return 1;
		}
		else
		{
			printf("read from fifo is :%s\n", buf);
			close(fd_r);
			int len = strlen(buf);
			ptrTmp = (char*)malloc(sizeof(char)*(len+1));
			*ptrTmp = '\0';
			strcpy(ptrTmp, buf);
			int data = atoi(ptrTmp);
			if (data == 0)
			{
				printf("get zero data\n");
				return 0;
			}
			printf("Conv: %d\n", data);
			sprintf(buf, "%s%d", buf, len);
			fd_w = open(clientfifo, O_WRONLY);
			write(fd_w, buf, strlen(buf));
			close(fd_w);
			return 0;
		}
	}
}	
