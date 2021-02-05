#include<iostream>
#include<time.h>

using namespace std;
class Base
{
public:
	int ba;
	int bb;
	Base(int tmpa,int tmpb)
	{}
};

class CSub
{
public:
	CSub(int tmpv)
	{

	}
};

class A : public Base
{
public:
	int m_x;
	int m_y;
	int& m_yy;
	CSub cmysub;
	const int m_myc;
	A(int &tmpvalue) :m_x(0), m_y(0),m_yy(tmpvalue),m_myc(tmpvalue),Base(tmpvalue, tmpvalue)
						, cmysub(tmpvalue)
	{
		//m_yy = tmpvalue;    //这种复制将会是错误的
	}
};

class X {
public:
	int m_i;
	X(int value = 0) : m_i(value)  //类型转换构造函数
	{
		printf(" this = %p", this);
		cout << "X(int)构造函数被调用" << endl;
	}
	X(const X& tmpv)
	{
		printf(" this = %p", this);
		cout << "X拷贝构造函数被调用" << endl;
	}
	X& operator = (const X& tmp)
	{
		printf(" this = %p", this);
		cout << "X拷贝赋值运算符被调用" << endl;
		return *this;
	}
	~X()
	{
		printf(" this = %p", this);
		cout << "X析构函数被调用" << endl;
	}

};

class B {
public:
	X xobj;  //类类型对象
	int m_test;
	//构造函数
	//B(int tmpvalue) //这里构造了xobj,耗费了一次调用构造函数的机会
	//				//站在编译器角度
	//					//X xobj;
	//					//xobj.X::X()
	//{
	//	xobj = 1000;//这里构造一个临时对象，把临时对象调用拷贝赋值运算符把内容给了xobj,释放掉临时对象
	//						//  X tmpobj;  //生成一个临时对象
	//						//  tmpobj.X::X(1000);   //临时对象调用了构造函数
	//						//	xobj.X::operator=(tmpobj); //调用的是xobj的拷贝赋值运算符
	//						//  tmpobj.X::~X();   //调用析构函数回收临时对象

	//	m_test = 500;

	//}

	//用初始化列表代替上述方式，把初始化列表中的代码看成是函数体内代码的一部分； 
	int m_test1;
	int m_test2;
	B(int tmpvalue) :xobj(1000)//,m_test2(100),m_test(m_test1)  //这种写法是错误的。
		//站在编译器视角
		//X xobj;
		//xobj.X::X(1000)		
	{
		cout << "mtest = " << m_test << endl;
		cout << "mtest1 = " << m_test1 << endl;
		m_test = 500;
	}
};
int main() {
	//(1)何时必须用成员初始化列表
	//a)如果成员是个引用
	//int abc = 1;
	//A a(abc);

	//b)如果是个const类型成员
	//c)如果这个类是继承一个基类，并且基类中有构造函数，这个构造函数里边还有参数。
	//d)如果成员变量类型是某个类类型，而这个类的构造函数带参数时。

	//(2)使用初始化列表的优势
	//除了必须用初始化列表的场合，我们用初始化列表还有什么其他目的? 有，就是提高程序运行效率。
	//对于类类型成员变量 xobj 放到初始化列表中能够比较明显的看到效率的提升。
		//当时如果是个简单类型的成员变量 ，比如 int类型，放在初始化列表或者放在函数体里效率差别不大
	//提醒:成员变量初始化尽量放在初始化列表里，显得 高端，大气上档次
	//(3)初始化列表细节探究
	//说明：
		//(3.1)初始化列表中的代码可以看做是别编译器安插到构造函数体中的，只是这些代码有些特殊。
		//(3.2)这些代码是在任何用户自己的构造函数体代码之前执行的。
				//所以要区分构造函数中的  用户代码 和 编译器插入 的 初始化所属的代码
		//(3.3)这些列表中变量的初始化顺序是 定义顺序，而不是在初始化列表中的顺序。
			//不建议在初始化列表中进行两个成员都在初始化列表中出现的成员之间的初始化
	B myaobj(1000);
	return 0;
}