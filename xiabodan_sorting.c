//by xiabodan  swust 2015.6 
#include <stdio.h>
#include <stdlib.h>

#include "xiabodan_sorting.h"

typedef   int elementtype;
#define N 10

static void print(elementtype A[],int n)  ;
static void swap(elementtype *a,elementtype *b);

static void insertion(elementtype A[],int n);
static void shell(elementtype A[],int n)	;
static void bubble(elementtype A[],int n);
static void selection(elementtype A [],int n);
static void mergesort(elementtype A [],int n);
static void quick1(elementtype A[],int n);

void xiabodan_sorting(void)
{
	elementtype A[N]={23,49,66,36,56,45,63,13,34,78};
	//quick1(A,N);
	//print(A,N);

	mergesort(A,N);
	print(A,N);
}

/*
int main(int argc,char** argv)
{
	
	elementtype A[N]={23,49,66,36,56,45,63,13,34,78};
	//insertion( A , N);
	//print(A,N);

	//shell( A , N);
	//print(A,N);

	//bubble( A , N);
	//print(A,N);

	//selection(A,N);
	//print( A,N );

	//quick1(A,N);
	//print(A,N);
	
	mergesort(A,N);
	print(A,N);
}
*/
void print(elementtype A[],int n)  
{
	int i = 0;
	printf("after sorting\n");
	for(i=0;i<n;i++)
	{
		printf(" %d \n",A[i]);
	}
}

//²åÈëÅÅÐò
//stable
//O(N^2) comparisons and swaps
//Adaptive: O(n) time when nearly sorted
//Very low overhead
void insertion(elementtype A[],int n)
{
	int p = 0 ;
	int j = 0 ;
	for(p=1;p<n;p++ )
	{
		elementtype tem = A[p] ; 
		for(j=p;j>0&&A[j-1]>tem;j--)
		{
			 A[j] = A[j-1];
		}
		A[j] = tem;
	}
			
}

//Ï£¶ûÅÅÐò
//O(N^3/2)   unstable
//Adaptive: O(N.lg(N)) time when nearly sorted
//Very low overhead
void shell(elementtype A[],int n)
{
	int i,j,inc;
	elementtype tem;

	for(inc=N/2;inc>0;inc /=2)
	{
		for(i=inc;i<N;i++)
		{
			tem = A[i];
			for(j=i;j>=inc;j-=inc)
			{
				if(tem<A[j-inc])
					A[j] = A[j-inc];
				else
					break;
			}
			A[j] = tem;
		}
	}
}

//Ã°ÅÝÅÅÐò
//O(N^2)   stable
//Adaptive: O(N) time when nearly sorted
//Very low overhead
void bubble(elementtype A[],int n)
{
	int flag = 1;
	int i,j;
	for(i=0;i<n;i++)
	{
		flag = 0;
		for(j=n-1;j>i;j--)
		{
			if(A[j]<A[j-1])
			{
				flag = 1;
				swap(A+j,A+j-1 );
			}
				
		}
		if(flag == 0) break;
	}
}

//Ñ¡ÔñÅÅÐò
//Not stable
//O(1) extra space
//¦¨(n2) comparisons
//¦¨(n) swaps
//Not adaptive
void selection(elementtype A[],int n)
{
	int i,j;
	int k;
	for(i=0;i<n;i++)
	{
		k = i;
		for(j=i+1;j<n;j++)
		{
			if(A[j]<A[k])
			{	
				k = j;
			}
		}
		
		swap(A+i,A+k);
	}
}

//¹é²¢ÅÅÐò
//Stable
//(n) extra space for arrays (as shown)
//(lg(n)) extra space for linked lists
//(n¡¤lg(n)) time
//Not adaptive
//Does not require random access to data
void Merge(elementtype A[],elementtype TA[],int lpos,int rpos,int rightend)
{
	int leftend = rpos-1;
	int numelement = rightend -lpos + 1;
	int tpos = lpos;

	while(lpos<=leftend && rpos<=rightend)
		if(A[lpos] <= A[rpos])
			TA[tpos++] = A[lpos++];
		else
			TA[tpos++] = A[rpos++];

	while(lpos<=leftend)
		TA[tpos++] = A[lpos++];
	while(rpos<=rightend)
		TA[tpos++] = A[rpos++];

	int i = 0;
	for(i=0;i<numelement;i++,rightend--)
	{
		A[rightend] = TA[rightend];
	}
		
}
void MSort(elementtype A[],elementtype TA[],int left,int right)
{
	int center ;
	if(left < right)
	{
		center = (left+right)/2;
		MSort(A,TA,left,center);
		MSort(A,TA,center+1,right);
		Merge(A,TA,left,center+1,right);
	}
}
void mergesort(elementtype A[],int n)
{
	elementtype *TA;
	TA = (elementtype*)malloc(sizeof(elementtype)); //just malloc once 
	if(NULL != TA)
	{
		MSort(A,TA,0,n-1);
		free(TA);
	}
	else
		printf("error: TA can't be empty!\n");
}

//¿ìËÙÅÅÐò
//not Stable
//O(lg(n)) extra space (see discussion)
//O(n2) time, but typically O(n¡¤lg(n)) time
//Not adaptive
#define CUT 3
elementtype median3(elementtype A[],int left ,int right)
{
	int center = (left +right) / 2;
	if(A[left]>A[center])
		swap(&A[left],&A[center]);
	if(A[left]>A[right])
		swap(&A[left],&A[right]);
	if(A[center]>A[right])
		swap(&A[center],&A[right]);

	swap(&A[center],&A[right-1]);

	return A[right-1];
}
void Qsort(elementtype A[],int left, int right)
{
	int i,j;
	elementtype pivot;

	if(left + CUT<= right)
	{
		pivot = median3(A,left,right); //select middle element as pivot
		i = left;j = right-1;
		for(;;)
		{
			while(A[++i]<pivot){}
			while(A[--j]>pivot){}
			if(i<j)
				swap(&A[i],&A[j]);
			else
				break;
		}
		swap(&A[i],&A[right-1]);

		Qsort(A,left,i-1);
		Qsort(A,i+1,right);
	}
	else
		insertion(A+left,right-left+1);
}
void quick1(elementtype A[],int n)
{
	Qsort(A,0,n-1);
}




void swap(elementtype *a,elementtype *b)
{
	elementtype tem = *a;
	*a	= *b;
	*b	= tem;
}



























