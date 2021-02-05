#include<iostream>
using namespace std;

class Grand //爷爷类
{
public:
	int m_grand;
};

class A1 :virtual public Grand
{
public:
	int m_a1;
};
class A2 :virtual public Grand
{
public:
	int m_a2;
};
class C1 :public A1, public A2
{
public:
	int m_c1;
};
int main()
{
	//一：虚基类(虚继承/虚派生)问题的提出
	//传统多继承造成的：空间问题，效率问题，二义性问题；
	cout << sizeof(Grand) << endl;  //四字节
	cout << sizeof(A1) << endl;     //四字节
	cout << sizeof(A2) << endl;     //四字节
	cout << sizeof(C1) << endl;     //八字节

	//C1 c1; //Grant被继承了两次
	////c1.m_grand = 12;   //有二义性，访问不明确，名字冲突
	////c1.A1::m_grand = 12;
	////c1.A2::m_grand = 13;

	////以上是，不是虚继承的时候

	////虚基类，让Grand类只被继承一次
	//c1.m_grand = 12;   //引入虚基类之后，就不会出现访问不明确的问题
	//c1.A1::m_grand = 12;
	//c1.A2::m_grand = 13;

	cout << "以上代码Grand::m_grand存在才能运行" << endl;

	//二：虚基类初探Grand
	//两个概念：
		//(1)虚基类表 vbtable(virtual base table.)
		//(2)虚基类表指针 vbptr(virtual base talbe pointer)
	//空类sizeof(Grand) == 1好理解
	//virtual虚继承之后，A1,A2里就会被编译器插入一个虚基类表指针，这个指针，有点类似于成员变量的感觉
	//A1，A2里因为有了虚基类表指针，因此占用了4个字节

	A1 a1;
	A2 a2;
	//虚基类表指针，用来指向虚基类表(后续讲解)。


	return 0;
}