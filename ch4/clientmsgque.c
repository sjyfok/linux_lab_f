#include "csfifo.h"


int main(int argc, char *argv[])
{
	char r_msg[BUFSIZ];
	char *temp = "client message to server";
	char *cf = "/tmp/cfifo";
	char *s_msg;
	char *cfifo;
	int fd_fifo;
	int ret;

	if (argc != 2)
	{
		printf("Usage: ./client n\n");
		return 0;
	}
	s_msg = malloc(strlen(temp)+strlen(argv[1])+sizeof(char));
	cfifo = malloc(strlen(cf)+strlen(argv[1]));
	strcpy(s_msg, argv[1]);
	strcpy(cfifo, cf);
	s_msg[strlen(argv[1])] = '#';
	strcat(s_msg, temp);
	strcat(cfifo, argv[1]);
	
	if (((ret = mkfifo(cfifo, 0666)) < 0) && errno != EEXIST)
	{
		printf("fail to mkfifo\n");
		return 0;
	}
	if ((fd_fifo = open(CSFIFO, O_WRONLY)) < 0)
	{
		printf("fail to open fifo\n");
		return 0;
	}
	if (write(fd_fifo, s_msg, strlen(s_msg)) < 0)
	{
		printf("Fail to write fifo\n");
		return 1;
	}
	printf("Success to wirte fifo\n");

	close(fd_fifo);
	while(1)
	{
		if ((fd_fifo = open(cfifo, O_RDONLY)) < 0)
		{
			printf("Fail to open fifo\n");
			sleep(10);
			continue;
		}
		if (read(fd_fifo, r_msg, BUFSIZ) < 0)
		{
			printf("Fail to read form fifo\n");
			return 1;
		}
		printf("r_msg: %s\n", r_msg);
		return 0;
	}
}
