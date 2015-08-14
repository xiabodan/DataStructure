#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
typedef int ElementType;
 
//hashtable
typedef unsigned int index;
typedef struct listnode* position;
typedef struct listnode* list;
struct listnode{
	ElementType data;
	position next;
};

typedef struct hashtbl*  hashtable;
struct hashtbl {
	int tablesize;
	list *thelists;
};

index HashFunc(const ElementType key,int tablesize)
{
	//unsigned int hashval = 0;
	//while(*key != '\0')	
		//hashval = (hashval << 5) + *key++;
	//return hashval % tablesize;
	return key % tablesize;
}

hashtable InitializeHashTable(int tablesize)
{
	hashtable H;
	H = (hashtable)malloc(sizeof(hashtable));
	if(NULL == H) return NULL;

	H->tablesize = tablesize;

	H->thelists = (list*)malloc(sizeof(list) * H->tablesize);
	int i = 0;
	for(i=0;i<H->tablesize;i++)//ÓÐ±íÍ·
	{
		H->thelists[i] = (list)malloc(sizeof(struct listnode));
		H->thelists[i]->next = NULL;
	}
	return H;
}
void DeleteHashTable(hashtable H)
{
	position P,tem;
	int i = 0;
	for(i=0;i<H->tablesize;i++)
	{
		P = H->thelists[i]->next;
		while(P != NULL)
		{
			tem = P;
			free(tem);
			P=P->next;
		}
	}
	free(H->thelists);
	free(H);
}
position Find(ElementType key,hashtable H)
{
	position P;
	list L;
	L = H->thelists[ HashFunc( key, H->tablesize) ];
	P = L->next;
	while(P != NULL && P->data != key)
		P = P->next;

	return P;
}

void Insert(ElementType key,hashtable H)
{
	position pos,newnode;
	list L;
	pos = Find(key,H);
	if(pos == NULL)
	{
		newnode = (position)malloc(sizeof(position));
		L = H->thelists[ HashFunc( key, H->tablesize) ];
		newnode->data = key;
		newnode->next = L->next;
		L->next = newnode;
	}
}
void PrintHashTable(hashtable H)
{
	position P;
	int i = 0;
	for(i=0;i<H->tablesize;i++)
	{
		P = H->thelists[i]->next;
		printf("H->thelists[%d] = ",i);
		while(P != NULL)
		{
			printf(" %d ->",P->data);
			P=P->next;
		}
		printf("NULL\n");	
	}
}

int main()
{
	//int nums[2] = {1,1};
	//bool r = containsDuplicate(nums,2);
	//printf("containsDuplicate is : %d \n",r);
	int num[10] = {3,45,5,64,7,9,8,3,75,75};
	hashtable H;
	H = InitializeHashTable(10);
	int i = 0;
	for(i=0;i<10;i++)
	{	
		Insert(num[i],H);
	}
	PrintHashTable(H);
	DeleteHashTable(H);
}

