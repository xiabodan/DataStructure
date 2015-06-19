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


//test_6_3_3 ���ziseof����
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

//sizeof �÷�ע��sizeof�ǹؼ���strlen�ǿ⺯��
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

//const����ע������
int  test_7_1_2(void)
{
	//const double pi ; //error : uninitialized const  ��pi�� [-fpermissive]
	const double bi = 3.1415 ; //��ȷ: const ���������ʱ������ʼ��
	//bi = 3.1415;      //eroor: const ������ֻ���� �����޸�
	return 0;
}

//������ָ��
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
	// int *P ��Ч��int a[]�����ǲ�����ȫ����
	// ���Խ�ָ���ʾΪ�������ʽ�����ǲ��ܻ��ŵ���
	// *(p+i) = *(a+i) = a[i] = p[i]
	// a ������������׵�ַ��&a ����������������׵�ַ
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
	// int **P ��Ч��int *a[]�����ǲ�����ȫ����
	// ���Խ�ָ���ʾΪ�������ʽ�����ǲ��ܻ��ŵ���
	char a3[3][20] = {{"first point!"},{"seconed point!"},{"third point!"}};
	//char **p3 = (char**)malloc(sizeof(char)*2*3);
	char *p3[4] ;
	for(i=0;i<3;i++)
	{
		p3[i] = a3[i];
	}
	test_7_4_4(p3);

	
	// int (*P)[n] ��Ч��int a[m][n]�����ǲ�����ȫ����
	// ���Խ�ָ���ʾΪ�������ʽ�����ǲ��ܻ��ŵ���
	// a ��������Ԫ���׵�ַ��a[i]�����i ���׵�ַ
	char a2[3][4] ={{1,2,3,5},{4,5,6,5},{7,8,9,5}};
	for(i=0;i<3;i++)
	{
		printf(" %d ",&a2[i]);
		for(j=0;j<4;j++)
		{
			printf(" %d \n",&a2[i][j]);
		}
	}
	printf(" %d %d \n",a2+1,&a2[1]); // ��һ���׵�ַ
	printf(" %d %d \n",a2+2,a2[2]); // �ڶ��е�0���׵�ַ
	printf(" %d %d \n",*(*(a2+2)+3),a2[2][3]); // �ڶ��е�2��Ԫ��
	test_7_4_4(a2);
	char (*p2)[4];
	p2 = a2;
	printf(" %d \n",p2[2][3]);
}

//��;ָ�룬����ָ��
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

	*pint = 20;   	// ����! pint �Ѿ����ͷű������ͷ��ڴ��ˡ�
					// ���û������1 ��仰��pint��λ��ָ�룬��ô��仰�����������ᱨ��
				  	// ������������1 ��仰��������������������仰
	cout << "*pint:"  <<*pint <<endl;
	cout << "*plong:" << *plong <<endl;
	cout << "&pint:"<<pint  <<endl;
	cout << "&plong:" << plong	<<endl;
	delete plong;

	return 0;
}
//����ָ����ģ����
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
//����ģ��
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

//��
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
	static const double g = 9.7; //����
	static const char h = 82; //����

	static int get_static_num() //�����static ����Ȼ�ڹ��о�̬�����оͲ��ܵ�����
	{
		return e;
	}
	static int get_static_const_num() //�����static ����Ȼ�ڹ��о�̬�����оͲ��ܵ�����
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
int xiabo::c = 5;   //��̬��Ա��ȷ��ʼ������
int xiabo::e = 0;   //protected static ҲҪ��ʼ��

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
	return xiabo::get_static_num();//��������ʵ���з��ʣ������ڹ��о�̬��Ա��������
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
	//cout << A.e <<endl; //e Ϊ��̬��Ա��������������ʵ���з��ʣ�ֻ�����ڹ��о�̬��Ա��������		
	//cout << A.f <<endl;  //f Ϊ��̬�����ĳ�Ա��������������ʵ���з��ʣ�ֻ�����ڹ��о�̬��Ա��������
	cout << A.g <<endl;//���9.7
	cout << A.h <<endl;//��� R
	cout << a <<endl;	//��� R
	cout << C.a <<endl;
	cout << C.b <<endl;

	A.a = 10;
	B.a = A.a;
	cout << B.a <<endl;

	A.c = 20;
	cout << A.c <<endl;//20  
	cout << B.c <<endl;//20  A ��B ������̬��Ա����c

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
	int size  ;      //��ȷ�����ǳ�ֵΪ�����
	static const int b = 1; 
	//const int c = 1; //error: ���������ڹ��캯���ĳ�ʼ���б���
	int fun1(void);

	
private:
	int c ;

};

int A619::fun1(void)
{
	c = 3;//c ��˽�г�Ա������ֻ�ܳ�Ա��������
	cout << c <<endl;
}
int test_10_3_4(void)
{
	A619 A;
	cout << A.size <<endl;//true: size�ǹ��г�Ա�������ǳ�Ա����Ҳ�ܷ���
	A.fun1();
	//cout << A.c <<endl;//error: c ��˽�г�Ա������ֻ���ڳ�Ա�����з���
}

//���м̳к�˽�м̳�
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
		base_public();   //ok������Ĺ�����Ա����������Ϊ������Ա
		base_protected();//ok������ı�����Ա����������Ϊ������Ա
		//base_private();    //error:���м̳�Ҳ��������ʻ����private
		
		int public_cat_a;
		public_cat_a = base_a; //ok������Ĺ�����Ա����������Ϊ������Ա
		public_cat_a = base_b; //ok������ı�����Ա����������Ϊ������Ա
		//public_cat_a = base_c; //error��������˽�г�Ա�����������ǲ��ɼ���

		base_a = 1;
		base_b = 1; //ok: �����е�protected�������Ա�����м��ܷ���Ҳ���޸�
		//base_c = 1; //error : �����е�private�Ȳ��ܷ���Ҳ�����޸�
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
		
		protected_cat_a = base_a; //ok������Ĺ�����Ա����������Ϊ������Ա
		protected_cat_a = base_b; //ok������ı�����Ա����������Ϊ������Ա
		//protected_cat_a = base_c; //error��������˽�г�Ա�����������ǲ��ɼ���
		base_a = 1;
		base_b = 1; //ok: �����е�protected�������Ա�����м��ܷ���Ҳ���޸�
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
		
		private_cat_a = base_a; //ok������Ĺ�����Ա����������Ϊ˽�г�Ա
		private_cat_a = base_b; //ok������ı�����Ա����������Ϊ˽�г�Ա
		//private_cat_a = base_c; //error��������˽�г�Ա�����������ǲ��ɼ���
		base_a = 1;
		base_b = 1; //ok: �����е�protected�������Ա�����м��ܷ���Ҳ���޸�
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
	//a = animal1.base_b;  //error:�ⲿ�������ܷ���protected��Ա

	public_cat public_cat1; //���м̳�
	public_cat1.base_public();
	public_cat1.public_cat_public();

	a = public_cat1.base_a;//ok������Ĺ�����Ա����������Ϊ������Ա���Զ���ɼ�
	//a = public_cat1.base_b; //error������ı�����Ա����������Ϊ������Ա���Զ��󲻿ɼ�
	//a = public_cat1.base_c; //error��������˽�г�Ա�����������ǲ��ɼ���,�Զ��󲻿ɼ�
	public_cat1.base_a = 1;
	//public_cat1.base_b = 1; //error: �����е�protected���ⲿ�����в��ɼ�Ҳ�����޸�
	//base_c = 1;                 //error : �����е�private�Ȳ��ܷ���Ҳ�����޸�
	
	protected_cat protected_cat1;//�����̳�
	//a = protected_cat1.base_a;//error������Ĺ�����Ա����������Ϊ������Ա���Զ��󲻿ɼ�
	//a = protected_cat1.base_b; //error������ı�����Ա����������Ϊ������Ա���Զ��󲻿ɼ�
	//a = protected_cat1.base_c; //error��������˽�г�Ա�����������ǲ��ɼ���,�Զ��󲻿ɼ�

	private_cat private_cat1;//˽�м̳�
	//a = protected_cat1.base_a;//error������Ĺ�����Ա����������Ϊ˽�г�Ա���Զ��󲻿ɼ�
	//a = protected_cat1.base_b; //error������ı�����Ա����������Ϊ˽�г�Ա���Զ��󲻿ɼ�
	//a = protected_cat1.base_c; //error��������˽�г�Ա�����������ǲ��ɼ���,�Զ��󲻿ɼ�

	protected_protected_cat protected_protected_cat1;
	//a = protected_protected_cat1.base_a; //error: �����̳У������Աֻ����ֱ����������ʣ��޷������¼̳У���ʹ�ǹ��м����̳�

	public_public_cat public_public_cat1;
	a = public_public_cat1.base_a;  //ok
	

}

int test_12_1_1(void)
{
	printf("%f\n",5); //0.00000
	printf("%d\n",6.01231);//��ȷ����
}
int test_12_1_2(void)
{
	struct a1{
		unsigned int x:1;  //1λ
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
	char tem[n]; //C++֧�ֱ䳤����
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
          //assert��des>=src+num||src>dst+num��;  
    unsigned char * psrc = (unsigned char *)src;//byte ��Ϊunsigned char����  
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
	//strcpy����ʵ��
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

	//memcpy����ʵ��
	char str1[] = "abcdefghijk";
	printf("%s\n",str1);
	int step1 = 4;
	int j = strlen(str) - step1;
	char tem1[20];
	memcpy1(tem1,str1+j,step1);
	memcpy1(tem1+step1,str1,j);
	memcpy1(str1,tem1,strlen(str) );
	printf("memcpy:%s\n",str1);
	//����memcpy����
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
