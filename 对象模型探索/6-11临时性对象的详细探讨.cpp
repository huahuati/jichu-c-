#include<iostream>
#include<string>
using namespace std;

namespace _nmspl
{
	//�������캯����ص���ʱ�Զ���
	class A
	{
	public:
		A()
		{
			cout << "A::A()���캯����ִ��" << endl;
		}
		A(const A& tmpobj)
		{
			cout << "A::A()�������캯����ִ��" << endl;

		}
		~A()
		{
			cout << "A::~A()����������ִ��" << endl;

		}
	};

	A operator + (const A& obj1, const A& obj2)
	{
		A tmpobj;

		return tmpobj;  //������������ʱ���󣬰�tmpobj���������ͨ�����ÿ������캯������tempobj�����ݿ����������ʱ����
								//Ȼ�󷵻ص��������ʱ����
	}
	void func()
	{
		A myboj1;
		A myboj2;
		A reusltobj = myboj1 + myboj2;  //��operator +�ﷵ�ص���ʱ����ֱ�ӹ��쵽��resultobj �

		return;
	}
}
namespace _nmsp2
{
	//����������ֵ�������ص���ʱ�Զ���
	class A
	{
	public:
		A()
		{
			cout << "A::A()���캯����ִ��" << endl;
		}
		A(const A& tmpobj)
		{
			cout << "A::A()�������캯����ִ��" << endl;

		}
		A& operator = (const A& tmpaobj)
		{
			cout << "A::operaotr()������ֵ�������ִ��" << endl;
			return *this;
		}
		~A()
		{
			cout << "A::~A()����������ִ��" << endl;

		}
	};
	A operator + (const A& obj1, const A& obj2)
	{
		A tmpobj;

		return tmpobj;  //������������ʱ���󣬰�tmpobj���������ͨ�����ÿ������캯������tempobj�����ݿ����������ʱ����
								//Ȼ�󷵻ص��������ʱ����
	}
		void func()
		{
			A myboj1;
			A myboj2;
			A reusltobj;
			reusltobj = myboj1 + myboj2;  //������ֵ�����

			return;
		}
}

namespace _nmsp3
{
	//����ֱ�Ӷ��������ʱ��������
	//(3.1)��ʱ���󱻴ݻ�
	//(3.2)��ʱ������󶨶�������
	class A
	{
	public:
		A()
		{
			cout << "A::A()���캯����ִ��" << endl;
		}
		A(const A& tmpobj)
		{
			cout << "A::A()�������캯����ִ��" << endl;

		}
		A& operator = (const A& tmpaobj)
		{
			cout << "A::operaotr()������ֵ�������ִ��" << endl;
			return *this;
		}
		~A()
		{
			cout << "A::~A()����������ִ��" << endl;

		}
		int m_i;
	};
	A operator + (const A& obj1, const A& obj2)
	{
		A tmpobj;
		tmpobj.m_i = obj1.m_i + obj2.m_i;
		return tmpobj;
	}
	void func()
	{
		A myobj1;
		myobj1.m_i = 1;
		A myobj2;
		myobj2.m_i = 2;


		//A tmpobjal = (myobj1 +myobj2);  ����������Ҫ�ĵط����������ǲ�����룬��������ʱ���󹩱�����������ǳ��򿪷��ߴ�
					//Ҫʵ�ֵ���ͼ
		printf("(myboj1 + myobj2).m_i = %d\n", (myobj1 + myobj2).m_i);
		//myobj1 + myobj2;   //��������ʱ����Ȼ�����ʱ���������������ˡ�

	
		cout << "�ֽ��� ----��ʱ���󱻴ݻ�-----" << endl;
		const char* p = (string("123") + string("456")).c_str();//��һ�������⣬��Ϊ��ʱ����������оͱ��ݻ�
		string aaa = (string("123") + string("345"));
		const char * q = aaa.c_str();   //���Ӧ��ok

		printf("p = %s\n", p);
		printf("q = %s\n", q);

		cout << "�ֽ��� ----��ʱ���󱻱���-----" << endl;
		const string& aaa =string("123") + string("456");
		printf("aaa = %s\n", aaa.c_str());
		return;
	}
}
int main()
{
	//_nmspl::func();
	//_nmsp2::func();
	_nmsp3::func();
	return 0;
}