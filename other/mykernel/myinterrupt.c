/*
 *  linux/mykernel/myinterrupt.c
 *
 *  Kernel internal my_timer_handler
 *
 *  Copyright (C) 2013  Mengning
 *
 */
#include <linux/kernel_stat.h>
#include <linux/export.h>
#include <linux/interrupt.h>
#include <linux/percpu.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/swap.h>
#include <linux/pid_namespace.h>
#include <linux/notifier.h>
#include <linux/thread_info.h>
#include <linux/time.h>
#include <linux/jiffies.h>
#include <linux/posix-timers.h>
#include <linux/cpu.h>
#include <linux/syscalls.h>
#include <linux/delay.h>
#include <linux/tick.h>
#include <linux/kallsyms.h>
#include <linux/irq_work.h>
#include <linux/sched.h>
#include <linux/sched/sysctl.h>
#include <linux/slab.h>

#include <asm/uaccess.h>
#include <asm/unistd.h>
#include <asm/div64.h>
#include <asm/timex.h>
#include <asm/io.h>

#include "mypcb.h"

#define CREATE_TRACE_POINTS
#include <trace/events/timer.h>

extern tPCB task[MAX_TASK_NUM];
extern tPCB *my_current_task;
extern volatile int my_need_sched;
volatile int time_count = 0;
/*
 * Called by timer interrupt.
 */
void my_timer_handler(void)
{
//	printk(KERN_NOTICE "\n>>>>>>>>>>>>>>>>>my_timer_handler here<<<<<<<<<<<<<<<<<<\n\n");
#if 1
	if (time_count%2000 == 0 && my_need_sched != 1)
	{
		my_need_sched = 1;
	}
	time_count ++;
#endif
	return ;
}

void all_task_print(void);

tPCB *get_next(void)
{
	int pid, i;
	tPCB *point = NULL;
	tPCB *hig_pri = NULL;
	all_task_print();
	hig_pri = my_current_task;
	for (i = 0; i < MAX_TASK_NUM; i ++)
		if (task[i].priority < hig_pri->priority)
			hig_pri = &task[i];
	printk("     higst process is :%d priority is :%d\n", hig_pri->pid, hig_pri->priority);
	return hig_pri;
}

void my_schedule(void)
{
	tPCB *next;
	tPCB *prev;
	
	if (my_current_task == NULL
		|| my_current_task->next == NULL)
	{
		printk(KERN_NOTICE"     time out!!!but no more than 2 task,need no schedule\n");
		return;
	}
	next = get_next();
	prev = my_current_task;
	printk(KERN_NOTICE "    the next task is %d priority is %u\n", next->pid, next->priority);
	if (next->state == 0)
	{
	asm volatile(
		"pushl %%ebp\n\t"
		"movl %%esp,%0\n\t"
		"movl	%2,%%esp\n\t"
		"movl	$1f,%1\n\t"
		"pushl %3\n\t"
		"ret\n\t"
		"1:\t"
		"popl	%%ebp\n\t"
		: "=m"(prev->thread.sp),"=m"(prev->thread.ip)
		: "m"(next->thread.sp),"m"(next->thread.ip)
	);
	my_current_task = next;
	printk(KERN_NOTICE "    switch for %d process to %d process\n >>> process %d running!!!<<<\n\n", prev->pid, next->pid, next->pid);
	}
	else
	{
		next->state = 0;
		my_current_task = next;
		printk(KERN_NOTICE"   switch from %d process to %d process\n   >>>process %d running!!!<<<\n\n\n", prev->pid, next->pid, next->pid);
		asm volatile(
			"pushl %%ebp\n\t"
			"movl %%esp,%0\n\t"
			"movl %2, %%esp\n\t"
			"movl %2,	%%ebp\n\t"
			"movl	$1f,	%1\n\t"
			"pushl	%3\n\t"
			"ret\n\t"
			: "=m"(prev->thread.sp),"=m"(prev->thread.ip)
			: "m"(next->thread.sp),"m"(next->thread.ip)
		);
	}
	return;
}

void all_task_print(void)
{
	int i, cnum = 62;
	
	printk(KERN_NOTICE"\n   current task is:%d   all task in OS are:\n", my_current_task->pid);
	printk("   ");
	for(i = 0; i < cnum; i ++)
		printk("-");
	printk("\n   | process:");
	for (i = 0; i < MAX_TASK_NUM; i ++)
		printk("|%2d ", i);
	printk("|\n    | priority:");
	for (i = 0; i < MAX_TASK_NUM; i ++)
		printk("|%2d ", task[i].priority);
	printk("|\n   ");
	for (i = 0; i < cnum; i ++)
		printk("-");
	printk("\n");

}
