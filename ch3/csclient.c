#include "csfifo.h"

int main(int argc, char **argv)
{
	char r_msg[BUFSIZ];
	char *temp = "client message to server";
	char *cf = "/tmp/csfifo";
	char *s_msg;
	char *cfifo;
		

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
	
	int ret = mkfifo(cf, 0600);
	if (ret == -1)
	{
		printf("Fail to mkfifo\n");
		return -1;
	}
	int fd_rw = open(cf, O_RDWR);
	if (fd_rw == -1)
	{
		printf("Fail to open fifo\n");
		return -1;
	}
	ret = write(fd_rw, s_msg, strlen(s_msg));
	if (ret == -1)
	{
		printf("Fail to write to fifo\n");
		return -1;
	}
	else
	{
		printf("write to fifo successful\n");
	}
	while (1)
	{
		sleep(5);
		ret = open(cf, 
		if (
	}	
}
