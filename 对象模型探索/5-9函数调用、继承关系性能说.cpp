#include<iostream>
#include<ctime>
using namespace std;

namespace _nmspl  //�����ռ�
{
	//һ:���������б�������ѭ�������Ż�
	//debug,release
	//(1)ѭ���Ż�����ѭ���Ż���1����䣻
	//(2)�ڱ����ڼ䣬������Ҳ����������������Щ����������ڱ����ڼ���ܸ㶨
	__int64 mytest(int mv)
	{
		int i = 0;
		__int64 icout = 0;
		for (int i = 1; i < 1000000; i++)
		{
			icout += 1;

		}
		return icout;
	}
	void func()
	{
		clock_t start, end;
		__int64 mycout = 1;
		start = clock();
		for (int i = 0; i <= 1000; i++)
		{
			//mycout += mytest(6);  //�����е�ʱ����������Ż�,
										//���̶�����ʱ�������������ֲ����̶��ĺ���������Ϊһ�ֲ���ı��ʽ��
			//mycout += mytest(i); 
			mycout += mytest(6);
		}
		end = clock();
		cout << "��ʱ(����): " << end - start << endl;
		cout << "mycout = " << mycout << endl;
	}
}

namespace _nmsp2
{

	//�����̳й�ϵ������ӣ�����һ��Ҳ����
	//�ܶ�����£����ż̳���ȵ����ӣ���������ִ��ʱ��Ҳ�����ӣ�
	//(2.1)���ؼ̳�һ��Ҳ�ᵼ�¿�������
	class A
	{
	public:
		A()
		{
			cout << "A::A()" << endl;
		}
	};
	class A1
	{
	public:
		A1()
		{
			cout << "A1::A()1" << endl;
		}
	};
	class B :public A,public A1
	{
	public:
	};
	class C : public B
	{
	public:
		C()
		{
			cout << "C::C()" << endl;
		}
	};
	void func()
	{
		C cobj;

	}
}

namespace _nmsp3
{
	//�����̳й�ϵ������ӣ��麯�����µĿ�������
	class A
	{
	public:
		A()
		{
			cout << "A::A()" << endl;
		}
		virtual void myvirfunc() {}
	};

	class B :public A
	{
	public:
	};
	class C : public B
	{
	public:
		C()
		{
			cout << "C::C()" << endl;
		}
	};
	void func()
	{
		C* pc = new C();
	}
}
int main() {
	//_nmspl::func();
	_nmsp2::func();
	return 0;
}