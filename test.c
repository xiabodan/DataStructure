
#include "apue.h"
#include <stdlib.h>
#include <stdio.h>

int globvar = 6;

int main()
{
//	int i = 10;
//	printf("%d %d %d %d %d  \n",i,i++,i++,++i,i);
	
	int var = 88;
	pid_t pid;
	if((pid = fork()) < 0)
	{
		printf("fork error\n");
	}
	else if( 0 == pid)
	{
		globvar++;
		var++;
		exit(1);
	}
	else
	{
		sleep(2);
	}

	printf("pid = %ld,globvar = %d, var = %d\n",(long)getpid(),globvar,var);
	
	exit(0);
	
}
