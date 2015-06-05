#include <stdio.h>
#include <stdlib.h>

#include "xiabodan_queue.h"

typedef int elementtype;

typedef struct headnode *queue;
typedef struct node 	*position;
struct node {
	elementtype data;
	position 	next;
};
struct headnode{
	int 		size;
	position 	front;
	position 	rear;
};   // headnode is only use head mark, next point to follow node , rear point to the end node, size declaration the length of whole queue.

static queue init_queue(void);
static void delete_queue(queue Q);
static int isempty(queue Q);
static elementtype dequeue(queue Q);
static void enqueue(elementtype data,queue Q);


queue init_queue(void)
{
	queue Q;
	Q = (queue)malloc(sizeof(struct headnode));
	Q->front = NULL;
	Q->rear  = NULL;
	Q->size	 = 0;
	return Q;
}
void delete_queue(queue Q)
{
	while(!isempty(Q))
		dequeue(Q);
	free(Q);
}
int isempty(queue Q)
{
	return ((Q->front == NULL)&&(Q->rear == NULL)&&(Q->size == 0));
}
void enqueue(elementtype data,queue Q)
{
	position P;
	P = (position)malloc(sizeof(struct node));
	P->data = data;
	P->next = NULL;

	if(isempty(Q))	//when Q is empty ,the new node(P) is both front node and rear node.
		Q->front = P;
	else
		Q->rear->next = P;//when Q isn't empty ,the new node(P) is rear node, the front node isn't change, but original rear->next will point to P

	Q->rear = P;
	Q->size++;
}
elementtype dequeue(queue Q)
{
	elementtype data;
	position tem;
	if(!isempty(Q))
	{
		tem = Q->front;
		data = Q->front->data;
		Q->size--;
		Q->front = tem->next;
		if(Q->size == 0)
			Q->rear = NULL;
		free(tem);
		return data;
	}
	else
	{	
		printf("enqueue : error ! Q is a empty queue !\n");
		return 0 ; 
	}
}


/*
int main(int argc ,char** argv)
{
	queue Q;
	elementtype data;
	int i = 0;
	Q = init_queue();
	printf("queue size is : %d\n\n",Q->size);
	printf("enqueue 10 datas\n");
	for(i=0;i<10;i++)
	{	
		enqueue(i, Q);
	}
	printf("queue size is : %d\n\n",Q->size);
	printf("enqueue 5 datas\n");
	for(i=0;i<5;i++)
	{	
		data = dequeue(Q);
		printf("dequeue data is : %d\n",data);
	}
	printf("enqueue 10 datas\n\n");
	for(i=10;i<20;i++)
	{	
		enqueue(i, Q);
	}
	printf("queue size is : %d\n",Q->size);

	for(i=0;i<15;i++)
	{	
		data = dequeue(Q);
		printf("dequeue data is : %d\n",data);
	}
	printf("queue size is : %d\n",Q->size);
}
*/

void xiabodan_queue(void )
{
	queue Q;
	elementtype data;
	int i = 0;
	Q = init_queue();
	printf("queue size is : %d\n\n",Q->size);
	printf("enqueue 10 datas\n");
	for(i=0;i<10;i++)
	{	
		enqueue(i, Q);
	}
	printf("queue size is : %d\n\n",Q->size);
	printf("enqueue 5 datas\n");
	for(i=0;i<5;i++)
	{	
		data = dequeue(Q);
		printf("dequeue data is : %d\n",data);
	}
	printf("enqueue 10 datas\n\n");
	for(i=10;i<20;i++)
	{	
		enqueue(i, Q);
	}
	printf("queue size is : %d\n",Q->size);

	for(i=0;i<15;i++)
	{	
		data = dequeue(Q);
		printf("dequeue data is : %d\n",data);
	}
	printf("queue size is : %d\n",Q->size);
}