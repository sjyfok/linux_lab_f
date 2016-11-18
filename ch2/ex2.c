#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

static int shdata = 4;

void* create(void *arg)
{
	printf("new pthread...\n");
	printf("shdata = %d\n", shdata);
	shdata ++;
	printf("shdata = %d\n", shdata);
	return (void*)0;
}

int main(void)
{
	pthread_t  tid;
	int err;

	err = pthread_create(&tid, NULL, create, NULL);
	if (err != 0)
	{
		printf("fail to create new thread...\n");
		return -1;
	}
	sleep(1);
	printf("create new thread...\n");
	printf("main thread shdata = %d\n", shdata);
	return 0;
}

