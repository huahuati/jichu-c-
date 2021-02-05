#include<iostream>
using namespace std;

class FAC //父类
{
public:
	int m_fai;
	int m_faj;
};

class MYACLS : public FAC //子类
{
public:
	int m_i;
	int m_j;
};

class Base   //sizeof = 八字节
{
public:
	int m_il;
	char m_c1;
	char m_c2;
	char m_c3;
};

class Base1 {
public:
	int m_li;
	char m_c1;
};
class Base2 :public Base1
{
public:
	char m_c2;
};

class Base3 :public Base2
{
public:
	char m_c3;
};

int main() {
	//第五节  单一继承下的数据成员布局
	printf("FAC::m_fai = %p\n", &FAC::m_fai);
	printf("FAC::m_faj = %p\n", &FAC::m_faj);

	cout << "分界线----------" << endl;

	printf("MYACLS::m_faj = %p\n", &MYACLS::m_faj);
	printf("MYACLS::m_faj = %p\n", &MYACLS::m_faj);

	cout << "分界线----------" << endl;

	printf("MYACLS::m_i = %p\n", &MYACLS::m_i);
	printf("MYACLS::m_j = %p\n", &MYACLS::m_j);

	//(1)一个子类对象，所包含的内容，是它自己的成员，加上他父类的成员的总和
	//(2)从偏移值看，父类成员先出现，然后才是孩子类成员。

	FAC myobj;
	MYACLS mycalobj;   //子类对象中包含父类子对象

	cout << "分界线------Base" << endl;
	cout << sizeof(Base) << endl;   //八个字节
	printf("Base::m_il = %p\n", &Base::m_il);
	printf("Base::m_c1 = %p\n", &Base::m_c1);
	printf("Base::m_c2 = %p\n", &Base::m_c2);
	printf("Base::m_c3 = %p\n", &Base::m_c3);

	cout << "分界线------Base1" << endl;
	cout << sizeof(Base1) << endl;  //八字节

	cout << "分界线------Base2" << endl;
	cout << sizeof(Base2) << endl;//十二字节

	cout << "分界线------Base3" << endl;
	cout << sizeof(Base3) << endl;//十六字节
	printf("Base3::m_il = %p\n", &Base3::m_li);
	printf("Base3::m_c1 = %p\n", &Base3::m_c1);
	printf("Base3::m_c2 = %p\n", &Base3::m_c2);
	printf("Base3::m_c3 = %p\n", &Base3::m_c3);

	//liunx和windows上数据布局不一样，说明：
	//a)编译器在不断的进步和用优化；
	//b)不同厂商编译器，实现细节也不一样；
	//c)内存拷贝就要谨慎

	//就不能用memcpy内存拷贝把base2内存字节往base3里面拷贝，尤其是在linux里面
	return 0;
}