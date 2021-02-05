#include<iostream>
using namespace std;

namespace _nmspl
{

	//一:new内存分配细节探秘
	//注意到，一块内存的回收，影响范围很广，远远不是10个字节，而是一大片。
	//跟配内存这个事    int* ppointint = new int(10);
			//绝不是简单的分配出去4个字节，而是在这4个字节周围，编译器做了很多处理，比如记录分配出去的字节数等等。
	//分配内存时，为了记录和管理分配出去的内存，额外多分配了不少内存，造成了浪费；尤其是频繁的申请小块内存是，造成的浪费更明显。



	//new，delete(malloc,free)内存没有看上去那么简单，他们的工作内部是很复杂的。


	void func()
	{
		//char* ppoint = new char[10];
		//memset(ppoint, 1, 10);
		//delete[] ppoint;

		int* ppointint = new int(10);
		delete ppointint;
	}
}

namespace _nmsp2
{

	//二:重载类中的operator new 和 operator delete操作符
	//A* pa = new A();
	//编译器视角
		//void* temp = operator new(sizeof(A));
		//A * pa = static_cast<A*>(temp);
		//pa->A::A()
	
	//delete pa;
	//编译器视角
		//pa->A::~A();
		//operator delete(pa);   
	class A {
	public:
		static void* operator new(size_t size);
		static void operator delete(void *phead);
		A() {
			int abc;
			abc = 10;
		}
		~A()
		{
			int abc;
			abc = 10;
		}
	};

	void* A::operator new(size_t size)
	{
		A* ppoint = (A*)malloc(size);
		return ppoint;
	}

	void A::operator delete(void* phead){
		free(phead);
	}
	void func()
	{
		A* pa = new A();
		delete pa;

		//A* pa = ::new A();  ::全局操作符  ，调用全局的new和delete
		//::delete pa;
	}
}

namespace _nmsp3 {
	//
	class A {
	public:
		static void* operator new[](size_t size);
		static void operator delete[](void* phead);
		A() {
			int abc;
			abc = 10;
		}
		~A()
		{
			int abc;
			abc = 10;
		}
	};

	void* A::operator new[](size_t size)
	{								//size是7个字节，是因为还有4个字节是记录的是 A* pa = new A[3]() 中的 3数组的大小
		A* ppoint = (A*)malloc(size);
		return ppoint;
	}

	void A::operator delete[](void* phead) {
		free(phead);
	}
	void func()
	{
		A* pa = new A[3]();   //构造和析构函数被调用3次，但是operator new[] 和operator delete[]仅仅被调用一次
		delete[] pa;
	}
}
int main()
{
	//_nmspl::func();
	//_nmsp2::func();
	_nmsp3::func();
	return 0;
}