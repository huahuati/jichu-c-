#include<iostream>
using namespace std;

namespace _nmspl
{

	//һ:new�ڴ����ϸ��̽��
	//ע�⵽��һ���ڴ�Ļ��գ�Ӱ�췶Χ�ܹ㣬ԶԶ����10���ֽڣ�����һ��Ƭ��
	//�����ڴ������    int* ppointint = new int(10);
			//�����Ǽ򵥵ķ����ȥ4���ֽڣ���������4���ֽ���Χ�����������˺ܶദ�������¼�����ȥ���ֽ����ȵȡ�
	//�����ڴ�ʱ��Ϊ�˼�¼�͹�������ȥ���ڴ棬���������˲����ڴ棬������˷ѣ�������Ƶ��������С���ڴ��ǣ���ɵ��˷Ѹ����ԡ�



	//new��delete(malloc,free)�ڴ�û�п���ȥ��ô�򵥣����ǵĹ����ڲ��Ǻܸ��ӵġ�


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

	//��:�������е�operator new �� operator delete������
	//A* pa = new A();
	//�������ӽ�
		//void* temp = operator new(sizeof(A));
		//A * pa = static_cast<A*>(temp);
		//pa->A::A()
	
	//delete pa;
	//�������ӽ�
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

		//A* pa = ::new A();  ::ȫ�ֲ�����  ������ȫ�ֵ�new��delete
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
	{								//size��7���ֽڣ�����Ϊ����4���ֽ��Ǽ�¼���� A* pa = new A[3]() �е� 3����Ĵ�С
		A* ppoint = (A*)malloc(size);
		return ppoint;
	}

	void A::operator delete[](void* phead) {
		free(phead);
	}
	void func()
	{
		A* pa = new A[3]();   //�������������������3�Σ�����operator new[] ��operator delete[]����������һ��
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