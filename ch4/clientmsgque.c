#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define	MSGKEY 75

struct msgform {
	long mytype;
	char mtext[1000];
} msg;


void client(void)
{
	int flag =  IPC_CREAT |  0666;
	int msg_id, i;
	
	msg_id = msgget(MSGKEY, flag);
	if (msg_id < 0)
	{
		perror("msgget: ");
		exit(1);
	}
	for (i = 10; i >= 1; i --)
	{
		msg.mytype = i;
		strcpy(msg.mtext, "hello");
		printf("(client)send\n");
		msgsnd(msg_id, &msg, sizeof(msg.mtext), 0);
	}
	exit(0);
	/*if (msgctl(msg_id, IPC_RMID, NULL) < 0)
	{
		perror("rm smg");
		exit(1);
	}
	exit(0);*/
}

int main(void)
{
	client();
	return 0;
}
