#include<iostream>

using namespace std;

class A {
public:
	int a;
	A() {
		cout << "A::A()的this指针是" << this << endl;
	}

	void funA() {
		cout << "A::funA()的this指针是" << this << endl;
	}
};

class B {
public:
	int b;
	B() {
		cout << "B::B()的this指针是" << this << endl;
	}
	void funB() {
		cout << "B::funcB()的this指针是" << this << endl;
	}
};

class C : public A, public B
{
public:
	int c;
	C() {
		cout << "C::C()的this指针是" << this << endl;
	}
	void funC() {
		cout << "C::funcC()的this指针是" << this << endl;
	}
};
int main() {

	//this指针调整:多重继承
	cout << sizeof(A) << endl;
	cout << sizeof(B) << endl;
	cout << sizeof(C) << endl;

	C myc;
	myc.funA();
	myc.funB();
	myc.funC();

	//派生类对象包含基类子对象的。
	//如果派生类只从一个基类继承的话，那么这个派生类对象的地址和基类对象的地址相同
	//如果派生类对象同时继承多个基类，那么：
		//第一个基类子对象的开始地址和派生类对象的开始地址相同
		//后续这些基类子对象的开始地址和派生类对象的开始地址相差多少呢?那就的吧前边那些基类对象所占用的内存空间干掉。

	//总结:调用那个子类的成员函数，这个this指针就会被编译器自动调整到对象内存布局中，对应该子类对象的起始地址那里去。
	return 0;
}