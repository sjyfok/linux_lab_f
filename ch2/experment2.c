#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

static int shdata = 4;
void *create(void *arg)
{
	printf("new pthread ...\n");
	shdata ++;
	printf("share data = %d\n", shdata);
	return (void*)0;
}

int main(int argc, char *argv[])
{
	pthread_t tid;
	int error;

	error = pthread_create(&tid, NULL, create, NULL);
	if (error != 0 )
	{
		printf("Fail to pthread_create\n");
		exit(-1);
	}
	sleep(1);
	printf("pthread_create sucess!\n");
	printf("parent process shdata = %d\n", shdata);
	return 0;
}
