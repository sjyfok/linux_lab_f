#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/time.h>

#define		CHAIRS	5

sem_t customers;
sem_t barbers;
pthread_mutex_t mutex;
int waiting = 0;

void barber(void);
void customer(void);
void cut_hair(void);

int main(void)
{
	pthread_t tid_b, tid_c;
	int i = 0;
	sem_init(&customers, 0, 0);
	sem_init(&barbers, 0, 1);

	pthread_create(&tid_b, NULL, barber, NULL);

	while (1)
	{
		sleep(1);
		pthread_create(&tid_c, NULL, customer, NULL);
	}
}

void barber(void)
{
	while(1)
	{
		sem_wait(&customers);
		pthread_mutex_lock(&mutex);
		waiting = waiting -1;
		sem_post(&barbers);
		pthread_mutex_unlock(&mutex);
		cut_hair();
	}
}

void cut_hair(void)
{
	printf(" Barber: I am cutting the customer's hair...\n");
	sleep(1);
	printf(" Barber: done.\n");
}

void customer(void)
{
	pthread_mutex_lock(&mutex);
	if (waiting < CHAIRS)
	{
		printf("add customer.\n");
		waiting += 1;
		sem_post(&customers);
		pthread_mutex_unlock(&mutex);
		sem_wait(&barbers);
	} else {
		printf("Too many wait.\n");
		pthread_mutex_unlock(&mutex);
	}
	return ;
}
