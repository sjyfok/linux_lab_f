/*vfork 和 fork 的区别
vfork 和父进程共享存储空间 vfork
修改的变量在父进程可以得到体现
而fork则不是如此，fork和父进程具有不同的地址空间
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
	int data = 0;
	pid_t pid;
	int choose = 0;

	while((choose = getchar()) != 'q')
	{
		switch(choose)
		{
			case '1': 
				pid = fork();
				if (pid < 0)
				{
					printf("Error!\n");
				}
				if (pid == 0)
				{
					data ++;
					exit(0);
				}
				wait(pid);
				if (pid > 0)
				{
					printf("data is %d\n", data);
				}
				break;
			case '2':
				pid = vfork();
				if (pid < 0)
				{
					perror("Error!\n");
				}
				if (pid == 0)
				{
					data ++;
					exit(0);
				}
				wait(pid);
				if (pid > 0)
				{
					printf("data is %d\n", data);
				}
				break;
			default:
				break;
		}
	}
}
