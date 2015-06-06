#include <stdlib.h>
#include <stdio.h>

typedef int elementtype;
typedef struct node* position;
typedef struct node* bsearchtree;

bsearchtree MakeEmpty(bsearchtree T);
position find(elementtype data,bsearchtree T);
position findmax(bsearchtree T);
position findmin(bsearchtree T);
bsearchtree insert(elementtype data,bsearchtree T);
bsearchtree delete(elementtype data,bsearchtree T);
void print_tree(bsearchtree T);



struct node {
	elementtype data;
	position	left;
	position	right;

};

bsearchtree MakeEmpty(bsearchtree T)
{
	if(NULL != T)
	{
		MakeEmpty(T->left);
		MakeEmpty(T->right);
		free(T);
	}
	return NULL;
}

position find(elementtype data,bsearchtree T)
{
	if(NULL == T)
		return NULL;
	if(T->data > data)
		return find(data,T->left);
	if(T->data < data)
		return find(data,T->right);
	else
		return T;
}

position findmin(bsearchtree T)
{
	if(NULL == T)
		return NULL;
	if(T->left == NULL)
		return T;
	else
		return findmin(T->left);
}

position findmax(bsearchtree T)
{
	if(NULL != T)
		while(T->right != NULL)
			T = T->right;
	return T;
}

bsearchtree insert(elementtype data,bsearchtree T)
{
	if(NULL == T)   
	{
		T = (position)malloc(sizeof(position));
		T->data 	= data;
		T->left 	= NULL;
		T->right	= NULL;
	}
	else
	{
		if(data < T->data)
			T->left = insert( data, T->left);
		if(data > T->data)
			T->right = insert(data, T->right);
		//when T->data == data do nothing
	}

	return T;//return root node
}
bsearchtree delete(elementtype data,bsearchtree T)
{
	position tem;
	if(NULL == T)
		printf("delete:error T is empty");
	else if(data<T->data)
		T->left = delete(data,T->left)	; //go left to find data
	else if(data>T->data)
		T->right= delete(data,T->right) ; //go right to find data
	else if(T->left && T->right)		  //data is  found here ,and need to be deleted element   have  both children
	{
		//replace wih smallest in right subtree
		tem = findmin(T->right);		  
		T->data = tem->data;
		T->right = delete(T->data,T->right);
	}
	else  //need to be deleted element   just have one children
	{
		tem = T;
		if(NULL == T->left )
			T = T->right;
		if(NULL == T->right)
			T = T->left;
		free(tem);
	}

	return T;
}	

void print_tree(bsearchtree T)
{
	if(NULL ==T)
		return;
	print_tree(T->left);
	printf("  %d \n",T->data);
	print_tree(T->right);
}

int main(int argc, char** argv)
{
	bsearchtree T;
	position P;
	T = insert(12,T);
	T = insert(2,T);
	T = insert(22,T);
	T = insert(7,T);
	T = insert(54,T);
	T = insert(23,T);
	T = insert(18,T);
	T = insert(48,T);
	T = insert(112,T);
	T = insert(42,T);
	T = insert(222,T);
	T = insert(57,T);
	T = insert(84,T);
	T = insert(16,T);
	T = insert(455,T);
	T = insert(59,T);
	print_tree(T);

	//P = find( 22,T);
    if(T  != NULL) {
        T = delete(22,T);
        printf("After deletion:\n");
        print_tree(T);
    }
	return 0;
}
