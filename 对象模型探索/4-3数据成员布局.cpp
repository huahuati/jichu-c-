#include<iostream>
using namespace std;
#define GET(A,m)(int)(&((A*)0)->m)  //这个宏也可以得到偏移值
//定义一个类
#pragma pack(1)  //对齐方式设置为1字节对齐(不对齐)
class MYACLA
{
public:
	int m_i;
	static int m_si;  //声明不是定义
	int m_j;
	static int m_sj;
	int m_k;
	static int m_sk;

	char m_c;   //1字节
	int m_n;    //4字节
private:
	int m_pria;
	int m_prib;

public:
	void printMenPoint()
	{
		cout << "打印成员变量偏移值-------" << endl;
		printf("MYACLA::m_i = %d\n", &MYACLA::m_i);
		printf("MYACLA::m_j = %d\n", &MYACLA::m_j);
		printf("MYACLA::m_k = %d\n", &MYACLA::m_k);
		printf("MYACLA::m_c = %d\n", &MYACLA::m_c);
		printf("MYACLA::m_n = %d\n", &MYACLA::m_n);
		printf("MYACLA::m_pria = %d\n", &MYACLA::m_pria);
		printf("MYACLA::m_prib = %d\n", &MYACLA::m_prib);
	}
	virtual void func(){}  //虚函数在类对象内存的首位置
};
#pragma pack()  //取消指定对齐，恢复缺省对齐;
int MYACLA::m_sj = 0;   //这才是定义

int main() {

	//一：观察成员变量地址规律
	MYACLA myobj;
	cout << sizeof(myobj) << endl;

	//普通成员变量的存储顺序，是按照在类中定义顺序从上到下来的；
	//比较晚出现的成员变量在内存中有更高的地址
	//类定义中public,private,protected的数量，不影响类对象的sizeof
	myobj.m_i = 2;
	myobj.m_k = 8;
	myobj.m_j = 5;

	printf("myobj.m_i = %p\n", &myobj.m_i);
	printf("myobj.m_j = %p\n", &myobj.m_j);
	printf("myobj.m_k = %p\n", &myobj.m_k);

	cout << "分界线---------------分界线" << endl;

	MYACLA* pmyobj = new MYACLA();
	printf("pmyobj->m_i = %p\n", &pmyobj->m_i);
	printf("pmyobj->m_j = %p\n", &pmyobj->m_j);
	printf("pmyobj->m_k = %p\n", &pmyobj->m_k);


	//二：边界调整，字节对齐
	//某些因数会导致成员变量之间排列不连续，就是边界调整(字节对齐),调整的目的是提高效率，编译器自动调整。
				//调整:往成员之间填补一些字节，使用类对象的sizeof字节数凑成一个4的整数倍，8的整数倍。
	//因为统一字节对齐问题，引入一个概念叫一字节对齐(不对齐)
			//#pragma pack(1)
			//#pragma pack()
	//有虚函数时，编译器往往定义类中添加vptr虚函数表指针：内部的数据成员

	cout << "分界线---------------分界线" << endl;
	printf("myobj.m_i = %p\n", &myobj.m_i);
	printf("myobj.m_j = %p\n", &myobj.m_j);
	printf("myobj.m_k = %p\n", &myobj.m_k);
	printf("myobj.m_c = %p\n", &myobj.m_c);
	printf("myobj.m_n = %p\n", &myobj.m_n);

	//三：成员变量偏移值的打印
	//成员变量偏移值，就是这个成员变量的地址，离对象首地址偏移是多少。
	pmyobj->printMenPoint();

	cout << "打印成员变量偏移值--------" << endl;
	cout << GET(MYACLA, m_j) << endl;

	//成员变量指针
	int MYACLA::* mypoint = &MYACLA::m_n;
	printf("mypoint->m_n偏移值 = %d\n", mypoint);
	return 0;
}