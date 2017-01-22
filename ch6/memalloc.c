#include <stdio.h>
#include <stdlib.h>


#define	USE_N   10
#define	FREE_N  10
#define	minisize 100


struct TMEMTABLE
{
	int address;
	int length;
	int flag;
}used_table[USE_N], free_table[FREE_N], swp_item;

void SortMemTable(struct TMEMTABLE *ptable, int len)
{

	int i, k;
	for (i = 0; i < len; i ++)
	{
		for (k = i+1; k < len; k ++)
		{
			if (ptable[k].flag)
			{
				if (ptable[i].length > ptable[k].length)
				{
					swp_item = ptable[k];
					ptable[k] = ptable[i];
					ptable[i] = swp_item;
				}
			}
		}
	}
}


void allocate(char j, int xk)
{
	int i, k, ad;
	if (xk > minisize)
	{
		ad = xk;
	}
	else
	{
		ad = minisize;
	}
	for (i = 0; i < FREE_N; i ++)
	{
		if (free_table[i].flag == 1 && free_table[i].length >= ad)
		{
			for (k = 0; k < USE_N; k ++)
			{
				if (used_table[k].flag == 0)
				{
					used_table[k].flag = j;
					used_table[k].address = free_table[i].address;
					used_table[k].length = xk;				
					break;
				}
			}
			if (k < USE_N)
			{
				free_table[i].length -= ad;
				free_table[i].address += ad;
				if (free_table[i].length == 0) 
				{
					free_table[i].flag = 0;
				} 
				SortMemTable(&free_table[i], FREE_N-i);
			}
			else
			{
				printf("no used table\n");
				return;
			}
		}
	}
}


int RealseUseTable(char j, struct TMEMTABLE* pfreeitem)
{
	int i;

	for (i = 0; i < USE_N; i ++)
	{
		if (used_table[i].flag == j)
		{
			*pfreeitem = used_table[i];
			pfreeitem->flag = 1;
			used_table[i].flag = 0;
			used_table[i].address = 0;
			used_table[i].length = 0;
			return i;
		}
	}
	return -1;
}

void MoveFreeTableByOne(int idx)
{
	int i;

	for (i = idx+1; i < FREE_N; i ++)
	{
		if (free_table[i].flag)
		{
			free_table[i-1] = free_table[i];
		}
		else
		{
			break;
		}
	}
}

//*pitem meybe cause merge  return next meybe cause merge idx
int ScanForMerge(int idx)
{
	int i, tmpaddr, j;
	struct TMEMTABLE *pitem = free_table+idx;
	for (i = 0; i < FREE_N; i ++)
	{
		if (!free_table[i].flag)
			return i;
		if (i != idx)
		{
			tmpaddr = pitem->address+pitem->length;
			if (free_table[i].address == tmpaddr)
			{
				pitem->length += free_table[i].length;
				free_table[i].flag = 0;
				free_table[i].length = 0;
				free_table[i].start = 0;
				MoveFreeTableByOne(i);
				if (i < idx)
					return idx-1;
				else
					return idx;
			}
			tmpaddr = free_table[i].address+free_table[i].length;
			if (tmpaddr == pitem->address)
			{
				free_table[i].length += pitem->length;
				MoveFreeTableByOne(idx);
				if (i < idx)
					return i;
				else
					return i-1;
			}
		}
	}
	return i;
}

//merge succ return 0 else return -1
int MergeFreeTable(struct TMEMTABLE *pitem)
{
	int i, len;
	for (i = 0; i < FREE_N; i ++)
	{
		if (!free_table[i].flag)
			break;
	}
	len = i;
	for (i = 0; i < len; i ++)
	{
		//insert before
		int tmp = pitem->address + pitem->length;
		if (tmp == free_table[i].address)
		{
			free_table[i].address = pitem->address;
			free_table[i].length += pitem->length;
			printf("before\n");
			break;
		}
		else  //insert after
		{
			tmp = free_table[i].address+free_table[i].length;
			if (tmp == pitem->address)
			{
				free_table[i].length += pitem->length;
				printf("after\n");
				break;
			}
		}
	}
	printf("Merge: %d %d\n", i, len);
	if (i >= len)
	{
		return -1;
	}
	else
	{
		//SortMemTable(&free_table[k], FREE_N-k);
		int ret = ScanForMerge(i);
		printf("ret: %d\n", ret);
		while(free_table[ret].flag)
		{
			ret = ScanForMerge(ret);
		}
		return 0;
	}
}

void reclaim(char j)
{
	//find by name
	struct TMEMTABLE free_item;

	if (RealseUseTable(j, &free_item) < 0)
	{
		printf("no the job\n");
		return ;
	}
	printf("%d %d %d\n", free_item.address, free_item.length, free_item.flag);
	if (MergeFreeTable(&free_item) < 0)
	{
		//alloc freetable
		int i;
		printf("alloc\n");
		for (i = 0; i < FREE_N; i ++)
		{
			if (!free_table[i].flag)
			{
				free_table[i] = free_item;
				break;
			}
		}
	}
	SortMemTable(free_table, FREE_N);
}

int main(void)
{
	int i, xk, a;
	char J;
	for (i = 0; i < USE_N; i ++)
	{
		used_table[i].address = 0;
		used_table[i].length = 0;
		used_table[i].flag = 0;
	}
	free_table[0].flag = 1;
	free_table[0].address = 0;
	free_table[0].length = 102400;
	while(1)
	{
		printf("choice:(0-exit, 1-allocate, 2-reclaim 3-display memory)\n");
		printf("choice:(0-3)");
		scanf("%d", &a);
	//	a = getc(stdin);
	//	a -= 0x30;
		//sprintf((char*)&a, "%d");
		switch(a)
		{
			case 0:
				exit(0);
			case 1:
				printf("input name of job J and memory length xk\n");
				scanf("%*c%c%d", &J,&xk);
				allocate(J, xk);
				break;
			case 2:
				printf("input name of job J for reclaim memory\n");
				scanf("%*c%c", &J);
				reclaim(J);
				break;
			case 3:
				printf("free table:\n start    lenght    flag\n");
				for (i = 0; i < FREE_N; i ++)
				{
					printf("%5d%10d%6d\n", free_table[i].address, free_table[i].length, free_table[i].flag);
				}
				printf("press any key to continue\n");
				getchar();
				printf("used table:\n start   lenght    flag\n");
				for (i = 0; i < USE_N; i ++)
				{
					if (used_table[i].flag != 0)
					{
						printf("%5d%10d%6c\n", used_table[i].address, used_table[i].length, used_table[i].flag);
					}
					else
					{
						printf("%5d%10d%6d\n", used_table[i].address, used_table[i].length, used_table[i].flag);
					}
				}

				break;
			default:
				break;
		}
	}
	return 0;
}
