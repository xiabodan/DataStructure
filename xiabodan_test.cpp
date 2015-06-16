#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <conio.h>

using namespace std;

typedef unsigned char  uchar;

void test_5_4_1(void)
{
	float a = 1.0f;
	cout << (int)a <<	endl;
	cout << &a <<		endl;
	cout << (int&)a <<	endl;
	cout << boolalpha << ((int)a == (int&)a )<<endl;

	float b = 0.0f;
	cout << (int)b <<	endl;
	cout << &b <<		endl;
	cout << (int&)b <<	endl;
	cout << boolalpha << ((int)b == (int&)b )<<endl;
}

void test_5_5_1(void)
{
	uchar a = 0xA5;
	uchar b = ~a >> 4+1;

	//cout << b <<endl;
	printf ("b = %d \n",b);
}

int test_5_6_2(int N, int* score,int* type)
{
	double sum1 = 0,sum2 = 0;
	int average = 0; 
	int n1 = 0,n2 = 0;
	int i;
	if(N && score && type)
	{
		for(i=0;i<N;i++)
		{
			switch(type[i])
			{
				case 1:sum1 += score[i];++n1;break;
				case 2:sum2 += score[i];++n2;break;
				default:break;
			}
				
		}
		if(n1) sum1 = (int)(sum1 / n1);
		if(n2) sum2 = (int)(sum2 / n2);
		average = n1 ? (n2 ? (sum1 * 0.6 + sum2 * 0.4) : sum1) : sum2;
	}
	return average;
}

int test_5_6_2(void)
{
	int score[10] = {97,96,95,94,93,92,91,90,98,99};
	int type[10]  = {1,2,1,2,1,1,1,2,2,1};
	int average = test_5_6_2(10,score,type);
	cout << average <<endl;

	return 0;
}


//test_6_3_3
class A1
{
	public:
		int a;
		static int b;
	A1();
	~A1();
};
class A2
{
	public:
		int a;
		char c;
	A2();
	~A2();
};
class A3
{
	public:
		int b;
		long long  c;
	A3();
	~A3();
};
class A4
{
	public:
		float a;
		int b ;
		char  c;
	A4();
	~A4();
};
class A5
{
	public:
		double d;
		float a;
		int b ;
		char  c;
	A5();
	~A5();
};

int test_6_3_3(void)
{
	cout << sizeof(A1) << endl;
	cout << sizeof(A2) << endl;
	cout << sizeof(A3) << endl;
	cout << sizeof(A4) << endl;
	cout << sizeof(A5) << endl;
	return 0;
}

int test_6_3_7(void)
{
	int i = 0;
	string strArr1[] = {"Trend","Micro","Soft","H"};
	string *pStrArr1 = new string[2];
	pStrArr1[0] = "US";
	pStrArr1[1] = "CN";
	int tem  = sizeof(strArr1);
	int tem1 = sizeof(string );
	int tem2 = sizeof(pStrArr1);
	cout << tem  << endl;
	cout << tem1 << endl;
	cout << tem2 << endl;
	for(i=0;i<sizeof(strArr1)/sizeof(string);i++)
	{
		cout << strArr1[i];
	}
	for(i=0;i<sizeof(*pStrArr1)*2/sizeof(string);i++)
	{
		cout << pStrArr1[i];
	}
	cout << endl;
		
}


int  test_7_1_2(void)
{
	//const double pi ; //error : uninitialized const  ‘pi’ [-fpermissive]
	const double bi = 3.1415 ; //正确: const 变量定义的时候必须初始化
	//bi = 3.1415;      //eroor: const 变量是只读的 不能修改
	return 0;
}

int test_7_4_4(char (*p)[4])
{
	int i,j;
	int sum = 0 ;
	for(i=0;i<3;i++)
		for(j=0;j<4;j++)
			//sum += p[i][j];
			sum += *(*(p+i)+j);

	int average = sum/12;
	printf(" %d \n",average);
	return 0;
}
int test_7_4_4(char **p)
{
	char *p1[20];
	p1[0] = *p;
	p1[1] = *(p+1);
	p1[2] = *(p+2);
	p1[3] = *(p+3);
	cout << *(p1 + 3) << endl;
	cout << p1[1][1] << endl;
}

int test_7_4_4(void)
{
	// int *P 等效于int a[]，但是不能完全混用
	// 可以将指针表示为数组的形式，但是不能混着调用
	// *(p+i) = *(a+i) = a[i] = p[i]
	// a 代表的是数组首地址；&a 代表的是整个数组首地址
	int *p1 = (int*)malloc(sizeof(int)*6);
	int i = 0,j =0 ,k=0 ;
	for(i=0;i<6;i++)
	{
		p1[i] = i*2;
		printf("%d \n",p1[i]);
		printf("%d \n",p1+i);
	}
	int a1[6] = {0};
	printf("\n");
	for(i=0;i<6;i++)
	{
		a1[i] = p1[i];
		printf("%d \n",*(a1+i));
		printf("%d \n",&a1[i]);
	}
	printf("\n");
	// int **P 等效于int *a[]，但是不能完全混用
	// 可以将指针表示为数组的形式，但是不能混着调用
	char a3[3][20] = {{"first point!"},{"seconed point!"},{"third point!"}};
	//char **p3 = (char**)malloc(sizeof(char)*2*3);
	char *p3[4] ;
	for(i=0;i<3;i++)
	{
		p3[i] = a3[i];
	}
	test_7_4_4(p3);

	
	// int (*P)[n] 等效于int a[m][n]，但是不能完全混用
	// 可以将指针表示为数组的形式，但是不能混着调用
	// a 代表首行元素首地址；a[i]代表第i 行首地址
	char a2[3][4] ={{1,2,3,5},{4,5,6,5},{7,8,9,5}};
	for(i=0;i<3;i++)
	{
		printf(" %d ",&a2[i]);
		for(j=0;j<4;j++)
		{
			printf(" %d \n",&a2[i][j]);
		}
	}
	printf(" %d %d \n",a2+1,&a2[1]); // 第一行首地址
	printf(" %d %d \n",a2+2,a2[2]); // 第二行第0列首地址
	printf(" %d %d \n",*(*(a2+2)+3),a2[2][3]); // 第二行第2列元素
	test_7_4_4(a2);
	char (*p2)[4];
	p2 = a2;
	printf(" %d \n",p2[2][3]);
}

int main()
{
	//test_5_4_1();
	//test_5_5_1();
	//test_5_6_2();
	//test_6_3_3();	
	//test_6_3_7();

	test_7_4_4();
	return 0;
}
