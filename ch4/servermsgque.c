#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <stdio.h>


#define	MSGKEY 75

struct msgform {
	long mytype;
	char mtext[1000];
} msg;


void server(void)
{
	int flag = IPC_CREAT | IPC_EXCL | 0666;
	int msg_id;
	
	msg_id = msgget(MSGKEY, flag);
	if (msg_id < 0)
	{
		perror("msgget: ");
		exit(1);
	}
	do
	{
		size_t msglen = 0;
		msglen = msgrcv(msg_id, &msg, sizeof(msg.mtext), 1, MSG_NOERROR);
		if (msglen >= 0)
		{
			printf("Recv msg: %s\n", msg.mtext);
		}
	} while(msg.mytype != 1);
	exit(0);
}

int main(void)
{
	server();
	return 0;
}
