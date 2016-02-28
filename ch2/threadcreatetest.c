#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *create(void *arg)
{
	printf("New thread create....");
}

int main(int argc, char *argv[])
{
	pthread_t tidp;
	int error;

	error = pthread_create(&tidp, NULL, create, NULL);
	if (error != 0)
	{
		printf("pthread_create is not create ...");
		return -1;
	}
	printf("prthread_create ...");
	return 0;
}
