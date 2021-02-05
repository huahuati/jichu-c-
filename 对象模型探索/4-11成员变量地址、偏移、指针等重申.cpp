#include<iostream>
using namespace std;

class MYACLA
{
public:
	int m_i;
	int m_j;
	int m_k;
};

void myfunc(int MYACLA::*mempoint, MYACLA& obj)
{
	obj.*mempoint = 260;  //注意写法
}
int main() {
	//一：对象成员变量内存地址及其指针
	MYACLA myobj;
	myobj.m_i = myobj.m_j = myobj.m_k = 0;
	printf("myobj.mi = %p\n", &myobj.m_i);   //对象的成员变量是由真正的内存地址的；
	cout << "分界线------" << endl;

	MYACLA* pmyobj = new MYACLA();
	printf("pmyobj->m_i = %p\n", &pmyobj->m_i);
	printf("pmyobj->m_j = %p\n", &pmyobj->m_j);
	printf("pmyobj->m_k = %p\n", &pmyobj->m_k);
	cout << "分界线------" << endl;

	int* p1 = &myobj.m_i;
	int* p2 = &pmyobj->m_j;

	*p1 = 15;
	*p2 = 30;

	cout << "分界线------" << endl;
	printf("p1地址=%p,p1值 = %d\n", p1,*p1);
	printf("p2地址=%p,p2值 = %d\n", p2,*p2);

	cout << "分界线------" << endl;
	//二：成员变量的偏移值及其指针(和具体对象是没有关系的)
	cout << "打印成员变量偏移值------------" << endl;
	printf("MYACLA::m_i偏移值 = %d\n", &MYACLA::m_i);   //打印偏移值，这里用的%d
	printf("MYACLA::m_j偏移值 = %d\n", &MYACLA::m_j);
	
	//用成员变量指针来打印偏移值也可以，看些法
	//成员变量里边保存的 实际上是个偏移值(不是个实际内存地址)
	int MYACLA::* mypoint = &MYACLA::m_j;
	printf("MYACLA::* mypoint偏移值 = %d\n", mypoint);
	mypoint = &MYACLA::m_i;   //注意，单独使用是直接用名字，定义时才需要加MYACLA
	printf("MYACLA::* mypoint偏移值 = %d\n", mypoint);

	//三：没有指向任何数据成员变量的指针
	//通过一个对象名或者对象指针后面跟成员变量指针来访问某个对象的成员变量
	myobj.m_i = 13;
	myobj.*mypoint = 22;
	pmyobj->*mypoint = 19;

	myfunc(mypoint, myobj);
	myfunc(mypoint, *pmyobj);

	cout << "sizeof(mypoint) =" <<sizeof(mypoint) << endl; //也是四个字节

	int* ptest = 0;
	int MYACLA::* mypoint2 = 0;  //成员变量指针
	//mypoint = 0;//成员变量指针
	//mypoint= NULL; //0xfffffff

	printf("mypoint2 = %d\n", mypoint2);
	//if(mypoint2 == mypoint)  //不成立
	int MYACLA::* mypint10 = &MYACLA::m_i;
	if (mypoint == mypint10)  //成立的
	{
		cout << "成立" << endl;
	}
	return 0;
}