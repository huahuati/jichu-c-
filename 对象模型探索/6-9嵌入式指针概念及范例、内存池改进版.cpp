#include<iostream>
using namespace std;

namespace _nmpsl
{
	//一:嵌入式指针
	//(1.1)
	//一般引用在内存池相关的代码中；  成功使用嵌入式指针有个前提条件:类A对象的sizeof必须不小于4字节
	//嵌入式指针工作原理:借用A对象所占用的内存空间中的前4个字节，用这4个字节来链住这些空闲的内存块。
		//但是一旦某一个块被分配出去，那么这个块的前4个字节就不在需要，此时这4个字节可以被正常使用
	//(1.2)嵌入式指针演示代码
	//sizeof()超过4字节的类就可以安全的使用嵌入式指针。
	class TestEp
	{
	public:
		int m_i;
		int m_j;
	public:
		struct obj  //结构体,在类里面和类外面都是一样的
		{
			//成员，是个指针
			struct obj* next;   //这个next就是个嵌入式指针
						//自己是一个obj结构对象，那么把自己这个对象的next指针指向另外一个obj结构对象，最终
								//把多个自己这种类型的对象通过链串起来；
		};
	};
	void func()
	{
		TestEp mytset;
		cout << sizeof(mytset) << endl;  //8
		TestEp::obj *ptemp;   //定义一个指针
		ptemp = (TestEp::obj *) & mytset;  //把对象mytest首地址给了这个指针ptemp,这个指针ptemp指向对象mytest首地址；
		cout << sizeof(ptemp->next) << endl;  //4
		cout << sizeof(TestEp::obj) << endl;  //4
		ptemp->next = nullptr;       //ptmep->next 与ptemp指向的内存相同
	}

}
namespace _nmps2
{

	//二：内存池代码的改进
	//单独的为内存池技术来写一个类

	class myallocator
	{
	public:
		//分配内存接口
		void* allocate(size_t size)
		{
			obj* tmplink;
			if (m_FreePosi == nullptr)
			{
				//为空，要申请内存，要申请一大块内存
				size_t realsize = m_sTrunkCout * size;   //申请m_sTrunkCout这么多倍的内存
				m_FreePosi = (obj*)malloc(realsize);
				tmplink = m_FreePosi;

				//把分配出来的这一大块内存(5小块)，彼此用链链起来，供后续使用
				for (int i = 0; i < m_sTrunkCout - 1; ++i) // 0--3
				{
					tmplink->next = (obj*)((char*)tmplink + size);
					tmplink = tmplink->next;
				}//end for
				tmplink->next = nullptr;
			}//end if
			tmplink = m_FreePosi;
			m_FreePosi = m_FreePosi->next;
			return tmplink;
		}

		void deallocate(void* phead)
		{
			((obj*)phead)->next = m_FreePosi;
			m_FreePosi = (obj*)phead;
		}
	private:
		//写在类内的结构，这样之让其在类内使用
		struct obj
		{
			struct obj* next; // 这个next就是个嵌入式指针
		};
		int m_sTrunkCout = 5; //一次分配5倍该类内存作为内存池子的大小
		obj* m_FreePosi = nullptr;
	};



	class A
	{
	public:
		int m_i;
		int m_j;   //为了保证sizeof(A)凑够四字节；
	public:
		static myallocator myalloc;   //静态成员变量
		static void* operator new(size_t size)
		{
			return myalloc.allocate(size);
		}
		static void operator delete(void* phead)
		{
			return myalloc.deallocate(phead);
		}
	};
	myallocator A::myalloc;   //定义静态成员变量

	void func()
	{
		A* mypa[100];
		for (int i = 0; i < 15; ++i)
		{
			mypa[i] = new A();
			printf("%p\n", mypa[i]);
		}
		for (int i = 0; i < 15; ++i)
		{
			delete mypa[i];
		}
	}
}
int main()
{
	//_nmpsl::func();
	_nmps2::func();
	return 0;
}