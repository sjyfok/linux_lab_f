#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>

int total_words = 0;

pthread_mutex_t counter_clock = PTHREAD_MUTEX_INITIALIZER;
int main(int ac, char *av[])
{
	void *count_words(void*);
	pthread_t t1, t2;
	if (ac != 3)
	{
		printf("Usage:%s file1 file2\n", av[0]);
		exit(1);
	}
	pthread_create(&t1, NULL,count_words, av[1]);
	pthread_create(&t2, NULL, count_words, av[2]);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	printf("total_words: %d\n", total_words);
}

void *count_words(void *f)
{
	char * filename=(char*)f;
	FILE *fp;
	int c, prevc = '\0';

	if ((fp = fopen(filename, "r")) != NULL)
	{
		while((c = getc(fp)) != EOF)
		{
			if (!isalnum(c)&&isalnum(prevc))
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
