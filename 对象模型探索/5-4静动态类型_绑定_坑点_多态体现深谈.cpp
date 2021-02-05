#include<iostream>
using namespace std;

class Base
{
public:
	void myfunc()  //普通函数
	{
		cout << "Base::myfunc()" << endl;
	}
	virtual void myvirfunc(int value = 1)
	{

		cout << "Base::myvirfunc(),value = " <<  value << endl;
	}
};
class Derive :public Base
{
public:
	void myfunc() //普通成员函数
	{
		cout << "Derive::myfunc()" << endl;
	}
	virtual void myvirfunc(int value = 2)
	{
		cout << "Derive::myvirfunc(),value = " << value << endl;
	}
};
class Derive2 :public Base {
public:
};

class A
{
public :
	virtual void myvirfunc()
	{

	}
};
int main() {
	//一：静态类型和动态类型
	//静态类型：对象定义时的类型，编译期间就确定好的东西
	//Base base;  //base的静太类型是Base;
	//Derive derive;   //derive的静态类型是Derive，没有动态类型，因为既不是指针也不是引用
	//Base* pbase;   //pbase的静态类型依旧是Base *  ，至少目前没有动态类型，因为它没有指向任何对象
	//Base* pbase2 = new Derive();  //pbase2的静态类型依旧是Base * ，动态类型是Derive
	//Base* pbase3 = new Derive2();  //pbase3的静态类型依旧是Base * , 动态类型是Derive2

	//动态类型：对象目前所指向的类型(运行的时候才决定的类型)；一般只有指针或者引用才有动态类型的说法。
			//而且一般都是父类的指针或者引用
	//另外，动态类型在执行过程中可以改变：比如
	//pbase = pbase2;   //pbase的动态类型Derive
	//pbase = pbase3;  //pbase的动态类型改变为Derive2;

	//二：静态绑定和动态绑定
	//静态绑定：绑定的是静态类型，所对应的函数或者属性依赖于对象的静态类型，发生在编译期间
	//动态绑定：绑定的是动态类型，所对象的函数或者属性依赖于对象的动态类型，发生在运行期；
	//a)普通成员函数式静态绑定，而虚函数是动态绑定
	//b)缺省参数一般是静态绑定
	
	//三：继承的非虚函数坑
	Derive derive;
	Derive* pderive = &derive;
	pderive->myfunc();

	Base* pbase = &derive;
	pbase->myfunc();
	//由结果得出结论:普通成员函数是静态绑定，话句话说,myfunc()是普通成员函数。这里到底调用父类的myfunc还是子类的myfunc取决于调用者的静态类型
	//因为这里pbase的静态类型是Base，所以调用的是Base里的myfunc();pderive的静态类型是Derive *,所以调用的是Derive的myfunc();

	//结论：不应该在子类中重新定义一继承来的非虚函数。

	//四：虚函数的动态绑定
	cout << "分界线-------" << endl;
	Base base;
	pderive->myvirfunc();  //执行Derive的myvirtual()------>Derive::myvirfunc();
	pbase->myvirfunc();   //pbase动态类型是Derive，而虚函数是动态绑定，参照的是它的动态类型；   --- Derive::myvirfunc()
							//缺省value参数打印出来的居然是1：
						 //pderive的动态类型是Derive,所以调用的是Derive的myvirtual();"Derive::myvirfunc(),value = " value = 1
						//这就始于函数参数缺省值的静态绑定,所以缺省参数绑定到了父类函数的缺省参数上去了
	pbase = &base;
	pbase->myvirfunc();  //-----Base::myvirfunc();
	//虚函数是动态绑定;换句话说，myvirtual()是虚函数，这里到底执行那个myvirtual()取决于调用者的动态类型。
			//这里pbase的动态分别Derive，Base，所以调用的也分别是Derive和Base的myvirtual(),
				//pderive的动态类型是Derive,所以调用的是Derive的myvirtual();

	//五:重新定义虚函数的缺省参数坑
	//不要重新定义虚函数的缺省参数值

	//六:c++中的多态性的体现
	//c++ 中“多态性”
	//多态性这个概念，分两方面谈:
	//a)从代码实现上
	//b)从表现形式上
	//有一个观点是肯定的:有多态，必须是存在虚函数，没有虚函数，就没有多态，有虚函数并且不需调用。

	//(1)从代码实现上
	//当我们调用一个虚函数是，通过走的是不是通过查询虚函数表来找到虚函数入口地址，去执行虚函数。如果走的是这个途径，那么就是多态
			//如果不走这个途径，他就不是多态

	A* pa = new A();
	pa->myvirfunc();   //是多态

	A a;
	a.myvirfunc();  //不是多态

	A* pa = &a;
	pa->myvirfunc();    //这个也是多态

	//b)从表现形式上(通过代码来体现)
	//(1)有继承关系，有父类有子类，父类中必须有虚函数(这意味着子类中一定会有虚函数)，子类重写父类的虚函数；
	//(2)父类指针或者引用指向子类对象
	//(3)当以父类指针或者 引用调用子类中重写了的虚函数时，我们就能看出来多态的表现了，因为调用的是子类的虚函数；
	Base& yinbase = derive;
	yinbase.myvirfunc(); //"Derive::myvirfunc(),value = " 1
	return 0;
}