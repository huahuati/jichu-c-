#include<iostream>

using namespace std;

class X {
public:
	int m_i;
	int* p_m1;
	X(const X& tmpx)
	{
		p_m1 = new int(100);//自己创建的内存
		memcpy(p_m1, tmpx.p_m1, sizeof(int)); //把目标对象的内存内容拷贝过来，叫深拷贝。
		m_i = tmpx.m_i;

		cout << "拷贝构造函数被调用" << endl;
	}
	X()//缺省构造函数
	{
		p_m1 = new int(100); 
		m_i = 0;
		cout << "构造函数被调用" << endl;
	}
	~X()
	{
		delete p_m1;
		cout << "析构函数被调用" << endl;
	}
	X(int value) :m_i(value) //类型转换构造函数
	{
		p_m1 = new int(100);
		cout << "X(int)构造函数调用" << endl;
	}
};
int main() {
	//第九节  程序优化续、拷贝构造续、深浅拷贝
	cout << "-------------begin-------------" << endl;
	X x10(1000);
	cout << "--------------" << endl;
	X xl1 = 1000;   //隐式类型转换
	cout << "--------------" << endl;
	X x12 = X(1000);
	cout << "--------------" << endl;
	X x13 = (X)1000;
	cout << "-------------end---------------" << endl;

	//从编译器视角(不优化)
	X x10;
	x10.X::X(1000);

	//后边三行
	X _tmp0; 
	_tmp0.X::X(1000); //带一个参数的构造函数被调用

	X x14;
	x14.X::X(_tmp0);   //拷贝构造函数被调用
	_tmp0.X::~X();   //调用析构函数。

	//总结:当编译器面临用一个类对象作为另外一个类对象初值的情况，各种编译器表现不同。但是所有编译器都为了提高效率而努力。
	//我们也没有办法确定我们自己使用的编译器是否一定会调用拷贝构造函数

	//拷贝构造函数是够必须有?  不一定，视情况而定。
	//如果只有一些简单的成员变量类型，int，double,根据就不需要拷贝构造函数；编译器背部本生就支持成员变量的
			//bitwise(按位) copy 按位拷贝

	X x0;
	x0.m_i = 150;
	
	X x1(x0);//有自己的拷贝构造函数编译器必然会调用
	cout << x1.m_i << endl;  //编译器支持bitwise拷贝，所以x1.m_1 = 150;

	//当需要处理很复杂的成员变量的时候。
	//假如我们增加了自己的拷贝构造函数，导致编译器本身的bitwise拷贝能力实效，所以结论:
		//假如你增加了自己的拷贝构造函数后，就要对每个成员变量的值的初始化负责了；
	//深浅拷贝问题；
	return 0;
}