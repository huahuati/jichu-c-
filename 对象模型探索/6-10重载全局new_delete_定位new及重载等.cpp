#include<iostream>
using namespace std;

void *operator new(size_t size)
{
	return malloc(size);
}
void* operator new[](size_t size)  //����汾
{
	return malloc(size);
}

void operator delete(void* phead)
{
	free(phead);
}
void operator delete[](void* phead)
{
	free(phead);
}
namespace _nmspl
{
	//һ:����ȫ��operator new ��operator delete����
			//����ȫ��operator new[] ��operator delete[]����
	class A {

	public:
		A(){
			cout << "A::A()" << endl;
		}
		~A()
		{
			cout << "A::~A()" << endl;
		}
};

	void func()
	{
		int* pint = new int(12);
		delete pint;

		char* parr = new char[10];
		delete[] parr;

		A* pa = new A[3]();
		delete[] pa;

	}
}

namespace _nmsp2
{
	//��λnew(placement new)
	//��placement new������û��placement delete
	//����:���Ѿ������ԭʼ�ڴ��г�ʼ��һ������
	//a)�Ѿ����䣬��λnew���������ڴ棬��Ҫ��ǰ�������λnewҪ���õ��ڴ���������
	//b)��ʼ��һ������(��ʼ��һ��������ڴ�)�����Ǿ����ɵ����������Ĺ��캯��
	//��λnew�����ܹ���һ��Ԥ�ȷ���õ��ڴ��ַ�й���һ������
	//��ʽ��
	//new(��ַ)������()

	class A
	{
	public:
		int m_a;
		A() :m_a(0)
		{
			int test;
			test = 1;
		}
		A(int tempvalue) : m_a(tempvalue)
		{
			int test;

		}
		~A() {
			int abc;
			abc = 1;
		}
		//��ͳnew 
		void* operator new(size_t size)
		{
			A* ppoint = (A*)malloc(size);
			return ppoint;
		}
		//��λnew����������
		void* operator new(size_t size, void* phead)
		{
			return phead; //�յ��ڴ濪ʼ��ַ��ֻ��Ҫԭ·����
		}
	};
	void func()
	{
		void* mymenPoint = (void*) new char[sizeof(A)]; //�ڴ�������ȷ������
		A* pmyAobj1 = new (mymenPoint)A();  //�����޲ι��캯�������ﲢ�����������ڴ�

		void* mymenPoint2 = (void*) new char[sizeof(A)];
		A* pmyAobj2 = new (mymenPoint2)A(12); //���ô�һ�������Ĺ��캯�������ﲢ�����������ڴ�

		//delete pmyAobj1;
		//delete pmyAobj2;   //Ҳ���ͷ�

		pmyAobj1->~A();   //�ֹ��������������ǿ��Եģ����ֹ����ù��캯���ǲ����Եġ�
		pmyAobj2->~A();   //������������

		delete[](void*)pmyAobj1;
		delete[](void*)pmyAobj2;
	}
}

namespace _nmsp3
{
	//�������ְ汾��operator new ����
	//�������غܶ�汾��operator new,ֻҪÿ���汾������ͬ���У����ǵ�һ�������ǹ̶��ģ�����size_t;��ʾ��Ҫnew�����sizeofֵ
	class A
	{
	public:
		void* operator new(size_t size, int tvp1, int tvp2)
		{
			return nullptr;
		}
		A()
		{
			int test;
			test = 1;
		}
	};
	void func()
	{
		A* pa = new(1234, 56) A();  //�Զ���newû�е��ù��캯��
	}
}
int main() {

	//_nmspl::func();
	//_nmsp2::func();
	_nmsp3::func();
	return 0;
}