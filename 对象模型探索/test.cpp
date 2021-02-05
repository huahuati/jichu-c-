#include<iostream>
#include<string>
using namespace std;

class Myallocator
{
private:
	struct obj {
		struct obj* next;   //embedded pointer(Ƕ��ʽָ��)
	};
public:
	void* allocate(size_t);
	void deallocate(void*, size_t);
private:
	obj* freeStore = nullptr;
	const int CHUNK = 5;   //СһЩ�Ա�۲�
};

void Myallocator::deallocate(void* p, size_t)
{
	//��*p�ջز��� free list ǰ��
	((obj*)p)->next = freeStore;
	freeStore = (obj*)p;
}

void* Myallocator::allocate(size_t size)
{
	obj* p;

	if (!freeStore)
	{
		//linked listΪ�գ���������һ���
		size_t chunk = CHUNK * size;
		freeStore = p = (obj*)malloc(chunk);

		//��ԭ�����������һ��鵱��linkedlist �㣬С��С���ƴ������
		for (int i = 0; i < (CHUNK - 1); ++i)
		{
			p->next = (obj*)((char*)p + size);
			p = p->next;
		}
		p->next = nullptr;  //last
	}
	p = freeStore;
	freeStore = freeStore->next;
	return p;
}

class Foo
{
public:
	long L;
	string str;
	static Myallocator MyAlloc;
public:
	Foo(long l):L(l){}
	static void *operator new(size_t size)
	{
		return MyAlloc.allocate(size);
	}
	static void operator delete(void* pdead, size_t size)
	{
		return MyAlloc.deallocate(pdead, size);
	}
};
Myallocator Foo::MyAlloc;

int main()
{
	Foo* p[100];
	cout << "sizeof(Foo)= " << sizeof(Foo) << endl;
	for (int i = 0; i < 23; ++i)
	{
		p[i] = new Foo(i);
		cout << p[i] << " " << p[i]->L << endl;
	}
	for (int i = 0; i < 23; ++i)
		delete p[i];
	return 0;
}