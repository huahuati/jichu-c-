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
	//void f() { cout << "Base::f()" << endl; }
	//void g() { cout << "Base::g()" << endl; }
	//void h() { cout << "Base::h()" << endl; }
};

int main() {
	//继承关系作用下虚函数的手工调用

	cout << sizeof(Base) << endl;
	cout << sizeof(Derive) << endl;
	cout << "--------------------------" << endl;
	Derive* d = new Derive();
	Derive* d2 = new Derive();

	//(1)一个类只有包含虚函数才会存在虚函数表，同属于一个类的对象共享虚函数，但是有各自的vptr(虚函数表指针)，
			//当然所指向的指针地址(虚函数表首地址)相同。

	long* pvptr = (long*)d;
	long* vptr = (long*)(*pvptr);

	long* pvptr2 = (long*)d2;
	long* vptr2 = (long*)(*pvptr2);

	//(2)父类中有虚函数就等于子类中有虚函数。换句话来说，父类中有虚函数表，则子类中肯定有虚函数表。因为是继承父类的
				//如果子类中把父类的虚函数的virtual去掉，是不是这些函数就不再是虚函数了?
					//只要在父类中是虚函数，那么子类中即便不写virtual，也依旧是虚函数
		//不管是父类还是子类，都只会有一个虚函数表，不能认为子类中有一个虚函数表+父类中有一个虚函数表，
			//得到一个结论:子类中有两个虚函数表。（这个结论是错误的）

		//子类中是否可能会有多个虚函数表呢?后续解释
	//(3)如果子类中完全没有新的虚函数，则我们可以认为子类的虚函数表和父类的虚函数表内容相同。
		//但，仅仅是内容相同，这两个表在内存中存于不容位置，换句话来说，这是内容相同的两张表。
			//虚函数表中每一项，保存着一个虚函数的首地址，但如果子类的虚函数表项和父类的虚函数表项代表同一个函数
				//这表示子类没有覆盖父类的虚函数，则该表项所指向的该函数的地址应该相同。

	//(4)超出虚函数表部分内容不可知

	//(5)初始化赋值时，调用拷贝构造函数指向相同的虚函数表
	Derive derive;
	long* pvptrderive = (long*)(&derive);
	long* vptrderive = (long*)(*pvptrderive);

	Derive derive2;
	long* pvptrderive2 = (long*)(&derive2);
	long* vptrderive2 = (long*)(*pvptrderive2);

	Base base = derive;//直接用子类对象给父类对象值，子类中的属于父类那部分内容会被编译器自动区分(切割)出来
							//并拷贝给了父类对象。所以Base base = derive;实际上干了两个事情:
								//第一个事情:生成一个Base对象
								//第二个事情:用derive来初始化base对象值
							//这里编译器给我们做了一个选择，显然derive初始化base初始化base对象的时候，
								//derive的虚函数表指针值并没有覆盖base对象的虚函数表指针值。
	
	long* pvptrbase = (long*)(&base);
	long* vptrbase = (long*)(*pvptrbase);


	//oo(面向对象) 和OB(基于对象)概念:
	//c++通过类的指针和引用来支持多态，这是一种程序设计风格，这就是我们常说的面向对象。object-oriented model;
	//OB(object-based),也叫作ADT抽象数据模型[abstract datatype model]，不支持多态，执行速度更快，
		//因为函数调用的解析不需要运行时决定(没有多态),而是在编译期间就解析完成，内存空间紧凑程度上更紧凑，因为没有虚函数

	Base* pbase = new Derive();
	Base& base2 = derive2;
	//但是显然，OB的设计灵活性就差
	//c++既支持面向对象程序设计(继承，多态)(oo),也支持基于对象(OB)程序设计。
	return 0;
}