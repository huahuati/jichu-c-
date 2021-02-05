#include<iostream>
using namespace std;

namespace _nmpsl
{
	//һ:Ƕ��ʽָ��
	//(1.1)
	//һ���������ڴ����صĴ����У�  �ɹ�ʹ��Ƕ��ʽָ���и�ǰ������:��A�����sizeof���벻С��4�ֽ�
	//Ƕ��ʽָ�빤��ԭ��:����A������ռ�õ��ڴ�ռ��е�ǰ4���ֽڣ�����4���ֽ�����ס��Щ���е��ڴ�顣
		//����һ��ĳһ���鱻�����ȥ����ô������ǰ4���ֽھͲ�����Ҫ����ʱ��4���ֽڿ��Ա�����ʹ��
	//(1.2)Ƕ��ʽָ����ʾ����
	//sizeof()����4�ֽڵ���Ϳ��԰�ȫ��ʹ��Ƕ��ʽָ�롣
	class TestEp
	{
	public:
		int m_i;
		int m_j;
	public:
		struct obj  //�ṹ��,��������������涼��һ����
		{
			//��Ա���Ǹ�ָ��
			struct obj* next;   //���next���Ǹ�Ƕ��ʽָ��
						//�Լ���һ��obj�ṹ������ô���Լ���������nextָ��ָ������һ��obj�ṹ��������
								//�Ѷ���Լ��������͵Ķ���ͨ������������
		};
	};
	void func()
	{
		TestEp mytset;
		cout << sizeof(mytset) << endl;  //8
		TestEp::obj *ptemp;   //����һ��ָ��
		ptemp = (TestEp::obj *) & mytset;  //�Ѷ���mytest�׵�ַ�������ָ��ptemp,���ָ��ptempָ�����mytest�׵�ַ��
		cout << sizeof(ptemp->next) << endl;  //4
		cout << sizeof(TestEp::obj) << endl;  //4
		ptemp->next = nullptr;       //ptmep->next ��ptempָ����ڴ���ͬ
	}

}
namespace _nmps2
{

	//�����ڴ�ش���ĸĽ�
	//������Ϊ�ڴ�ؼ�����дһ����

	class myallocator
	{
	public:
		//�����ڴ�ӿ�
		void* allocate(size_t size)
		{
			obj* tmplink;
			if (m_FreePosi == nullptr)
			{
				//Ϊ�գ�Ҫ�����ڴ棬Ҫ����һ����ڴ�
				size_t realsize = m_sTrunkCout * size;   //����m_sTrunkCout��ô�౶���ڴ�
				m_FreePosi = (obj*)malloc(realsize);
				tmplink = m_FreePosi;

				//�ѷ����������һ����ڴ�(5С��)���˴�������������������ʹ��
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
		//д�����ڵĽṹ������֮����������ʹ��
		struct obj
		{
			struct obj* next; // ���next���Ǹ�Ƕ��ʽָ��
		};
		int m_sTrunkCout = 5; //һ�η���5�������ڴ���Ϊ�ڴ���ӵĴ�С
		obj* m_FreePosi = nullptr;
	};



	class A
	{
	public:
		int m_i;
		int m_j;   //Ϊ�˱�֤sizeof(A)�չ����ֽڣ�
	public:
		static myallocator myalloc;   //��̬��Ա����
		static void* operator new(size_t size)
		{
			return myalloc.allocate(size);
		}
		static void operator delete(void* phead)
		{
			return myalloc.deallocate(phead);
		}
	};
	myallocator A::myalloc;   //���徲̬��Ա����

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