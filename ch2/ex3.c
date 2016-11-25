#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

int total_words = 0;

pthread_mutex_t counter_clock = PTHREAD_MUTEX_INITIALIZER;

int isalnum(int ch)
{
	if (ch >= '0' && ch <= '9')
		return 1;
	if (ch >= 'a' && ch <= 'z')
		return 1;
	if (ch >= 'A' && ch <= 'Z')
		return 1;
	
	return 0;
}

void* count_words(void *f)
{
	char *filename = (char *)f;
	FILE *fp;
	int c, prevc = '\0';

	if ((fp = fopen(filename, "r")) != NULL)
	{
		while ((c = getc(fp)) != EOF)
		{
			if (!isalnum(c) && isalnum(prevc))
			{
				pthread_mutex_lock(&counter_clock);
				total_words ++;
				pthread_mutex_unlock(&counter_clock);
			}
			prevc = c;
		}
		fclose(fp);
	}
	else
	{
		perror(filename);
	}
	return NULL;
}

int main(int ac, char *av[])
{
	void *count_words(void*);
	pthread_t  tid1, tid2;
	int err;
	void *status;

	if (ac != 3)
	{
		printf("Usage:%s file1 file2\n", av[0]);
		exit(1);
	}

	err = pthread_create(&tid1, NULL, count_words, av[1]);
	if (err != 0)
	{
		printf("fail to create new thread...\n");
		return -1;
	}
	err = pthread_create(&tid2, NULL, count_words, av[2]);
	if (err != 0)
	{
		printf("fail to create new thread...\n");
		return -1;
	}
	err = pthread_join(tid1, &status); 
	if (err != 0)
	{
		printf("Fail to wait %d.\n", tid1);
		exit(1);
	}
	err = pthread_join(tid2, &status);
	if (err != 0)
	{
		printf("Fail to wait %d.\n", tid2);
		exit(1);
	}
	printf("The file1 and file2 has %d's words\n", total_words); 
	return 0;
}

