#include <stdlib.h>
#include <stdio.h>



/*
  * Gauss summation
  */
int recursion(n)
{
	if(1 == n)
		return 1;
	else {
		return recursion(n-1)+ n;
	}
}

int main(int argc , char** argv)
{
	int data;
	data  = recursion(100);
	printf("recursion data is :%d \n",data);
}
