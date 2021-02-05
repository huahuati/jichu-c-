#include<iostream>
using namespace std;
class Base {
public:
	virtual void f() { cout << "Base::f()" << endl; }
	virtual void g() { cout << "Base::g()" << endl; }
	virtual void h() { cout << "Base::h()" << endl; }
	virtual ~Base() {}
};

class Base2
{
public:
	virtual void hBase2() {
		{ cout << "Base2::hBase2()" << endl; }
	}
	//~Base2()
	//{
	//	int ab;
	//	ab = 1;
	//}
	virtual ~Base2()
	{
		int ab;
		ab = 1;
	}
};

class Derive :public Base,public Base2 {
public:
	virtual void i() { cout << "Derive::i()" << endl; }
	virtual void g() { cout << "Base::g()" << endl; }
	void myselffunc(){} //只属于Derive的函数
	virtual ~Derive(){}
};
int main() {
	//一:多继承下的虚函数
	//多重继承复杂体现在后边这个类型上；
	Base2* pb2 = new Derive();
	//编译器视角
		//Derive* temp = new Derive();
		//Base2 *pb2 = (Base *)((char *)temp +sizeof(Base));
		//下面那行是错误的。
		//Base2* pb2 = temp + sizeof(Base);  //跳转的不是sizeof(Base)个字节，而是sizeof(Base) *sizeof(Base2)字节;
	delete pb2;  //，如果Base2无虚析构函数，会有异常

	//二：如何成功删除用第二基类指针new出来的继承对象
	//a)要删除的实际是整个Derive()对象
	//b)要能够保证Derive()对象的析构函数被正常调用
	//c)编译器会调用Base2()的析构函数，还是调用Derive的析构函数呢?
	//d)执行delete pb2是，系统的动做会是?
		//d.1)如果Base2里没有析构函数，编译器会直接删除以pb2开头的这段内存，一定报异常，因为这段内存压根就不是new其实的内存。
		//d.2)如果Base2里有一个析构函数，但整个析构函数是个普通析构函数（非虚析构函数）,那么当delete pb2
				//这个析构函数就被被系统调用，但是delete的仍旧是pb2开头这段内存，所以一定报异常。因为这段内存压根就不是new起始的内存
			//另一种解释：析构函数如果不是虚函数，编译器会实施静态绑定，静态绑定意味着delete Base2指针时，
				//删除的内存开始地址就是pb2的当前位置。
		//d.3)如果Base2里是一个虚析构函数
				//~Derice()
					//~Base2()
						//~Base()
		//d.4)Derive里就算没有虚析构函数，因为Base2里有虚析构函数，编译器也会为此给Derive生成虚析构函数，
				//为了调用~base2()和~Base()虚析构函数
	//e)范式涉及到继承的，所有类都要求写虚析构函数 ！！！！！！！！！！！！！！！！！！

	Base *pbm = new Base();
	Base2 *pb222 = new Base2();
	Derive* p11212 = new Derive();

	p11212->g();
	p11212->i(); //走虚函数表

	Derive dddd;
	dddd.i();//直接调用虚函数

	//Derive类的第二虚函数表中发现了thunk字样：
	//一般这个东西在多重继承中(从第二个虚函数表开始可能就会有);用于this指针调整。这个东西其实是一段代码，这段代码干两个事情
			//(1)调整this指针，调整到对象首地址
			//(2)调用Derive析构函数

	return 0;
}