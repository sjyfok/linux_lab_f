#include <sys/mman.h>
#include <sys/types.h>
#include <linux/sem.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>

#define	MAXSEM	5

int fullid;
int emptyid;
int mutxid;

int main(void)
{
	struct sembuf P, V;
	union semun arg;

	int *array;
	int *sum;
	int *set;
	int *get;

	pid_t pid;
	
	array = mmap(NULL, sizeof(int)*MAXSEM, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	sum = mmap(NULL, sizeof(int), PROT_READ | PORT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	set = mmap(NULL, sizeof(int), PROT_READ | PORT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	get = mmap(NULL, sizeof(int), PROT_READ | PORT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

	fullid = semget(100, 1, IPC_CREATE);
	emptyid = semget(101, 1, IPC_CREATE);
	mutxid = semget(102, 1, IPC_CREATE);
	arg.val = 0;
	if (semctl(fullid, 0, SETVAL, arg) == -1)
	{
		perror("semctl setval error");
	}
	arg.val = MAXSEM;
	if (semctl(emptyid, 0, SETVAL, arg) == -1)
	{
		perror("setctl setval error");
	}
	arg.val = 1;
	if (semctl(mutxid, 0, SETVAL, arg) == -1)
	{
		perror("semctl setval error");
	}
	*sum = 0;
	*set = 0;
	*get = 0;
	P.sem_num = 0;
	P.sem_op = -1;
	P.sem_flg = SEM_UNDO;

	V.sem_num = 0;
	V.sem_op = 1;
	V.sem_flg = SEM_UNDO;

	pid = fork();
	if (pid == 0)
	{
		int i = 0;
		while (i < 100)
		{
			semop(mutxid, &P, 1);
			semop(emptyid, &P, 1);
			array[*(set)%MAXSEM] = i+1;
			*set ++;
			semop(fullid, &V, 1);
			semop(mutxid, &V, 1);
			i ++;
		}
		sleep(5);
		printf("product is exit\n");
		exit(0);
	}
	else
	{
		if (pid > 0)
		{
		}
		else
		{
			perror("Fail to fork");
		}
	}
}
