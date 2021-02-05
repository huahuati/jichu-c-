#include<iostream>
using namespace std;

namespace _nmspl
{
	//一：对象的构造顺序
	//	A()
	//		B()
	//			C()
	//二：虚函数的继续观察
	//虚函数指针的赋值过程
	//	vptr = A::vftable
	//		vptr = B::vftable
	//			vptr = C::vftable
	//	由此可以得出，对象C的vptr指针是在不断地被擦写，最后赋值为 C::vftable虚函数表的首地址
	//千万不要在构造函数中，使用诸如memcpy或者直接操作等手段，来修改虚函数表指针的值，否则，调用虚函数时就可能造成系统奔溃。	

	//三：构造函数中虚函数的调用
	//某个类的构造函数 中 调用一个虚函数，那么走的不是虚函数表。而是直接调用
	class A
	{
	public:
		A()
		{
			printf("A this = %p\n", this);
			cout << "A::A()" << endl;
		}
		virtual ~A() {}
		virtual void myvirtual() {}
		virtual void myvirtua2() {}
	};
	class B : public A
	{
	public:
		B()
		{
			printf("B this = %p\n", this);
			cout << "B::B()" << endl;
		}
		virtual ~B() {}
		virtual void myvirtual() {}
		virtual void myvirtua2() {}
	};
	class C : public B
	{
	public:
		C():m_c(11)
		{
			myvirtual();   //构造函数中，直接调用虚函数，不会走虚函数表(静态调用方式)
			printf("C this = %p\n", this);
			cout << "C::C()" << endl;
		}
		virtual ~C() {}
		virtual void myvirtual() { myvirtua2(); //这个走虚函数表
								  }
		virtual void myvirtua2() {}
		int m_c;
	};

	void func()
	{
		C cobj;
		C* myobj = new C();
		myobj->myvirtual();  //代码实现上的多态，
	}
}

int main()
{
	_nmspl::func();
	return 0;
}