#include<iostream>
using namespace std;

namespace _nmspl
{
	//һ:�ֲ���̬����Ĺ��������
	//a)���������myfunc()��������ô�������ᴥ��A�Ĺ��캯��;
	//b)�ֲ���̬�����ڴ��ַ�����ڴ�����ڼ��ȷ���õģ�
	//c)��̬�ֲ����տ�ʼҲ����ʼ��Ϊ0��
	//d)�ֲ���̬���������������main����ִ�н�����ű����õġ�(ǰ���������̬�ֲ����󱻹����)

	//�ֲ���̬����ֻ�ᱻ����һ�Σ��ڵ��õ�ʱ���죻��main����ִ����Ϻ�����

	class A
	{
	public:
		A() {
			cout << "A::A()" << endl;
		}
		~A()
		{
			cout << "A::~A()" << endl;
		}
		int m_i;
	};

	void myfunc()
	{
		//�ֲ���̬����
		static A s_aobj1;  //ֻ�ᱻ����һ��
							//����myfunc()���������ü��Σ�s_aobj1���־�̬�ֲ�����ֻ�ᱻ����1��(ֻ����һ�ι��캯��)
		static A s_aobj2;
		printf("s_aobj1�ĵ�ַ��%p\n", &s_aobj1);
		printf("s_aobj2�ĵ�ַ��%p\n", &s_aobj2);
	}

	void func()
	{
		myfunc();
		myfunc();
	}
}
namespace _nmsp2 {
	//�����ֲ���̬����������ڴ����
	class A
	{
	public:
		A() {
			cout << "A::A()" << endl;
		}
		~A()
		{
			cout << "A::~A()" << endl;
		}
		int m_i;
	};

	void myfunc()
	{
		static A s_aobj[1000000];   //�����ڴ�Ӧ���������ģ�
									//���ڴ��㹻���ʱ�򣬱������ڲ������Ż���72
		for (int i = 0; i < 1000000; i++)   //�ñ������ķ����ڴ��Ż�����ʵЧ
		{
			s_aobj[i].m_i = i;    
		}
		printf("s_aobj������׵�ַ%p\n", s_aobj);
	}

	void func()
	{
		myfunc();
		myfunc();
	}
}
int main() {
	//_nmspl::func();
	_nmsp2::func();
	return 0;
}