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



int main()
{
	//test_5_4_1();
	//test_5_5_1();
	
	//int score[10] = {97,96,95,94,93,92,91,90,98,99};
	//int type[10]  = {1,2,1,2,1,1,1,2,2,1};
	//int average = test_5_6_2(10,score,type);
	//cout << average <<endl;
	
	test_6_3_3();
	return 0;
}
