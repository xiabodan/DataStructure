#include <stdlib.h>
#include <stdio.h>
#include "xiabodan_list.h"

typedef struct node *list;
typedef struct node *position;
typedef struct node
{
	int data;
	position next;
}node;

static list init_list(void);
static void delete_list(list L);
static int isempty(list L);
static void insert_node(position L,int data);
static void delete_node(list L,position P);
static position find_last(list L);
static position find_value(list L,int data);
static position find_pre(list L,position P );
static void print(list L);



list init_list(void){
	list L  = (list)malloc(sizeof(node));
	L->next = NULL;
	return L;
}
void delete_list(list L){
	position P ,next;
	P = L;
	do{
		next = P->next;
		free(P);
		P = next;
	}while(next != NULL);
}
int isempty(list L){
	return (L->next == NULL);
}
void insert_node(position P,int data){
	position tem ;
	tem = (position)malloc(sizeof(node));
	tem->data = data;
	tem->next = P->next;
	P->next = tem;
}
void delete_node(list L,position P){
	position pre ;
	pre = find_pre( L, P);
	if(pre != NULL)
	{
		pre->next = P->next;
		free(P);
	}
	else
	{
		printf("delete_node:p is not in the list!\n");
	}
	
}
position find_last(list L){
	position P;
	P=L;
	while(P->next != NULL)
	{
		P = P->next;
	}
	return P;
	
}
position find_value(list L,int data){
	position P ;
	P = L;
	while(P->next != NULL)
	{
		P = P->next;
		if(P->data == data)
			return P;
	}
	return NULL;
}

position find_pre(list L,position P ){
	position tem ;
	tem = L;
	while(tem->next != NULL)
	{
		if(tem->next == P)
			return tem;
		tem = tem->next;
	}
	return NULL;
}
void print(list L){
	position P;
	
	if(isempty( L))
	{
		printf("print: L is a null list!\n");
		return ;
	}
	P = L;
	while(P->next !=NULL)
	{
		P = P->next;
		printf("print:%p : %d \n",P,P->data);
	}
	printf("\n");
}

/*
int main(int argc ,char** argv)
{
	int a[6]= {1,2,3,4,5,6};
	int i=0;
	list L;
	L = init_list();

	print(L);
	printf("insert node\n");
	for(i=0;i<6;i++)
	{
		insert_node( L,a[i]);
	}
	print( L);
	printf("delete node\n");
	position P;
	P = find_value( L, 5);
	delete_node( L,P);
	print( L);
	printf("find node and insert node\n");
	P = find_value( L, 2);
	insert_node( P,111);
	print( L);
	
	delete_list( L);
	print( L);
	
}
*/


void xiabodan_list(void)
{
	int a[6]= {1,2,3,4,5,6};
	int i=0;
	list L;
	L = init_list();

	print(L);
	printf("insert node\n");
	for(i=0;i<6;i++)
	{
		insert_node( L,a[i]);
	}
	print( L);
	printf("delete node\n");
	position P;
	P = find_value( L, 5);
	delete_node( L,P);
	print( L);
	printf("find node and insert node\n");
	P = find_value( L, 2);
	insert_node( P,111);
	print( L);
	
	delete_list( L);
	print( L);
}


