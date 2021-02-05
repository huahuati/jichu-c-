#include<iostream>
using namespace std;

class FAC
{
public:
	int m_fai;
	int m_faj;
};

class MYACLS : public FAC 
{
public:
	int m_i;
	static int m_si;   //声明不是定义
	int m_j;

	void myfunc()
	{
		m_i = 5;
		m_j = 6;
	}
};

int MYACLS::m_si = 0;   //这个是定义

int main() {

	//一：静态成员变量的存取
	//静态成员变量，可以当做一全局量，但是他只在类的空间内可见；引用时 类名::静态成员变量名
	//静态成员变量只有一个实体，保存在可执行文件的数据段。

	MYACLS myobj;
	MYACLS* pmyobj = new MYACLS();

	cout << MYACLS::m_si << endl;
	cout << myobj.m_si << endl;
	cout << pmyobj->m_si << endl;

	MYACLS::m_si = 1;
	myobj.m_si = 2;
	pmyobj->m_si = 3;
	

	//普通成员变量
	printf("myobj.m_i = %p\n", &myobj.m_i);
	printf("pmyobj->m_i = %p\n", &pmyobj->m_i);

	//静态成员变量，内存在可执行文件中。
	printf("MYACLS::m_si = %p\n", &MYACLS::m_si);
	printf("myobj.m_si = %p\n", &myobj.m_si);
	printf("pmyobj->m_si = %p\n", &pmyobj->m_si);

	//二：非静态成员变量的存取(普通的成员变量)，存放在类的对象中。存取通过类对象(类对象指针)
	cout << "分界线-------" << endl;
	pmyobj->myfunc();
	//编译器角度:MYACLS::myfunc(pmyobj)
	//MYACLS::myfunc(MYACLS *const this)
	//{
			//this->m_i = 5;
			//this->m-j = 6;
	//}
	//对于普通成员变量的访问，编译器是把类对象的首地址加上成员变量的偏移值
	//&myobj + 4 = &myobj.m_j;
	cout << "分界线-------" << endl;
	printf("MYACLS::m_fai = %p\n", &MYACLS::m_fai); //如果有父类，父类中的成员的偏移值最低
	printf("MYACLS::m_faj = %p\n", &MYACLS::m_faj);
	printf("MYACLS::m_i = %p\n", &MYACLS::m_i);
	printf("MYACLS::m_j = %p\n", &MYACLS::m_j);

	//虚基类的访问方式不同，后续讲解
	return 0;
}