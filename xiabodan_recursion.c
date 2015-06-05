#include <stdlib.h>
#include <stdio.h>

#include "xiabodan_recursion.h"

static int recursion1(int n);
/*
  * Gauss summation
  */
int recursion1(int n)
{
	if(1 == n)
		return 1;
	else {
		return recursion1(n-1)+ n;
	}
}



/*
int main(int argc , char** argv)
{
	int data;
	data  = recursion(100);
	printf("recursion data is :%d \n",data);
}
*/

void xiabodan_recursion(void)
{
	int data;
	data  = recursion1(100);
	printf("recursion data is :%d \n",data);
}

