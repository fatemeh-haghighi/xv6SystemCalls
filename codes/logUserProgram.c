#include "types.h"
#include "stat.h"
#include "user.h"


int main()
{
	int pid = getpid();
	while (pid == 0)
		pid = getpid();
	int pid1 = fork();
	if(pid1 == 0)
	{
		int i = 0;
		i++;
		exit();
	}
	else if (pid1 > 0)
	{
		int j = 0;
		j++;
		wait();
	}	
	log_syscalls();
	exit();
}