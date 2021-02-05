#include<iostream>
using namespace std;
class Base {
public:
	virtual void f() { cout << "Base::f()" << endl; }
	virtual void g() { cout << "Base::g()" << endl; }
	virtual void h() { cout << "Base::h()" << endl; }
	virtual ~Base() {}
	virtual Base* clone() const
	{
		return new Base();
	}
};

class Base2
{
public:
	virtual void hBase2() {
		{ cout << "Base2::hBase2()" << endl; }
	}
	virtual ~Base2()
	{}
	virtual Base2* clone() const
	{
		return new Base2();
	}
};


class Derive :public Base,public Base2 {
public:
	virtual void i() { cout << "Derive::i()" << endl; }
	virtual void g() { cout << "Base::g()" << endl; }
	void myselffunc(){} //只属于Derive的函数
	virtual ~Derive(){}
	virtual Derive* clone() const
	{
		return new Derive();
	}
};

class BASE
{
public:
	virtual void f() {}
	virtual ~BASE() {}
	int M_BASEi;
};

class DERIVE : public virtual BASE
{
public:
	virtual ~DERIVE() {}
	int M_DERIVEI;
};
int main() {
	//一：多重继承第二基类对虚函数支持的影响(this指针调整作用)
	//子类继承几个父类，子类就有几个虚函数表

	//多重继承下，有几种情况，第二个或者后续的基类会对虚函数的支持产生影响
	//this指针调整，调整的目的是干什么?
	//this指针调整的目的就是让对象指针正确的指向对象首地址、从而能正确的调用对象的成员函数或者说正确的数据成员存储位置

	//a)通过指向第二个基类的指针调用继承类的虚函数；
	Base2* pb2 = new Derive();
	delete pb2;   //调用继承类的虚析构函数

	//b)一个指向派生类的指针，调用第二个基类中的虚函数
	Derive* pd3 = new Derive;
	pd3->hBase2();

	//c)允许虚函数的返回值类型有所变化
	Base2* pb1 = new Derive();  //pb1指向的是Base2字对象的首地址
	Base2* pb2 = pb1->clone(); //Derive::clone();
					//执行clone时，pb1首先会调整到回指向Derive对象的首地址，这样调用的是Derive版本的clone()
		
	//二：虚继承下的虚函数
	cout << sizeof(DERIVE) << endl;  //16字节
	DERIVE dobj;			//1-4虚基类表指针
	dobj.M_BASEi = 2;	   //13-16字节
	dobj.M_DERIVEI = 5;		//5-8字节

	DERIVE* pdobj = new DERIVE();
	pdobj->f();			//9-12字节虚函数表指针

	DERIVE* pderive = new DERIVE();
	BASE* pbase2 = (BASE*)pderive;
	pbase2->M_BASEi = 7;
	return 0;
}