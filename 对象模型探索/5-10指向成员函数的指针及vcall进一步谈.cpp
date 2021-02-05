#include<iostream>
using namespace std;

namespace _nmsp1

{
	//一：指向成员函数的指针
	//成员函数地址、编译时就确定好的。但是，调用成员函数是需要通过对象来调用的。
	//但是常规(非静态)成员函数，要想调用，都需要一个对象来调用它；

	class A {

	public:
		void myfunc1(int tempvalue1)
		{
			cout << "tempvalue1 = " << tempvalue1 << endl;
		}
		void myfunc2(int tempvalue2)
		{
			cout << "tempvalue2 = " << tempvalue2 << endl;
		}

		static void mysfunc(int tempvalue)
		{
			cout << "A::mysfunc()静态成员函数--tempvalue = " << tempvalue << endl;
		}
	};
	void func()
	{
		A mya;
		void (A:: * pmypoint)(int tempvalue) = &A::myfunc1;   //定义一个成员函数指针并给初值；
		pmypoint = &A::myfunc2;   //给成员函数指针赋值

		(mya.*pmypoint)(15);    //通过成员函数指针来调用成员函数，必须通过对象的介入才能调用

		A* pmya = new A();
		(pmya->*pmypoint)(20);   //用对象指针介入来使用成员函数指针，来调用成员函数

		//编译器视角
		//pmypoint(&mya,15);
		//pmypoint(pmya,15);   //&mya和pmya是传递给this指针的。
		void(* pmyspoint)(int tempvalue) = &A::mysfunc;  //一个普通函数指针，而不是成员函数指针
		pmyspoint(80);

		//通过成员函数指针对常规的成员函数的成本，和通过普通的函数指针来调用静态成员函数，成本上差不多

	}
}

namespace _nmsp2
{
	//二：指向虚成员函数的指针及vcall进一步谈
	//vcall（vcall trunk） = virtual call : 虚调用
	//它代表一段要执行的代码的地址，这段代码能引导我们区执行正确的虚函数；
	//或者我们直接把vcall看成虚函数表，如果这么看待的话，那么vcall{0}代表的就是虚函数表里的第一个函数；
		//vcall{4}就代表虚函数表里的第二个虚函数  

	//完善理解:&A::myvirfunc: 打印出来的是一个地址，这个地址中有一段代码，这个代码中记录的是该虚函数表中的一个偏移值
		//有了这个偏移值，再有了具体的对象指针，就能够知道调用的是哪个虚函数表里边的哪个虚函数了；


	//成员函数指针里，保存的可能是一个vcall(vcall trunk)地址(虚函数),要么也可能是一个真正的成员函数地址；
	//如果是一个vcall地址，那vcall就能引导编译器找出正确的虚函数表中的虚函数地址进行调用。


	class A {

	public:
		void myfunc1(int tempvalue1)
		{
			cout << "tempvalue1 = " << tempvalue1 << endl;
		}
		void myfunc2(int tempvalue2)
		{
			cout << "tempvalue2 = " << tempvalue2 << endl;
		}

		static void mysfunc(int tempvalue)
		{
			cout << "A::mysfunc()静态成员函数--tempvalue = " << tempvalue << endl;
		}
		virtual void myvirfuncPrev(int tempvalue)
		{
			cout << "A::myvirfuncPrev()虚成员函数--tempvalue = " << tempvalue << endl;
		}
		virtual void myvirfunc(int tempvalue)
		{
			cout << "A::myvirfunc()虚成员函数--tempvalue = " << tempvalue << endl;
		}

		~A()
		{}
	};


	void func()
	{
		void (A:: * pmyvirfunc)(int tempvalue) = &A::myvirfunc;   //成员函数指针

		A* pvaobj = new A;
		pvaobj->myvirfunc(190);
		(pvaobj->*pmyvirfunc)(190);  //也是通过虚函数表调用
		printf("%p\n", &A::myvirfunc);
		
		pmyvirfunc = &A::myfunc2;
		(pvaobj->*pmyvirfunc)(33);

		delete pvaobj;

	}
}

namespace _nmsp3
{
	//三:vcall在继承关系中的体现
	class A {

	public:
		virtual void myvirfunc(int tempvalue)
		{
			cout << "A::myvirfunc()虚成员函数--tempvalue = " << tempvalue << endl;
		}

		~A()
		{}
	};

	class B : public A
	{
	public:
		virtual void myvirfunc(int tempvalue)
		{
			cout << "B::myvirfunc()虚成员函数--tempvalue = " << tempvalue << endl;
		}
		virtual ~B(){}
	};
	void func()
	{
		B* pmyb = new B();   //pmy：对象指针
		void (B:: * pmyvirfunc)(int tempvalue) = &A::myvirfunc;  //成员函数指针 //记录的是偏移值
		(pmyb->*pmyvirfunc)(190);
	
		printf("%p\n", &A::myvirfunc);  //vcall地址 和下个vcall地址不一样
		printf("%p\n", &B::myvirfunc); 
	}
}
int main()
{
	//_nmsp1::func();
	//_nmsp2::func();
	_nmsp3::func();

	return 0;
}