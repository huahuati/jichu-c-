#include<iostream>

using namespace std;

class X {
public:
	int m_i;
	X(const X& temp)
	{
		m_i = temp.m_i;
		cout << "拷贝构造函数被调用" << endl;
	}
	X()
	{
		m_i = 0;
		cout << "构造函数被调用" << endl;
	}
	~X() {
		cout << "析构函数被调用" << endl;
	}
	void functest() {
		cout << "FUNCTEST()被调用" << endl;
	}
};

void func(X tmpx) {

	return;
}

//老编译器看func
//void func(x& tmpx)
//{
//	return;
//}

X func1() 
{
	X x0;
	//...
	return x0;
}

//编译器角度的func
void func1(X& extra)
{
	X x0;  //从编译器角度，这行不调用x的构造函数；
	extra.X::X(x0);
	return;
}
int main() {
	//第七节  程序转化语义
	//写的代码，编译器会对代码进行拆分，拆分成编译器更容易理解和实现的代码。
	//看看编译器是如何解析这些代码的。
	//站在程序员角度/站在编译器角度
	//程序员看代码视角 和 编译器看代码视角之间不断切换

	//(1)定义时初始化对象(程序员视角)
	X x0;
	x0.m_i = 15;
	X x1 = x0;	//定义的时候初始化
	X x2(x0);
	X x3 = (x0);

	//切换到编译器角度，编译器会拆分成两个步骤(编译器视角)
	X x3;				//步骤一:定义一个对象，为对象分配内存。从编译器视角来看，这句是不调用X类的构造函数的。
	x3.X::X(x0);		//步骤二:直接调用对象的拷贝构造函数去了。 //对应上述  X x3 = (x0); 的操作


	//(2)参数的初始化(程序员视角/现代编译器)
	X x4;
	func(x4);

	//老编译器视觉
	X tmpobj;  //编译器产生一个临时对象
	tmpobj.X::X(x4);   //调用拷贝构造函数
	func(tmpobj);    //用临时对象
	tmpobj.X::~X(); // func()被调用完成后，本析构被调用

	//(3)返回值初始化(程序员角度)
	X my = func1();
	int abc;
	abc = 0;

	//编译器对上述代码的理解
	X my;  //不会调用X 的构造函数
	func(my);

	//程序员视角
	func1().functest();

	//编译器视角
	X my;  //不会调用 X 的构造函数
	(func1(my), my).functest();//逗号表达式:先计算表达式1，再计算表达式2，整个逗号表达式的结果是表达式2的值。

	//程序员视角
	X(*pf)();   //定义一个函数指针，返回一个X类类型
	pf = func1;
	pf().functest;

	//编译器视角
	X my;  //不调用构造函数
	void (*pf)(X&);
	pf = func1;
	pf(my);
	my.functest();
	return 0;
}
