#include<iostream>
#include<ctime>
using namespace std;

namespace _nmsp1
{
	//һ���ڴ�صĸ����ʵ��ԭ�����
	//malloc:�ڴ��˷ѣ�Ƶ������С���ڴ棬���˷Ѹ�������
	// "�ڴ��",Ҫ���ʲô����?
	//(1)����malloc�ĵ��ô���������malloc()���ô�������ζ�ż��ٶ��ڴ���˷�
	//(2)����malloc�ĵ��ô������Ƿ��ܹ���߳�������Ч��?  ����һЩ�ٶȺ�Ч���ϵ��������������������ԣ�

	//"�ڴ�ص�ʵ��ԭ��":
	//(1)��malloc���� һ����ڴ棬��Ҫ�����ʱ�򣬴������ڴ���һ��һ��ķ�����㣬��һ����ڴ����Ĳ���ʱ��
			//����malloc������һ����ڴ棬Ȼ����һ��һ��ķ�����㡣

	//�ڴ�����ã�
			//(1)�����ڴ��˷�
			//(2)�������Ч��


	void func()
	{

	}
}

namespace _nmsp2
{
//#define MYMEMPOOL
	//��:���һ������ڴ��ʵ����ʾ����
	//���һ������ڴ�� ��A
	//A *pa = new A();  delete pa;  ���ڴ�ص��ֶ�ʵ��new��deleteһ������

	//��:�ڴ�ش������˵��
	class A
	{
	public:
		static void* operator new(size_t size);
		static void operator delete(void* phead);
		static int m_iCout;//�������ͳ�ƣ�ÿnewһ�Σ���ͳ��һ��
		static int m_iMallocCout;   //ûmallocһ�Σ���ͳ��һ��
	private:
		A* next;
		static A* m_FreePosi;		//����ָ��һ����Է����ȥ���ڴ���׵�ַ
		static int m_sTrunkCout;	//һ�η�����ٱ��ĸ����ڴ�
	};

	int A::m_iCout = 0;
	int A::m_iMallocCout = 0;

	A* A::m_FreePosi = nullptr;
	int A::m_sTrunkCout = 5;  //һ�η���5���ĸ����ڴ���Ϊ�ڴ���ӵĴ�С��
	void* A::operator new(size_t size)
	{
#ifdef MYMEMPOOL
		A *ppoint = (A*)malloc(size);
		return ppoint;
#endif
		//�ڴ�صĺ���ʵ�ִ���
		A* tmplink;
			if (m_FreePosi == nullptr)
			{
				//Ϊ�գ�Ҫ�����ڴ棬Ҫ����һ����ڴ�
				size_t realsize = m_sTrunkCout * size;  //����m_sTrunkCout��ô�౶���ڴ�
				m_FreePosi = reinterpret_cast<A*>(new char[realsize]);  //��ͳnew�����õ��ǵײ��malloc
				tmplink = m_FreePosi;

				//�ѷ����������һ����ڴ�(5С��)�˴�Ҫ��������������ʹ��
				for (; tmplink != &m_FreePosi[m_sTrunkCout - 1]; ++tmplink)
				{
					tmplink->next = tmplink + 1;
				}
				tmplink->next = nullptr;
				++m_iMallocCout;
			}
			tmplink = m_FreePosi;
			m_FreePosi = m_FreePosi->next;
			++m_iCout;
			return tmplink;
	}

	void A::operator delete(void* phead)  //��û���������ͷ��ڴ棬�Ƿ�����ʹ���ڴ�
	{
#ifdef  MYMEMPOOL
		free (phead);
		return ;
#endif
		(static_cast<A*>(phead))->next = m_FreePosi;
		m_FreePosi = static_cast<A*>(phead); 
	}
	void func()
	{
		clock_t start, end;// ����ͷ�ļ� #include<ctime>
		start = clock();
		for (int i = 0; i < 15; i++)
		{
			A* pa = new A();
			//printf("%p\n", pa);
		}
		end = clock();
		cout << "��������ڴ�Ĵ���Ϊ:" << A::m_iCout << " ʵ��malloc�Ĵ���Ϊ: " << A::m_iMallocCout 
			<< " ��ʱ(����):" << end - start << endl;
	}
}
int main() {
	_nmsp2::func();
	return 0;
}