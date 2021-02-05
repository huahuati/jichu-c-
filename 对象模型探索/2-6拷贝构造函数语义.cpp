#include<iostream>
using namespace std;

class CTB {
public:
	//CTB(const CTB&) {
	//	cout << "CTB（）的拷贝构造函数执行了" << endl;
	//}
	//CTB() {}
	virtual void myirfun() {}
};

class CTBSon : public CTB
{
public:
	//virtual void myirfun() {}
};
class ASon
{
public:
	int m_testson;
};

class A {
public :
	int m_test;
	ASon asuobj;
	CTB m_ctb;
};

class Grand //爷爷类
{
public:
};
class A1 : virtual public Grand{
public:
};
class A2 : virtual public Grand
{
public:
};
class C : public A1, public A2
{
public:
};
int main(){
	//第六节  拷贝构造函数语义
	//传统上，大家认为:如果我们没有定义一个自己的拷贝构造函数，编译器会帮助我们合成一个拷贝构造函数
	//这个合成的拷贝构造函数，也是在必要的时候才会被编译器合成出来。  所以 "必要的时候"
	A myal;
	myal.m_test = 15;
	myal.asuobj.m_testson = 120;
	A mya2 = myal;   //调用拷贝构造函数。这个mya2.m_test = 15，这个其实是编译器内部的一个手法：
								//成员变量初始化手法，比如int这种简单类型，直接就按值就拷贝过去。
										//编译器不需要合成拷贝构造函数的情况下编译器直接帮我们直接搞定
	//a)A mya2 = myal; 是拷贝一个对象
	//b)自己没有写类A的拷贝构造函数，编译器也没有帮助我们生成拷贝构造函数
	//c)我们发现myal对象的一些成员变量确实被拷贝到Mya2中去。这是编译器内部的一些直接拷贝数据的实现手法，
			//比如类 A 中 有ASon 成员变量 asuobj,也会递归的去拷贝类ASon的每个成员变量

	//某些情况下，如果不写自己的拷贝构造函数，编译器就会帮助我们合成处拷贝构造函数来。
			//那编译器在什么情况下回帮组我们合成出拷贝构造函数来呢?编译器合成出来拷贝构造函数又要干什么事情呢?
		//(1)如果一个类 A 没有拷贝构造函数，但是含有一个类类型CTB的成员变量。该类型CTB含有拷贝构造函数
				//当代码中有涉及到 A 的拷贝构造时，编译器就会为类 A 合成一个拷贝构造函数
						//合成的拷贝构造函数去掉用 CTB 的拷贝构造函数

			//编译器合成的拷贝构造函数往往都是干一些特殊的事情。如果只是一些类成员变量值的拷贝拷贝这些事，
				//编译器是不用专门合成出拷贝构造函数来干的，编译器内部就干了；

		//(2)如果一个类CTBSon没有拷贝构造函数，但是它有一个父类CTB，父类有拷贝构造函数
			//当代码中有涉及到类 CTBSon 的拷贝构造时，编译器会为 CTBSon 和成一个拷贝构造函数

	CTBSon myctbson;
	CTBSon myctbson2 = myctbson;

		//(3)如果一个类 CTBSon 没有拷贝构造函数，但是该类声明了或者继承了虚函数
			//当代码中有涉及到类 CTBSon 的拷贝构造函数式，编译器会为 CTBSon 合成一个拷贝构造函数。往这个拷贝构造函数里插入语句:
				//这个语句的含义 是设定类对象myctbson2的虚函数表指针。虚函数表指针，虚函数表等概念，详细见第三章
		//(4)如果一个类没有拷贝构造函数，但是该类含有虚基类
			//当代码中有涉及到类的拷贝构造是，编译器会为该类合成一个拷贝构造函数

	C cc;
	C cc2 = cc;   //当代码中涉及到拷贝语义时。

		//(5)(6)其他情况未知，自行探索
	return 0;
}