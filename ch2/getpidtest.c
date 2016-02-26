#include <stdio.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
	pid_t my_pid, parent_pid;
	uid_t my_uid, my_euid;
	gid_t my_gid, my_egid;

	my_pid = getpid();
	parent_pid = getppid();
	my_uid = getuid();
	my_euid = geteuid();
	my_gid = getgid();
	my_egid = getegid();

	printf("Process ID:%ld\n", my_pid);
	printf("Parent ID:%ld\n", parent_pid);
	printf("User ID:%ld\n", my_uid);
	printf("Effective User ID:%ld\n", my_euid);
	printf("Group ID:%ld\n", my_gid);
	printf("Effective Group ID:%ld\n", my_egid);
}
