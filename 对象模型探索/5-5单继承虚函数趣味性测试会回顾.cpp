#include<iostream>
using namespace std;
class Base {
public:
	virtual void f() { cout << "Base::f()" << endl; }
	virtual void g() { cout << "Base::g()" << endl; }
	virtual void h() { cout << "Base::h()" << endl; }
};

class Derive :public Base {
public:
	virtual void i() { cout << "Derive::i()" << endl; }
	virtual void g() { cout << "Base::g()" << endl; }
	void myselffunc(){} //只属于Derive的函数
};
int main() {

	//一：单一继承下的虚函数
	//Derive myderive;
	//Derive* pmyderive = &myderive;
	//pmyderive->f();
	//pmyderive->g();
	//pmyderive->h();
	//pmyderive->i();


	Base* pb = new Derive(); //基类指针指向一个子类对象
	pb->g();
	//编译器视角
	//(*pb->vptr[1](pb));
	Derive myderive;
	Base& yb = myderive;  //基类引用一个子类对象
	yb.g();
	//我们唯一需要在执行期间知道的东西就是通过哪个虚函数表来调用虚函数(父类的还是子类)

	//二：回顾和一些小实验
	//虚函数地址:编译期间，写在了可执行文件中，编译器已经构建出来。
	//vptr编译期间产生。编译器在构造函数中插入了给vptr赋值的代码。当创建对象时，因为要执行对象的构造函数，此时vptr就被赋值。

	Derive a1;
	Derive a2;
	Derive* pa3 = new Derive();   //虚函数表地址相同

	Base b1;
	return 0;
}