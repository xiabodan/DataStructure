//by xiabodan
#include <stdio.h>
#include <stdlib.h>

#include "xiabodan_stack.h"

typedef int elementtype;

typedef struct node *stack;
typedef struct node *position;
struct node {
	elementtype data;
	position next;
};

static int isempty(stack S);
static void delete_stack(stack S);
static stack create_stack(void);
static elementtype top(stack S);
static elementtype pop(stack S);
static void push(stack S,elementtype data);


 
int isempty(stack S)
{
	return (S->next == NULL);
}
stack create_stack(void)
{
	stack S;
	S = (position)malloc(sizeof(struct node));
	if( S == NULL)
	{	
		printf("create_stack : out of space");
		return ;
	}
	S->next = NULL; // S->next is top of stack ,because header can't store element
	return  S;
}
void delete_stack(stack S)
{
	 if(S == NULL)
	 	printf("S is a empty stack!\n");
	 else 
	 {
	 	while( !isempty( S))
			pop(S);
	 }
}

elementtype pop(stack S)
{
	elementtype data;
	if(!isempty(S))
	{
		position tem;
		tem = S->next;//tem  point to the top node
		data = S->next->data;
		S->next = tem->next;//also S->next = S->next->next
		free(tem);
		return data;
	}
	else 
		printf("pop : empty stack!\n");
	return 0;
}

elementtype top(stack S)
{
	if(!isempty(S))
		return (S->next->data);
	printf("top : empty stack!\n");
	return 0;
}

void push(stack S,elementtype data)
{
	position P;
	P = (position)malloc(sizeof(struct node));
	if( P == NULL)
	{	
		printf("push : out of space");
		return ;
	}
	P->data = data;    
	P->next = S->next;  //compare list , insert node location the first node here,but insert node anywhere in list
	S->next = P;
}

/*
int main(int argc ,char** argv)
{
	stack S;
	int i = 0 ;
	elementtype data;
	S = create_stack();
	printf("push 10 datas from 0 to 9 \n");
	for(i=0;i<10;i++)
	{
		push(S,i);
	}
	printf("S is empty? %d \n",isempty( S));

	printf("pop 5 datas \n");
	for(i=0;i<5;i++)
	{
		data = pop(S);
		printf("pop data is : %d\n",data);
	}
	printf("push 2 datas 11,12\n");
	push(S,11);
	push(S,12);
	printf("pop all remain datas \n");
	while(!isempty( S))
	{
		data = pop(S);
		printf("pop data is : %d\n",data);
	}
	printf("S is empty? %d \n",isempty( S));
	delete_stack(S);
	
}
*/
	
void xiabodan_stack(void)
{
	stack S;
	int i = 0 ;
	elementtype data;
	S = create_stack();
	printf("push 10 datas from 0 to 9 \n");
	for(i=0;i<10;i++)
	{
		push(S,i);
	}
	printf("S is empty? %d \n",isempty( S));

	printf("pop 5 datas \n");
	for(i=0;i<5;i++)
	{
		data = pop(S);
		printf("pop data is : %d\n",data);
	}
	printf("push 2 datas 11,12\n");
	push(S,11);
	push(S,12);
	printf("pop all remain datas \n");
	while(!isempty( S))
	{
		data = pop(S);
		printf("pop data is : %d\n",data);
	}
	printf("S is empty? %d \n",isempty( S));
	delete_stack(S);

}
