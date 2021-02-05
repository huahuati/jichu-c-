#include<iostream>
using namespace std;

//父类
class Base
{
public:
	virtual void f() { cout << "Base::f()" << endl; }
	virtual void g() { cout << "Base::g()" << endl; }
	virtual void h() { cout << "Base::h()" << endl; }
};

class Derive :public Base
{
	virtual void g() { cout << "Dervie::g()" << endl; }
};

int main() {
	//继承关系作用下虚函数的手工调用
	
	cout << sizeof(Base) << endl;
	cout << sizeof(Derive) << endl;
	cout << "--------------------------" << endl;
	Derive* d = new Derive();   //派生类指针
	long* pvptr = (long*)d;    //指向对象的指针d转成了long *类型。
	long* vptr = (long*)(*pvptr);   //(*pvptr)表示pvptr指向的对象，也就是Derive本身。Derive对象是4字节的。代表的是虚函数表指针地址。

	for (int i = 0; i <= 4; i++)   //循环5次
		printf("vptr[%d] = 0x:%p\n", i, vptr[i]);

	cout << "--------------------------" << endl;
	typedef void(*Func)(void);   //定义一个函数指针类型
	Func f = (Func)vptr[0];   //f就是函数指针变量。vptr[0]是指向第一个虚函数的。
	Func g = (Func)vptr[1];
	Func h = (Func)vptr[2]; 
	Func i = (Func)vptr[3]; 
	Func j = (Func)vptr[4]; 

	f();
	g();
	h();
	//i(), j();//会报异常
	cout << "--------------------------" << endl;
	Base* dpar = new Base();
	long* pvptrpar = (long*)dpar;
	long* vptrpar = (long*)(*pvptrpar);

	for (int i = 0; i <= 4; i++)  //循环5次；
		printf("vptr[%d] = 0x:%p\n", i, vptr[i]);

	Func fpar = (Func)vptrpar[0];   //f就是函数指针变量。vptr[0]是指向第一个虚函数的。
	Func gpar = (Func)vptrpar[1];
	Func hpar = (Func)vptrpar[2];

	cout << "--------------------------" << endl;
	fpar();
	gpar();
	hpar();
	return 0;
}