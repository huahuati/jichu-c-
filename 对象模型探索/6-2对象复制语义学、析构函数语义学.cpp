#include<iostream>

using namespace std;

namespace _nmspl
{
	//一：对象默认复制行为
	//如果不写自己的拷贝构造函数和拷贝赋值运算符，编译器也会有默认的对象拷贝和对象复制行为。

	//二：拷贝赋值运算符，拷贝构造函数
	//当我们提供自己的拷贝赋值运算符和拷贝构造函数式，就接管了系统默认的拷贝行为，此时。
		//我们就有责任在拷贝赋值运算符和拷贝构造函数中写适当的代码，来完成对象的拷贝或者赋值的任务。
	
	//三:如何禁止对象的拷贝构造和赋值：把拷贝构造函数和拷贝赋值运算符私有起来，只是声明，不需要写函数体。


	class A
	{
	public:
		int m_i, m_j;
		A& operator = (const A& tmp)   //拷贝赋值运算符
		{
			m_i = tmp.m_i;
			m_j = tmp.m_j;
			return *this;
		}
		A(const A& tmp)   //拷贝构造函数
		{
			m_i = tmp.m_i;
			m_j = tmp.m_j;
		}
		A(){}   //缺省构造函数，有拷贝构造函数就要有缺省构造函数

	//private:
	//	A& operator = (const A& tmp);
	//	A(const A& tmp);
		//以上之后就不能拷贝和赋值了。
	};
	void func()
	{
		A aobj;
		aobj.m_i = 15;
		aobj.m_j = 20;

		A aobj2 = aobj;   //执行拷贝构造函数(如果你写了拷贝构造函数)

		A aobj3;
		aobj3.m_i = 13;
		aobj3.m_j = 16;
		aobj2 = aobj3;  //执行拷贝赋值运算符（如果写了拷贝赋值运算符)
	}
}
namespace _nmsp2
{
	//四：析构函数语义
	//(4.1)析构函数被合成
	//什么情况下编译器会给我们生成一个析构函数?
	//a)如果继承一个基类，基类中带析构函数，那么编译器就会合成出一个析构函数来调用基类中的析构函数。
	//b)如果类成员是一个类类型成员，并且这个成员带析构函数，编译器也会合成出一个析构函数，这个析构函数
		//这个析构函数存在的意义是要调用类类型对象的析构函数

	//(4.2)析构函数被扩展
	//如果我们有自己的析构函数，那么编译器就会在适当的情况下会扩展析构函数代码:
	//a)如果类成员是一个类类型成员，并且这个成员带析构函数，编译器扩展类的析构函数代码。
		//先执行本类的析构函数代码，然后在执行 类 中的类对象的析构函数代码。
	//b)如果继承一个基类，基类中带析构函数，那么编译器就会扩展析构函数代码来调用基类中的析构函数。
		//先执行子类的析构函数代码，然后在执行父类析构函数代码。

	//虚基类：虚基类会带来更多的复杂性，也会对程序执行效率有一定的影响。
	class JI
	{
	public:
		virtual ~JI()
		{
			cout << "JI::~JI()" << endl;
		}
	};
	class A//:public JI
	{
	public:
		JI m_j;  //类类型成员变量
		virtual ~A()
		{
			cout << "A::~A()" << endl;
		}
	};
	void func()
	{
		A aobj;
	}
}
int main() {

	//_nmspl::func();
	_nmsp2::func();
}