#include<iostream>
using namespace std;

namespace _namel
{
	class A
	{
	public:
		int m_i;   //成员变量
		A(){}
		virtual void func() {}
		~A() {}
	};
	void func()
	{
		//从new 说起
		//(1.1)new类对象时加不加括号的差别
		//(1.1.1)如果是个空类，那么如下两种写法没什么区别，视线中，不可能光写一个空类
		//(1.1.2)类A中有成员变量则:
				//带括号的初始化会把一些和成员变量有关的内存清0，但不是整个对象的内存全部清0；
						//有虚函数的时候，虚函数指针不会被清零
		//(1.1.3)//当类A有构造函数，下面两种写法得到的结果一样了。
		
		//(2.2)new干了啥
		//new 可以叫关键字/ 操作符
		//new干了两个事情:一个是调用operator new ，一个是调用了类A的构造函数
		A* pa = new A();
			//以上A* pa = new A();的分解;
				//operator new ();  //函数
					//_malloc();  c语言中的malloc
						//A::A();  //有构造函数就调用

		delete pa;
			//以上delete pa 的分解
		//A::~A()  析构函数
			//operator delete() 函数
				//free();  c语言中的free()函数

		//(2.3)malloc干了啥
		//很复杂的，别搞这个啦
		A* pa2 = new A;

		int* p3 = new int;   //初值随机
		int* p4 = new int(); //初值为零
		int* p5 = new int(100);	//初值100
		
		//

		int abc;
		abc = 6;

	}
}
int main()
{
	_namel::func();
	return 0;
}