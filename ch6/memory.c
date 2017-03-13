#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/time.h>
#include <unistd.h>

#define		BUSY	1
#define		IDLE	0

typedef struct _Page 
{
	int page_id;
}Page;

typedef struct _PageQueue 
{
	Page page;
	struct _PageQueue *next;
}PageQueue;

typedef struct _Block
{
	Page *page;
	long time;
	int state;
}Block;

typedef struct _BlockQueue
{
	Block block;
	struct _BlockQueue *next;
} BlockQueue;

typedef struct _process
{
	PageQueue pages;
	unsigned int pageLength;
} process;

long GetSystemUtime(void)
{
	struct timeval nowit;

	gettimeofday(&nowit, NULL);
	return 1000000*nowit.tv_sec+nowit.tv_usec;
}

void PrintBlockList(BlockQueue *blockQueue, int pageID, int color, int listType)
{
	BlockQueue *presentBlock;
	char str1[5], *str2;
	presentBlock = blockQueue;
	if (1)
	{
		while(presentBlock != NULL)
		{
			if (presentBlock->block.state == IDLE)
				printf("|  ");
			else
			{
				if (presentBlock->block.page->page_id == pageID)
					printf("|\033[1;40;%dm%d\033[0m",color, presentBlock->block.page->page_id);
				else
					printf("| %d", presentBlock->block.page->page_id);
			}
			presentBlock = presentBlock->next;
		}
	}
	else
	{
		while(presentBlock->next != blockQueue)
		{
			if (presentBlock->block.state == IDLE)
				printf("| ");
			else
			{
				if (presentBlock->block.page->page_id == pageID)
					printf("|\033[1;40;%dm%d\033[0m", color, presentBlock->block.page->page_id);
				else
					printf("|%d", presentBlock->block.page->page_id);
			}
			presentBlock = presentBlock->next;
		}
		if (presentBlock->block.state == IDLE)
			printf("| ");
		else
		{
			if (presentBlock->block.page->page_id == pageID)
				printf("|\033[1;40;%dm%d\033[0m", color, presentBlock->block.page->page_id);
			else
				printf("|%d", presentBlock->block.page->page_id);
		}
		presentBlock = presentBlock->next;
	}
}

void *InitializeBlockQueue(unsigned int size)
{
	BlockQueue *head = NULL, *p, *q;

	int i;

	for (i = 0; i < size; i ++)
	{
		p = (BlockQueue*)malloc(sizeof(BlockQueue));
		p->block.page->page_id = 0;
		p->block.time = 0;
		p->block.state = IDLE;
		p->next = NULL;
		if (head == NULL)
			head = p;
		else
			q->next = p;
		q = p;
	}
}

void *InitializePageQueue(unsigned int pageLength, int maxPageID)
{
	PageQueue *head = NULL, *p, *q;
	time_t t;
	int i = 0;

	srand((unsigned)time(&t));
	head = NULL;
	printf("Page Serials:");
	for (i = 0; i < pageLength; i ++)
	{
		p = malloc(sizeof(PageQueue));
		p->page.page_id = (int)(rand()%(maxPageID+1));
		printf("%d", p->page.page_id);
		p->next = NULL;
		if (head == NULL)
			head = p;
		else
			q->next = p;
		q = p;
	}
	printf("\n");
	return head;
}

void InitializeProcess(process *proc, unsigned int pageSize, unsigned int maxPageID)
{
	int i;
	proc->pageLength = pageSize;
	proc->pages.next = InitializePageQueue(pageSize, maxPageID);
}

void FIFO(BlockQueue *blockQueue, process *proc)
{
	
}

int main(int argc, char **argv)
{
	int blockNumber, pageNumber, pageMaxNumber;
	BlockQueue *blocks;
	process proc;

	if (argc != 4)
	{
		printf("usage: vm BlockNumber PageNumber PageTypeNumber\n");
		return 1;
	}
	blockNumber = atoi(argv[1]);
	pageNumber = atoi(argv[2]);
	pageMaxNumber = atoi(argv[3]);
	printf("Block Number:%d, Page Number:%d, Page Type Number:%d\n", 
		blockNumber, pageNumber, pageMaxNumber);
	
	blocks = InitializeBlockQueue(blockNumber);
	InitializeProcess(&proc, pageNumber, pageMaxNumber);

	//PrintBlockList(blocks, int pageID, int color, int listType)


	FIFO(blocks, &proc);
}
