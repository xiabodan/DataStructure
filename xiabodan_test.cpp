#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <boost/lexical_cast.hpp>
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


//test_6_3_3 ÀàµÄziseofŒÆËã
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

//sizeof ÓÃ·š×¢ÒâsizeofÊÇ¹ØŒü×ÖstrlenÊÇ¿âº¯Êý
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

//const¶šÒå×¢ÒâÊÂÏî
int  test_7_1_2(void)
{
	//const double pi ; //error : uninitialized const  ¡®pi¡¯ [-fpermissive]
	const double bi = 3.1415 ; //ÕýÈ·: const ±äÁ¿¶šÒåµÄÊ±ºò±ØÐë³õÊŒ»¯
	//bi = 3.1415;      //eroor: const ±äÁ¿ÊÇÖ»¶ÁµÄ ²»ÄÜÐÞžÄ
	return 0;
}

//Êý×éÓëÖžÕë
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
	cout << *(p1 + 1) << endl;
	cout << p1[1][1] << endl;
	cout << *(*(p1+1)+1) << endl;
}

int test_7_4_4(void)
{
	// int *P µÈÐ§ÓÚint a[]£¬µ«ÊÇ²»ÄÜÍêÈ«»ìÓÃ
	// ¿ÉÒÔœ«ÖžÕë±íÊŸÎªÊý×éµÄÐÎÊœ£¬µ«ÊÇ²»ÄÜ»ì×Åµ÷ÓÃ
	// *(p+i) = *(a+i) = a[i] = p[i]
	// a Žú±íµÄÊÇÊý×éÊ×µØÖ·£»&a Žú±íµÄÊÇÕûžöÊý×éÊ×µØÖ·
	printf("test *p\n");
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
	printf("test **p\n");
	// int **P µÈÐ§ÓÚint *a[]£¬µ«ÊÇ²»ÄÜÍêÈ«»ìÓÃ
	// ¿ÉÒÔœ«ÖžÕë±íÊŸÎªÊý×éµÄÐÎÊœ£¬µ«ÊÇ²»ÄÜ»ì×Åµ÷ÓÃ
	char a3[3][20] = {{"first point!"},{"seconed point!"},{"third point!"}};
	//char **p3 = (char**)malloc(sizeof(char)*2*3);
	char *p3[4] ;
	for(i=0;i<3;i++)
	{
		p3[i] = a3[i];
	}
	test_7_4_4(p3);

	printf("test (*p)[n]\n");
	// int (*P)[n] µÈÐ§ÓÚint a[m][n]£¬µ«ÊÇ²»ÄÜÍêÈ«»ìÓÃ
	// ¿ÉÒÔœ«ÖžÕë±íÊŸÎªÊý×éµÄÐÎÊœ£¬µ«ÊÇ²»ÄÜ»ì×Åµ÷ÓÃ
	// a Žú±íÊ×ÐÐÔªËØÊ×µØÖ·£»a[i]Žú±íµÚi ÐÐÊ×µØÖ·
	char a2[3][4] ={{1,2,3,5},{4,5,6,5},{7,8,9,5}};
	for(i=0;i<3;i++)
	{
		printf(" %d ",&a2[i]);
		for(j=0;j<4;j++)
		{
			printf(" %d \n",&a2[i][j]);
		}
	}
	printf(" %d %d \n",a2+1,&a2[1]); // µÚÒ»ÐÐÊ×µØÖ·
	printf(" %d %d \n",a2+2,a2[2]); // µÚ¶þÐÐµÚ0ÁÐÊ×µØÖ·
	printf(" %d %d \n",*(*(a2+2)+3),a2[2][3]); // µÚ¶þÐÐµÚ2ÁÐÔªËØ
	test_7_4_4(a2);
	char (*p2)[4];
	p2 = a2;
	printf(" %d \n",p2[2][3]);
}

//ÃÔÍŸÖžÕë£¬Ðü¿ÕÖžÕë
int test_7_5_1(void)
{
	unsigned short *pint = (unsigned short*)malloc(sizeof(unsigned short));
	*pint = 10;
	cout << "*pint:"<<*pint <<endl;
	cout << "&pint:"<<pint  <<endl;
	free(pint);
	//pint = NULL;   //1  : if have no this sentence, pint will be hung point 

	long * plong = new long;
	*plong = 90000;
	cout << "*plong:" << *plong <<endl;
	cout << "&plong:" << plong	<<endl;

	*pint = 20;   	// ŽíÎó! pint ÒÑŸ­±»ÊÍ·Å±àÒëÆ÷ÊÍ·ÅÄÚŽæÁË¡£
					// Èç¹ûÃ»ÓÐÉÏÃæ1 ÕâŸä»°œ«pintÖÃÎ»¿ÕÖžÕë£¬ÄÇÃŽÕâŸä»°±àÒëÆ÷œ«²»»á±šŽí
				  	// Èç¹ûÓÐÁËÉÏÃæµÄ1 ÕâŸä»°£¬±àÒëÆ÷œ«²»ÔÙÔÊÐíÕâŸä»°
	cout << "*pint:"  <<*pint <<endl;
	cout << "*plong:" << *plong <<endl;
	cout << "&pint:"<<pint  <<endl;
	cout << "&plong:" << plong	<<endl;
	delete plong;

	return 0;
}
//º¯ÊýÖžÕëÓëÄ£°æ±à³Ì
int add(int a,int b)
{
	return (a+b);
}
int minus1(int a, int b)
{
	return (a-b);
}
int multi(int a, int b)
{
	return (a*b);
}
void test(int (*p)(int ,int),int a,int b)
{
	int r = (*p)(a,b);
	printf("a = %d, b = %d ,f(a,b) = %d\n",a,b,r);
	
}
int test_9_3_1(void)
{
	int a = 1,b=4,c=-5,d=9,e=29;
	test(add,a,b);
	test(minus1,b,c);
	test(multi,d,e);

	return 0;
}
//º¯ÊýÄ£°æ
template <typename T>
T min1(T a,T b)
{
	return (a<b)?a:b;
}
int test_9_3_2(void)
{
	 int n1=2,n2=10;  
     double d1=1.5,d2=5.6;  
     cout<< "min:"<<min<int>(n1,n2)<<endl;  
     cout<< "min:"<<min<double>(d1,d2)<<endl;  
}

//Àà
class xiabo
{
public:
	xiabo():a(1),b(1)
	{
		e++;
		const int m = 17;
	}
	xiabo(int i)
	{
		cout <<"xiabo i:" << i << endl;
	}
	~xiabo(){}

	int a;
	int b;
	static int c ;
	//static int c = 5; //error : ISO C++ forbids in-class initialization of non-const static member 'c'
	static const int d = 8;
	static const double g = 9.7; //¿ÉÒÔ
	static const char h = 82; //¿ÉÒÔ

	static int get_static_num() //±ØÐëŒÓstatic £¬²»È»ÔÚ¹«ÓÐŸ²Ì¬º¯ÊýÖÐŸÍ²»ÄÜµ÷ÓÃÁË
	{
		return e;
	}
	static int get_static_const_num() //±ØÐëŒÓstatic £¬²»È»ÔÚ¹«ÓÐŸ²Ì¬º¯ÊýÖÐŸÍ²»ÄÜµ÷ÓÃÁË
	{
		return f;
	}

	int fun1(void);
protected:
	static int e ; 
	static const int f = 30; //
	int fun2(void);

private:
	int fun3(void);
	
};
int xiabo::c = 5;   //Ÿ²Ì¬³ÉÔ±ÕýÈ·³õÊŒ»¯·œ·š
int xiabo::e = 0;   //protected static Ò²Òª³õÊŒ»¯

int xiabo::fun1(void)
{
	return 0;
}
int xiabo::fun2(void)
{

	return 0;
}
int xiabo::fun3(void)
{

	return 0;
}


int return_protected_static(void)
{
	//return xiabo::e; //errro!
	return xiabo::get_static_num();//²»ÔÊÐíÔÚÊµÀýÖÐ·ÃÎÊ£¬ÔÊÐíÔÚ¹«ÓÐŸ²Ì¬³ÉÔ±º¯Êý·ÃÎÊ
}
int return_protected_static_const()
{
	return xiabo::get_static_const_num();
}

int test_10_3_1(void)
{
	xiabo A;
	xiabo B;
	xiabo C(99);
	char  a = 82;
	cout << A.a <<endl;
	cout << A.b <<endl;
	cout << A.c <<endl;
	cout << A.d <<endl;
	//cout << A.e <<endl; //e ÎªŸ²Ì¬³ÉÔ±±äÁ¿£¬²»ÔÊÐíÔÚÊµÀýÖÐ·ÃÎÊ£¬Ö»ÔÊÐíÔÚ¹«ÓÐŸ²Ì¬³ÉÔ±º¯Êý·ÃÎÊ		
	//cout << A.f <<endl;  //f ÎªŸ²Ì¬±£»€µÄ³ÉÔ±³£Á¿£¬²»ÔÊÐíÔÚÊµÀýÖÐ·ÃÎÊ£¬Ö»ÔÊÐíÔÚ¹«ÓÐŸ²Ì¬³ÉÔ±º¯Êý·ÃÎÊ
	cout << A.g <<endl;//Êä³ö9.7
	cout << A.h <<endl;//Êä³ö R
	cout << a <<endl;	//Êä³ö R
	cout << C.a <<endl;
	cout << C.b <<endl;

	A.a = 10;
	B.a = A.a;
	cout << B.a <<endl;

	A.c = 20;
	cout << A.c <<endl;//20  
	cout << B.c <<endl;//20  A ºÍB œ«¹²ÏíŸ²Ì¬³ÉÔ±±äÁ¿c

	cout << return_protected_static() <<endl;
	cout << xiabo::get_static_num()   <<endl;
	
	cout << return_protected_static_const() <<endl;
	cout << xiabo::get_static_const_num()   <<endl;

}

//test_10_3_3
class base
{
private:
	
	int m_j;
	int m_i;
	
public:
	base(int i):m_j(i),m_i(m_j) //
	{
		cout << "base(int i)" << m_i << "  " << m_j<<endl;
	}
	
	base():m_j(0),m_i(m_j)
	{
		cout << "base()" << m_i << "  " << m_j<<endl;
	}

	int get_i(){return m_i;}
	int get_j(){return m_j;}
	
};
int test_10_3_3(void)
{
	base obj(98);
	cout << obj.get_i() << "  " << obj.get_j() << endl;

	base obj1;
	cout << obj1.get_i() << "  " << obj1.get_j() << endl;
	return 0;
}

class A619
{
public:
	A619(){const int a = 1;c=2;}
	int size  ;      //ÕýÈ·£¬µ«ÊÇ³õÖµÎªËæ»úÊý
	static const int b = 1; 
	//const int c = 1; //error: ³£Á¿±ØÐëÔÚ¹¹Ôìº¯ÊýµÄ³õÊŒ»¯ÁÐ±íÖÐ
	int fun1(void);

	
private:
	int c ;

};

int A619::fun1(void)
{
	c = 3;//c ÊÇËœÓÐ³ÉÔ±±äÁ¿£¬Ö»ÄÜ³ÉÔ±º¯Êý·ÃÎÊ
	cout << c <<endl;
}
int test_10_3_4(void)
{
	A619 A;
	cout << A.size <<endl;//true: sizeÊÇ¹«ÓÐ³ÉÔ±±äÁ¿£¬·Ç³ÉÔ±º¯ÊýÒ²ÄÜ·ÃÎÊ
	A.fun1();
	//cout << A.c <<endl;//error: c ÊÇËœÓÐ³ÉÔ±±äÁ¿£¬Ö»ÄÜÔÚ³ÉÔ±º¯ÊýÖÐ·ÃÎÊ
}

//¹«ÓÐŒÌ³ÐºÍËœÓÐŒÌ³Ð
class animal
{
public:
	animal():base_a(1),base_b(2),base_c(3){}
	int  base_a;
	void base_public(){cout << "base_public()"<<base_a<<base_b<<base_c<<endl;}
protected:
	int  base_b;
	void base_protected(){cout << "base_protected()"<<base_a<<base_b<<base_c<<endl;}
private:
	int  base_c;
	void base_private(){cout << "base_private()"<<base_a<<base_b<<base_c<<endl;}
	
};
class public_cat : public animal
{
public:
	public_cat(){}
public:
	int public_cat_public(void)
	{
		base_public();   //ok£º»ùÀàµÄ¹«¹²³ÉÔ±ÔÚÅÉÉúÀàÖÐÎª¹«¹²³ÉÔ±
		base_protected();//ok£º»ùÀàµÄ±£»€³ÉÔ±ÔÚÅÉÉúÀàÖÐÎª±£»€³ÉÔ±
		//base_private();    //error:¹«ÓÐŒÌ³ÐÒ²²»ÔÊÐí·ÃÎÊ»ùÀàµÄprivate
		
		int public_cat_a;
		public_cat_a = base_a; //ok£º»ùÀàµÄ¹«¹²³ÉÔ±ÔÚÅÉÉúÀàÖÐÎª¹«¹²³ÉÔ±
		public_cat_a = base_b; //ok£º»ùÀàµÄ±£»€³ÉÔ±ÔÚÅÉÉúÀàÖÐÎª±£»€³ÉÔ±
		//public_cat_a = base_c; //error£º»ùÀàÖÐËœÓÐ³ÉÔ±ÔÚÅÉÉúÀàÖÐÊÇ²»¿ÉŒûµÄ

		base_a = 1;
		base_b = 1; //ok: »ùÀàÖÐµÄprotectedÔÚ×ÓÀà³ÉÔ±º¯ÊýÖÐŒÈÄÜ·ÃÎÊÒ²ÄÜÐÞžÄ
		//base_c = 1; //error : »ùÀàÖÐµÄprivateŒÈ²»ÄÜ·ÃÎÊÒ²²»ÄÜÐÞžÄ
	}
		
};

class protected_cat : protected animal
{
public:
	protected_cat(){}
public:
	int protected_cat_a;
	int protected_cat_public(void)
	{
		
		protected_cat_a = base_a; //ok£º»ùÀàµÄ¹«¹²³ÉÔ±ÔÚÅÉÉúÀàÖÐÎª±£»€³ÉÔ±
		protected_cat_a = base_b; //ok£º»ùÀàµÄ±£»€³ÉÔ±ÔÚÅÉÉúÀàÖÐÎª±£»€³ÉÔ±
		//protected_cat_a = base_c; //error£º»ùÀàÖÐËœÓÐ³ÉÔ±ÔÚÅÉÉúÀàÖÐÊÇ²»¿ÉŒûµÄ
		base_a = 1;
		base_b = 1; //ok: »ùÀàÖÐµÄprotectedÔÚ×ÓÀà³ÉÔ±º¯ÊýÖÐŒÈÄÜ·ÃÎÊÒ²ÄÜÐÞžÄ
	}

};

class private_cat : private animal
{
public:
	private_cat(){}
public:
	int private_cat_a;
	int private_cat_public(void)
	{
		
		private_cat_a = base_a; //ok£º»ùÀàµÄ¹«¹²³ÉÔ±ÔÚÅÉÉúÀàÖÐÎªËœÓÐ³ÉÔ±
		private_cat_a = base_b; //ok£º»ùÀàµÄ±£»€³ÉÔ±ÔÚÅÉÉúÀàÖÐÎªËœÓÐ³ÉÔ±
		//private_cat_a = base_c; //error£º»ùÀàÖÐËœÓÐ³ÉÔ±ÔÚÅÉÉúÀàÖÐÊÇ²»¿ÉŒûµÄ
		base_a = 1;
		base_b = 1; //ok: »ùÀàÖÐµÄprotectedÔÚ×ÓÀà³ÉÔ±º¯ÊýÖÐŒÈÄÜ·ÃÎÊÒ²ÄÜÐÞžÄ
	}

};
class protected_protected_cat:protected protected_cat
{
	
};

class public_public_cat:public public_cat
{
	
};

int test_11_2_1 (void)
{
	int a ;
	animal animal1;
	//a = animal1.base_b;  //error:Íâ²¿º¯Êý²»ÄÜ·ÃÎÊprotected³ÉÔ±

	public_cat public_cat1; //¹«ÓÐŒÌ³Ð
	public_cat1.base_public();
	public_cat1.public_cat_public();

	a = public_cat1.base_a;//ok£º»ùÀàµÄ¹«¹²³ÉÔ±ÔÚÅÉÉúÀàÖÐÎª¹«¹²³ÉÔ±£¬¶Ô¶ÔÏó¿ÉŒû
	//a = public_cat1.base_b; //error£º»ùÀàµÄ±£»€³ÉÔ±ÔÚÅÉÉúÀàÖÐÎª±£»€³ÉÔ±£¬¶Ô¶ÔÏó²»¿ÉŒû
	//a = public_cat1.base_c; //error£º»ùÀàÖÐËœÓÐ³ÉÔ±ÔÚÅÉÉúÀàÖÐÊÇ²»¿ÉŒûµÄ,¶Ô¶ÔÏó²»¿ÉŒû
	public_cat1.base_a = 1;
	//public_cat1.base_b = 1; //error: »ùÀàÖÐµÄprotectedÔÚÍâ²¿º¯ÊýÖÐ²»¿ÉŒûÒ²²»ÄÜÐÞžÄ
	//base_c = 1;                 //error : »ùÀàÖÐµÄprivateŒÈ²»ÄÜ·ÃÎÊÒ²²»ÄÜÐÞžÄ
	
	protected_cat protected_cat1;//±£»€ŒÌ³Ð
	//a = protected_cat1.base_a;//error£º»ùÀàµÄ¹«¹²³ÉÔ±ÔÚÅÉÉúÀàÖÐÎª±£»€³ÉÔ±£¬¶Ô¶ÔÏó²»¿ÉŒû
	//a = protected_cat1.base_b; //error£º»ùÀàµÄ±£»€³ÉÔ±ÔÚÅÉÉúÀàÖÐÎª±£»€³ÉÔ±£¬¶Ô¶ÔÏó²»¿ÉŒû
	//a = protected_cat1.base_c; //error£º»ùÀàÖÐËœÓÐ³ÉÔ±ÔÚÅÉÉúÀàÖÐÊÇ²»¿ÉŒûµÄ,¶Ô¶ÔÏó²»¿ÉŒû

	private_cat private_cat1;//ËœÓÐŒÌ³Ð
	//a = protected_cat1.base_a;//error£º»ùÀàµÄ¹«¹²³ÉÔ±ÔÚÅÉÉúÀàÖÐÎªËœÓÐ³ÉÔ±£¬¶Ô¶ÔÏó²»¿ÉŒû
	//a = protected_cat1.base_b; //error£º»ùÀàµÄ±£»€³ÉÔ±ÔÚÅÉÉúÀàÖÐÎªËœÓÐ³ÉÔ±£¬¶Ô¶ÔÏó²»¿ÉŒû
	//a = protected_cat1.base_c; //error£º»ùÀàÖÐËœÓÐ³ÉÔ±ÔÚÅÉÉúÀàÖÐÊÇ²»¿ÉŒûµÄ,¶Ô¶ÔÏó²»¿ÉŒû

	protected_protected_cat protected_protected_cat1;
	//a = protected_protected_cat1.base_a; //error: ±£»€ŒÌ³Ð£¬»ùÀà³ÉÔ±Ö»ÄÜÓÉÖ±œÓÅÉÉúÀà·ÃÎÊ£¬ÎÞ·šÔÙÏòÏÂŒÌ³Ð£¬ŒŽÊ¹ÊÇ¹«ÓÐŒÌÐøŒÌ³Ð

	public_public_cat public_public_cat1;
	a = public_public_cat1.base_a;  //ok
	

}

int test_12_1_1(void)
{
	printf("%f\n",5); //0.00000
	printf("%d\n",6.01231);//²»È·¶šÊý
}
int test_12_1_2(void)
{
	struct a1{
		unsigned int x:1;  //1Î»
		unsigned int z:32; //32bit
		unsigned int y:4;  //4bit
	};
	struct a1 d = {
		1,
		32,
		5,
	};

	cout << &d << endl;
	d.z = d.x + d.y;
	cout << d.x << endl; 
	cout << d.y << endl;
	cout << d.z << endl;
	cout << sizeof(d) <<endl;
	return 0;
}

void itoa(int num ,char *str,int n)
{
	char tem[n]; //C++Ö§³Ö±ä³€Êý×é
	int i= 0, j = 0;
	while(num)
	{
		tem[i++] = num % 10 + '0';
		num = num / 10;
	}
	tem[i] = '\0';
	printf("tem = %s \n",tem);
	printf("strlen tem = %d \n",strlen(tem));
	while(i>0)
	{
		str[j++] = tem[--i];
	}
	str[j] = '\0';
	printf("str = %s \n",str);
}
int test_14_1_1(void)
{
	int num = 12345;
	char string[10];
	itoa(num,string,10);
	printf("int = %d ,string = %c ,strlen = %d \n",num,string[3],strlen(string));

	return 0;
}
int  atoi(char *str ,int n)
{
	int i = 0;
	int num =0;
	while(str[i])
	{
		num = num*10 + (str[i] - '0');
		i++;
	}
	printf("num = %d ,strlen str = %d\n",num,strlen(str));
	return num;
}

int test_14_1_2(void)
{
	char str[10] = {"12345"};
	int num = atoi(str,10);
}
char *strcpy1(char* strdst, char* strsrc )
{
	assert((strdst != NULL)&&(strsrc != NULL));
	char *address = strdst;
	while((*strdst++ = *strsrc++) != '\0')
		NULL;

	return address;
}

void *memcpy1(void *dst,const void *src,size_t num)  
{  
    assert((dst!=NULL)&&(src!=NULL));  
          //assert£šdes>=src+num||src>dst+num£©;  
    unsigned char * psrc = (unsigned char *)src;//byte ŒÈÎªunsigned charÀàÐÍ  
    unsigned char * pdst = (unsigned char *)dst;  
    while(num-->0)*pdst++ = *psrc++;  
    return dst;  
}  

int test_14_1_3(void)
{
	char strsrc[]={"asdfghjkl123456789"};
	char strdst[20];
	char* address;
	address = strcpy1(strdst, strsrc);
	printf("src = %s,dst = %s,strlen of src = %d,strlen of dst = %d\n",strsrc,strdst,strlen(strsrc),strlen(strdst));
	printf("length is :%d\n",strlen(address));
	printf("sizeof is :%d\n",sizeof(address));
	printf("sizeof is src:%d\n",sizeof(strsrc));
	printf("sizeof is dst:%d\n",sizeof(strdst));
}
void test_14_2_3()
{
	//strcpy·œ·šÊµÏÖ
	char str[] = "abcdefghijk";
	printf("%s\n",str);
	int step = 3;
	int i = strlen(str) - step;
	//char* tem = (char*)malloc(sizeof(str));
	char tem[20];
	strcpy1( tem,str+i);
	strcpy1( tem+step,str);
	
	*(tem + strlen(str)) = '\0';
	strcpy1(str,tem);
	printf("strcpy:%s\n",str);

	//memcpy·œ·šÊµÏÖ
	char str1[] = "abcdefghijk";
	printf("%s\n",str1);
	int step1 = 4;
	int j = strlen(str) - step1;
	char tem1[20];
	memcpy1(tem1,str1+j,step1);
	memcpy1(tem1+step1,str1,j);
	memcpy1(str1,tem1,strlen(str) );
	printf("memcpy:%s\n",str1);
	
	//²âÊÔmemcpyº¯Êý
	int a[10] = {1,2,3,4,5,6,7,8,9,10};
	int b[10];
	memcpy1(b,a,10*4);
	for(int i=0;i<10;i++)
	{
		printf("a[%d] = %d\n",i,b[i]);
	}
}
void test_my_1(void)
{
	const char str4[] = "abc";
	const char str3[] = "abc";
	const char *str5  = "abc";
	const char *str6  = "abc";
	cout << boolalpha << (str3 == str4)<<endl;
	cout << boolalpha << (str5 == str6)<<endl;
	cout << boolalpha << (&str5 == &str6)<<endl;
	cout << "str3: " << str3 <<endl;	
	cout << "str4: " << str4 <<endl;	
	cout << "str5: " << str5 <<endl;
	cout << "str6: " << str6 <<endl;
	cout << "&str5: " << &str5 <<endl;
	cout << "&str6: " << &str6 <<endl;

	printf(" \n");
	printf("str3 add is 0x%x \n",str3);//string str3 fisrt element address
	printf("str3+1 add is 0x%x \n",str3+1);//string str3 seconed element address
	printf("&str3 add is 0x%x \n",&str3);//whole string str3 front address
	printf("&str3+1 add is 0x%x \n",&str3+1);//next arry front address,not seconed element address. here point string str4
	printf("str4 add is 0x%x \n",str4); //here : str4 = &str3 + 1

	printf(" \n");
	printf("str5 add is 0x%x \n",str5);//string str5  first address
	printf("str5+1 add is 0x%x \n",str5+1);//string str5  seconed address
	printf("&str5 add is 0x%x \n",&str5);//point str5 address
	printf("&str5+1 add is 0x%x \n",&str5+1);
	printf("&str6 add is 0x%x \n",&str6); //
	printf("str6 add is 0x%x \n",str6); //
}

int test_my_2(int a)
{
	a = 100;
	printf("test_my_2 int a : &a = 0x%x \n",&a);
	return a;
}
int test_my_2(int* a)
{
	*a = 100;
	printf("test_my_2 int* a : &a = 0x%x \n",&a);
	return 100;
}
void test_my_2_1(int* a,int *b)
{
	int c = 100;
	a = &c;
	*b = c;
	printf("*a = %d\n",*a);
	printf("void test_my_2 int* a int *b: &a = 0x%x , &c = 0x%x \n",&a,&c);
	printf("void test_my_2 int* a int *b: &b = 0x%x , &c = 0x%x \n",&b,&c);
}

int test_my_2_2(int* a)
{
	*a = 100;
}

int test_my_2_3(int* a)
{
	a = (int*)malloc(sizeof(int)*5);
	int i = 0;
	for(i=0;i<5;i++)
		a[i] = i;
	
}

int test_my_2_4(char** a)
{
	//*a = (char*)malloc(sizeof(char)*5);
	char *s = "asdgw";
	*a = s;
}

void test_my_2(void)
{
	int a = 10;
	int r = test_my_2(a);
	printf("main : &a = 0x%x \n",&a);
	printf("a = %d,return a = %d\n",a,r); // a=10 ,r=100
	
	printf("\n");
	r = test_my_2(&a);
	printf("main : &a = 0x%x \n",&a);
	printf("a = %d,return a = %d\n",a,r);//a =100,r =100
	
	printf("\n");
	int b = 10,c = 10;
	test_my_2_1(&b,&c);
	printf("main : &b = 0x%x ,&c = 0x%x \n",&b,&c);
	printf("b = %d,c = %d\n",b,c);//10 ,100

	printf("\n");
	int d = 10;
	int *p=&d;
	printf("*p = %d\n",*p);//10 
	test_my_2_2(p);
	printf("*p = %d\n",*p);//100

	printf("**Test secondary pointer function transform parameter1**\n");
	int *p1 =NULL;
	test_my_2_3(p1);
	if(!p1)	
		printf("p1 is NULL ,have not malloc space!\n");//Ҫִ\D0д˾仰\A3\AC\D2\F2Ϊû\D3\D0\D5\FDȷ\B7\D6\C5\E4\BFռ\E4

	printf("**Test secondary pointer function transform parameter2**\n");
	char *p2 = (char*)malloc(sizeof(char)*5);
	test_my_2_4(&p2);	
	if(p2)
	{
		printf("p1 malloc space success!\n");
		int i = 0;
		for(i=0;i<5;i++)
		{
			printf("p1[%d] = %c\n",i,p2[i]);
		}
	}
	else
		printf("p1 is NULL ,have not malloc space!\n");

	
	printf("*************Test The secondary pointer*****************\n");
	char** p3 = (char**)malloc(sizeof(char*)*3);//\B1\D8\D0\EBΪp3һ\BC\B6ָ\D5\EB\B7\D6\C5\E4\C4ڴ\E6\BFռ䡣
	//char** p3 = NULL;
	p3[0] = "qwert";
	p3[1] = "asdfg";
	p3[2] = "zxcvb";
	cout << p3[0] << endl;
	cout << p3[1] << endl;
	cout << p3[2] << endl;
}

int main()
{
	//test_5_4_1();
	//test_5_5_1();
	//test_5_6_2();
	//test_6_3_3();	
	//test_6_3_7();
	//test_7_4_4();
	//test_7_5_1();
	//test_9_3_1();
	//test_9_3_2();
	//test_10_3_1();
	//test_10_3_3();
	//test_10_3_4();
	//test_11_2_1();
	//test_12_1_1();
	//test_12_1_2();
	//test_14_1_1();
	//test_14_1_2();
	//test_14_1_3();
	//test_14_2_3();
	//test_my_1();
	//test_my_2();
	int i  = 5;	
	printf("%d  %d  %d  %d  %d  %d  \n",i,i,++i,++i,i++,i++);
	using boost::lexical_cast;
  	int a= lexical_cast<int>("123456");
  	double b = lexical_cast<double>("123.456");
  	std::cout << a << std::endl;
  	std::cout << b << std::endl;
	return 0;
}
