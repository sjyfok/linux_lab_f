#define	MAX_TASK_NUM	10
#define	KERNEL_STACK_SIZE	1024*8
#define	PRIORITY_MAX	30

struct Thread {
	unsigned long ip;
	unsigned long	sp;
};

typedef struct PCB {
	int pid;
	volatile	long state;
	char stack[KERNEL_STACK_SIZE];

	struct Thread thread;
	unsigned long task_entry;
	struct PCB *next;
	unsigned long priority;
}tPCB;

void my_schedule(void);
