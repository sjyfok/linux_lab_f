#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <error.h>
#include <string.h>

typedef struct {
	char name[4];
	int age;
}people;

int main(int argc, char **argv)
{
	int shmid; 
	people *ptr;

	shmid = shmget(100, sizeof(people), IPC_CREAT | 0600);
	if (shmid < 0)
	{
		perror("fail shmget");
		exit(0);
	}
	ptr = (people*)shmat(shmid, NULL, 0);
	strcpy(ptr->name, "aaa");
	ptr->age = 15;
	shmid = shmdt(ptr);
	if (shmid < 0)
	{
		perror("fail to shmdt");
		exit(0);
	}
	return 0;
}
