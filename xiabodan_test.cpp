#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

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


//test_6_3_3 类的ziseof计算
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

//sizeof 用法注意sizeof是关键字strlen是库函数
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

//const定义注意事项
int  test_7_1_2(void)
{
	//const double pi ; //error : uninitialized const  ‘pi’ [-fpermissive]
	const double bi = 3.1415 ; //正确: const 变量定义的时候必须初始化
	//bi = 3.1415;      //eroor: const 变量是只读的 不能修改
	return 0;
}

//数组与指针
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

//迷途指针，悬空指针
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

	*pint = 20;   	// 错误! pint 已经被释放编译器释放内存了。
					// 如果没有上面1 这句话将pint置位空指针，那么这句话编译器将不会报错
				  	// 如果有了上面的1 这句话，编译器将不再允许这句话
	cout << "*pint:"  <<*pint <<endl;
	cout << "*plong:" << *plong <<endl;
	cout << "&pint:"<<pint  <<endl;
	cout << "&plong:" << plong	<<endl;
	delete plong;

	return 0;
}
//函数指针与模版编程
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
//函数模版
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

//类
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
	static const double g = 9.7; //可以
	static const char h = 82; //可以

	static int get_static_num() //必须加static ，不然在公有静态函数中就不能调用了
	{
		return e;
	}
	static int get_static_const_num() //必须加static ，不然在公有静态函数中就不能调用了
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
int xiabo::c = 5;   //静态成员正确初始化方法
int xiabo::e = 0;   //protected static 也要初始化

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
	return xiabo::get_static_num();//不允许在实例中访问，允许在公有静态成员函数访问
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
	//cout << A.e <<endl; //e 为静态成员变量，不允许在实例中访问，只允许在公有静态成员函数访问		
	//cout << A.f <<endl;  //f 为静态保护的成员常量，不允许在实例中访问，只允许在公有静态成员函数访问
	cout << A.g <<endl;//输出9.7
	cout << A.h <<endl;//输出 R
	cout << a <<endl;	//输出 R
	cout << C.a <<endl;
	cout << C.b <<endl;

	A.a = 10;
	B.a = A.a;
	cout << B.a <<endl;

	A.c = 20;
	cout << A.c <<endl;//20  
	cout << B.c <<endl;//20  A 和B 将共享静态成员变量c

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
	int size  ;      //正确，但是初值为随机数
	static const int b = 1; 
	//const int c = 1; //error: 常量必须在构造函数的初始化列表中
	int fun1(void);

	
private:
	int c ;

};

int A619::fun1(void)
{
	c = 3;//c 是私有成员变量，只能成员函数访问
	cout << c <<endl;
}
int test_10_3_4(void)
{
	A619 A;
	cout << A.size <<endl;//true: size是公有成员变量，非成员函数也能访问
	A.fun1();
	//cout << A.c <<endl;//error: c 是私有成员变量，只能在成员函数中访问
}

//公有继承和私有继承
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
		base_public();   //ok：基类的公共成员在派生类中为公共成员
		base_protected();//ok：基类的保护成员在派生类中为保护成员
		//base_private();    //error:公有继承也不允许访问基类的private
		
		int public_cat_a;
		public_cat_a = base_a; //ok：基类的公共成员在派生类中为公共成员
		public_cat_a = base_b; //ok：基类的保护成员在派生类中为保护成员
		//public_cat_a = base_c; //error：基类中私有成员在派生类中是不可见的

		base_a = 1;
		base_b = 1; //ok: 基类中的protected在子类成员函数中既能访问也能修改
		//base_c = 1; //error : 基类中的private既不能访问也不能修改
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
		
		protected_cat_a = base_a; //ok：基类的公共成员在派生类中为保护成员
		protected_cat_a = base_b; //ok：基类的保护成员在派生类中为保护成员
		//protected_cat_a = base_c; //error：基类中私有成员在派生类中是不可见的
		base_a = 1;
		base_b = 1; //ok: 基类中的protected在子类成员函数中既能访问也能修改
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
		
		private_cat_a = base_a; //ok：基类的公共成员在派生类中为私有成员
		private_cat_a = base_b; //ok：基类的保护成员在派生类中为私有成员
		//private_cat_a = base_c; //error：基类中私有成员在派生类中是不可见的
		base_a = 1;
		base_b = 1; //ok: 基类中的protected在子类成员函数中既能访问也能修改
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
	//a = animal1.base_b;  //error:外部函数不能访问protected成员

	public_cat public_cat1; //公有继承
	public_cat1.base_public();
	public_cat1.public_cat_public();

	a = public_cat1.base_a;//ok：基类的公共成员在派生类中为公共成员，对对象可见
	//a = public_cat1.base_b; //error：基类的保护成员在派生类中为保护成员，对对象不可见
	//a = public_cat1.base_c; //error：基类中私有成员在派生类中是不可见的,对对象不可见
	public_cat1.base_a = 1;
	//public_cat1.base_b = 1; //error: 基类中的protected在外部函数中不可见也不能修改
	//base_c = 1;                 //error : 基类中的private既不能访问也不能修改
	
	protected_cat protected_cat1;//保护继承
	//a = protected_cat1.base_a;//error：基类的公共成员在派生类中为保护成员，对对象不可见
	//a = protected_cat1.base_b; //error：基类的保护成员在派生类中为保护成员，对对象不可见
	//a = protected_cat1.base_c; //error：基类中私有成员在派生类中是不可见的,对对象不可见

	private_cat private_cat1;//私有继承
	//a = protected_cat1.base_a;//error：基类的公共成员在派生类中为私有成员，对对象不可见
	//a = protected_cat1.base_b; //error：基类的保护成员在派生类中为私有成员，对对象不可见
	//a = protected_cat1.base_c; //error：基类中私有成员在派生类中是不可见的,对对象不可见

	protected_protected_cat protected_protected_cat1;
	//a = protected_protected_cat1.base_a; //error: 保护继承，基类成员只能由直接派生类访问，无法再向下继承，即使是公有继续继承

	public_public_cat public_public_cat1;
	a = public_public_cat1.base_a;  //ok
	

}

int test_12_1_1(void)
{
	printf("%f\n",5); //0.00000
	printf("%d\n",6.01231);//不确定数
}
int test_12_1_2(void)
{
	struct a1{
		unsigned int x:1;  //1位
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
	char tem[n]; //C++支持变长数组
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
          //assert（des>=src+num||src>dst+num）;  
    unsigned char * psrc = (unsigned char *)src;//byte 既为unsigned char类型  
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
	//strcpy方法实现
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

	//memcpy方法实现
	char str1[] = "abcdefghijk";
	printf("%s\n",str1);
	int step1 = 4;
	int j = strlen(str) - step1;
	char tem1[20];
	memcpy1(tem1,str1+j,step1);
	memcpy1(tem1+step1,str1,j);
	memcpy1(str1,tem1,strlen(str) );
	printf("memcpy:%s\n",str1);
	//测试memcpy函数
	int a[10] = {1,2,3,4,5,6,7,8,9,10};
	int b[10];
	memcpy1(b,a,10*4);
	for(int i=0;i<10;i++)
	{
		printf("a[%d] = %d\n",i,b[i]);
	}
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
	test_14_1_3();
	test_14_2_3();

	
	return 0;
}
